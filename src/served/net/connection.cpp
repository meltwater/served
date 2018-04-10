/*
 * Copyright (C) 2014 MediaSift Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <served/status.hpp>
#include <served/net/connection.hpp>
#include <served/net/connection_manager.hpp>
#include <served/request_error.hpp>

#include <utility>
#include <vector>

using namespace served;
using namespace served::net;

connection::connection( boost::asio::io_service &    io_service
                      , boost::asio::ip::tcp::socket socket
                      , connection_manager &         manager
                      , multiplexer        &         handler
                      , size_t                       max_req_size_bytes
                      , int                          read_timeout
                      , int                          write_timeout
                      )
	: _io_service(io_service)
	, _status(status_type::READING)
	, _socket(std::move(socket))
	, _connection_manager(manager)
	, _request_handler(handler)
	, _max_req_size_bytes(max_req_size_bytes)
	, _read_timeout(read_timeout)
	, _write_timeout(write_timeout)
	, _request()
	, _request_parser(_request, _max_req_size_bytes)
	, _read_timer(_io_service, boost::posix_time::milliseconds(read_timeout))
	, _write_timer(_io_service, boost::posix_time::milliseconds(write_timeout))
{}

void
connection::start()
{
	boost::system::error_code ec;
	boost::asio::ip::tcp::endpoint endpoint = _socket.remote_endpoint(ec);
	if (ec)
	{
		_connection_manager.stop(shared_from_this());
		return;
	}

	_request.set_source(endpoint.address().to_string());
	do_read();

	if ( _read_timeout > 0 )
	{
		auto self(shared_from_this());

		_read_timer.async_wait([this, self](const boost::system::error_code& error) {
			if ( error.value() != boost::system::errc::operation_canceled )
			{
				_connection_manager.stop(shared_from_this());
			}
		});
	}
}

void
connection::stop()
{
	_socket.close();
}

void
connection::do_read()
{
	auto self(shared_from_this());

	_socket.async_read_some(boost::asio::buffer(_buffer.data(), _buffer.size()),
		[this, self](boost::system::error_code ec, std::size_t bytes_transferred) {
			if (!ec)
			{
				request_parser_impl::status_type result;
				result = _request_parser.parse(_buffer.data(), bytes_transferred);

				if ( request_parser_impl::FINISHED == result )
				{
					// Parsing is finished, stop reading and send response.

					_read_timer.cancel();
					_status = status_type::DONE;

					try
					{
						_request_handler.forward_to_handler(_response, _request);
					}
					catch (const served::request_error & e)
					{
						_response.set_status(e.get_status_code());
						_response.set_header("Content-Type", e.get_content_type());
						_response.set_body(e.what());
					}
					catch (...)
					{
						response::stock_reply(status_5XX::INTERNAL_SERVER_ERROR, _response);
					}

					if ( _write_timeout > 0 )
					{
						_write_timer.async_wait([this, self](const boost::system::error_code& error) {
							if ( error.value() != boost::system::errc::operation_canceled )
							{
								_connection_manager.stop(shared_from_this());
							}
						});
					}
					do_write();

					try
					{
						_request_handler.on_request_handled(_response, _request);
					}
					catch (...)
					{
					}
				}
				else if ( request_parser_impl::EXPECT_CONTINUE == result )
				{
					// The client is expecting a 100-continue, so we serve it and continue reading.

					response::stock_reply(served::status_1XX::CONTINUE, _response);
					do_write();
				}
				else if ( request_parser_impl::READ_HEADER == result
				       || request_parser_impl::READ_BODY   == result )
				{
					// Not finished reading response, continue.

					do_read();
				}
				else if ( request_parser_impl::REJECTED_REQUEST_SIZE == result )
				{
					// The request is too large and has been rejected

					_status = status_type::DONE;

					response::stock_reply(served::status_4XX::REQ_ENTITY_TOO_LARGE, _response);
					do_write();
				}
				else if ( request_parser_impl::ERROR == result )
				{
					// Error occurred while parsing, respond with BAD_REQUEST

					_status = status_type::DONE;

					response::stock_reply(served::status_4XX::BAD_REQUEST, _response);
					do_write();
				}
			}
			else if (ec != boost::asio::error::operation_aborted)
			{
				_connection_manager.stop(shared_from_this());
			}
		}
	);
}

void
connection::do_write()
{
	auto self(shared_from_this());

	boost::asio::async_write(_socket, boost::asio::buffer(_response.to_buffer()),
		[this, self](boost::system::error_code ec, std::size_t) {
			if ( !ec )
			{
				if ( status_type::READING == _status )
				{
					// If we're still reading from the client then continue
					do_read();
					return;
				}
				else
				{
					// Initiate graceful connection closure.
					boost::system::error_code ignored_ec;
					_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
				}
			}

			if ( ec != boost::asio::error::operation_aborted )
			{
				_connection_manager.stop(shared_from_this());
			}
		}
	);
}
