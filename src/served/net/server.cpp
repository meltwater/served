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

#include <signal.h>
#include <utility>
#include <thread>

#include <served/net/server.hpp>

using namespace served;
using namespace served::net;

server::server( const std::string & address
              , const std::string & port
              , multiplexer       & mux
              )
	: _io_service()
	, _signals(_io_service)
	, _acceptor(_io_service)
	, _connection_manager()
	, _socket(_io_service)
	, _request_handler(mux)
	, _read_timeout(0)
	, _write_timeout(0)
	, _req_max_bytes(0)
{
	/*
	 * Register to handle the signals that indicate when the server should exit.
	 * It is safe to register for the same signal multiple times in a program,
	 * provided all registration for the specified signal is made through Asio.
	 */
	_signals.add(SIGINT);
	_signals.add(SIGTERM);
#if defined(SIGQUIT)
	_signals.add(SIGQUIT);
#endif // defined(SIGQUIT)

	do_await_stop();

	// Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
	boost::asio::ip::tcp::resolver resolver(_io_service);
	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve({address, port});

	_acceptor.open(endpoint.protocol());
	_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	_acceptor.bind(endpoint);
	_acceptor.listen();

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
		std::vector<std::thread> v_threads;
		for ( int i = 0; i < n_threads; i++ )
		{
			v_threads.push_back(std::thread([this](){
				_io_service.run();
			}));
		}
		for ( auto & thread : v_threads )
		{
			if ( thread.joinable() )
			{
				thread.join();
			}
		}
	}
	else
	{
		_io_service.run();
	}
}

void
server::set_read_timeout(int time_milliseconds)
{
	_read_timeout = time_milliseconds;
}

void
server::set_write_timeout(int time_milliseconds)
{
	_write_timeout = time_milliseconds;
}

void
server::set_max_request_bytes(size_t num_bytes)
{
	_req_max_bytes = num_bytes;
}

void
server::stop()
{
	if ( ! _io_service.stopped() )
	{
		_io_service.stop();
	}
}

void
server::do_accept()
{
	_acceptor.async_accept(_socket,
		[this](boost::system::error_code ec) {
			// Check whether the server was stopped by a signal before this
			// completion handler had a chance to run.
			if (!_acceptor.is_open())
			{
				return;
			}
			if (!ec)
			{
				_connection_manager.start(
					std::make_shared<connection>( _io_service
					                            , std::move(_socket)
					                            , _connection_manager
					                            , _request_handler
					                            , _req_max_bytes
					                            , _read_timeout
					                            , _write_timeout
					                            ));
			}
			do_accept();
		}
	);
}

void
server::do_await_stop()
{
	_signals.async_wait(
		[this](boost::system::error_code /*ec*/, int /*signo*/) {
			/* The server is stopped by cancelling all outstanding asynchronous
			 * operations. Once all operations have finished the io_service::run()
			 * call will exit.
			 */
			_acceptor.close();
			_connection_manager.stop_all();
		});
}
