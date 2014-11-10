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

int main(int argc, char const* argv[])
{
	served::multiplexer mux;
	mux.handle("/form_post")
		.post([&](served::response & res, const served::request & req) {
			// check headers for the correct content type
			if (req.header("content-type") != "application/x-www-form-urlencoded") {
				// return 400 bad request if the content type is wrong for this
				// example.
				served::response::stock_reply(400, res);
			} else {
				// copy the query string as we will be deleting parts as we
				// iterate through each key / value pair.
				std::string query = req.url().query();
				size_t pos = 0;

				// find each pair of key / value strings delimeted by '&'
				while ((pos = query.find("&")) != std::string::npos) {
					// save the key / value pair, and look for the index of the
					// divider, delimited by '='
				    std::string pair = query.substr(0, pos);
					size_t div_index = pair.find('=');

					// write the key and value to the response string, just to
					// prove we correctly parsed the query string
					if (div_index != std::string::npos) {
						res << "Key: " << pair.substr(0, div_index) << ", Value: " 
							<< pair.substr(div_index + 1, std::string::npos) << "\n";
					}

					// erase the pair we just processed from the query string
				    query.erase(0, pos + 1);
				}
			}
		});

	served::net::server server("0.0.0.0", "8080", mux);
	server.run(10);

	return (EXIT_SUCCESS);
}
