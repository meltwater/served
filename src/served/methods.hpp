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
 * HTTP method enum
 */
enum class method {
	Get, Post, Head, Put, Delete, Options, Trace, Connect, Brew
};

/*
 * Convert an HTTP method enum to a string
 *
 * @param m the method to convert to a string
 *
 * @return the method enum as a string
 */
inline std::string
method_to_string(method m)
{
	switch(m)
	{
		case method::Get:
			return "GET";
		case method::Post:
			return "POST";
		case method::Head:
			return "HEAD";
		case method::Put:
			return "PUT";
		case method::Delete:
			return "DELETE";
		case method::Options:
			return "OPTIONS";
		case method::Trace:
			return "TRACE";
		case method::Connect:
			return "CONNECT";
		case method::Brew:
			return "BREW";
	}
	return "";
}

/*
 * Convert a string to an HTTP method enum
 *
 * @param str the string to convert to an enum
 *
 * @return the string converted to an enum
 */
inline method
method_from_string(const std::string & str)
{
	if ( "GET" == str ) {
		return method::Get;
	}
	if ( "POST" == str ) {
		return method::Post;
	}
	if ( "HEAD" == str ) {
		return method::Head;
	}
	if ( "PUT" == str ) {
		return method::Put;
	}
	if ( "DELETE" == str ) {
		return method::Delete;
	}
	if ( "OPTIONS" == str ) {
		return method::Options;
	}
	if ( "TRACE" == str ) {
		return method::Trace;
	}
	if ( "CONNECT" == str ) {
		return method::Connect;
	}
	if ( "BREW" == str ) {
		return method::Brew;
	}
	throw std::runtime_error("method string not recognised");
}

} // served

#endif // SERVED_METHODS_HPP
