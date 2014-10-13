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

#ifndef SERVED_REQUEST_HPP
#define SERVED_REQUEST_HPP

#include <string>
#include <unordered_map>

#include <served/uri.hpp>
#include <served/cookie.hpp>

namespace served {

class request
{
public:
	//  -----  constructors  -----

	//  -----  mutators  -----

	void set_destination(std::string const& destination);
	void set_source     (std::string const& source);
	void set_header     (std::string const& header, std::string const& value);
	void set_cookie     (cookie const& value);
	void set_body       (std::string const& body);

	//  -----  component accessors  -----

	const uri url() const;

	const std::string source() const;

	const std::string header(std::string const& header) const;
	const cookie      cookie(std::string const& key) const;
	const std::string body  () const;

private:
	// Appropriate map type for request may differ from response
	typedef std::unordered_map<std::string, std::string>    header_list;
	typedef std::unordered_map<std::string, served::cookie> cookie_list;

	uri         _destination;
	std::string _source;
	header_list _headers;
	cookie_list _cookies;
	std::string _body;
};

} // served

#endif // SERVED_REQUEST_HPP
