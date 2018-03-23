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

#include <served/request_parser.hpp>
#include <cstring>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

struct uri_t
{
	string uri;
	string path;
	string query;
	string fragment;
};

struct http_request_header
{
	vector<tuple<string, string>> fields;
	string                        method;
	uri_t                         uri;
	string                        http_version;
	string                        content;
};

class mock_request_parser : public served::request_parser
{
	http_request_header d_header;

public:
	mock_request_parser()
		: served::request_parser()
	{}

	virtual ~mock_request_parser() {}

	http_request_header get_header() { return d_header; }

protected:
	virtual void http_field(const char *data, const char *field, size_t flen,
			const char *value, size_t vlen) override
	{
		(void) data;
		d_header.fields.push_back(make_tuple(string(field, flen), string(value, vlen)));
		CAPTURE(string(field, flen));
		CAPTURE(string(value, vlen));
	}

	virtual void request_method(const char *data, const char *at,
			size_t length) override
	{
		(void) data;
		d_header.method = string(at, length);
		CAPTURE(d_header.method);
	}

	virtual void request_uri(const char *data, const char *at,
			size_t length) override
	{
		(void) data;
		d_header.uri.uri = string(at, length);
		CAPTURE(d_header.uri.uri);
	}

	virtual void fragment(const char *data, const char *at,
			size_t length) override
	{
		(void) data;
		d_header.uri.fragment = string(at, length);
		CAPTURE(d_header.uri.fragment);
	}

	virtual void request_path(const char *data, const char *at,
			size_t length) override
	{
		(void) data;
		d_header.uri.path = string(at, length);
		CAPTURE(d_header.uri.path);
	}

	virtual void query_string(const char *data, const char *at,
			size_t length) override
	{
		(void) data;
		d_header.uri.query = string(at, length);
		CAPTURE(d_header.uri.query);
	}

	virtual void http_version(const char *data, const char *at,
			size_t length) override
	{
		(void) data;
		d_header.http_version = string(at, length);
		CAPTURE(d_header.http_version);
	}

	virtual void header_done(const char *data, const char *at,
			size_t length) override
	{
		(void) data;
		d_header.content = string(at, length);
		CAPTURE(string(at, length));
	}
};

TEST_CASE("request parser can parse http requests", "[request_parser]")
{
	mock_request_parser parser;
	const char* request =
		"POST /you/got/served?reason=science#idet HTTP/1.1\r\n"
		"Host: api.datasift.com\r\n"
		"Content-Type: text/xml; charset=utf-8\r\n"
		"Content-Length: 15\r\n"
		"\r\n"
		"you got served!\r\n";
	size_t read_bytes = parser.execute(request, strlen(request));

	SECTION("parser behaviour")
	{
		SECTION("will parse header without errors")
		{
			REQUIRE(served::request_parser::FINISHED == parser.get_status());
		}
		SECTION("parse returns offset to beginning of content")
		{
			REQUIRE(string(&request[read_bytes], strlen(request)-read_bytes) == "you got served!\r\n");
		}
	}

	SECTION("header is parsed correctly")
	{
		http_request_header header = parser.get_header();

		SECTION("check request")
		{
			REQUIRE(header.method       == "POST");
			REQUIRE(header.http_version == "HTTP/1.1");
			REQUIRE(header.content      == "you got served!\r\n");
		}
		SECTION("check uri")
		{
			REQUIRE(header.uri.uri      == "/you/got/served?reason=science");
			REQUIRE(header.uri.path     == "/you/got/served");
			REQUIRE(header.uri.query    == "reason=science");
			REQUIRE(header.uri.fragment == "idet");
		}
		SECTION("check fields")
		{
			for (auto& field : header.fields)
			{
				if (get<0>(field) == "Host")
				{
					REQUIRE(get<1>(field) == "api.datasift.com");
				}
				else if (get<0>(field) == "Content-Type")
				{
					REQUIRE(get<1>(field) == "text/xml; charset=utf-8");
				}
				else if (get<0>(field) == "Content-Length")
				{
					REQUIRE(get<1>(field) == "15");
				}
			}
		}
	}
}

TEST_CASE("request parser can handle utf-8", "[request_parser]")
{
	mock_request_parser parser;
	const char* request =
		u8"POST /you/got/served?reason=science#idet HTTP/1.1\r\n"
		u8"Host: api.datasift.com\r\n"
		u8"Content-Type: text/xml; charset=utf-8\r\n"
		u8"Content-Length: 15\r\n"
		u8"\r\n"
		u8"Unicode character: \u2018\r\n";
	size_t read_bytes = parser.execute(request, strlen(request));

	SECTION("parser behaviour")
	{
		SECTION("will parse header without errors")
		{
			REQUIRE(served::request_parser::FINISHED == parser.get_status());
		}
		SECTION("parse returns offset to beginning of content")
		{
			REQUIRE(string(&request[read_bytes], strlen(request)-read_bytes) == u8"Unicode character: \u2018\r\n");
		}
	}
	SECTION("header is parsed correctly")
	{
		http_request_header header = parser.get_header();

		SECTION("check request")
		{
			REQUIRE(header.method       == u8"POST");
			REQUIRE(header.http_version == u8"HTTP/1.1");
			REQUIRE(header.content      == u8"Unicode character: \u2018\r\n");
		}
		SECTION("check uri")
		{
			REQUIRE(header.uri.uri      == u8"/you/got/served?reason=science");
			REQUIRE(header.uri.path     == u8"/you/got/served");
			REQUIRE(header.uri.query    == u8"reason=science");
			REQUIRE(header.uri.fragment == u8"idet");
		}
		SECTION("check fields")
		{
			for (auto& field : header.fields)
			{
				if (get<0>(field) == u8"Host")
				{
					REQUIRE(get<1>(field) == u8"api.datasift.com");
				}
				else if (get<0>(field) == u8"Content-Type")
				{
					REQUIRE(get<1>(field) == u8"text/xml; charset=utf-8");
				}
				else if (get<0>(field) == u8"Content-Length")
				{
					REQUIRE(get<1>(field) == u8"15");
				}
			}
		}
	}
}

TEST_CASE("request parser can handle request in chunks", "[request_parser]")
{
	mock_request_parser parser;

	auto chunks = std::vector<std::string> {{
		u8"GET /you/got/served?reason=science#idet HTTP/1.1\r\n",
		u8"Host: api.datasift.com\r\n",
		u8"Accepts: text/xml; charset=utf-8\r\n",
		u8"\r\n"
	}};

	for ( const auto & chunk : chunks )
	{
		size_t read_bytes = parser.execute(chunk.c_str(), chunk.length());
		REQUIRE( read_bytes == chunk.length() );
	}


	SECTION("parser behaviour")
	{
		SECTION("will parse chunked header without errors")
		{
			REQUIRE(parser.get_status() == mock_request_parser::FINISHED);
		}
	}
	SECTION("header is parsed correctly")
	{
		http_request_header header = parser.get_header();

		SECTION("check request")
		{
			REQUIRE(header.method       == u8"GET");
			REQUIRE(header.http_version == u8"HTTP/1.1");
		}
		SECTION("check uri")
		{
			REQUIRE(header.uri.uri      == u8"/you/got/served?reason=science");
			REQUIRE(header.uri.path     == u8"/you/got/served");
			REQUIRE(header.uri.query    == u8"reason=science");
			REQUIRE(header.uri.fragment == u8"idet");
		}
		SECTION("check fields")
		{
			for (auto& field : header.fields)
			{
				if (get<0>(field) == u8"Host")
				{
					REQUIRE(get<1>(field) == u8"api.datasift.com");
				}
				else if (get<0>(field) == u8"Accepts")
				{
					REQUIRE(get<1>(field) == u8"text/xml; charset=utf-8");
				}
			}
		}
	}
}
