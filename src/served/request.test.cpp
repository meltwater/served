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

#include <served/request.hpp>

TEST_CASE("Test req const, ref and copy handling", "[request]")
{
	served::uri uri;
	uri.set_URI("/base/path?id=1");

	served::request req;
	req.set_destination(uri);
	req.set_HTTP_version("HTTP/1.1");
	req.set_source("127.0.0.1");
	req.set_header("header1", "header one");
	req.set_body("hello world");

	auto test_copy = [](served::request r)
	{
		REQUIRE( r.url().URI()       == "/base/path?id=1" );
		REQUIRE( r.source()          == "127.0.0.1" );
		REQUIRE( r.header("header1") == "header one" );
		REQUIRE( r.body()            == "hello world" );

		served::uri uri2;
		uri2.set_URI("/foo/bar?id=2");

		r.set_destination(uri2);
		r.set_source("192.168.0.45");
		r.set_header("header1", "new header one");
		r.set_body("hello second world");

		REQUIRE( r.url().URI()       == "/foo/bar?id=2" );
		REQUIRE( r.source()          == "192.168.0.45" );
		REQUIRE( r.header("header1") == "new header one" );
		REQUIRE( r.body()            == "hello second world" );
	};

	auto test_const_copy = [](const served::request r)
	{
		REQUIRE( r.url().URI()       == "/base/path?id=1" );
		REQUIRE( r.source()          == "127.0.0.1" );
		REQUIRE( r.header("header1") == "header one" );
		REQUIRE( r.body()            == "hello world" );
	};

	auto test_const_ref = [](served::request const& r)
	{
		REQUIRE( r.url().URI()       == "/base/path?id=1" );
		REQUIRE( r.source()          == "127.0.0.1" );
		REQUIRE( r.header("header1") == "header one" );
		REQUIRE( r.body()            == "hello world" );
	};

	test_copy      (req);
	test_const_copy(req);
	test_const_ref (req);
}

TEST_CASE("Test header case sensitivity", "[request]")
{
	served::request req;
	req.set_header("TeStInG-HeAdEr-1", "value one");
	req.set_header("testing-header-2", "value two");
	req.set_header("TESTING-HEADER-3", "value three");

	REQUIRE( req.header("TESTING-HEADER-1") == "value one" );
	REQUIRE( req.header("tEsTiNg-hEaDeR-2") == "value two" );
	REQUIRE( req.header("testing-header-3") == "value three" );
}
