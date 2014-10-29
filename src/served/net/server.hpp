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

#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include <string>
#include <served/net/connection_manager.hpp>
#include <served/multiplexer.hpp>

namespace served { namespace net {

class server
{
	boost::asio::io_service        d_io_service;
	boost::asio::signal_set        d_signals;
	boost::asio::ip::tcp::acceptor d_acceptor;
	connection_manager             d_connection_manager;
	boost::asio::ip::tcp::socket   d_socket;
	multiplexer &                  d_request_handler;

public:
	server(const server&) = delete;
	server& operator=(const server&) = delete;

	explicit server( const std::string & address
	               , const std::string & port
	               , multiplexer       & mux     );

	void run(int n_threads = 1);
	void stop();

private:
	void do_accept();

	void do_await_stop();
};

} } // net, served

#endif // SERVER_HPP
