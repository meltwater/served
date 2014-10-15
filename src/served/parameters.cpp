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

#include <served/parameters.hpp>

namespace served {

//  -----  parameter setting  -----

std::string &
parameters::operator[](std::string const& key)
{
	return _list[key];
}

void
parameters::set(std::string const& key, std::string const& value)
{
	_list[key] = value;
}

//  -----  parameter accessors  -----

const std::string
parameters::operator[](std::string const& key) const
{
	auto it = _list.find(key);
	if ( it != _list.end() )
	{
		return it->second;
	}
	return std::string();
}

const std::string
parameters::get(std::string const& key) const
{
	auto it = _list.find(key);
	if ( it != _list.end() )
	{
		return it->second;
	}
	return std::string();
}

} // served
