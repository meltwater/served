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
#include <sstream>

#include <served/version.hpp>
#include <served/response.hpp>

namespace served {

//  -----  constructors  -----

response::response()
	: _status(status_2XX::OK)
{
}

//  -----  response mutators  -----

void
response::set_header(std::string const& header, std::string const& value)
{
	// All headers set to lower case.
	std::string mut_header;
	mut_header.resize(header.size());

	std::transform(header.begin(), header.end(), mut_header.begin(), ::tolower);

	_headers[mut_header] = header_pair(header, value);
}

void
response::set_status(int status_code)
{
	_status = status_code;
}

void
response::set_body(const std::string & body)
{
	_body.clear();
	_body.str(body);
}

response&
response::operator<<(std::string const& rhs)
{
	_body << rhs;
	return (*this);
}

//  -----  accessors  -----

const int
response::status()
{
	return _status;
}

const size_t
response::body_size()
{
	_body.seekp(0, std::ios::end);
	return _body.tellp();
}

//  -----  serialization  -----

const std::string
response::to_buffer()
{
	std::stringstream ss;

	ss << "HTTP/1.1 " << _status << " " << status::status_to_reason(_status) << "\r\n";

	// If server header not specified we add served version stamp
	if ( _headers.find("server") == _headers.end() )
	{
		ss << "Server: served-v" << APPLICATION_VERSION_STRING << "\r\n";
	}
	for ( const auto & header : _headers )
	{
		ss << std::get<0>(header.second) << ": " << std::get<1>(header.second) << "\r\n";
	}

	// If content length not specified we check body size
	if ( _headers.find("content-length") == _headers.end() )
	{
		ss << "Content-Length: " << body_size() << "\r\n";
	}

	ss << "X-Clacks-Overhead: GNU Terry Pratchett\r\n";

	ss << "\r\n";
	ss << _body.str();

	_buffer = ss.str();
	return _buffer;
}

//  -----  stock reply  -----

void
response::stock_reply(int status_code, response & res)
{
	res.set_status(status_code);
	res.set_header("Content-Type", "text/plain");

	switch (status_code)
	{
	// 2XX
	case served::status_2XX::OK:
		res << "Successful";
		break;
	case served::status_2XX::NO_CONTENT:
		break;
	// 4XX
	case served::status_4XX::BAD_REQUEST:
		res << "Detected a bad request";
		break;
	case served::status_4XX::NOT_FOUND:
		res << "Resource not found";
		break;
	case served::status_4XX::REQUEST_TIMEOUT:
		res << "The request timed out";
		break;
	case served::status_4XX::METHOD_NOT_ALLOWED:
		res << "Method is not supported for this resource";
		break;
	case served::status_4XX::UNAUTHORIZED:
		res << "Client is unauthorized to access this resource";
		break;
	case served::status_4XX::FORBIDDEN:
		res << "Access to this resource is forbidden";
		break;
	case served::status_4XX::IM_A_TEAPOT:
		res << "I'm a teapot";
		break;
	case served::status_4XX::TOO_MANY_REQUESTS:
		res << "Too many requests have been detected from this client";
		break;
	// 5XX
	case served::status_5XX::INTERNAL_SERVER_ERROR:
		res << "Encountered an internal server error";
		break;
	default:
		// TODO: Maybe throw exception here?
		break;
	}
}

} // served
