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
	enum status_type { READING = 0, DONE };

private:
	status_type                  d_status;
	boost::asio::ip::tcp::socket d_socket;
	connection_manager &         d_connection_manager;
	multiplexer        &         d_request_handler;
	std::array<char, 8192>       d_buffer;
	request                      d_request;
	request_parser_impl          d_request_parser;
	response                     d_response;

public:
	connection(const connection&) = delete;

	connection& operator=(const connection&) = delete;

	/*
	 * Constructs a new connection.
	 *
	 * @param socket the boost::asio socket for the connection
	 * @param manager the connection manager that oversees this connection
	 * @param handler the multiplexer responsible for routing requests
	 */
	explicit connection( boost::asio::ip::tcp::socket socket
	                   , connection_manager &         manager
	                   , multiplexer        &         handler );

	/*
	 * Prompts the connection to start reading from its TCP socket.
	 */
	void start();

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
};

typedef std::shared_ptr<connection> connection_ptr;

} } // net, served

#endif // SERVED_CONNECTION_HPP
