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

#include <algorithm>
#include <locale>

#include <served/request.hpp>

namespace served {

//  -----  constructors  -----

//  -----  mutators  -----

void
request::set_destination(std::string const& destination)
{
	_destination = uri(destination);
}

void
request::set_source(std::string const& source)
{
	_source = source;
}

void
request::set_header(std::string const& header, std::string const& value)
{
	// All headers set to lower case.
	std::string mut_header;
	mut_header.resize(header.size());

	std::transform(header.begin(), header.end(), mut_header.begin(), ::tolower);

	_headers[mut_header] = value;
}

void
request::set_cookie(served::cookie const& value)
{
	_cookies[value.name()] = value;
}

void
request::set_body(std::string const& body)
{
	_body = body;
}

//  -----  component accessors  -----

const uri
request::url() const
{
	return _destination;
}

const std::string
request::source() const
{
	return _source;
}

const std::string
request::header(std::string const& header) const
{
	// All headers set to lower case.
	std::string mut_header;
	mut_header.resize(header.size());

	std::transform(header.begin(), header.end(), mut_header.begin(), ::tolower);

	header_list::const_iterator it = _headers.find(mut_header);
	if ( it != _headers.end() )
	{
		return it->second;
	}
	return std::string();
}

const served::cookie
request::cookie(std::string const& key) const
{
	cookie_list::const_iterator it = _cookies.find(key);
	if ( it != _cookies.end() )
	{
		return it->second;
	}
	return served::cookie();
}

const std::string
request::body() const
{
	return _body;
}

} // served
