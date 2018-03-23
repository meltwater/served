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

#include <served/status.hpp>
#include <served/request_error.hpp>
#include <served/multiplexer.hpp>
#include <served/mux/matchers.hpp>

namespace served {

//  -----  constructors  -----

multiplexer::multiplexer()
	: _base_path("")
	, _base_path_segments()
{
}

multiplexer::multiplexer(const std::string & base_path)
	: _base_path(base_path)
	, _base_path_segments(get_segments(_base_path))
{
}

//  -----  plugin injection  -----

void
multiplexer::use_before(served_plugin_req_handler plugin)
{
	_plugin_pre_handlers.push_back(plugin);
}

void
multiplexer::use_after(served_plugin_req_handler plugin)
{
	_plugin_post_handlers.push_back(plugin);
}

void
multiplexer::use_wrapper(served_plugin_req_wrapper plugin)
{
	_plugin_wrappers.push_back(plugin);
}

//  -----  path parsing  -----

std::vector<std::string>
split_path(const std::string & path)
{
	std::vector<std::string> chunks;

	const char * path_ptr = path.c_str();
	const size_t path_len = path.length();

	char * const tmp = new char[path.length()];
	char * end = tmp;

	const char * const eol = path_ptr + path_len;

	for (; path_ptr < eol; ++path_ptr)
	{
		if ( '/' ==  *path_ptr )
		{
			if ( end != tmp )
			{
				chunks.push_back(std::string(tmp, end));
				end = tmp;
			}
		}
		else
		{
			*end++ = *path_ptr;
		}
	}

	if ( end != tmp )
	{
		chunks.push_back(std::string(tmp, end));
	}
	else if ( '/' == path[path.length() - 1] )
	{
		// Push back an empty string for paths ending in /
		chunks.push_back("");
	}
	delete[] tmp;
	return chunks;
}

multiplexer::path_compiled_segments
multiplexer::get_segments(const std::string & path)
{
	path_compiled_segments segments;

	for ( const auto & chunk : split_path(path) )
	{
		segments.push_back(mux::compile_to_matcher(chunk));
	}

	return segments;
}

//  -----  http request handlers  -----

served::methods_handler &
multiplexer::handle(const std::string & path, const std::string info /* = "" */)
{
	// Remove any duplicates.
	for ( auto it = _handler_candidates.begin(); it != _handler_candidates.end(); )
	{
		if ( std::get<2>(*it) == path )
		{
			it = _handler_candidates.erase(it);
		}
		else
		{
			++it;
		}
	}

	_handler_candidates.push_back(
		path_handler_candidate(get_segments(path), served::methods_handler(_base_path + path, info), path));

	return std::get<1>(_handler_candidates.back());
}

void
multiplexer::handler(served::response & res, served::request & req)
{
	bool pattern_matched = false;

	// Default to OK empty response
	res.set_status(status_2XX::OK);
	res.set_body("");

	// Iterate plugin pre request handlers
	for ( const auto & handler : _plugin_pre_handlers )
	{
		handler(res, req);
	}

	// Split request path into segments
	auto   request_segments = split_path(req.url().path());
	size_t r_size           = request_segments.size();

	// If a base path was specified check for a match
	const size_t b_size = _base_path_segments.size();
	if ( 0 != b_size )
	{
		if ( b_size > r_size )
		{
			throw served::request_error(served::status_4XX::NOT_FOUND, "Path not found");
		}

		// Check if each segment matches
		size_t seg_index = 0;
		for ( ; seg_index < b_size; seg_index++ )
		{
			if ( ! _base_path_segments[seg_index]->check_match(request_segments[seg_index]) )
			{
				throw served::request_error(served::status_4XX::NOT_FOUND, "Path not found");
			}
		}

		// Collect parameters from REST path segments
		for ( seg_index = 0; seg_index < b_size; seg_index++ )
		{
			_base_path_segments[seg_index]->get_param(req.params, request_segments[seg_index]);
		}

		request_segments.erase(request_segments.begin(), request_segments.begin() + b_size);
		r_size = request_segments.size();
	}

	// For each candidate
	for ( const auto & candidate : _handler_candidates )
	{
		// Get its segments
		const auto & handler_segments = std::get<0>(candidate);
		const size_t h_size           = handler_segments.size();

		// If the candidate segment count is lower than the pattern then skip
		if ( h_size > r_size )
		{
			continue;
		}

		// Check if each segment matches
		size_t seg_index = 0;
		for ( ; seg_index < h_size; seg_index++ )
		{
			if ( ! handler_segments[seg_index]->check_match(request_segments[seg_index]) )
			{
				break;
			}
		}

		// If all segments were matched then we have our chosen candidate
		if ( seg_index == h_size )
		{
			pattern_matched = true;

			// Check that the request method is supported by this candidate
			auto method_handler = std::get<1>(candidate);
			if ( ! method_handler.method_supported( req.method() ) )
			{
				throw served::request_error(served::status_4XX::METHOD_NOT_ALLOWED, "Method not allowed");
			}

			// Collect parameters from REST path segments
			for ( seg_index = 0; seg_index < h_size; seg_index++ )
			{
				handler_segments[seg_index]->get_param(req.params, request_segments[seg_index]);
			}

			method_handler[ req.method() ](res, req);

			break;
		}
	}

	// If no candidates were matched then we throw a 404
	if ( ! pattern_matched )
	{
		throw served::request_error(served::status_4XX::NOT_FOUND, "Path not found");
	}
}

//  -----  request forwarding  -----

void
multiplexer::forward_to_handler(served::response & res, served::request & req)
{
	if ( _plugin_wrappers.size() > 0 )
	{
		unsigned int wrapper_index = 0;
		std::function<void()> iterate_wrappers = [&]() {
			if ( wrapper_index == _plugin_wrappers.size() )
			{
				handler(res, req);
			}
			else
			{
				auto wrapper = _plugin_wrappers[wrapper_index];
				wrapper_index++;
				wrapper(res, req, iterate_wrappers);
			}
		};
		iterate_wrappers();
	}
	else
	{
		handler(res, req);
	}
}

void
multiplexer::on_request_handled(served::response & res, served::request & req)
{
	for ( const auto & handler : _plugin_post_handlers )
	{
		handler(res, req);
	}
}

//  -----  accessors  -----

const served_endpoint_list
multiplexer::get_endpoint_list()
{
	served_endpoint_list list;
	for ( const auto & handler : _handler_candidates )
	{
		std::get<1>(handler).propagate_endpoint(list);
	}
	return list;
}

served_req_handler
multiplexer::get_endpoint_list_handler_YAML()
{
	return [this](served::response & res, const served::request & req) {
		(void) req;
	    res.set_header("Content-Type", "text/yaml");

		res << "%YAML 1.2\n---";

		auto endpoint_list = this->get_endpoint_list();

		for ( const auto & endpoint : endpoint_list )
		{
			res << "\n-";
			res << "\n\tendpoint: " << endpoint.first;

			const std::string summary = std::get<0>(endpoint.second);
			if ( summary.length() > 0 )
			{
				res << "\n\tsummary: " << summary;
			}

			res << "\n\tmethods:";
			for ( const auto & method : std::get<1>(endpoint.second) )
			{
				res << "\n\t\t- " << method;
			}
		}
	};
}

} // served
