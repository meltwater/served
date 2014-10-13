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

#ifndef SERVED_COOKIE_HPP
#define SERVED_COOKIE_HPP

#include <string>

namespace served {

class cookie
{
public:
	//  -----  constructors  -----

	cookie(
	        std::string const& name
	      , std::string const& value
	      , std::string const& domain      = ""
	      , std::string const& expires     = ""
	      , int                max_age     = 0
	      , bool               secure_only = false
	      , bool               http_only   = false
	);

    //  -----  mutators  -----

	void set_name       (std::string const& name);
	void set_value      (std::string const& value);
	void set_domain     (std::string const& domain);
	void set_expires    (std::string  const& expires);
	void set_max_age    (int max_age); // RFC 1123
	void set_secure_only(bool secure_only);
	void set_http_only  (bool http_only);

    //  -----  component accessors  -----

	const std::string name   () const;
	const std::string value  () const;
	const std::string domain () const;
	const std::string expires() const;

	int max_age() const;

	bool secure_only() const;
	bool http_only  () const;

private:
	std::string _name;
	std::string _value;
	std::string _domain;
	std::string _expires;
	int         _max_age;
    bool        _secure_only;
    bool        _http_only;
};

} // served

#endif // SERVED_COOKIE_HPP
