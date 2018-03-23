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
#include <served/plugins.hpp>

#include <fstream>
#include <sstream>

/* binary_data example
 *
 * This example is a quick demo of sending a binary file over HTTP. Notice that you do not have to
 * explicitly set the Content-Length header because if this value is omitted then served calculates
 * it for you based on the response length.
 */
int main(int, char const**)
{
	served::multiplexer mux;
	mux.use_after(served::plugin::access_log);

	const std::string image_name("served-logo.png");

	mux.handle("/picture")
		.get([&](served::response & res, const served::request &) {
			std::ifstream ifs(image_name);
			res.set_body(std::string(
				(std::istreambuf_iterator<char>(ifs) ),
				(std::istreambuf_iterator<char>()    )
			));
			res.set_header("content-type", "image/png");
		});

	std::cout << "Try this example by opening http://localhost:8123/picture in a browser" << std::endl;

	served::net::server server("0.0.0.0", "8123", mux);
	server.run(10);

	return (EXIT_SUCCESS);
}
