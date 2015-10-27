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

#ifndef SERVED_RESPONSE_HPP
#define SERVED_RESPONSE_HPP

#include <sstream>
#include <iostream>
#include <map>
#include <functional>
 
#include <served/status.hpp>

namespace served {

/*
 * Represents a HTTP response.
 *
 * This class represents a HTTP response, and provides an appropriate interface
 * for setting properties, and then generating a response string. The class is
 * composed of a status code, headers, and the body of the response.
 *
 * The response to a given HTTP request is built by method handlers in response
 * to a request. This class is used to simplify the method of composing an
 * appropriate response to a request.
 */
class response
{
	typedef std::tuple<std::string, std::string> header_pair;
	typedef std::map<std::string, header_pair>   header_list;

	int               _status;
	header_list       _headers;
	mutable std::stringstream _body; //for body_size()
	std::string       _buffer;

public:
	//  -----  constructors  -----

	/*
	 * Construct an empty response.
	 */
	response();

	//  -----  response mutators  -----

	/*
	 * Sets a header field.
	 *
	 * Setting the same header twice will overwrite the previous, and header keys are case
	 * insensitive. When sent to the client the header key will be as written here.
	 *
	 * @param header the header key
	 * @param value the header value
	 */
	void set_header(std::string const& header, std::string const& value);

	/*
	 * Set the HTTP status of the response.
	 *
	 * @param status_code the status code
	 */
	void set_status(int status_code);

	/*
	 * Set the entire body of the response.
	 *
	 * Sets the body of the response, overwriting any previous data stored in the body.
	 *
	 * @param body the response body
	 */
	void set_body(const std::string & body);

	/*
	 * Pipe data to the body of the response.
	 *
	 * Appends data onto the body of the reponse.
	 *
	 * @param rhs data to be appended
	 */
	response& operator<<(std::string const& rhs);

	//  -----  accessors  -----

	/*
	 * Get the status of the response.
	 *
	 * @return the status of the response
	 */
	const int status() const;

	/*
	 * Get the byte count of the response body.
	 *
	 * @return the size of the response body
	 */
	const size_t body_size() const;

	//  -----  serializer  -----

	/*
	 * Generate an HTTP response from this object.
	 *
	 * Uses the configured parameters to generate a full HTTP response and returns it as a
	 * std::string.
	 *
	 * @return the HTTP response
	 */
	const std::string to_buffer();

	//  -----  stock reply  -----

	/*
	 * Generate a general response to a specific HTTP status code.
	 *
	 * Constructs a response with a generic body to match a status code for when a detailed response
	 * isn't required.
	 *
	 * @param status_code the HTTP status code to generate for
	 * @param res the response object to modify
	 */
	static void stock_reply(int status_code, response & res);

	std::function<void()> onComplete;
};

} // served

#endif // SERVED_RESPONSE_HPP
