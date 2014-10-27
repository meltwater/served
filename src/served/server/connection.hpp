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

namespace served { namespace server {

class connection_manager;

class connection
	: public std::enable_shared_from_this<connection>
{
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

	explicit connection( boost::asio::ip::tcp::socket socket
	                   , connection_manager &         manager
	                   , multiplexer        &         handler );

	void start();
	void stop();

private:
	void do_read();
	void do_write();
};

typedef std::shared_ptr<connection> connection_ptr;

} } // server, served

#endif // SERVED_CONNECTION_HPP
