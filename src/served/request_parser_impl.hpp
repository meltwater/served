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

namespace served {

/*
 * An implementation of a request parser.
 *
 * Responsible for moving sections of an incoming HTTP request to a served request object.
 *
 */
class request_parser_impl : public served::request_parser {
public:
	enum expect_type { NONE = 0, CONTINUE };

private:
	request &   d_request;
	expect_type d_expected;

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
		, d_expected(expect_type::NONE)
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
	std::tuple<request_parser::status, size_t> parse(const char *data, size_t len);

	/*
	 * Check whether an Expect header has been encountered.
	 *
	 * The HTTP 1.1 protocol allows for a client to send an Expect header stating an expected
	 * response from the server before continuing. This returns either the expect type or NONE if
	 * one hasn't been encountered.
	 *
	 * @return the blocking expect_type, or expect_type::NONE
	 */
	expect_type get_expected();

	/*
	 * Set the expect type of the request parser.
	 *
	 * This is used to determine whether or not the request is blocked whilst waiting for a response
	 * to an 'Expect' header.
	 *
	 * @param expected the new expected type
	 */
	void set_expected(expect_type expected);

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
};

} // served namespace

#endif // SERVED_REQUEST_PARSER_IMPL_HPP
