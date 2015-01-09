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

/* query_params example
 *
 * This example demonstrates how you can iterate and locate query parameters from the request URL,
 * since the query string is already parsed for you.
 */
int main(int argc, char const* argv[])
{
	served::multiplexer mux;
	mux.handle("/query")
		.get([&](served::response & res, const served::request & req) {
			// iterate all query params
			for ( const auto & query_param : req.query )
			{
				res << "Key: " << query_param.first << ", Value: " << query_param.second << "\n";
			}
			// get a specific param value, returns an empty string if it doesn't exist.
			res << "test: " << req.query["test"] << "\n";
		});

	std::cout << "Try this example with:" << std::endl;
	std::cout << " curl \"http://localhost:8123/query?test=example&other=param\"" << std::endl;

	served::net::server server("0.0.0.0", "8123", mux);
	server.run(10);

	return (EXIT_SUCCESS);
}
