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

#ifndef SERVED_METHODS_HPP
#define SERVED_METHODS_HPP

#include <string>
#include <stdexcept>

namespace served {

/*
 * TBC
 */
enum method {
	GET, POST, HEAD, PUT, DELETE, OPTIONS, TRACE, CONNECT, BREW
};

/*
 * TBC
 */
inline std::string
method_to_string(enum method m)
{
	switch(m)
	{
		case method::GET:
			return "GET";
		case method::POST:
			return "POST";
		case method::HEAD:
			return "HEAD";
		case method::PUT:
			return "PUT";
		case method::DELETE:
			return "DELETE";
		case method::OPTIONS:
			return "OPTIONS";
		case method::TRACE:
			return "TRACE";
		case method::CONNECT:
			return "CONNECT";
		case method::BREW:
			return "BREW";
	}
	return "";
}

/*
 * TBC
 */
inline enum method
method_from_string(const std::string & str)
{
	if ( "GET" == str )
	{
		return method::GET;
	}
	if ( "POST" == str )
	{
		return method::POST;
	}
	if ( "HEAD" == str )
	{
		return method::HEAD;
	}
	if ( "PUT" == str )
	{
		return method::PUT;
	}
	if ( "DELETE" == str )
	{
		return method::DELETE;
	}
	if ( "OPTIONS" == str )
	{
		return method::OPTIONS;
	}
	if ( "TRACE" == str )
	{
		return method::TRACE;
	}
	if ( "CONNECT" == str )
	{
		return method::CONNECT;
	}
	if ( "BREW" == str )
	{
		return method::BREW;
	}
	throw std::runtime_error("method string not recognised");
}

} // served

#endif // SERVED_METHODS_HPP
