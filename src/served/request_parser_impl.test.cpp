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

#define CATCH_CONFIG_MAIN
#include "../test/catch.hpp"

#include <served/methods.hpp>
#include <served/request_parser_impl.hpp>

TEST_CASE("request parser impl can parse http requests", "[request_parser_impl]") {
	served::request req;
	served::request_parser_impl parser(req);
	const char* request =
		"POST /you/got/served?reason=science#idet HTTP/1.1\r\n"
		"Host: api.datasift.com\r\n"
		"Content-Type: text/xml; charset=utf-8\r\n"
		"Content-Length: 15\r\n"
		"\r\n"
		"you got served!\r\n";
	size_t read_bytes = parser.execute(request, strlen(request));
	SECTION("header is parsed correctly") {
		SECTION("check request") {
			REQUIRE(req.method()       == served::method::POST);
			REQUIRE(req.HTTP_version() == "HTTP/1.1");
			REQUIRE(req.body()         == "you got served!\r\n");
		}
		SECTION("check uri") {
			REQUIRE(req.url().URI()      == "/you/got/served?reason=science");
			REQUIRE(req.url().path()     == "/you/got/served");
			REQUIRE(req.url().query()    == "reason=science");
			REQUIRE(req.url().fragment() == "idet");
		}
		SECTION("check fields") {
			REQUIRE(req.header("Host")           == "api.datasift.com");
			REQUIRE(req.header("Content-Type")   == "text/xml; charset=utf-8");
			REQUIRE(req.header("CONTENT-LENGTH") == "15");
		}
	}
}

TEST_CASE("request parser impl can handle utf-8", "[request_parser_impl]") {
	served::request req;
	served::request_parser_impl parser(req);
	const char* request =
		u8"POST /you/got/served?reason=science#idet HTTP/1.1\r\n"
		u8"Host: api.datasift.com\r\n"
		u8"Content-Type: text/xml; charset=utf-8\r\n"
		u8"Content-Length: 15\r\n"
		u8"\r\n"
		u8"Unicode character: \u2018\r\n";
	size_t read_bytes = parser.execute(request, strlen(request));

	SECTION("header is parsed correctly") {
		SECTION("check request") {
			REQUIRE(req.method()       == served::method::POST);
			REQUIRE(req.HTTP_version() == u8"HTTP/1.1");
			REQUIRE(req.body()         == u8"Unicode character: \u2018\r\n");
		}
		SECTION("check uri") {
			REQUIRE(req.url().URI()      == u8"/you/got/served?reason=science");
			REQUIRE(req.url().path()     == u8"/you/got/served");
			REQUIRE(req.url().query()    == u8"reason=science");
			REQUIRE(req.url().fragment() == u8"idet");
		}
		SECTION("check fields") {
			REQUIRE(req.header("HOST")           == u8"api.datasift.com");
			REQUIRE(req.header("CONTENT-TYPE")   == u8"text/xml; charset=utf-8");
			REQUIRE(req.header("CONTENT-length") == u8"15");
		}
	}
}
