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
 * Single line class summary.
 *
 * Describe the abstraction this class represents in detail. What are its primary
 * responsibilities?
 *
 * Describe typical usage scenario(s).
 *
 * Describe any design assumptions.
 */
class methods_handler
{
	const std::string                            _path;
	const std::string                            _info;
	std::map<served::method, served_req_handler> _handlers;

public:
	//  -----  constructors  -----

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @param path ...
	 * @param info ...
	 */
	methods_handler(const std::string path, const std::string info = "");

	//  -----  method registering  -----

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @param handler ...
	 *
	 * @return chainable methods_handler reference to *this
	 */
	methods_handler & get (served_req_handler handler);

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @param handler ...
	 *
	 * @return chainable methods_handler reference to *this
	 */
	methods_handler & post(served_req_handler handler);

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @param handler ...
	 *
	 * @return chainable methods_handler reference to *this
	 */
	methods_handler & head(served_req_handler handler);

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @param handler ...
	 *
	 * @return chainable methods_handler reference to *this
	 */
	methods_handler & put (served_req_handler handler);

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @param handler ...
	 *
	 * @return chainable methods_handler reference to *this
	 */
	methods_handler & del (served_req_handler handler);

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @param method ...
	 * @param handler ...
	 *
	 * @return chainable methods_handler reference to *this
	 */
	methods_handler & method(const served::method method, served_req_handler handler);

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @param method ...
	 *
	 * @return true if the method is support, otherwise false
	 */
	bool method_supported(const served::method method) const
	{
		return ( _handlers.find(method) != _handlers.end() );
	}

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @param method ...
	 *
	 * @return request handler associated with the given method
	 */
	served_req_handler operator[](const served::method method)
	{
		return _handlers[method];
	}

	//  -----  endpoint propagation  -----

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * @param endpoints ...
	 */
	void propagate_endpoint(served_endpoint_list & endpoints) const;
};

} // served

#endif // SERVED_METHODS_HANDLER_HPP
