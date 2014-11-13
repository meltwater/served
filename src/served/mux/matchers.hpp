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

#ifndef SERVED_MATCHERS_HPP
#define SERVED_MATCHERS_HPP

#include <string>

#include <served/mux/segment_matcher.hpp>
#include <served/mux/empty_matcher.hpp>
#include <served/mux/static_matcher.hpp>
#include <served/mux/regex_matcher.hpp>
#include <served/mux/variable_matcher.hpp>

namespace served { namespace mux {

/*
 * Compiles a segment of path into a matchable segment object.
 *
 * @param path_segment the segment of path to compile
 */
inline segment_matcher_ptr
compile_to_matcher(const std::string & path_segment)
{
	if ( path_segment.empty() )
	{
		return segment_matcher_ptr(new empty_matcher());
	}
	if ( path_segment[0] == '{' && path_segment[path_segment.length() - 1] == '}' )
	{
		std::string trimmed_segment(path_segment.substr(1, path_segment.length() - 2));
		size_t colon_index = trimmed_segment.find(':');
		if ( colon_index == std::string::npos )
		{
			return segment_matcher_ptr(
				new variable_matcher(trimmed_segment)
			);
		}
		return segment_matcher_ptr(
			new regex_matcher(
				trimmed_segment.substr(0, colon_index),
				trimmed_segment.substr(colon_index + 1, std::string::npos)
			));
	}
	return segment_matcher_ptr(new static_matcher(path_segment));
}

} }

#endif // SERVED_MATCHERS_HPP
