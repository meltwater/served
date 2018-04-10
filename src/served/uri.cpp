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

#include <served/uri.hpp>

namespace served {

static const char hex_table[] = "0123456789ABCDEF";

static const signed char dec_to_hex[256] = {
    /*       0  1  2  3   4  5  6  7   8  9  A  B   C  D  E  F */
    /* 0 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 1 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 2 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 3 */  0, 1, 2, 3,  4, 5, 6, 7,  8, 9,-1,-1, -1,-1,-1,-1,

    /* 4 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 5 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 6 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 7 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,

    /* 8 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 9 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* A */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* B */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,

    /* C */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* D */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* E */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* F */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1
};

std::string
query_escape(const std::string& s) {
	const unsigned char* src_ptr = (const unsigned char*)s.c_str();
	const size_t         src_len = s.length();

	unsigned char* const tmp = new unsigned char[src_len * 3];
	unsigned char*       end = tmp;

	const unsigned char * const eol = src_ptr + src_len;

	for (; src_ptr < eol; ++src_ptr) {
		unsigned char c = *src_ptr;
		if ((c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') ||
			c == '-' || c == '.' || c == '_' || c == '~')
		{
			*end++ = *src_ptr;
		} else {
			*end++ = '%';
			*end++ = hex_table[*src_ptr >> 4];
			*end++ = hex_table[*src_ptr & 0x0F];
		}
	}
	std::string result((char*)tmp, (char*)end);
	delete[] tmp;
	return result;
}

std::string
query_unescape(const std::string& s) {
	const unsigned char* src_ptr = (const unsigned char*)s.c_str();
	const size_t         src_len = s.length();

	const unsigned char* const eol = src_ptr + src_len;
	const unsigned char* const last_decodable = eol - 2;

	char* const tmp = new char[src_len];
	char* end = tmp;

	while (src_ptr < last_decodable) {
		if (*src_ptr == '%') {
			signed char dec1, dec2;
			if (-1 != (dec1 = dec_to_hex[*(src_ptr + 1)])
				&& -1 != (dec2 = dec_to_hex[*(src_ptr + 2)]))
			{
				*end++ = (dec1 << 4) + dec2;
				src_ptr += 3;
				continue;
			}
		}
		*end++ = *src_ptr++;
	}

	while (src_ptr < eol) {
		*end++ = *src_ptr++;
	}
	std::string result((char*)tmp, (char*)end);
	delete[] tmp;
	return result;
}

//  -----  constructors  -----

//  -----  URI component mutators  -----

void
uri::set_URI(std::string const& uri)
{
	_uri = uri;
}

void
uri::set_path(std::string const& path)
{
	_path = path;
}

void
uri::set_query(std::string const& query)
{
	_query = query;
}

void
uri::set_fragment(std::string const& fragment)
{
	_fragment = fragment;
}

//  -----  URI component selectors  -----

const std::string
uri::URI() const
{
	return _uri;
}

const std::string
uri::path() const
{
	return _path;
}

const std::string
uri::query() const
{
	return _query;
}

const std::string
uri::fragment() const
{
	return _fragment;
}

} // served
