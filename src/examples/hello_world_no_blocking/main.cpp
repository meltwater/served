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
#include <unistd.h>

/* hello_world_no_blocking example
 *
 * This example is a basic example of served run in non blocking way.
 */
int main(int, char const**)
{
	served::multiplexer mux;

	mux.handle("/hello")
		.get([](served::response & res, const served::request &) {
			res << "Hello world";
		});

	std::cout << "Try this example with:" << std::endl;
	std::cout << " curl http://localhost:8123/hello" << std::endl;

	served::net::server server("127.0.0.1", "8123", mux);
	server.run(10, false); // Run with a pool of 10 threads (not blocking)

	std::cout << "We receive the control and we can do other stuff! Sleeping..." << std::endl;
	int j = 0;
	while (j < 6) {
	  std::cout << "Sleeping: " << j << std::endl;
	  j += 1;
	  sleep(1);
	}

	std::cout << "Time to stop the server" << std::endl;
	server.stop();

	return 0;
}
