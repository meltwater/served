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

#include <served/methods.hpp>
#include <served/uri.hpp>
#include <served/parameters.hpp>

namespace served {

/*
 * Represents a HTTP request.
 *
 * This class represents a parsed HTTP request, composed of the method (eg. GET,
 * PUT, POST, etc..), the version (eg. 1.1), the uri (eg. /endpoint/get?start=0&len=5#item1),
 * the headers (eg. 'Content-Type: application/json'), the body, and the source.
 *
 * This class is typically created by the request parser when a request is
 * received. The new object is then passed to method handlers that were registered
 * by the user to the multiplexer.
 */
class request
{
	// Appropriate map type for request may differ from response
	typedef std::unordered_map<std::string, std::string> header_list;

	enum method _method;
	uri         _destination;
	std::string _HTTP_version;
	std::string _source;
	header_list _headers;
	std::string _body;

public:
	//  -----  mutators  -----

	/*
	 * Clear all request fields back to their default values.
	 */
	void clear();

	/*
	 * Set the HTTP method of this request.
	 *
	 * @param method the HTTP method
	 */
	void set_method(const enum method & method);

	/*
	 * Set the destination of this request.
	 *
	 * The destination is the URL path of the request, used to determine which resource is being
	 * requested.
	 *
	 * @param destination the URI of the request
	 */
	void set_destination(const uri & destination);

	/*
	 * Set the HTTP version of this request.
	 *
	 * Sets the HTTP protocol version of this request.
	 *
	 * @param http_version the HTTP protocol version
	 */
	void set_HTTP_version(const std::string & http_version);

	/*
	 * Set the source of this request.
	 *
	 * Sets the address to be associated with the client of this request.
	 *
	 * @param source the source address
	 */
	void set_source(const std::string & source);

	/*
	 * Set a header value of this request.
	 *
	 * @param header the key of the header to be set
	 * @param value the value of the header
	 */
	void set_header(const std::string & header, const std::string & value);

	/*
	 * Set the body of the request.
	 *
	 * @param body the body of the request
	 */
	void set_body(const std::string & body);

	/*
	 * Obtain a reference to the URL of this request.
	 *
	 * @return a reference to the URL
	 */
	uri & url();

	//  -----  component accessors  -----

	/*
	 * Get the HTTP method of the request.
	 *
	 * @return HTTP method of the request
	 */
	const enum method method() const;

	/*
	 * Get the URL of this request.
	 *
	 * @return URL of the request
	 */
	const uri url() const;

	/*
	 * Get the HTTP version of the request.
	 *
	 * @return HTTP version of the request
	 */
	const std::string HTTP_version() const;

	/*
	 * Get the source of this request.
	 *
	 * @return the address of the source
	 */
	const std::string source() const;

	/*
	 * Get a header value from this request.
	 *
	 * @param header the key of the header to obtain
	 *
	 * @return either the header value, or an empty string if the header does not exist
	 */
	const std::string header(std::string const& header) const;

	/*
	 * Get the body of the request.
	 *
	 * @return the body of the request
	 */
	const std::string body() const;

public:
	//  -----  public members  -----

	parameters params;
	parameters query;
};

} // served

#endif // SERVED_REQUEST_HPP
