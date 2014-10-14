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

#include <served/cookie.hpp>

namespace served {

cookie::cookie(
	    std::string const& name
	  , std::string const& value
	  , std::string const& domain
	  , std::string const& expires
	  , int                max_age
	  , bool               secure_only
	  , bool               http_only
)
	: _name(name)
	, _value(value)
	, _domain(domain)
	, _expires(expires)
	, _max_age(max_age)
	, _secure_only(secure_only)
	, _http_only(http_only)
{
}

//  -----  mutators  -----

void
cookie::set_name(std::string const& name)
{
	_name = name;
}

void
cookie::set_value(std::string const& value)
{
	_value = value;
}

void
cookie::set_domain(std::string const& domain)
{
	_domain = domain;
}

void
cookie::set_expires(std::string  const& expires)
{
	_expires = expires;
}

void
cookie::set_max_age(int max_age)
{
	_max_age = max_age;
}

void
cookie::set_secure_only(bool secure_only)
{
	_secure_only = secure_only;
}

void
cookie::set_http_only(bool http_only)
{
	_http_only = http_only;
}

//  -----  component accessors  -----

const std::string
cookie::name() const
{
	return _name;
}

const std::string
cookie::value() const
{
	return _value;
}

const std::string
cookie::domain() const
{
	return _domain;
}

const std::string
cookie::expires() const
{
	return _expires;
}

int
cookie::max_age() const
{
	return _max_age;
}

bool
cookie::secure_only() const
{
	return _secure_only;
}

bool
cookie::http_only() const
{
	return _http_only;
}

} // served
