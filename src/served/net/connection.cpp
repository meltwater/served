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

using namespace served::net;

connection::connection( boost::asio::io_service &    io_service
                      , boost::asio::ip::tcp::socket socket
                      , connection_manager &         manager
                      , multiplexer        &         handler
                      , size_t                       max_header_size_bytes
                      , size_t                       max_body_size_bytes
                      , int                          read_timeout
                      , int                          write_timeout
                      )
	: d_io_service(io_service)
	, d_status(status_type::READING)
	, d_socket(std::move(socket))
	, d_connection_manager(manager)
	, d_request_handler(handler)
	, d_request()
	, d_request_parser(d_request, max_header_size_bytes, max_body_size_bytes)
	, d_read_timeout(read_timeout)
	, d_write_timeout(write_timeout)
	, d_read_timer(d_io_service, boost::posix_time::milliseconds(read_timeout))
	, d_write_timer(d_io_service, boost::posix_time::milliseconds(write_timeout))
{}

void
connection::start()
{
	do_read();

	if ( d_read_timeout > 0 )
	{
		auto self(shared_from_this());

		d_read_timer.async_wait([this, self](const boost::system::error_code& error) {
			if ( error.value() != boost::system::errc::operation_canceled )
			{
				d_connection_manager.stop(shared_from_this());
			}
		});
	}
}

void
connection::stop()
{
	d_socket.close();
}

void
connection::do_read()
{
	auto self(shared_from_this());

	d_socket.async_read_some(boost::asio::buffer(d_buffer.data(), d_buffer.size()),
		[this, self](boost::system::error_code ec, std::size_t bytes_transferred) {
			if (!ec)
			{
				request_parser_impl::status_type result;
				result = d_request_parser.parse(d_buffer.data(), bytes_transferred);

				if ( request_parser_impl::FINISHED == result )
				{
					// Parsing is finished, stop reading and send response.

					d_read_timer.cancel();
					d_status = status_type::DONE;

					try
					{
						d_request_handler.forward_to_handler(d_response, d_request);
					}
					catch (const served::request_error & e)
					{
						d_response.set_status(e.get_status_code());
						d_response.set_body(e.what());
					}
					catch (...)
					{
						response::stock_reply(status_5XX::INTERNAL_SERVER_ERROR, d_response);
					}

					if ( d_write_timeout > 0 )
					{
						d_write_timer.async_wait([this, self](const boost::system::error_code& error) {
							if ( error.value() != boost::system::errc::operation_canceled )
							{
								d_connection_manager.stop(shared_from_this());
							}
						});
					}
					do_write();

					try
					{
						d_request_handler.on_request_handled(d_response, d_request);
					}
					catch (...)
					{
					}
				}
				else if ( request_parser_impl::EXPECT_CONTINUE == result )
				{
					// The client is expecting a 100-continue, so we serve it and continue reading.

					response::stock_reply(served::status_1XX::CONTINUE, d_response);
					do_write();
				}
				else if ( request_parser_impl::READ_HEADER == result
				       || request_parser_impl::READ_BODY   == result )
				{
					// Not finished reading response, continue.

					do_read();
				}
				else if ( request_parser_impl::REJECTED_HEADER_SIZE == result )
				{
					// The header is too large and has been rejected

					d_status = status_type::DONE;

					response::stock_reply(served::status_4XX::REQ_HEADER_FIELDS_TOO_LARGE, d_response);
					do_write();
				}
				else if ( request_parser_impl::REJECTED_BODY_SIZE == result )
				{
					// The body is too large and has been rejected

					d_status = status_type::DONE;

					response::stock_reply(served::status_4XX::REQ_ENTITY_TOO_LARGE, d_response);
					do_write();
				}
				else if ( request_parser_impl::ERROR == result )
				{
					// Error occurred while parsing, respond with BAD_REQUEST

					d_status = status_type::DONE;

					response::stock_reply(served::status_4XX::BAD_REQUEST, d_response);
					do_write();
				}
			}
			else if (ec != boost::asio::error::operation_aborted)
			{
				d_connection_manager.stop(shared_from_this());
			}
		}
	);
}

void
connection::do_write()
{
	auto self(shared_from_this());

	boost::asio::async_write(d_socket, boost::asio::buffer(d_response.to_buffer()),
		[this, self](boost::system::error_code ec, std::size_t) {
			if ( !ec )
			{
				if ( status_type::READING == d_status )
				{
					// If we're still reading from the client then continue
					do_read();
				}
				else
				{
					// Otherwise we initiate graceful connection closure.

					d_write_timer.cancel();

					boost::system::error_code ignored_ec;
					d_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
						ignored_ec);
					d_connection_manager.stop(shared_from_this());
				}
			}
			else if ( ec != boost::asio::error::operation_aborted )
			{
				d_connection_manager.stop(shared_from_this());
			}
		}
	);
}
