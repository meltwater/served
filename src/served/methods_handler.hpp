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

#ifndef SERVED_METHODS_HANDLER_HPP
#define SERVED_METHODS_HANDLER_HPP

#include <map>
#include <vector>
#include <functional>
#include <served/methods.hpp>
#include <served/request.hpp>
#include <served/response.hpp>

namespace served {

typedef std::function<void(response &, const request &)>  served_req_handler;
typedef std::tuple<std::string, std::vector<std::string>> served_method_list;
typedef std::map<std::string, served_method_list>         served_endpoint_list;

/*
 * Represents a single endpoint with various HTTP method handlers.
 *
 * The methods handler contains a list of request handlers, separated by HTTP method, for a single
 * endpoint, and provides a convenient interface for specifying new request handlers.
 *
 * A method handler is returned when handle has been called on a multiplexer, and should then be
 * used for daisy chaining calls until all method handlers are specified.
 */
class methods_handler
{
	std::string                                  _path;
	std::string                                  _info;
	std::map<served::method, served_req_handler> _handlers;

public:
	//  -----  constructors  -----

	/*
	 * Create a methods_handler from an endpoint path and summary.
	 *
	 * The endpoint path should be the raw path used when registering a handler. The info param is
	 * optional, but should be a short summary of the resource this endpoint points to and is
	 * exposed when obtaining a list of registered endpoints from the multiplexer.
	 *
	 * @param path the endpoint path of this handler
	 * @param info a short summary of the resource
	 */
	explicit methods_handler(const std::string path, const std::string info = "");

	//  -----  method registering  -----

	/*
	 * Used to specify a handler for a GET HTTP method at this endpoint.
	 *
	 * @param handler the handler to be called for this HTTP method
	 *
	 * @return chainable methods_handler reference to *this
	 */
	methods_handler & get (served_req_handler handler);

	/*
	 * Used to specify a handler for a POST HTTP method at this endpoint.
	 *
	 * @param handler the handler to be called for this HTTP method
	 *
	 * @return chainable methods_handler reference to *this
	 */
	methods_handler & post(served_req_handler handler);

	/*
	 * Used to specify a handler for a HEAD HTTP method at this endpoint.
	 *
	 * @param handler the handler to be called for this HTTP method
	 *
	 * @return chainable methods_handler reference to *this
	 */
	methods_handler & head(served_req_handler handler);

	/*
	 * Used to specify a handler for a PUT HTTP method at this endpoint.
	 *
	 * @param handler the handler to be called for this HTTP method
	 *
	 * @return chainable methods_handler reference to *this
	 */
	methods_handler & put (served_req_handler handler);

	/*
	 * Used to specify a handler for a DELETE HTTP method at this endpoint.
	 *
	 * @param handler the handler to be called for this HTTP method
	 *
	 * @return chainable methods_handler reference to *this
	 */
	methods_handler & del (served_req_handler handler);

	/*
	 * Used to specify a handler for a specific HTTP method at this endpoint.
	 *
	 * @param method the HTTP method that a handler should be called for
	 * @param handler the handler to be called for this HTTP method
	 *
	 * @return chainable methods_handler reference to *this
	 */
	methods_handler & method(const served::method method, served_req_handler handler);

	/*
	 * Indicates whether a specific HTTP method has a handler registered for this endpoint.
	 *
	 * @param method the method to check
	 *
	 * @return true if the method is supported, otherwise false.
	 */
	bool method_supported(const served::method method) const
	{
		return ( _handlers.find(method) != _handlers.end() );
	}

	/*
	 * An operator for acquiring a reference to a handler for a method.
	 *
	 * @param method the HTTP method we want the handler for
	 *
	 * @return request handler associated with the given method
	 */
	served_req_handler operator[](const served::method method)
	{
		return _handlers[method];
	}

	//  -----  endpoint propagation  -----

	/*
	 * Populates an endpoint list with registered handlers.
	 *
	 * Adds the registered endpoint, a list of methods supported and, if provided, a summary of this
	 * endpoint to the provided list.
	 *
	 * @param endpoints the list of endpoints that should be populated with information
	 */
	void propagate_endpoint(served_endpoint_list & endpoints) const;
};

} // served

#endif // SERVED_METHODS_HANDLER_HPP
