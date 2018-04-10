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

#include <served/mux/regex_matcher.hpp>
#include <stdexcept>

namespace served { namespace mux {

//  -----  constructors  -----

regex_matcher::regex_matcher(const std::string & variable_name, const std::string & regex)
	: _variable_name(variable_name)
	, _regex(regex)
{ }

//  -----  matching logic  -----

bool
regex_matcher::check_match(const std::string & path_segment)
{
    return std::regex_match(path_segment, _regex);
}

//  -----  REST param collecting  -----

void
regex_matcher::get_param(served::parameters & params, const std::string & path_segment)
{
	if ( ! _variable_name.empty() )
	{
		params[_variable_name] = path_segment;
	}
}

} } // mux, served
