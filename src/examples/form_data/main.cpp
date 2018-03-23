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

/* form_data example
 *
 * This example demonstrates how you might specify and validate a form endpoint.
 */
int main(int, char const**)
{
	served::multiplexer mux;
	mux.handle("/form_post")
		.post([&](served::response & res, const served::request & req) {
			// check headers for the correct content type
			if ( req.header("content-type") != "application/x-www-form-urlencoded" )
			{
				// return 400 bad request if the content type is wrong for this example.
				served::response::stock_reply(400, res);
			}
			else
			{
				res << "Body data: " << req.body();
			}
		});

	std::cout << "Try this example with:" << std::endl;
	std::cout << " curl http://localhost:8123/form_post -d \"hello world!\"" << std::endl;

	served::net::server server("0.0.0.0", "8123", mux);
	server.run(10);

	return (EXIT_SUCCESS);
}
