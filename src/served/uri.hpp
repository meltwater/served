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

#ifndef SERVED_URI_HPP
#define SERVED_URI_HPP

#include <string>

namespace served {

class uri
{
public:
	//  -----  constructors  -----

	//  -----  URI component mutators  -----

	void set_href    (std::string const& href);
	void set_protocol(std::string const& protocol);
	void set_host    (std::string const& host);
	void set_hostname(std::string const& hostname);
	void set_port    (std::string const& port);
	void set_path    (std::string const& path);
	void set_pathname(std::string const& pathname);
	void set_query   (std::string const& query);
	void set_hash    (std::string const& hash);

	//  -----  URI component selectors  -----

	// For href: "http://localhost:8080/foo/bar?test=one#element"
	//
	// "http://localhost:8080/foo/bar?test=one#element"
	const std::string href()     const;
	//
	// "http"
	const std::string protocol() const;
	//
	// "localhost:8080"
	const std::string host()     const;
	//
	// "localhost"
	const std::string hostname() const;
	//
	// "8080
	const std::string port()     const;
	//
	// "/foo/bar?test=one#element"
	const std::string path()     const;
	//
	// "/foo/bar"
	const std::string pathname() const;
	//
	// "?test=one"
	const std::string query()    const;
	//
	// "#element"
	const std::string hash()     const;

private:
	std::string _href;
	std::string _protocol;
	std::string _host;
	std::string _hostname;
	std::string _port;
	std::string _path;
	std::string _pathname;
	std::string _query;
	std::string _hash;
};

} // served

#endif // SERVED_URI_HPP
