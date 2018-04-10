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

/* handlers example
 *
 * This is a demonstration of using various handler mechanisms, including REST parameters with rejex
 * based value validation.
 */
int main(int, char const**)
{
	served::multiplexer mux;

	// GET or POST /handlers/{id}/{number:[0-9]+}
	mux.handle("/handlers/{id}/{number:[0-9]+}")
		.get([](served::response & res, const served::request & req) {
			res << "id: ";
			res << req.params["id"];
			res << ", number: ";
			res << req.params["number"];
		})
		.post([](served::response & res, const served::request & req) {
			res << "id: ";
			res << req.params["id"];
			res << ", number: ";
			res << req.params["number"];

			std::cout << req.body() << std::endl;
		});

	// GET /handlers/{id}
	mux.handle("/handlers/{id}")
		.get([](served::response & res, const served::request & req) {
			res << "id: ";
			res << req.params["id"];
		});

	// GET /handlers
	mux.handle("/handlers")
		.get([](served::response & res, const served::request &) {
			res << "You got served";
		});

	std::cout << "Try this example with:" << std::endl;
	std::cout << " curl http://localhost:8123/handlers" << std::endl;
	std::cout << " curl http://localhost:8123/handlers/test" << std::endl;
	std::cout << " curl http://localhost:8123/handlers/test/10" << std::endl;
	std::cout << " curl http://localhost:8123/handlers/test/NaN" << std::endl;

	served::net::server server("127.0.0.1", "8123", mux);
	server.run(10);

	return (EXIT_SUCCESS);
}
