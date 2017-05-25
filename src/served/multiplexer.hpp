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

typedef std::function<void(response &, request &)>                        served_plugin_req_handler;
typedef std::function<void(response const &, request const &)>            served_plugin_req_handler_const;

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
	typedef std::vector<served_plugin_req_handler>                                   plugin_handler_list;
	typedef std::vector<served_plugin_req_handler_const>                             plugin_handler_const_list;

	typedef std::vector<served::mux::segment_matcher_ptr>                            path_compiled_segments;
	typedef std::tuple<path_compiled_segments, served::methods_handler, std::string> path_handler_candidate;
	typedef std::vector<path_handler_candidate>                                      path_handler_candidates;

	const std::string       _base_path;
	path_compiled_segments  _base_path_segments;

	path_handler_candidates _handler_candidates;
	plugin_handler_list     _plugin_pre_handlers;
	plugin_handler_const_list     _plugin_post_handlers;

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
	 * Creates a multiplexer with a base path, which is listened for but ignored when selecting
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
	 * Register a plugin that should be called before each request.
	 *
	 * A plugin is a handler called regardless of the request route, this registers a handler
	 * to be called for every request before the actual request handler is called.
	 *
	 * @param plugin the plugin request handler
	 */
	void use_before(served_plugin_req_handler plugin);

	/*
	 * Register a plugin that should be called after each request.
	 *
	 * A plugin is a handler called regardless of the request route, this registers a handler
	 * to be called for every request after the actual request handler is called.
	 *
	 * @param plugin the plugin request handler
	 */
	void use_after (served_plugin_req_handler_const plugin);

	//  -----  http request handlers  -----

	/*
	 * Registers a handler for a specific HTTP endpoint.
	 *
	 * Returns an object used to specify request handlers per HTTP method for the endpoint.
	 *
	 * @param path the endpoint path to register handlers for
	 * @param info an optional summary of the resource of this endpoint
	 *
	 * @return returns a methods_handler used to specify handlers per HTTP method
	 */
	served::methods_handler & handle(const std::string & path, const std::string info = "");

	//  ----- request forwarding  -----

	/*
	 * Forwards a response and request object to a registered handler.
	 *
	 * Based on the URI target of the request object, forwards the request and response objects to
	 * an appropriate handler for producing a response. Always chooses the first registered match.
	 *
	 * @param res object used to generate an HTTP response
	 * @param req object containing information about the HTTP request
	 */
	void forward_to_handler(served::response & res, served::request & req);

	/*
	 * Triggers any post request handling work to be done.
	 *
	 * All post request handling work, such as post request plugin handler calls, is done via this
	 * call, and should be made by the server after forwarding a request object.
	 *
	 * @param res object used to generate an HTTP response
	 * @param req object containing information about the HTTP request
	 */
	void on_request_handled(served::response & res, served::request & req);

	//  -----  accessors  -----

	/*
	 * Constructs a full list of all endpoints registered.
	 *
	 * Registered endpoints contain a list of HTTP methods supported and an optional summary of the
	 * resource each endpoint represents.
	 *
	 * @return a list of all endpoints registered
	 */
	const served_endpoint_list get_endpoint_list();

	/*
	 * Creates a request handler that lists all registered handlers in YAML format.
	 *
	 * A handler is created that is bound to the multiplexer, and when called will generate a YAML
	 * list of all registered endpoints of the multiplexer.
	 *
	 * @return the handler for listing endpoints in YAML, can be registered at an endpoint
	 */
	 served_req_handler get_endpoint_list_handler_YAML();

private:
	//  -----  request handling  -----

	/*
	 * This is the actual request handler. It searches registered handlers for a match and, if
	 * found, calls that handler with the request and response objects.
	 *
	 * @param res object used to generate an HTTP response
	 * @param req object containing information about the HTTP request
	 */
	 void handler(served::response & res, served::request & req);

	//  -----  path parsing/compiling  -----

	/*
	 * Splits and compiles a path into segments.
	 *
	 * A request path is compiled into segments in order to accomodate for various path matching
	 * strategies, such as static, variable and regex. The compiled path is returned as a list of
	 * segments.
	 *
	 * @param path the endpoint path to be compiled
	 *
	 * @return the compiled list of path segments for matching
	 */
	path_compiled_segments get_segments(const std::string & path);
};

} // served

#endif // SERVED_MULTIPLEXER_HPP
