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

/*
 * Listens for new TCP connections, and distributes them across a pool of threads.
 *
 * The server is given an address and a port to bind to, and a multiplexer to use for forwarding
 * HTTP requests to handlers.
 *
 * When run is called the server will begin to accept and respond to incoming HTTP requests.
 */
class server
{
	boost::asio::io_service        _io_service;
	boost::asio::signal_set        _signals;
	boost::asio::ip::tcp::acceptor _acceptor;
    boost::asio::ip::tcp::socket   _socket;
    connection_manager             _connection_manager;
    multiplexer &                  _request_handler;
	int                            _read_timeout;
	int                            _write_timeout;
	size_t                         _req_max_bytes;
	std::vector<std::thread>	   _threads;

public:
	server(const server&) = delete;
	~server();

	server& operator=(const server&) = delete;

	/*
	 * Constructs a new server.
	 *
	 * @param address the address to bind to for incoming connections
	 * @param port the port to bind to for incoming connections
	 * @param mux the multiplexer to be used for forwarding requests to handlers
	 * @param register_signals specifies whether POSIX signals are captured or not
	 * @param read_timeout optional parameter that specifies a timeout for reading
	 * @param write_timeout optional parameter that specifies a timeout for writing
	 */
	explicit server( const std::string & address
	               , const std::string & port
	               , multiplexer       & mux
	               , bool              register_signals = true );

	/*
	 * A call that prompts the server into listening for HTTP requests.
	 *
	 * This call accepts a value for how large the thread pool should be for distributing requests
	 * and another param which defines the blocking nature.
	 *
	 * @param n_threads the number of threads to pool for request handling
	 * @param block if n_threads > 0, defines whether this operation is blocking or not
	 */
	void run(int n_threads = 1, bool block = true);

	/*
	 * Stops the server from accepting requests.
	 *
	 * This call blocks until all open connections are closed.
	 */
	void stop();

	/*
	 * Sets the maximum length of time in milliseconds to wait for a clients request to be received.
	 * If set to 0 (default) the value is ignored and no timeout is used.
	 *
	 * @param time_milliseconds the time in milliseconds to wait, 0 is ignored and no timeout is set
	 */
	void set_read_timeout(int time_milliseconds);

	/*
	 * Sets the maximum length of time in milliseconds to wait for a client to fully receive the
	 * response from the server. If set to 0 (default) the value is ignored and no timeout is used.
	 *
	 * @param time_milliseconds the time in milliseconds to wait, 0 is ignored and no timeout is set
	 */
	void set_write_timeout(int time_milliseconds);

	/*
	 * Sets the maximum size in bytes that a request is permitted to be before a client is rejected.
	 * If set to 0 (default) the limit is ignored.
	 *
	 * @param num_bytes the number of bytes permitted, 0 is ignored and no limit is used
	 */
	void set_max_request_bytes(size_t num_bytes);

private:
	/*
	 * An asynchronous call that triggers listening for a TCP connection or signal.
	 */
	void do_accept();

	/*
	 * Stops the server from listening for new connections and closes all open connections.
	 */
	void do_await_stop();
};

} } // net, served

#endif // SERVER_HPP
