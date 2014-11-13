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

#ifndef SERVED_PARAMS_HPP
#define SERVED_PARAMS_HPP

#include <unordered_map>
#include <string>

namespace served {

/*
 * Represents a collection of named parameters passed via the request URI.
 *
 * This class represents named parameters defined by the user when registering
 * method handlers in a multiplexer.
 *
 * When the multiplexer matches a method handler, the parsed parameters are
 * stored in an instance of this object which is then passed to the handler via
 * the request object.
 *
 * Parameters are stored in a hash map.
 */
class parameters
{
	typedef std::unordered_map<std::string, std::string> parameter_list;

	parameter_list _list;

public:
	//  -----  parameter setting  -----

	/*
	 * Accesses a parameter based on a key.
	 *
	 * The reference to the parameter is returned and can be modified through this operator. If the
	 * key does not yet exist then it is created.
	 *
	 * @param key the key of the parameter
	 *
	 * @return the parameter stored under the key
	 */
	std::string & operator[](std::string const& key);

	/*
	 * Set a parameter.
	 *
	 * @param key the key to store the parameter under
	 * @param value the value of the parameter
	 */
	void set(std::string const& key, std::string const& value);

	//  -----  parameter accessors  -----

	/*
	 * Obtain the value of a parameter.
	 *
	 * @param key the key of the parameter
	 *
	 * @return the value of the parameter, or an empty string if the key is not matched.
	 */
	const std::string operator[](std::string const& key) const;

	/*
	 * Obtain the value of a parameter.
	 *
	 * @param key the key of the parameter
	 *
	 * @return the value of the parameter, or an empty string if the key is not matched.
	 */
	const std::string get(std::string const& key) const;
};

} // served

#endif // SERVED_PARAMS_HPP
