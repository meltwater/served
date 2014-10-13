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

#include "uri.hpp"

namespace served {

uri::uri(std::string const& URI)
	: _URI(URI)
{
	// TODO: Parse URI into components
}

std::string
uri::href() const
{
	return _URI;
}

std::string
uri::protocol() const
{
	return _protocol;
}

std::string
uri::host() const
{
	return _host;
}

std::string
uri::hostname() const
{
	return _hostname;
}

std::string
uri::port() const
{
	return _port;
}

std::string
uri::path() const
{
	return _path;
}

std::string
uri::pathname() const
{
	return _pathname;
}

std::string
uri::query() const
{
	return _query;
}

std::string
uri::hash() const
{
	return _hash;
}

} // served
