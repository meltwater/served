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

#ifndef SERVED_REQUEST_HPP
#define SERVED_REQUEST_HPP

#include <string>
#include <unordered_map>

#include <served/methods.hpp>
#include <served/uri.hpp>
#include <served/parameters.hpp>

namespace served {

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
class request
{
	// Appropriate map type for request may differ from response
	typedef std::unordered_map<std::string, std::string>    header_list;

	enum method _method;
	uri         _destination;
	std::string _HTTP_version;
	std::string _source;
	header_list _headers;
	std::string _body;

public:
	//  -----  mutators  -----

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	void set_method      (const enum method & method);

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	void set_destination (const uri         & destination);

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	void set_HTTP_version(const std::string & http_version);

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	void set_source      (const std::string & source);

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	void set_header      (const std::string & header, const std::string & value);

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	void set_body        (const std::string & body);

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	uri & url();

	//  -----  component accessors  -----

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	const enum method method() const;

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	const uri         url() const;

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	const std::string HTTP_version() const;

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	const std::string source      () const;

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	const std::string header(std::string const& header) const;

	/*
	 * Describe the method in a single line.
	 *
	 * Describe the work this method does, what does it do? Is there anything
	 * the developer should be aware of?
	 *
	 * List each parameter, what is the purpose? What is considered valid / 
	 * invalid?
	 */
	const std::string body  () const;

public:
	//  -----  public members  -----

	parameters params;
};

} // served

#endif // SERVED_REQUEST_HPP
