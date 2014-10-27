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

#include "uri.hpp"

TEST_CASE("Test uri const, ref and copy handling", "[uri]")
{
	served::uri uri;
	uri.set_fragment("fragment1");
	uri.set_URI     ("path1");
	uri.set_query   ("query1");
	uri.set_path    ("path1");

	REQUIRE( uri.fragment() == "fragment1" );
	REQUIRE( uri.URI()      == "path1" );
	REQUIRE( uri.query()    == "query1" );
	REQUIRE( uri.path()     == "path1" );

	auto test_copy = [](served::uri u)
	{
		REQUIRE( u.fragment() == "fragment1" );
		REQUIRE( u.URI()      == "path1" );
		REQUIRE( u.query()    == "query1" );
		REQUIRE( u.path()     == "path1" );

		u.set_fragment("fragment2");
		u.set_URI     ("path2");
		u.set_query   ("query2");
		u.set_path    ("path2");

		REQUIRE( u.fragment() == "fragment2" );
		REQUIRE( u.URI()      == "path2" );
		REQUIRE( u.query()    == "query2" );
		REQUIRE( u.path()     == "path2" );
	};

	auto test_const_copy = [](const served::uri u)
	{
		REQUIRE( u.fragment() == "fragment1" );
		REQUIRE( u.URI()      == "path1" );
		REQUIRE( u.query()    == "query1" );
		REQUIRE( u.path()     == "path1" );
	};

	auto test_const_ref = [](served::uri const& u)
	{
		REQUIRE( u.fragment() == "fragment1" );
		REQUIRE( u.URI()      == "path1" );
		REQUIRE( u.query()    == "query1" );
		REQUIRE( u.path()     == "path1" );
	};

	test_copy      (uri);
	test_const_copy(uri);
	test_const_ref (uri);
}

TEST_CASE("query escape and unescape", "[uri]") {
	const char* unescaped_query = "you got served";
	const char* escaped_query   = "you%20got%20served";

	SECTION("escape") {
		REQUIRE(served::query_escape(unescaped_query) == escaped_query);
	}
	SECTION("unescape") {
		REQUIRE(served::query_unescape(escaped_query) == unescaped_query);
	}
}
