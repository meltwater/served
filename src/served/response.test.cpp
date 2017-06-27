/*
 * Copyright (C) MediaSift Ltd.
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

#include <test/catch.hpp>

#include <served/response.hpp>
#include <served/version.hpp>

TEST_CASE("can chain response streaming operator", "[response]") {
	served::response res;
	res << "Hello" << " " << "World!";
}

TEST_CASE("generates compliant HTTP response", "[response]") {
	std::string response =
		"HTTP/1.1 200 OK\r\n"
		"Server: served-v" + std::string(APPLICATION_VERSION_STRING) + "\r\n"
		"Content-Type: text/plain\r\n"
		"Content-Length: 10\r\n"
		"\r\n"
		"Successful";

	served::response res;
	served::response::stock_reply(200, res);
	REQUIRE(res.to_buffer() == response);
}
