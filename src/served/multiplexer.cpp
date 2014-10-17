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

#include <cstring>

#include <served/multiplexer.hpp>
#include <served/mux/matchers.hpp>

namespace served {

//  -----  constructors  -----

multiplexer::multiplexer()
	: _base_path("")
{
}

multiplexer::multiplexer(const std::string & base_path)
	: _base_path(base_path)
{
}

//  -----  plugin injection  -----

void
multiplexer::use_plugin(served_plugin_req_handler plugin)
{
	_plugin_handlers.push_back(plugin);
}

//  -----  path parsing  -----

multiplexer::path_compiled_segments
multiplexer::get_segments(const std::string & path)
{
	// TODO

	path_compiled_segments segments;
	segments.push_back(
		mux::segment_matcher_ptr((mux::segment_matcher *) new mux::empty_matcher())
	);
	return segments;
}

//  -----  http request handlers  -----

void
multiplexer::get(const std::string & path, served_req_handler handler)
{
	_method_handler_candidates[served::method::GET]
		.push_back(path_handler_candidate(get_segments(path), handler));
}

void
multiplexer::head(const std::string & path, served_req_handler handler)
{
	_method_handler_candidates[served::method::HEAD]
		.push_back(path_handler_candidate(get_segments(path), handler));
}

void
multiplexer::post(const std::string & path, served_req_handler handler)
{
	_method_handler_candidates[served::method::POST]
		.push_back(path_handler_candidate(get_segments(path), handler));
}

void
multiplexer::put(const std::string & path, served_req_handler handler)
{
	_method_handler_candidates[served::method::PUT]
		.push_back(path_handler_candidate(get_segments(path), handler));
}

//  -----  server control  -----

void
multiplexer::listen(const std::string & address, const std::string & port)
{
}

void
multiplexer::stop()
{
}

} // served
