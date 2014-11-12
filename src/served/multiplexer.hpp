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

#ifndef SERVED_MULTIPLEXER_HPP
#define SERVED_MULTIPLEXER_HPP

#include <map>
#include <tuple>
#include <vector>
#include <functional>
#include <served/methods.hpp>
#include <served/methods_handler.hpp>
#include <served/request.hpp>
#include <served/response.hpp>
#include <served/mux/segment_matcher.hpp>

namespace served {

typedef std::function<void(response &, request &)> served_plugin_req_handler;

/*
 * Used to register endpoint handlers.
 *
 * The multiplexer is used by a served HTTP server to determine which handler should be used to
 * resolve an HTTP request based on the target endpoint and the HTTP method of the request.
 *
 * A multiplexer is required by the served HTTP server and should be fully configured before
 * the server is run with all endpoints registered.
 *
 * The multiplexer must not be modified after running the HTTP server, as its internal components
 * will be accessible to all HTTP threads.
 */
class multiplexer
{
	typedef std::vector<served_plugin_req_handler>                      plugin_handler_list;

	typedef std::vector<served::mux::segment_matcher_ptr>               path_compiled_segments;
	typedef std::tuple<path_compiled_segments, served::methods_handler> path_handler_candidate;
	typedef std::vector<path_handler_candidate>                         path_handler_candidates;

	const std::string       _base_path;
	path_compiled_segments  _base_path_segments;

	path_handler_candidates _handler_candidates;
	plugin_handler_list     _plugin_pre_handlers;
	plugin_handler_list     _plugin_post_handlers;

public:
	//  -----  constructors  -----

	/*
	 * Default constructor for the mutliplexer.
	 *
	 * Creates a clean multiplexer, ready for endpoint registering.
	 */
	multiplexer();

	/*
	 * Constructor for the multiplexer with base path.
	 *
	 * Adds a base path to the multiplexer, which is listened for but ignored when selecting
	 * handlers.
	 *
	 * For example: with a base path "/base" and handler registered at "/foo/bar"
	 * the handler will be called for a request at "/base/foo/bar".
	 *
	 * @param base_path the base path that all registered endpoints are appended to.
	 */
	explicit multiplexer(const std::string & base_path);

	//  -----  plugin injection  -----

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @param plugin ...
	 */
	void use_before(served_plugin_req_handler plugin);

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @param plugin ...
	 */
	void use_after (served_plugin_req_handler plugin);

	//  -----  http request handlers  -----

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @param path ...
	 * @param info ...
	 *
	 * @return ...
	 */
	served::methods_handler & handle(const std::string & path, const std::string info = "");

	//  ----- request forwarding  -----

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @param res ...
	 * @param req ...
	 */
	void forward_to_handler(served::response & res, served::request & req);

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @param res ...
	 * @param req ...
	 */
	void on_request_handled(served::response & res, served::request & req);

	//  -----  accessors  -----

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @return ...
	 */
	const served_endpoint_list get_endpoint_list();

	/*
	 * Creates a request handler that lists registered handlers in YAML format.
	 *
	 * A handler is created that is bound to the multiplexer, and when called will generate a YAML
	 * list of all registered endpoints.
	 *
	 * @return the handler for listing endpoints in YAML
	 */
	 served_req_handler get_endpoint_list_handler_YAML();

private:
	//  -----  path parsing/compiling  -----

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @param path ...
	 *
	 * @return ...
	 */
	path_compiled_segments get_segments(const std::string & path);
};

} // served

#endif // SERVED_MULTIPLEXER_HPP
