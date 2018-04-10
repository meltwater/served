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

/* list_endpoints example
 *
 * This example demonstrates how to expose a list of registered API endpoints using the
 * mux.get_endpoints_list() method, which returns an iterable vector of endpoints.
 *
 * A version of this endpoints handler that prints endpoints in YAML is already written, and you can
 * use it like so:
 *
 * mux.handler("/endpoints").get(mux.get_endpoint_list_handler_YAML());
 */
int main(int, char const**)
{
	served::multiplexer mux;

	// serve up some big whoop
	mux.handle("/big_whoop")
		.get([](served::response & res, const served::request &) {
			res << "list big_whoop";
		})
		.post([](served::response & res, const served::request &) {
			res << "create big_whoop";
		});

	mux.handle("/big_whoop/{id}")
		.get([](served::response & res, const served::request & req) {
			res << "read big_whoop: ";
			res << req.params["id"];
		})
		.put([](served::response & res, const served::request & req) {
			res << "update big_whoop: ";
			res << req.params["id"];
		})
		.del([](served::response & res, const served::request & req) {
			res << "delete big_whoop: ";
			res << req.params["id"];
		});

	// GET /endpoints
	mux.handle("/endpoints")
		.get([&mux](served::response & res, const served::request &) {
			const served::served_endpoint_list endpoints = mux.get_endpoint_list();
			for (auto& endpoint : endpoints)
			{
				for (auto& method : std::get<1>(endpoint.second))
				{
					res << method << " " << endpoint.first << "\n";
				}
			}
		}
	);

	std::cout << "Try this example with:" << std::endl;
	std::cout << " curl http://localhost:8123/endpoints" << std::endl;

	served::net::server server("127.0.0.1", "8123", mux);
	server.run(10);

	return (EXIT_SUCCESS);
}
