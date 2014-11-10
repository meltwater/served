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

#ifndef SERVED_PATH_REGEX_MATCHER_HPP
#define SERVED_PATH_REGEX_MATCHER_HPP

#include <string>

#include <re2/re2.h>

#include <served/mux/segment_matcher.hpp>

namespace served { namespace mux {

/*
 * Single line class summary.
 *
 * Describe the abstraction this class represents in detail. What are its primary
 * responsibilities?
 *
 * Describe typical usage scenario(s).
 *
 * Describe any design assumptions.
 */
class regex_matcher : public segment_matcher
{
	const std::string _variable_name;
	re2::RE2          _regex;

public:
	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	explicit regex_matcher(const std::string & variable_name, const std::string & regex);

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	virtual bool check_match(const std::string & path_segment) override;

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	virtual void get_param(served::parameters & params, const std::string & path_segment) override;
};

} } // mux, served

#endif // SERVED_PATH_REGEX_MATCHER_HPP
