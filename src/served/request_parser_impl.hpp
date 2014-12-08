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

#ifndef SERVED_REQUEST_PARSER_IMPL_HPP
#define SERVED_REQUEST_PARSER_IMPL_HPP

#include <served/request_parser.hpp>
#include <served/request.hpp>

#include <sstream>

namespace served {

/*
 * An implementation of a request parser.
 *
 * Responsible for moving sections of an incoming HTTP request to a served request object, and uses
 * the headers and HTTP verb of the request to parse a body if one is expected.
 *
 * Call parse for each chunk of TCP data received, the parser will return a state that declares its
 * current position through the HTTP response. If the state is EXPECT_CONTINUE then the client
 * should be waiting for a 100 CONTINUE response before it will send its body.
 */
class request_parser_impl : public served::request_parser {
public:
	enum status_type
	{
		ERROR = 0,
		READ_HEADER,
		EXPECT_CONTINUE,
		READ_BODY,
		FINISHED,
		REJECTED_REQUEST_SIZE
	};

private:
	request &         _request;
	status_type       _status;
	size_t            _body_expected;
	std::stringstream _body_stream;
	size_t            _max_req_size_bytes;
	size_t            _bytes_parsed;

public:
	/*
	 * Constructs a parser by giving it a reference to a request object to be modified.
	 *
	 * @param req the request object to be modified
	 * @param max_header_size_bytes the max size of an acceptable request, a value of 0 is ignored
	 */
	explicit request_parser_impl(request & req, size_t max_req_size_bytes = 0)
		: served::request_parser()
		, _request(req)
		, _status(status_type::READ_HEADER)
		, _body_expected(0)
		, _body_stream()
		, _max_req_size_bytes(max_req_size_bytes)
		, _bytes_parsed(0)
	{}

	/*
	 * Parses a chunk of data into the request object and returns the current status of the parser.
	 *
	 * The status determines whether the parsing is complete, an error has occurred, the body is
	 * being read, or whether the client has requested a 100 CONTINUE response and is waiting.
	 *
	 * @return the new state of the parser
	 */
	status_type parse(const char *data, size_t len);

protected:
	/*
	 * Converts a block of data into an HTTP request header and stores it in the request object.
	 */
	virtual void http_field(const char *data, const char *field, size_t flen,
		const char *value, size_t vlen) override;

	/*
	 * Converts a block of data into an HTTP method and stores it in the request object.
	 */
	virtual void request_method(const char *data, const char *at,
		size_t length) override;

	/*
	 * Converts a block of data into an HTTP request URI and stores it in the request object.
	 */
	virtual void request_uri(const char *data, const char *at,
		size_t length) override;

	/*
	 * Converts a block of data into a URL fragment and stores it in the request object.
	 */
	virtual void fragment(const char *data, const char *at,
		size_t length) override;

	/*
	 * Converts a block of data into a URL request path and stores it in the request object.
	 */
	virtual void request_path(const char *data, const char *at,
		size_t length) override;

	/*
	 * Converts a block of data into a URL query string and stores it in the request object.
	 */
	virtual void query_string(const char *data, const char *at,
		size_t length) override;

	/*
	 * Converts a block of data into an HTTP protocol and stores it in the request object.
	 */
	virtual void http_version(const char *data, const char *at,
		size_t length) override;

	/*
	 * Called when the parser has completed reading the HEADER of the request.
	 *
	 * Currently not used.
	 */
	virtual void header_done(const char *data, const char *at,
		size_t length) override;

private:
	/*
	 * Checks whether the request has sent an Expect: 100-continue header.
	 *
	 * Scans the HTTP verb and headers of the request object to find out if a body is possible
	 * and whether a 100-continue has been requested.
	 *
	 * Should be used after the HTTP header is fully parsed to determine whether to send a
	 * 100 CONTINUE response before waiting for more data.
	 */
	bool requested_continue();

	/*
	 * Checks whether the request is sending a body.
	 *
	 * Scans the HTTP verb and headers of the request object to find out if a header should be
	 * expected, and how long the body will be.
	 *
	 * Should be used after the HTTP header is fully parsed to determine whether to wait for more
	 * data.
	 *
	 * @return the size of the expected body, or 0 if a body is not expected
	 */
	size_t expecting_body();

	/*
	 * Parse a chunk of body.
	 *
	 * Continues to read the body of a request and returns the status of the parser.
	 *
	 * @return status_type of request_parser_impl, FINISHED indicates the body is fully read
	 */
	status_type parse_body(const char *data, size_t len);
};

} // served namespace

#endif // SERVED_REQUEST_PARSER_IMPL_HPP
