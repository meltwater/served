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

#ifndef SERVED_REQ_ERROR_HPP
#define SERVED_REQ_ERROR_HPP

#include <stdexcept>

namespace served {
/*
 * An exception that contains an HTTP status code.
 *
 * The request error should be used during a request handle if an unrecoverable error occurs, and
 * allows a status code as well as a message to be specified for returning to the client.
 */
class request_error : public std::runtime_error
{
	int _status_code;

public:
	/*
	 * Construct a request error from a status code and a message.
	 *
	 * @param status_code the status code to return to the client
	 * @param message a message body to return to the client
	 */
	request_error(int status_code, std::string const& message)
		: std::runtime_error(message)
		, _status_code(status_code)
	{}

	/*
	 * Returns the status code of the request error.
	 *
	 * @return the status code
	 */
	int get_status_code() const
	{
		return _status_code;
	}
};

} // served

#endif // SERVED_REQ_ERROR_HPP
