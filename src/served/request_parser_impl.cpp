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
#include <string>

namespace served {

void
request_parser_impl::http_field( const char *
                               , const char * field
                               , size_t       flen
                               , const char * value
                               , size_t       vlen  )
{
	std::string header(field, flen), val(value, vlen);

	/* If multiple matching header field names are sent these must be safe to append via comma
	 * ref: (http://www.w3.org/Protocols/rfc2616/rfc2616-sec4.html#sec4.2)
	 */
	std::string existing = _request.header(header);
	if ( !existing.empty() )
	{
		val = existing + "," + val;
	}

	_request.set_header(header, val);
}

request_parser_impl::status_type
request_parser_impl::parse(const char *data, size_t len)
{
	_bytes_parsed += len;

	if ( _max_req_size_bytes > 0 && _bytes_parsed > _max_req_size_bytes )
	{
		_status = request_parser_impl::REJECTED_REQUEST_SIZE;
	}
	else if ( _status == status_type::READ_HEADER )
	{
		size_t extra_len = 0;
		try
		{
			extra_len = execute(data, len);
		}
		catch (...)
		{
			_status = status_type::ERROR;
			return _status;
		}

		request_parser::status status = get_status();

		if ( request_parser::FINISHED == status )
		{
			_body_expected = expecting_body();

			if ( requested_continue() )
			{
				if ( 0 == _body_expected )
				{
					_status = request_parser_impl::ERROR;
				}
				else
				{
					_status = request_parser_impl::EXPECT_CONTINUE;
				}
			}
			else if ( 0 != _body_expected )
			{
				_status = request_parser_impl::READ_BODY;
				parse_body(data + extra_len, len - extra_len);
			}
			else
			{
				_status = request_parser_impl::FINISHED;
			}
		}
		else if ( request_parser::ERROR == status )
		{
			_status = request_parser_impl::ERROR;
		}
	}
	else if ( _status == status_type::EXPECT_CONTINUE
	       || _status == status_type::READ_BODY       )
	{
		parse_body(data, len);
	}

	return _status;
}

void
request_parser_impl::request_method( const char *
                                   , const char * at
                                   , size_t       length )
{
	_request.set_method(method_from_string(std::string(at, length)));
}

void
request_parser_impl::request_uri( const char *
                                , const char * at
                                , size_t       length )
{
	_request.url().set_URI(std::string(at, length));
}

void
request_parser_impl::fragment( const char *
                             , const char * at
                             , size_t       length )
{
	_request.url().set_fragment(std::string(at, length));
}

void
request_parser_impl::request_path( const char *
                                 , const char * at
                                 , size_t       length )
{
	_request.url().set_path(std::string(at, length));
}

void
request_parser_impl::query_string( const char *
                                 , const char * at
                                 , size_t       length )
{
	std::string query = std::string(at, length);
	_request.url().set_query(query);

	// find each pair of key / value strings delimeted by '&'
	while ( query.length() > 0 )
	{
		size_t pos = query.find("&");

		std::string pair;
		if ( pos != std::string::npos )
		{
			pair = query.substr(0, pos);
		}
		else
		{
			pair = query;
			pos = query.length() - 1;
		}

		// save the key / value pair, and look for the index of the
		// divider, delimited by '='
		size_t div_index = pair.find('=');

		if (div_index != std::string::npos)
		{
			std::string key = query_unescape(pair.substr(0, div_index));
			std::string value = query_unescape(pair.substr(div_index + 1, std::string::npos));

			_request.query[key] = value;
		}

		// erase the pair we just processed from the query string
		query.erase(0, pos + 1);
	}
}

void
request_parser_impl::http_version( const char *
                                 , const char * at
                                 , size_t       length )
{
	_request.set_HTTP_version(std::string(at, length));
}

void
request_parser_impl::header_done( const char *
                                , const char *
                                , size_t      )
{
	// NOTE: Body parsing instigated in "parse"
}

bool
request_parser_impl::requested_continue()
{
	return _request.header("expect") == "100-continue";
}

size_t
request_parser_impl::expecting_body()
{
	switch (_request.method())
	{
	case method::PUT:
	case method::POST:
	{
		std::string type   = _request.header("content-type");
		std::string length = _request.header("content-length");

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
	if ( len > _body_expected )
	{
		len = _body_expected;
	}

	_body_stream.write(data, len);
	_body_expected -= len;

	if ( 0 == _body_expected )
	{
		_request.set_body(_body_stream.str());
		_body_stream.str(std::string());
		_status = status_type::FINISHED;
	}
	else
	{
		_status = status_type::READ_BODY;
	}

	return _status;
}

} // served
