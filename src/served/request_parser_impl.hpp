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
 * Responsible for moving sections of an incoming HTTP request to a served request object.
 *
 */
class request_parser_impl : public served::request_parser {
public:
	enum status_type { ERROR = 0, READ_HEADER, EXPECT_CONTINUE, READ_BODY, FINISHED };

private:
	request &         d_request;
	status_type       d_status;
	size_t            d_body_expected;
	std::stringstream d_body_stream;

public:
	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	explicit request_parser_impl(request & req)
		: served::request_parser()
		, d_request(req)
		, d_status(status_type::READ_HEADER)
		, d_body_expected(0)
		, d_body_stream()
	{}

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	status_type parse(const char *data, size_t len);

	/*
	 * Prompts the parser to finalise any remaining fields of the request object.
	 *
	 * Should be called after all remaining TCP data has been pushed.
	 */
	void finish();

protected:
	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	virtual void http_field(const char *data, const char *field, size_t flen,
		const char *value, size_t vlen) override;

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	virtual void request_method(const char *data, const char *at,
		size_t length) override;

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	virtual void request_uri(const char *data, const char *at,
		size_t length) override;

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	virtual void fragment(const char *data, const char *at,
		size_t length) override;

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	virtual void request_path(const char *data, const char *at,
		size_t length) override;

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	virtual void query_string(const char *data, const char *at,
		size_t length) override;

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	virtual void http_version(const char *data, const char *at,
		size_t length) override;

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
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
