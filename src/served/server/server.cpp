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

#include "server.hpp"

#include <signal.h>
#include <utility>
#include <thread>

using namespace served::server;

server::server( const std::string & address
              , const std::string & port
              , const std::string & doc_root )
	: d_io_service()
	, d_signals(d_io_service)
	, d_acceptor(d_io_service)
	, d_connection_manager()
	, d_socket(d_io_service)
	, d_request_handler(doc_root)
{
	/*
	 * Register to handle the signals that indicate when the server should exit.
	 * It is safe to register for the same signal multiple times in a program,
	 * provided all registration for the specified signal is made through Asio.
	 */
	d_signals.add(SIGINT);
	d_signals.add(SIGTERM);
#if defined(SIGQUIT)
	d_signals.add(SIGQUIT);
#endif // defined(SIGQUIT)

	do_await_stop();

	// Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
	boost::asio::ip::tcp::resolver resolver(d_io_service);
	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve({address, port});

	d_acceptor.open(endpoint.protocol());
	d_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	d_acceptor.bind(endpoint);
	d_acceptor.listen();

	do_accept();
}

void
server::run(int n_threads /* = 1 */)
{
	/*
	 * The io_service::run() call will block until all asynchronous operations
	 * have finished. While the server is running, there is always at least one
	 * asynchronous operation outstanding: the asynchronous accept call waiting
	 * for new incoming connections.
	 */
	if ( n_threads > 1 )
	{
		std::vector<std::thread> v_threads(n_threads);
		for ( int i = 0; i < n_threads; i++ )
		{
			v_threads.push_back(std::thread([&](){
				d_io_service.run();
			}));
		}
		for ( auto & thread : v_threads )
		{
			thread.join();
		}
	}
	else
	{
		d_io_service.run();
	}
}

void
server::do_accept()
{
	d_acceptor.async_accept(d_socket,
		[this](boost::system::error_code ec) {
			// Check whether the server was stopped by a signal before this
			// completion handler had a chance to run.
			if (!d_acceptor.is_open())
			{
				return;
			}
			if (!ec)
			{
				d_connection_manager.start(std::make_shared<connection>(
					std::move(d_socket), d_connection_manager, d_request_handler));
			}
			do_accept();
		}
	);
}

void
server::do_await_stop()
{
	d_signals.async_wait(
		[this](boost::system::error_code /*ec*/, int /*signo*/) {
			// The server is stopped by cancelling all outstanding asynchronous
			// operations. Once all operations have finished the io_service::run()
			// call will exit.
			d_acceptor.close();
			d_connection_manager.stop_all();
		});
}
