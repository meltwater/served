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

connection::connection( boost::asio::ip::tcp::socket socket
                      , connection_manager &         manager
                      , multiplexer        &         handler )
	: d_status(status_type::READING)
	, d_socket(std::move(socket))
	, d_connection_manager(manager)
	, d_request_handler(handler)
	, d_request()
	, d_request_parser(d_request)
{}

void
connection::start()
{
	do_read();
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
				request_parser::status result;
				std::tie(result, std::ignore) = d_request_parser.parse(d_buffer.data(), bytes_transferred);

				// Expect type informs us of any "Expect" headers received from the client
				auto expect_type = d_request_parser.get_expected();

				if ( result == request_parser::status::FINISHED )
				{
					if ( request_parser_impl::expect_type::NONE == expect_type )
					{
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

						do_write();

						try
						{
							d_request_handler.on_request_handled(d_response, d_request);
						}
						catch (...)
						{
						}
					}
					else if ( request_parser_impl::expect_type::CONTINUE == expect_type )
					{
						/* If the client is expecting a 100-continue then serve it, and ensure we read
						 * back from the client afterwards by leaving our d_status to READING.
						 */
						response::stock_reply(served::status_1XX::CONTINUE, d_response);
						d_request_parser.set_expected(request_parser_impl::expect_type::NONE);
						do_write();
					}
				}
				else if ( result == request_parser::ERROR )
				{
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
