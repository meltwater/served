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
	d_request.set_header(header, val);
}

request_parser_impl::status_type
request_parser_impl::parse(const char *data, size_t len)
{
	if ( d_status == status_type::READ_HEADER )
	{
		size_t d_len = execute(data, len);
		request_parser::status status = get_status();

		if ( request_parser::FINISHED == status )
		{
			d_body_expected = expecting_body();

			if ( requested_continue() )
			{
				if ( 0 == d_body_expected )
				{
					d_status = request_parser_impl::ERROR;
				}
				else
				{
					d_status = request_parser_impl::EXPECT_CONTINUE;
				}
			}
			else if ( 0 != d_body_expected )
			{
				d_status = request_parser_impl::READ_BODY;
				parse_body(data + d_len, len - d_len);
			}
			else
			{
				d_status = request_parser_impl::FINISHED;
			}
		}
		else if ( request_parser::ERROR == status )
		{
			d_status = request_parser_impl::ERROR;
		}
	}
	else if ( d_status == status_type::EXPECT_CONTINUE
	       || d_status == status_type::READ_BODY       )
	{
		parse_body(data, len);
	}

	return d_status;
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
	// NOTE: Body parsing instigated in "parse"
}

bool
request_parser_impl::requested_continue()
{
	return d_request.header("expect") == "100-continue";
}

size_t
request_parser_impl::expecting_body()
{
	switch (d_request.method())
	{
	case method::PUT:
	case method::POST:
	{
		std::string type   = d_request.header("content-type");
		std::string length = d_request.header("content-length");

		// TODO: Better validation here
		if ( !type.empty() && !length.empty() )
		{
			size_t len = 0;
			try
			{
				len = std::stoi(length);
			}
			catch (...) {}

			return len;
		}
		break;
	}
	default:
		break;
	}
	return 0;
}

request_parser_impl::status_type
request_parser_impl::parse_body(const char *data, size_t len)
{
	if ( len > d_body_expected )
	{
		len = d_body_expected;
	}

	d_body_stream.write(data, len);
	d_body_expected -= len;

	if ( 0 == d_body_expected )
	{
		d_request.set_body(d_body_stream.str());
		d_body_stream.str(std::string());
		d_status = status_type::FINISHED;
	}
	else
	{
		d_status = status_type::READ_BODY;
	}

	return d_status;
}

} // served
