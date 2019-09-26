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
request::clear()
{
	_method = served::method::GET;
	_destination = uri();
	_HTTP_version = "";
	_source = "";
	_body = "";
}

void
request::set_method(const enum method & method)
{
	_method = method;
}

void
request::set_destination(const uri & destination)
{
	_destination = destination;
}

void
request::set_HTTP_version(const std::string & HTTP_version)
{
	_HTTP_version = HTTP_version;
}

void
request::set_source(const std::string & source)
{
	_source = source;
}

void
request::set_header(const std::string & header, const std::string & value)
{
	// All headers set to lower case.
	std::string mut_header;
	mut_header.resize(header.size());

	std::transform(header.begin(), header.end(), mut_header.begin(), ::tolower);

	_headers[mut_header] = value;
}

void
request::set_body(const std::string & body)
{
	_body = body;
}

uri &
request::url()
{
	return _destination;
}

//  -----  component accessors  -----

enum method
request::method() const
{
	return _method;
}

const uri
request::url() const
{
	return _destination;
}

const std::string
request::HTTP_version() const
{
	return _HTTP_version;
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

const std::string
request::body() const
{
	return _body;
}

const request::header_list&
request::get_headers() const
{
	return _headers;
}

} // served
