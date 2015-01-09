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

#include <served/served.hpp>
#include <served/request_error.hpp>
#include <served/status.hpp>

#include <iostream>

/* request_logger_plugin example
 *
 * Here we demonstrate how you can implement a simple request logger using the mux.use_before plugin
 * register. The method gets called before each request is handled.
 *
 * If you want to log requests apache style then this logger is already implemented in
 * src/served/plugins.hpp, it has to be registered with mux.use_after, like so:
 *
 * mux.use_after(served::plugins::access_log);
 */
int main(int argc, char const* argv[])
{
	served::multiplexer mux;

	// register one or more handlers
	mux.handle("/served")
		.get([](served::response & res, const served::request & req) {
			res << "You got served!";
		});
	mux.handle("/itson")
		.get([](served::response & res, const served::request & req) {
			res << "Oh, it's on!";
		});

	// register middleware / plugin
	mux.use_before([](served::response & res, const served::request & req) {
		std::cout << "request: " << req.url().URI() << std::endl;
	});

	std::cout << "Try this example with:" << std::endl;
	std::cout << " curl http://localhost:1337/served" << std::endl;
	std::cout << " curl http://localhost:1337/itson" << std::endl;

	served::net::server server("127.0.0.1", "1337", mux);
	server.run(10);

	return (EXIT_SUCCESS);
}
