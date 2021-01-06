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


void stop_on_timeout(const boost::system::error_code& error, const connection_ptr & self){
    if ( error.value() != boost::system::errc::operation_canceled )
    {
        self->_connection_manager.stop(self);
    }
}


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
    connection_ptr self(shared_from_this());

    boost::system::error_code ec;
	boost::asio::ip::tcp::endpoint endpoint = _socket.remote_endpoint(ec);

	if (ec)
	{
        _connection_manager.stop(self);
		return;
	}

	_request.set_source(endpoint.address().to_string());
	do_read();

	if ( _read_timeout > 0 )
	{

        _read_timer.async_wait([self](const boost::system::error_code& error) {
            stop_on_timeout(error, self);
		});
	}
}

void
connection::stop()
{
    // use a lock here to avoid any race condition on timeout
    std::lock_guard _l(_conn_mutex);

    if(_status != status_type::STOPPED){

        _status = status_type::STOPPED;
        try{
            _socket.close();
        }catch(std::exception & e){
            std::cerr << "Error in connection::stop() " << e.what() << std::endl;
        }
    }

}

void
connection::do_read()
{
	connection_ptr self(shared_from_this());

	_socket.async_read_some(boost::asio::buffer(_buffer.data(), _buffer.size()),
        [self](boost::system::error_code ec, std::size_t bytes_transferred) {
			if (!ec)
			{
                std::lock_guard _l(self->_conn_mutex);
				request_parser_impl::status_type result;
                result = self->_request_parser.parse(self->_buffer.data(), bytes_transferred);

				if ( request_parser_impl::FINISHED == result )
				{
					// Parsing is finished, stop reading and send response.

                    self->_read_timer.cancel();
                    self->_status = status_type::DONE;

					try
					{
                        self->_request_handler.forward_to_handler(self->_response, self->_request);
					}
					catch (const served::request_error & e)
					{
                        self->_response.set_status(e.get_status_code());
                        self->_response.set_header("Content-Type", e.get_content_type());
                        self->_response.set_body(e.what());
					}
					catch (...)
					{
                        response::stock_reply(status_5XX::INTERNAL_SERVER_ERROR, self->_response);
					}

                    if ( self->_write_timeout > 0 )
					{
                        self->_write_timer.async_wait([self](const boost::system::error_code& error) {
                            stop_on_timeout(error, self);
						});
					}
                    self->do_write();

					try
					{
                        self->_request_handler.on_request_handled(self->_response, self->_request);
					}
					catch (...)
					{
					}
				}
				else if ( request_parser_impl::EXPECT_CONTINUE == result )
				{
					// The client is expecting a 100-continue, so we serve it and continue reading.

                    response::stock_reply(served::status_1XX::CONTINUE, self->_response);
                    self->do_write();
				}
				else if ( request_parser_impl::READ_HEADER == result
				       || request_parser_impl::READ_BODY   == result )
				{
					// Not finished reading response, continue.

                    self->do_read();
				}
				else if ( request_parser_impl::REJECTED_REQUEST_SIZE == result )
				{
					// The request is too large and has been rejected

                    self->_status = status_type::DONE;

                    response::stock_reply(served::status_4XX::REQ_ENTITY_TOO_LARGE, self->_response);
                    self->do_write();
				}
				else if ( request_parser_impl::ERROR == result )
				{
					// Error occurred while parsing, respond with BAD_REQUEST

                    self->_status = status_type::DONE;

                    response::stock_reply(served::status_4XX::BAD_REQUEST, self->_response);
                    self->do_write();
				}
			}
			else if (ec != boost::asio::error::operation_aborted)
			{
                self->_connection_manager.stop(self);
			}
		}
	);
}

void
connection::do_write()
{
	connection_ptr self(shared_from_this());

	boost::asio::async_write(_socket, boost::asio::buffer(_response.to_buffer()),
        [self](boost::system::error_code ec, std::size_t) {
			if ( !ec )
			{
                std::lock_guard _l(self->_conn_mutex);
                if ( status_type::READING == self->_status )
				{
					// If we're still reading from the client then continue
                    self->do_read();
					return;
				}
                else if(status_type::DONE == self->_status )
				{
					// Initiate graceful connection closure.
					boost::system::error_code ignored_ec;
                    self->_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
				}
			}

			if ( ec != boost::asio::error::operation_aborted )
			{
                self->_connection_manager.stop(self);
			}
		}
	);
}
