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
	: d_status(status_2XX::OK)
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

	d_headers[mut_header] = value;
}

void
response::set_status(int status_code)
{
	d_status = status_code;
}

void
response::set_body(const std::string & body)
{
	d_body.clear();
	d_body.str(body);
}

void
response::operator<<(std::string const& rhs)
{
	d_body << rhs;
}

//  -----  serialization  -----

const std::string
response::to_buffer()
{
	std::stringstream ss;

	ss << "HTTP/1.1 " << d_status << " " << status::status_to_reason(d_status) << "\r\n";

	if ( d_headers.find("server") == d_headers.end() )
	{
		ss << "server: served-v" << APPLICATION_VERSION_STRING << "\r\n";
	}
	if ( d_headers.find("content-length") == d_headers.end() )
	{
		d_body.seekp(0, std::ios::end);
		std::stringstream::pos_type offset = d_body.tellp();
		ss << "content-length: " << offset << "\r\n";
	}
	for ( const auto & header : d_headers )
	{
		ss << header.first << ": " << header.second << "\r\n";
	}

	ss << "\r\n";
	ss << d_body.str();

	d_buffer = ss.str();
	return d_buffer;
}

//  -----  stock reply  -----

void
response::stock_reply(int status_code, response & res)
{
	res.set_status(status_code);
	res.set_header("content-type", "text/plain");

	switch (status_code)
	{
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
