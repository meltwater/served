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

#include "served/response_parser.hpp"
#include <cstring>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

struct http_response_header {
	vector<tuple<string, string>> fields;
	string phrase;
	string status_code;
	string chunk_size;
	string http_version;
	string content;
	string last_chunk;
};

class mock_response_parser : public served::response_parser {
	http_response_header d_header;

public:
	mock_response_parser()
		: served::response_parser()
	{}

	virtual ~mock_response_parser() {}

	http_response_header get_header() { return d_header; }

protected:
	virtual void http_field(const char *data, const char *field, size_t flen,
			const char *value, size_t vlen) override {
		d_header.fields.push_back(make_tuple(string(field, flen), string(value, vlen)));
		CAPTURE(string(field, flen));
		CAPTURE(string(value, vlen));
	}

	virtual void phrase_element(const char *data, const char *at,
			size_t length) override {
		d_header.phrase = string(at, length);
		CAPTURE(d_header.phrase);
	}

	virtual void status_code_element(const char *data, const char *at,
			size_t length) override {
		d_header.status_code = string(at, length);
		CAPTURE(d_header.status_code);
	}

	virtual void chunk_size_element(const char *data, const char *at,
			size_t length) override {
		d_header.chunk_size = string(at, length);
		CAPTURE(d_header.chunk_size);
	}

	virtual void http_version_element(const char *data, const char *at,
			size_t length) override {
		d_header.http_version = string(at, length);
		CAPTURE(d_header.http_version);
	}

	virtual void header_done_element(const char *data, const char *at,
			size_t length) override {
		d_header.content = string(at, length);
		CAPTURE(d_header.content);
	}

	virtual void last_chunk_element(const char *data, const char *at,
			size_t length) override {
		d_header.last_chunk = string(at, length);
		CAPTURE(d_header.last_chunk);
	}
};

TEST_CASE("response parser can parse http responses", "[response_parser]") {
	mock_response_parser parser;
	const char* response =
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/xml; charset=utf-8\r\n"
		"Content-Length: 15\r\n"
		"\r\n"
		"you got served!\r\n";
	size_t read_bytes = parser.execute(response, strlen(response));

	SECTION("parser behaviour") {
		SECTION("will parse valid header without errors") {
			REQUIRE(served::response_parser::FINISHED == parser.get_status());
		}
	}
	SECTION("header is parsed correctly") {
		http_response_header header = parser.get_header();

		SECTION("check request") {
			REQUIRE(header.http_version == "HTTP/1.1");
			REQUIRE(header.status_code  == "200");
			REQUIRE(header.phrase       == "OK");
			REQUIRE(header.content      == "you got served!\r\n");
		}
		SECTION("check fields") {
			for (auto& field : header.fields) {
				if (get<0>(field) == "Content-Type") {
					REQUIRE(get<1>(field) == "text/xml; charset=utf-8");
				} else if (get<0>(field) == "Content-Length") {
					REQUIRE(get<1>(field) == "15");
				}
			}
		}
	}
}
