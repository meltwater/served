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

#include <served/response.hpp>

namespace served {

//  -----  response mutators  -----

void
response::set_header(std::string const& header, std::string const& value)
{
}

void
response::set_status(int status_code)
{
}

void
response::operator<<(std::string const& rhs)
{
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
	}
}

} // served
