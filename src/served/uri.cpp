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

#include <served/uri.hpp>

namespace served {

//  -----  constructors  -----

//  -----  URI component mutators  -----

void
uri::set_uri(std::string const& uri)
{
	_URI = uri;
}

void
uri::set_protocol(std::string const& protocol)
{
	_protocol = protocol;
}

void
uri::set_host(std::string const& host)
{
	_host = host;
}

void
uri::set_hostname(std::string const& hostname)
{
	_hostname = hostname;
}

void
uri::set_port(std::string const& port)
{
	_port = port;
}

void
uri::set_path(std::string const& path)
{
	_path = path;
}

void
uri::set_pathname(std::string const& pathname)
{
	_pathname = pathname;
}

void
uri::set_query(std::string const& query)
{
	_query = query;
}

void
uri::set_hash(std::string const& hash)
{
	_hash = hash;
}

//  -----  URI component selectors  -----

const std::string
uri::href() const
{
	return _URI;
}

const std::string
uri::protocol() const
{
	return _protocol;
}

const std::string
uri::host() const
{
	return _host;
}

const std::string
uri::hostname() const
{
	return _hostname;
}

const std::string
uri::port() const
{
	return _port;
}

const std::string
uri::path() const
{
	return _path;
}

const std::string
uri::pathname() const
{
	return _pathname;
}

const std::string
uri::query() const
{
	return _query;
}

const std::string
uri::hash() const
{
	return _hash;
}

} // served
