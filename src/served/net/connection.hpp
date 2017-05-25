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

#ifndef SERVED_CONNECTION_HPP
#define SERVED_CONNECTION_HPP

#include <boost/asio.hpp>

#include <served/multiplexer.hpp>
#include <served/response.hpp>
#include <served/request.hpp>
#include <served/request_parser_impl.hpp>

#include <array>
#include <memory>
#include <tbb/task_group.h>

namespace served { namespace net {

class connection_manager;

/*
 * Manages the lifecycle of a single HTTP connection.
 *
 * A connection is created by the server each time a new client connects.
 */
class connection
	: public std::enable_shared_from_this<connection>
{
public:
	enum status_type { READING = 0, PROCESSING, WRITING, DONE };

private:
	boost::asio::io_service &    _io_service;
	status_type                  _status;
	boost::asio::ip::tcp::socket _socket;
	connection_manager &         _connection_manager;
	multiplexer        &         _request_handler;
	std::array<char, 8192>       _buffer;
	size_t                       _max_req_size_bytes;
	int                          _read_timeout;
	int                          _write_timeout;
	request                      _request;
	request_parser_impl          _request_parser;
	response                     _response;
	boost::asio::deadline_timer  _read_timer;
	boost::asio::deadline_timer  _write_timer;
	tbb::task_group & 		 	 m_tg;
public:
	connection& operator=(const connection&) = delete;
	connection() = delete;
	connection(const connection&) = delete;

	/*
	 * Constructs a new connection.
	 *
	 * @param io_service the boost::asio::io_service for managing async operations
	 * @param socket the boost::asio socket for the connection
	 * @param manager the connection manager that oversees this connection
	 * @param handler the multiplexer responsible for routing requests
	 * @param max_request_size_bytes maximum permitted size of a request
	 * @param read_timer the timeout for reading, 0 is ignored
	 * @param write_timer the timeout for writing, 0 is ignored
	 */
	explicit connection( boost::asio::io_service &    io_service
	                   , boost::asio::ip::tcp::socket socket
	                   , connection_manager &         manager
	                   , multiplexer        &         handler
	                   , size_t                       max_request_size_bytes
	                   , int                          read_timeout
	                   , int                          write_timeout 
	                   , tbb::task_group    &		  tg);

	/*
	 * Prompts the connection to start reading from its TCP socket.
	 */
	void start();

	void restart();

	/*
	 * Prompts the connection to close the TCP connection early.
	 */
	void stop();

private:
	/*
	 * An asynchronous call that triggers a TCP read from the socket.
	 */
	void do_read();

	/*
	 * An asynchronous call that triggers a TCP write to the socket.
	 */
	void do_write();

	void do_write_1();
};

typedef std::shared_ptr<connection> connection_ptr;

} } // net, served

#endif // SERVED_CONNECTION_HPP
