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

#include <served/request_parser_impl.hpp>
#include <served/methods.hpp>

#include <algorithm>

namespace served {

void
request_parser_impl::http_field( const char * data
                               , const char * field
                               , size_t       flen
                               , const char * value
                               , size_t       vlen  )
{
	std::string header(field, flen), val(value, vlen);

	std::string mut_header;
	mut_header.resize(flen);

	std::transform(header.begin(), header.end(), mut_header.begin(), ::tolower);

	if ( mut_header == "expect" )
	{
		if ( val == "100-continue" )
		{
			d_expected = expect_type::CONTINUE;
		}
	}
	else
	{
		d_request.set_header(header, val);
	}
}

std::tuple<request_parser::status, size_t>
request_parser_impl::parse(const char *data, size_t len)
{
	size_t d_len = execute(data, len);
	return std::tuple<request_parser::status, size_t>(get_status(), d_len);
}


request_parser_impl::expect_type
request_parser_impl::get_expected()
{
	return d_expected;
}

void
request_parser_impl::set_expected(expect_type expected)
{
	d_expected = expected;
}

void
request_parser_impl::request_method( const char * data
                                   , const char * at
                                   , size_t       length )
{
	d_request.set_method(method_from_string(std::string(at, length)));
}

void
request_parser_impl::request_uri( const char * data
                                , const char * at
                                , size_t       length )
{
	d_request.url().set_URI(std::string(at, length));
}

void
request_parser_impl::fragment( const char * data
                             , const char * at
                             , size_t       length )
{
	d_request.url().set_fragment(std::string(at, length));
}

void
request_parser_impl::request_path( const char * data
                                 , const char * at
                                 , size_t       length )
{
	d_request.url().set_path(std::string(at, length));
}

void
request_parser_impl::query_string( const char * data
                                 , const char * at
                                 , size_t       length )
{
	d_request.url().set_query(std::string(at, length));
}

void
request_parser_impl::http_version( const char * data
                                 , const char * at
                                 , size_t       length )
{
	d_request.set_HTTP_version(std::string(at, length));
}

void
request_parser_impl::header_done( const char * data
                                , const char * at
                                , size_t       length )
{
	d_request.set_body(std::string(at, length));
}

} // served
