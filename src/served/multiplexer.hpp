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

#ifndef SERVED_MULTIPLEXER_HPP
#define SERVED_MULTIPLEXER_HPP

#include <thread>
#include <served/request.hpp>
#include <served/response.hpp>

namespace net { namespace http {

typedef std::function<void(response&, request const&)> served_req_handler

class multiplexer
{
public:
	//  -----  constructors  -----

	multiplexer();

	// Provides a base path that is listened for but ignored when selecting path
	// handlers.
	// For example: with a base path "/base" and handler registered at "/foo/bar"
	// the handler will be called for a request at "/base/foo/bar".
	multiplexer(std::string const& base_path);

	//  -----  http request handlers  -----

	void get (std::string const& path, served_req_handler handler);
	void head(std::string const& path, served_req_handler handler);
	void post(std::string const& path, served_req_handler handler);
	void put (std::string const& path, served_req_handler handler);

	//  -----  server control  -----
	//  TODO: move to server class?

	void listen(std::string const& address, std::string const& port);
	void stop();

private:
	std::string const _base_path;
};

} } // net, hpp

#endif // SERVED_MULTIPLEXER_HPP
