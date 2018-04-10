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

/* rest_resource example
 *
 * This example demonstrates how you might use served to create REST resources.
 */
int main(int, char const**)
{
	served::multiplexer mux;

	mux.handle("/customers")
		.get([](served::response & res, const served::request & req) {
			(void) res;
			(void) req;
			// list customers
		})
		.post([](served::response & res, const served::request & req) {
			(void) res;
			(void) req;
			// create customer
		});

	mux.handle("/customers/{id}")
		.get([](served::response & res, const served::request & req) {
			(void) res;
			(void) req;
			// read customer req.params["id"]
		})
		.put([](served::response & res, const served::request & req) {
			(void) res;
			(void) req;
			// update customer req.params["id"]
		})
		.del([](served::response & res, const served::request & req) {
			(void) res;
			(void) req;
			// delete customer req.params["id"]
		});

	served::net::server server("127.0.0.1", "8123", mux);
	server.run(10);

	return (EXIT_SUCCESS);
}
