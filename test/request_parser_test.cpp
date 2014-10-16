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
#include <served/request_parser.hpp>
#include <cstring>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

struct http_request_header {
	vector<tuple<string, string>> fields;
	string method;
	string uri;
	string fragment;
	string request_path;
	string query_string;
	string http_version;
	string content;
};

class mock_request_parser : public served::request_parser {
	http_request_header d_header;

public:
	mock_request_parser()
		: served::request_parser()
	{}

	virtual ~mock_request_parser() {}

	http_request_header get_header() { return d_header; }

protected:
	virtual void http_field(const char *data, const char *field, size_t flen,
			const char *value, size_t vlen) override {
		d_header.fields.push_back(make_tuple(string(field, flen), string(value, vlen)));
		CAPTURE(string(field, flen));
		CAPTURE(string(value, vlen));
	}

	virtual void request_method(const char *data, const char *at,
			size_t length) override {
		d_header.method = string(at, length);
		CAPTURE(d_header.method);
	}

	virtual void request_uri(const char *data, const char *at,
			size_t length) override {
		d_header.uri = string(at, length);
		CAPTURE(d_header.uri);
	}

	virtual void fragment(const char *data, const char *at,
			size_t length) override {
		d_header.fragment = string(at, length);
		CAPTURE(d_header.fragment);
	}

	virtual void request_path(const char *data, const char *at,
			size_t length) override {
		d_header.request_path = string(at, length);
		CAPTURE(d_header.request_path);
	}

	virtual void query_string(const char *data, const char *at,
			size_t length) override {
		d_header.query_string = string(at, length);
		CAPTURE(d_header.query_string);
	}

	virtual void http_version(const char *data, const char *at,
			size_t length) override {
		d_header.http_version = string(at, length);
		CAPTURE(d_header.http_version);
	}

	virtual void header_done(const char *data, const char *at,
			size_t length) override {
		d_header.content = string(at, length);
		CAPTURE(string(at, length));
	}
};

TEST_CASE("request parser can parse http requests", "[request_parser]") {
	mock_request_parser parser;
	const char* request =
		"POST /served/test.html HTTP/1.1\r\n"
		"Host: api.datasift.com\r\n"
		"Content-Type: text/xml; charset=utf-8\r\n"
		"Content-Length: 15\r\n"
		"\r\n"
		"you got served!\r\n";
	size_t read_bytes = parser.execute(request, strlen(request));

	SECTION("parser behaviour") {
		SECTION("will parse valid header without errors") {
			REQUIRE(served::request_parser::FINISHED == parser.get_status());
		}
		SECTION("parse returns offset to beginning of content") {
			REQUIRE(string(&request[read_bytes], strlen(request)-read_bytes) == "you got served!\r\n");
		}
	}
	SECTION("header is parsed correctly") {
		http_request_header header = parser.get_header();

		SECTION("check request") {
			REQUIRE(header.method       == "POST");
			REQUIRE(header.request_path == "/served/test.html");
			REQUIRE(header.uri          == "/served/test.html");
			REQUIRE(header.http_version == "HTTP/1.1");
			REQUIRE(header.content      == "you got served!\r\n");
		}
		SECTION("check fields") {
			for (auto& field : header.fields) {
				if (get<0>(field) == "Host") {
					REQUIRE(get<1>(field) == "api.datasift.com");
				} else if (get<0>(field) == "Content-Type") {
					REQUIRE(get<1>(field) == "text/xml; charset=utf-8");
				} else if (get<0>(field) == "Content-Length") {
					REQUIRE(get<1>(field) == "15");
				}
			}
		}
	}
}
