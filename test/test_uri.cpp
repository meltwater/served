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

#include "catch.hpp"

#include <served/uri.hpp>

TEST_CASE("Test uri const, ref and copy handling", "[uri]")
{
	served::uri uri;
	uri.set_hash    ("hash1");
	uri.set_host    ("host1");
	uri.set_href    ("href1");
	uri.set_path    ("path1");
	uri.set_port    ("port1");
	uri.set_query   ("query1");
	uri.set_hostname("hostname1");
	uri.set_pathname("pathname1");
	uri.set_protocol("protocol1");

	REQUIRE( uri.hash()     == "hash1" );
	REQUIRE( uri.host()     == "host1" );
	REQUIRE( uri.href()     == "href1" );
	REQUIRE( uri.path()     == "path1" );
	REQUIRE( uri.port()     == "port1" );
	REQUIRE( uri.query()    == "query1" );
	REQUIRE( uri.hostname() == "hostname1" );
	REQUIRE( uri.pathname() == "pathname1" );
	REQUIRE( uri.protocol() == "protocol1" );

	auto test_copy = [](served::uri u)
	{
		REQUIRE( u.hash()     == "hash1" );
		REQUIRE( u.host()     == "host1" );
		REQUIRE( u.href()     == "href1" );
		REQUIRE( u.path()     == "path1" );
		REQUIRE( u.port()     == "port1" );
		REQUIRE( u.query()    == "query1" );
		REQUIRE( u.hostname() == "hostname1" );
		REQUIRE( u.pathname() == "pathname1" );
		REQUIRE( u.protocol() == "protocol1" );

		u.set_hash    ("hash2");
		u.set_host    ("host2");
		u.set_href    ("href2");
		u.set_path    ("path2");
		u.set_port    ("port2");
		u.set_query   ("query2");
		u.set_hostname("hostname2");
		u.set_pathname("pathname2");
		u.set_protocol("protocol2");

		REQUIRE( u.hash()     == "hash2" );
		REQUIRE( u.host()     == "host2" );
		REQUIRE( u.href()     == "href2" );
		REQUIRE( u.path()     == "path2" );
		REQUIRE( u.port()     == "port2" );
		REQUIRE( u.query()    == "query2" );
		REQUIRE( u.hostname() == "hostname2" );
		REQUIRE( u.pathname() == "pathname2" );
		REQUIRE( u.protocol() == "protocol2" );
	};

	auto test_const_copy = [](const served::uri u)
	{
		REQUIRE( u.hash()     == "hash1" );
		REQUIRE( u.host()     == "host1" );
		REQUIRE( u.href()     == "href1" );
		REQUIRE( u.path()     == "path1" );
		REQUIRE( u.port()     == "port1" );
		REQUIRE( u.query()    == "query1" );
		REQUIRE( u.hostname() == "hostname1" );
		REQUIRE( u.pathname() == "pathname1" );
		REQUIRE( u.protocol() == "protocol1" );
	};

	auto test_const_ref = [](served::uri const& u)
	{
		REQUIRE( u.hash()     == "hash1" );
		REQUIRE( u.host()     == "host1" );
		REQUIRE( u.href()     == "href1" );
		REQUIRE( u.path()     == "path1" );
		REQUIRE( u.port()     == "port1" );
		REQUIRE( u.query()    == "query1" );
		REQUIRE( u.hostname() == "hostname1" );
		REQUIRE( u.pathname() == "pathname1" );
		REQUIRE( u.protocol() == "protocol1" );
	};

	test_copy      (uri);
	test_const_copy(uri);
	test_const_ref (uri);
}
