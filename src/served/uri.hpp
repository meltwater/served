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

#ifndef SERVED_URI_HPP
#define SERVED_URI_HPP

#include <string>

namespace served {

/*
 * Represents a URI (Uniform Resource Identifier).
 *
 * A URI consists of several parts, including the path, the query and the
 * fragment. This class represents a URI as a struct containing these parts,
 * with appropriate interface to get access to each of the parts.
 *
 * The URI may be used to represent a part of a HTTP request. Typically served
 * will create a URI when it parses a request out of convenience for the user.
 *
 * The URI class does not itself provide URL escaping, however separate methods
 * are provided which will enable the user to escape / unescape as required.
 */
class uri
{
public:
	//  -----  URI component mutators  -----

	/*
	 * Set the full URI string
	 *
	 * @param uri the full uri as a string
	 */
	void set_URI(std::string const& uri);

	/*
	 * Set the URI path string
	 *
	 * @param the uri path string
	 */
	void set_path(std::string const& path);

	/*
	 * Set the URI query string
	 *
	 * @param query the uri query string
	 */
	void set_query(std::string const& query);

	/*
	 * Set the URI fragment string
	 *
	 * @param fragment the uri fragment string
	 */
	void set_fragment(std::string const& fragment);

	//  -----  URI component selectors  -----

	/*
	 * For uri: "/foo/bar?test=one#element"
	 *
	 * "/foo/bar?test=one"
	 *
	 * @return the full uri
	 */
	const std::string URI() const;

	/*
	 * For uri: "/foo/bar?test=one#element"
	 *
	 * "/foo/bar"
	 *
	 * @return the uri path
	 */
	const std::string path() const;

	/*
	 * For uri: "/foo/bar?test=one#element"
	 *
	 * "test=one"
	 *
	 * @return the uri query
	 */
	const std::string query() const;

	/*
	 * For uri: "/foo/bar?test=one#element"
	 *
	 * "element"
	 *
	 * @return the uri fragment
	 */
	const std::string fragment() const;

private:
	std::string _uri;
	std::string _path;
	std::string _query;
	std::string _fragment;
};

/*
 * URL-encode a string.
 *
 * This method will escape special characters with % symbols to conform to the
 * HTTP URL encoding scheme.
 *
 * @param s the input string to encode
 *
 * @return the encoded input string
 */
std::string query_escape(const std::string& s);

/*
 * URL-decode a string.
 *
 * This method will unescape special characters with % symbols that conform to
 * the HTTP URL encoding scheme.
 *
 * @param s the input string to decode
 *
 * @return the decoded input string
 */
std::string query_unescape(const std::string& s);

} // served

#endif // SERVED_URI_HPP
