
#line 1 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
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

#include <served/request_parser.hpp>

#define LEN(AT, FPC) (FPC - buffer - AT)
#define MARK(M,FPC) (M = (FPC) - buffer)
#define PTR_TO(F) (buffer + F)

using namespace served;

/** Machine **/


#line 37 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
static const int request_parser_start = 1;
static const int request_parser_first_final = 194;
static const int request_parser_error = 0;

static const int request_parser_en_main = 1;


#line 224 "/home/vagrant/src/dev/served/src/served/request_parser.rl"


request_parser::request_parser()
	: cs(0)
	, d_offset(0)
{
	// Ragel generates an unused constant for the entry point.
	// The following will suppress the resulting warning.
	(void) request_parser_en_main;

#line 53 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	{
	cs = request_parser_start;
	}

#line 231 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
}

request_parser::~request_parser()
{}

size_t
request_parser::execute(const char *buffer, size_t len)
{
	//int    content_len;
	size_t nread = 0;
	size_t mark = 0;
	size_t field_start = 0;
	size_t field_len = 0;
	size_t query_start = 0;

	if(len == 0) return 0;

	const char *p  = buffer+d_offset;
	const char *pe = buffer+len;


#line 80 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto tr0;
	} else if ( (*p) >= 48 )
		goto tr0;
	goto st0;
st0:
cs = 0;
	goto _out;
tr0:
#line 37 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 106 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st175;
	} else if ( (*p) >= 48 )
		goto st175;
	goto st0;
tr2:
#line 62 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		request_method(buffer, PTR_TO(mark), LEN(mark, p));
	}
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 125 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	switch( (*p) ) {
		case 32: goto tr4;
		case 33: goto tr5;
		case 35: goto tr6;
		case 37: goto tr7;
		case 47: goto tr8;
		case 59: goto tr5;
		case 61: goto tr5;
		case 63: goto tr9;
		case 64: goto tr5;
		case 95: goto tr5;
		case 126: goto tr5;
	}
	if ( (*p) < 65 ) {
		if ( 36 <= (*p) && (*p) <= 57 )
			goto tr5;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr10;
	} else
		goto tr10;
	goto st0;
tr4:
#line 37 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
#line 92 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		request_path(buffer, PTR_TO(mark), LEN(mark,p));
	}
#line 67 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		request_uri(buffer, PTR_TO(mark), LEN(mark, p));
	}
	goto st4;
tr35:
#line 92 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		request_path(buffer, PTR_TO(mark), LEN(mark,p));
	}
#line 67 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		request_uri(buffer, PTR_TO(mark), LEN(mark, p));
	}
	goto st4;
tr41:
#line 37 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
#line 72 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		fragment(buffer, PTR_TO(mark), LEN(mark, p));
	}
	goto st4;
tr44:
#line 72 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		fragment(buffer, PTR_TO(mark), LEN(mark, p));
	}
	goto st4;
tr51:
#line 77 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(query_start, p);
	}
#line 82 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		query_string(buffer, PTR_TO(query_start), LEN(query_start, p));
	}
#line 67 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		request_uri(buffer, PTR_TO(mark), LEN(mark, p));
	}
	goto st4;
tr55:
#line 82 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		query_string(buffer, PTR_TO(query_start), LEN(query_start, p));
	}
#line 67 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		request_uri(buffer, PTR_TO(mark), LEN(mark, p));
	}
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 216 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	if ( (*p) == 72 )
		goto tr11;
	goto st0;
tr11:
#line 37 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 230 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	if ( (*p) == 84 )
		goto st6;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 84 )
		goto st7;
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 80 )
		goto st8;
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 47 )
		goto st9;
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 49 )
		goto st10;
	goto st0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	if ( (*p) == 46 )
		goto st11;
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	if ( 48 <= (*p) && (*p) <= 49 )
		goto st12;
	goto st0;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	switch( (*p) ) {
		case 10: goto tr19;
		case 13: goto tr20;
	}
	goto st0;
tr19:
#line 87 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		http_version(buffer, PTR_TO(mark), LEN(mark, p));
	}
	goto st13;
tr28:
#line 52 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
#line 57 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		http_field(buffer, PTR_TO(field_start), field_len, PTR_TO(mark), LEN(mark, p));
	}
	goto st13;
tr31:
#line 57 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		http_field(buffer, PTR_TO(field_start), field_len, PTR_TO(mark), LEN(mark, p));
	}
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 311 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	switch( (*p) ) {
		case 10: goto tr22;
		case 13: goto tr23;
		case 33: goto tr21;
		case 124: goto tr21;
		case 126: goto tr21;
	}
	if ( (*p) < 42 ) {
		if ( (*p) < 11 ) {
			if ( 1 <= (*p) && (*p) <= 8 )
				goto tr21;
		} else if ( (*p) > 31 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto tr21;
		} else
			goto tr21;
	} else if ( (*p) > 43 ) {
		if ( (*p) < 48 ) {
			if ( 45 <= (*p) && (*p) <= 46 )
				goto tr21;
		} else if ( (*p) > 57 ) {
			if ( (*p) > 90 ) {
				if ( 94 <= (*p) && (*p) <= 122 )
					goto tr21;
			} else if ( (*p) >= 65 )
				goto tr21;
		} else
			goto tr21;
	} else
		goto tr21;
	goto st0;
tr21:
#line 42 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(field_start, p);
	}
	goto st14;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
#line 353 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	switch( (*p) ) {
		case 33: goto st14;
		case 58: goto tr25;
		case 124: goto st14;
		case 126: goto st14;
	}
	if ( (*p) < 42 ) {
		if ( (*p) < 10 ) {
			if ( 1 <= (*p) && (*p) <= 8 )
				goto st14;
		} else if ( (*p) > 31 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st14;
		} else
			goto st14;
	} else if ( (*p) > 43 ) {
		if ( (*p) < 48 ) {
			if ( 45 <= (*p) && (*p) <= 46 )
				goto st14;
		} else if ( (*p) > 57 ) {
			if ( (*p) > 90 ) {
				if ( 94 <= (*p) && (*p) <= 122 )
					goto st14;
			} else if ( (*p) >= 65 )
				goto st14;
		} else
			goto st14;
	} else
		goto st14;
	goto st0;
tr25:
#line 47 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		field_len = LEN(field_start, p);
	}
	goto st15;
tr27:
#line 52 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
#line 400 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	switch( (*p) ) {
		case 0: goto st0;
		case 9: goto tr27;
		case 10: goto tr28;
		case 13: goto tr29;
		case 32: goto tr27;
		case 127: goto st0;
	}
	goto tr26;
tr26:
#line 52 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
#line 420 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	switch( (*p) ) {
		case 0: goto st0;
		case 10: goto tr31;
		case 13: goto tr32;
		case 127: goto st0;
	}
	goto st16;
tr20:
#line 87 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		http_version(buffer, PTR_TO(mark), LEN(mark, p));
	}
	goto st17;
tr29:
#line 52 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
#line 57 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		http_field(buffer, PTR_TO(field_start), field_len, PTR_TO(mark), LEN(mark, p));
	}
	goto st17;
tr32:
#line 57 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		http_field(buffer, PTR_TO(field_start), field_len, PTR_TO(mark), LEN(mark, p));
	}
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 454 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	if ( (*p) == 10 )
		goto st13;
	goto st0;
tr22:
#line 42 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(field_start, p);
	}
#line 97 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		header_done(buffer, p + 1, pe - p - 1);
		{p++; cs = 194; goto _out;}
	}
	goto st194;
tr34:
#line 97 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		header_done(buffer, p + 1, pe - p - 1);
		{p++; cs = 194; goto _out;}
	}
	goto st194;
st194:
	if ( ++p == pe )
		goto _test_eof194;
case 194:
#line 480 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	switch( (*p) ) {
		case 33: goto st14;
		case 58: goto tr25;
		case 124: goto st14;
		case 126: goto st14;
	}
	if ( (*p) < 42 ) {
		if ( (*p) < 10 ) {
			if ( 1 <= (*p) && (*p) <= 8 )
				goto st14;
		} else if ( (*p) > 31 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st14;
		} else
			goto st14;
	} else if ( (*p) > 43 ) {
		if ( (*p) < 48 ) {
			if ( 45 <= (*p) && (*p) <= 46 )
				goto st14;
		} else if ( (*p) > 57 ) {
			if ( (*p) > 90 ) {
				if ( 94 <= (*p) && (*p) <= 122 )
					goto st14;
			} else if ( (*p) >= 65 )
				goto st14;
		} else
			goto st14;
	} else
		goto st14;
	goto st0;
tr23:
#line 42 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(field_start, p);
	}
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 521 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	switch( (*p) ) {
		case 10: goto tr34;
		case 33: goto st14;
		case 58: goto tr25;
		case 124: goto st14;
		case 126: goto st14;
	}
	if ( (*p) < 42 ) {
		if ( (*p) < 11 ) {
			if ( 1 <= (*p) && (*p) <= 8 )
				goto st14;
		} else if ( (*p) > 31 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st14;
		} else
			goto st14;
	} else if ( (*p) > 43 ) {
		if ( (*p) < 48 ) {
			if ( 45 <= (*p) && (*p) <= 46 )
				goto st14;
		} else if ( (*p) > 57 ) {
			if ( (*p) > 90 ) {
				if ( 94 <= (*p) && (*p) <= 122 )
					goto st14;
			} else if ( (*p) >= 65 )
				goto st14;
		} else
			goto st14;
	} else
		goto st14;
	goto st0;
tr5:
#line 37 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 563 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	switch( (*p) ) {
		case 32: goto tr35;
		case 33: goto st19;
		case 35: goto tr37;
		case 37: goto st24;
		case 47: goto st26;
		case 59: goto st19;
		case 61: goto st19;
		case 63: goto tr40;
		case 95: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 64 ) {
		if ( 36 <= (*p) && (*p) <= 57 )
			goto st19;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st19;
	} else
		goto st19;
	goto st0;
tr6:
#line 37 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
#line 92 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		request_path(buffer, PTR_TO(mark), LEN(mark,p));
	}
#line 67 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		request_uri(buffer, PTR_TO(mark), LEN(mark, p));
	}
	goto st20;
tr37:
#line 92 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		request_path(buffer, PTR_TO(mark), LEN(mark,p));
	}
#line 67 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		request_uri(buffer, PTR_TO(mark), LEN(mark, p));
	}
	goto st20;
tr53:
#line 77 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(query_start, p);
	}
#line 82 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		query_string(buffer, PTR_TO(query_start), LEN(query_start, p));
	}
#line 67 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		request_uri(buffer, PTR_TO(mark), LEN(mark, p));
	}
	goto st20;
tr57:
#line 82 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		query_string(buffer, PTR_TO(query_start), LEN(query_start, p));
	}
#line 67 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		request_uri(buffer, PTR_TO(mark), LEN(mark, p));
	}
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 637 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	switch( (*p) ) {
		case 32: goto tr41;
		case 33: goto tr42;
		case 37: goto tr43;
		case 61: goto tr42;
		case 95: goto tr42;
		case 126: goto tr42;
	}
	if ( (*p) < 63 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto tr42;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr42;
	} else
		goto tr42;
	goto st0;
tr42:
#line 37 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 665 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	switch( (*p) ) {
		case 32: goto tr44;
		case 33: goto st21;
		case 37: goto st22;
		case 61: goto st21;
		case 95: goto st21;
		case 126: goto st21;
	}
	if ( (*p) < 63 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st21;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st21;
	} else
		goto st21;
	goto st0;
tr43:
#line 37 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
	goto st22;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
#line 693 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st23;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st23;
	} else
		goto st23;
	goto st0;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st21;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st21;
	} else
		goto st21;
	goto st0;
tr7:
#line 37 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
	goto st24;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
#line 726 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st25;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st25;
	} else
		goto st25;
	goto st0;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st19;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st19;
	} else
		goto st19;
	goto st0;
tr201:
#line 37 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
	goto st26;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
#line 759 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	switch( (*p) ) {
		case 32: goto tr35;
		case 33: goto st26;
		case 35: goto tr37;
		case 37: goto st27;
		case 61: goto st26;
		case 63: goto tr40;
		case 95: goto st26;
		case 126: goto st26;
	}
	if ( (*p) < 64 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st26;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st26;
	} else
		goto st26;
	goto st0;
tr202:
#line 37 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
	goto st27;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
#line 789 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st28;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st28;
	} else
		goto st28;
	goto st0;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st26;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st26;
	} else
		goto st26;
	goto st0;
tr9:
#line 37 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
#line 92 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		request_path(buffer, PTR_TO(mark), LEN(mark,p));
	}
	goto st29;
tr40:
#line 92 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		request_path(buffer, PTR_TO(mark), LEN(mark,p));
	}
	goto st29;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
#line 832 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	switch( (*p) ) {
		case 32: goto tr51;
		case 33: goto tr52;
		case 35: goto tr53;
		case 37: goto tr54;
		case 61: goto tr52;
		case 95: goto tr52;
		case 126: goto tr52;
	}
	if ( (*p) < 63 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto tr52;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr52;
	} else
		goto tr52;
	goto st0;
tr52:
#line 77 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(query_start, p);
	}
	goto st30;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
#line 861 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	switch( (*p) ) {
		case 32: goto tr55;
		case 33: goto st30;
		case 35: goto tr57;
		case 37: goto st31;
		case 61: goto st30;
		case 95: goto st30;
		case 126: goto st30;
	}
	if ( (*p) < 63 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st30;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st30;
	} else
		goto st30;
	goto st0;
tr54:
#line 77 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(query_start, p);
	}
	goto st31;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
#line 890 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st32;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st32;
	} else
		goto st32;
	goto st0;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st30;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st30;
	} else
		goto st30;
	goto st0;
tr8:
#line 37 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
	goto st33;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
#line 923 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	switch( (*p) ) {
		case 32: goto tr35;
		case 33: goto st26;
		case 35: goto tr37;
		case 37: goto st27;
		case 47: goto st34;
		case 61: goto st26;
		case 63: goto tr40;
		case 95: goto st26;
		case 126: goto st26;
	}
	if ( (*p) < 64 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st26;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st26;
	} else
		goto st26;
	goto st0;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	switch( (*p) ) {
		case 32: goto tr35;
		case 33: goto st35;
		case 35: goto tr37;
		case 37: goto st36;
		case 47: goto st26;
		case 58: goto st38;
		case 61: goto st35;
		case 63: goto tr40;
		case 64: goto st42;
		case 91: goto st47;
		case 95: goto st35;
		case 126: goto st35;
	}
	if ( (*p) < 65 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st35;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st35;
	} else
		goto st35;
	goto st0;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	switch( (*p) ) {
		case 32: goto tr35;
		case 33: goto st35;
		case 35: goto tr37;
		case 37: goto st36;
		case 47: goto st26;
		case 58: goto st38;
		case 61: goto st35;
		case 63: goto tr40;
		case 64: goto st42;
		case 95: goto st35;
		case 126: goto st35;
	}
	if ( (*p) < 65 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st35;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st35;
	} else
		goto st35;
	goto st0;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st37;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st37;
	} else
		goto st37;
	goto st0;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st35;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st35;
	} else
		goto st35;
	goto st0;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	switch( (*p) ) {
		case 32: goto tr35;
		case 33: goto st39;
		case 35: goto tr37;
		case 37: goto st40;
		case 47: goto st26;
		case 61: goto st39;
		case 63: goto tr40;
		case 64: goto st42;
		case 95: goto st39;
		case 126: goto st39;
	}
	if ( (*p) < 58 ) {
		if ( (*p) > 46 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st38;
		} else if ( (*p) >= 36 )
			goto st39;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st39;
		} else if ( (*p) >= 65 )
			goto st39;
	} else
		goto st39;
	goto st0;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	switch( (*p) ) {
		case 33: goto st39;
		case 37: goto st40;
		case 61: goto st39;
		case 64: goto st42;
		case 95: goto st39;
		case 126: goto st39;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 46 )
			goto st39;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st39;
		} else if ( (*p) >= 65 )
			goto st39;
	} else
		goto st39;
	goto st0;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st41;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st41;
	} else
		goto st41;
	goto st0;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st39;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st39;
	} else
		goto st39;
	goto st0;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	switch( (*p) ) {
		case 32: goto tr35;
		case 33: goto st43;
		case 35: goto tr37;
		case 37: goto st44;
		case 47: goto st26;
		case 58: goto st46;
		case 61: goto st43;
		case 63: goto tr40;
		case 91: goto st47;
		case 95: goto st43;
		case 126: goto st43;
	}
	if ( (*p) < 65 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st43;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st43;
	} else
		goto st43;
	goto st0;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	switch( (*p) ) {
		case 32: goto tr35;
		case 33: goto st43;
		case 35: goto tr37;
		case 37: goto st44;
		case 47: goto st26;
		case 58: goto st46;
		case 61: goto st43;
		case 63: goto tr40;
		case 95: goto st43;
		case 126: goto st43;
	}
	if ( (*p) < 65 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st43;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st43;
	} else
		goto st43;
	goto st0;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st45;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st45;
	} else
		goto st45;
	goto st0;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st43;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st43;
	} else
		goto st43;
	goto st0;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	switch( (*p) ) {
		case 32: goto tr35;
		case 35: goto tr37;
		case 47: goto st26;
		case 63: goto tr40;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st46;
	goto st0;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
	switch( (*p) ) {
		case 6: goto st48;
		case 58: goto st167;
		case 118: goto st169;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st91;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st91;
	} else
		goto st91;
	goto st0;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st49;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st49;
	} else
		goto st49;
	goto st0;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	if ( (*p) == 58 )
		goto st53;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st50;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st50;
	} else
		goto st50;
	goto st0;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	if ( (*p) == 58 )
		goto st53;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st51;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st51;
	} else
		goto st51;
	goto st0;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	if ( (*p) == 58 )
		goto st53;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st52;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st52;
	} else
		goto st52;
	goto st0;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	if ( (*p) == 58 )
		goto st53;
	goto st0;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	switch( (*p) ) {
		case 49: goto st84;
		case 50: goto st87;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st54;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st90;
	} else
		goto st90;
	goto st0;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	switch( (*p) ) {
		case 46: goto st55;
		case 58: goto st80;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st77;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st77;
	} else
		goto st77;
	goto st0;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	switch( (*p) ) {
		case 49: goto st72;
		case 50: goto st74;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st56;
	goto st0;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	if ( (*p) == 46 )
		goto st57;
	goto st0;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	switch( (*p) ) {
		case 49: goto st67;
		case 50: goto st69;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st58;
	goto st0;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	if ( (*p) == 46 )
		goto st59;
	goto st0;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	switch( (*p) ) {
		case 49: goto st62;
		case 50: goto st64;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st60;
	goto st0;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	if ( (*p) == 93 )
		goto st61;
	goto st0;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	switch( (*p) ) {
		case 32: goto tr35;
		case 35: goto tr37;
		case 47: goto st26;
		case 58: goto st46;
		case 63: goto tr40;
	}
	goto st0;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	if ( (*p) == 93 )
		goto st61;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st63;
	goto st0;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	if ( (*p) == 93 )
		goto st61;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st60;
	goto st0;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	switch( (*p) ) {
		case 48: goto st65;
		case 53: goto st66;
		case 93: goto st61;
	}
	goto st0;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st60;
	goto st0;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	if ( (*p) == 48 )
		goto st60;
	goto st0;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	if ( (*p) == 46 )
		goto st59;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st68;
	goto st0;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	if ( (*p) == 46 )
		goto st59;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st58;
	goto st0;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	switch( (*p) ) {
		case 46: goto st59;
		case 48: goto st70;
		case 53: goto st71;
	}
	goto st0;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st58;
	goto st0;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	if ( (*p) == 48 )
		goto st58;
	goto st0;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	if ( (*p) == 46 )
		goto st57;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st73;
	goto st0;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	if ( (*p) == 46 )
		goto st57;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st56;
	goto st0;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	switch( (*p) ) {
		case 46: goto st57;
		case 48: goto st75;
		case 53: goto st76;
	}
	goto st0;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st56;
	goto st0;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	if ( (*p) == 48 )
		goto st56;
	goto st0;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	if ( (*p) == 58 )
		goto st80;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st78;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st78;
	} else
		goto st78;
	goto st0;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	if ( (*p) == 58 )
		goto st80;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st79;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st79;
	} else
		goto st79;
	goto st0;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	if ( (*p) == 58 )
		goto st80;
	goto st0;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st81;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st81;
	} else
		goto st81;
	goto st0;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	if ( (*p) == 93 )
		goto st61;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st82;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st82;
	} else
		goto st82;
	goto st0;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	if ( (*p) == 93 )
		goto st61;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st83;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st83;
	} else
		goto st83;
	goto st0;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	if ( (*p) == 93 )
		goto st61;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st60;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st60;
	} else
		goto st60;
	goto st0;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	switch( (*p) ) {
		case 46: goto st55;
		case 58: goto st80;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st85;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st77;
	} else
		goto st77;
	goto st0;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	switch( (*p) ) {
		case 46: goto st55;
		case 58: goto st80;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st86;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st78;
	} else
		goto st78;
	goto st0;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
	switch( (*p) ) {
		case 46: goto st55;
		case 58: goto st80;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st79;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st79;
	} else
		goto st79;
	goto st0;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	switch( (*p) ) {
		case 46: goto st55;
		case 48: goto st88;
		case 53: goto st89;
		case 58: goto st80;
	}
	if ( (*p) < 65 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto st77;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st77;
	} else
		goto st77;
	goto st0;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	if ( (*p) == 58 )
		goto st80;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st86;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st78;
	} else
		goto st78;
	goto st0;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
	switch( (*p) ) {
		case 48: goto st86;
		case 58: goto st80;
	}
	if ( (*p) < 65 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto st78;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st78;
	} else
		goto st78;
	goto st0;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
	if ( (*p) == 58 )
		goto st80;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st77;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st77;
	} else
		goto st77;
	goto st0;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
	if ( (*p) == 58 )
		goto st95;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st92;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st92;
	} else
		goto st92;
	goto st0;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
	if ( (*p) == 58 )
		goto st95;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st93;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st93;
	} else
		goto st93;
	goto st0;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
	if ( (*p) == 58 )
		goto st95;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st94;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st94;
	} else
		goto st94;
	goto st0;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
	if ( (*p) == 58 )
		goto st95;
	goto st0;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
	if ( (*p) == 58 )
		goto st166;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st96;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st96;
	} else
		goto st96;
	goto st0;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	if ( (*p) == 58 )
		goto st100;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st97;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st97;
	} else
		goto st97;
	goto st0;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	if ( (*p) == 58 )
		goto st100;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st98;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st98;
	} else
		goto st98;
	goto st0;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
	if ( (*p) == 58 )
		goto st100;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st99;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st99;
	} else
		goto st99;
	goto st0;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	if ( (*p) == 58 )
		goto st100;
	goto st0;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
	if ( (*p) == 58 )
		goto st165;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st101;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st101;
	} else
		goto st101;
	goto st0;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
	if ( (*p) == 58 )
		goto st105;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st102;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st102;
	} else
		goto st102;
	goto st0;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
	if ( (*p) == 58 )
		goto st105;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st103;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st103;
	} else
		goto st103;
	goto st0;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
	if ( (*p) == 58 )
		goto st105;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st104;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st104;
	} else
		goto st104;
	goto st0;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
	if ( (*p) == 58 )
		goto st105;
	goto st0;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
	if ( (*p) == 58 )
		goto st164;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st106;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st106;
	} else
		goto st106;
	goto st0;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
	if ( (*p) == 58 )
		goto st110;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st107;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st107;
	} else
		goto st107;
	goto st0;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
	if ( (*p) == 58 )
		goto st110;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st108;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st108;
	} else
		goto st108;
	goto st0;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
	if ( (*p) == 58 )
		goto st110;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st109;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st109;
	} else
		goto st109;
	goto st0;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
	if ( (*p) == 58 )
		goto st110;
	goto st0;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
	if ( (*p) == 58 )
		goto st163;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st111;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st111;
	} else
		goto st111;
	goto st0;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
	if ( (*p) == 58 )
		goto st115;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st112;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st112;
	} else
		goto st112;
	goto st0;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
	if ( (*p) == 58 )
		goto st115;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st113;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st113;
	} else
		goto st113;
	goto st0;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
	if ( (*p) == 58 )
		goto st115;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st114;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st114;
	} else
		goto st114;
	goto st0;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
	if ( (*p) == 58 )
		goto st115;
	goto st0;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
	if ( (*p) == 58 )
		goto st151;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st116;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st116;
	} else
		goto st116;
	goto st0;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
	if ( (*p) == 58 )
		goto st120;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st117;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st117;
	} else
		goto st117;
	goto st0;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
	if ( (*p) == 58 )
		goto st120;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st118;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st118;
	} else
		goto st118;
	goto st0;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
	if ( (*p) == 58 )
		goto st120;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st119;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st119;
	} else
		goto st119;
	goto st0;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
	if ( (*p) == 58 )
		goto st120;
	goto st0;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
	if ( (*p) == 58 )
		goto st150;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st121;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st121;
	} else
		goto st121;
	goto st0;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
	if ( (*p) == 58 )
		goto st125;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st122;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st122;
	} else
		goto st122;
	goto st0;
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
	if ( (*p) == 58 )
		goto st125;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st123;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st123;
	} else
		goto st123;
	goto st0;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
	if ( (*p) == 58 )
		goto st125;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st124;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st124;
	} else
		goto st124;
	goto st0;
st124:
	if ( ++p == pe )
		goto _test_eof124;
case 124:
	if ( (*p) == 58 )
		goto st125;
	goto st0;
st125:
	if ( ++p == pe )
		goto _test_eof125;
case 125:
	if ( (*p) == 58 )
		goto st126;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st121;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st121;
	} else
		goto st121;
	goto st0;
st126:
	if ( ++p == pe )
		goto _test_eof126;
case 126:
	switch( (*p) ) {
		case 49: goto st143;
		case 50: goto st146;
		case 93: goto st61;
	}
	if ( (*p) < 48 ) {
		if ( 2 <= (*p) && (*p) <= 3 )
			goto st48;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st149;
		} else if ( (*p) >= 65 )
			goto st149;
	} else
		goto st127;
	goto st0;
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
	switch( (*p) ) {
		case 46: goto st55;
		case 58: goto st131;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st128;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st128;
	} else
		goto st128;
	goto st0;
st128:
	if ( ++p == pe )
		goto _test_eof128;
case 128:
	switch( (*p) ) {
		case 58: goto st131;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st129;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st129;
	} else
		goto st129;
	goto st0;
st129:
	if ( ++p == pe )
		goto _test_eof129;
case 129:
	switch( (*p) ) {
		case 58: goto st131;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st130;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st130;
	} else
		goto st130;
	goto st0;
st130:
	if ( ++p == pe )
		goto _test_eof130;
case 130:
	switch( (*p) ) {
		case 58: goto st131;
		case 93: goto st61;
	}
	goto st0;
st131:
	if ( ++p == pe )
		goto _test_eof131;
case 131:
	switch( (*p) ) {
		case 49: goto st136;
		case 50: goto st139;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st132;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st142;
	} else
		goto st142;
	goto st0;
st132:
	if ( ++p == pe )
		goto _test_eof132;
case 132:
	switch( (*p) ) {
		case 46: goto st55;
		case 58: goto st80;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st133;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st133;
	} else
		goto st133;
	goto st0;
st133:
	if ( ++p == pe )
		goto _test_eof133;
case 133:
	switch( (*p) ) {
		case 58: goto st80;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st134;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st134;
	} else
		goto st134;
	goto st0;
st134:
	if ( ++p == pe )
		goto _test_eof134;
case 134:
	switch( (*p) ) {
		case 58: goto st80;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st135;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st135;
	} else
		goto st135;
	goto st0;
st135:
	if ( ++p == pe )
		goto _test_eof135;
case 135:
	switch( (*p) ) {
		case 58: goto st80;
		case 93: goto st61;
	}
	goto st0;
st136:
	if ( ++p == pe )
		goto _test_eof136;
case 136:
	switch( (*p) ) {
		case 46: goto st55;
		case 58: goto st80;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st137;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st133;
	} else
		goto st133;
	goto st0;
st137:
	if ( ++p == pe )
		goto _test_eof137;
case 137:
	switch( (*p) ) {
		case 46: goto st55;
		case 58: goto st80;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st138;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st134;
	} else
		goto st134;
	goto st0;
st138:
	if ( ++p == pe )
		goto _test_eof138;
case 138:
	switch( (*p) ) {
		case 46: goto st55;
		case 58: goto st80;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st135;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st135;
	} else
		goto st135;
	goto st0;
st139:
	if ( ++p == pe )
		goto _test_eof139;
case 139:
	switch( (*p) ) {
		case 46: goto st55;
		case 48: goto st140;
		case 53: goto st141;
		case 58: goto st80;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto st133;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st133;
	} else
		goto st133;
	goto st0;
st140:
	if ( ++p == pe )
		goto _test_eof140;
case 140:
	switch( (*p) ) {
		case 58: goto st80;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st138;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st134;
	} else
		goto st134;
	goto st0;
st141:
	if ( ++p == pe )
		goto _test_eof141;
case 141:
	switch( (*p) ) {
		case 48: goto st138;
		case 58: goto st80;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto st134;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st134;
	} else
		goto st134;
	goto st0;
st142:
	if ( ++p == pe )
		goto _test_eof142;
case 142:
	switch( (*p) ) {
		case 58: goto st80;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st133;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st133;
	} else
		goto st133;
	goto st0;
st143:
	if ( ++p == pe )
		goto _test_eof143;
case 143:
	switch( (*p) ) {
		case 46: goto st55;
		case 58: goto st131;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st144;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st128;
	} else
		goto st128;
	goto st0;
st144:
	if ( ++p == pe )
		goto _test_eof144;
case 144:
	switch( (*p) ) {
		case 46: goto st55;
		case 58: goto st131;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st145;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st129;
	} else
		goto st129;
	goto st0;
st145:
	if ( ++p == pe )
		goto _test_eof145;
case 145:
	switch( (*p) ) {
		case 46: goto st55;
		case 58: goto st131;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st130;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st130;
	} else
		goto st130;
	goto st0;
st146:
	if ( ++p == pe )
		goto _test_eof146;
case 146:
	switch( (*p) ) {
		case 46: goto st55;
		case 48: goto st147;
		case 53: goto st148;
		case 58: goto st131;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto st128;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st128;
	} else
		goto st128;
	goto st0;
st147:
	if ( ++p == pe )
		goto _test_eof147;
case 147:
	switch( (*p) ) {
		case 58: goto st131;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st145;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st129;
	} else
		goto st129;
	goto st0;
st148:
	if ( ++p == pe )
		goto _test_eof148;
case 148:
	switch( (*p) ) {
		case 48: goto st145;
		case 58: goto st131;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto st129;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st129;
	} else
		goto st129;
	goto st0;
st149:
	if ( ++p == pe )
		goto _test_eof149;
case 149:
	switch( (*p) ) {
		case 58: goto st131;
		case 93: goto st61;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st128;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st128;
	} else
		goto st128;
	goto st0;
st150:
	if ( ++p == pe )
		goto _test_eof150;
case 150:
	switch( (*p) ) {
		case 49: goto st143;
		case 50: goto st146;
	}
	if ( (*p) < 48 ) {
		if ( 2 <= (*p) && (*p) <= 3 )
			goto st48;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st149;
		} else if ( (*p) >= 65 )
			goto st149;
	} else
		goto st127;
	goto st0;
st151:
	if ( ++p == pe )
		goto _test_eof151;
case 151:
	switch( (*p) ) {
		case 49: goto st156;
		case 50: goto st159;
	}
	if ( (*p) < 48 ) {
		if ( 2 <= (*p) && (*p) <= 3 )
			goto st48;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st162;
		} else if ( (*p) >= 65 )
			goto st162;
	} else
		goto st152;
	goto st0;
st152:
	if ( ++p == pe )
		goto _test_eof152;
case 152:
	switch( (*p) ) {
		case 46: goto st55;
		case 58: goto st131;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st153;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st153;
	} else
		goto st153;
	goto st0;
st153:
	if ( ++p == pe )
		goto _test_eof153;
case 153:
	if ( (*p) == 58 )
		goto st131;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st154;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st154;
	} else
		goto st154;
	goto st0;
st154:
	if ( ++p == pe )
		goto _test_eof154;
case 154:
	if ( (*p) == 58 )
		goto st131;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st155;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st155;
	} else
		goto st155;
	goto st0;
st155:
	if ( ++p == pe )
		goto _test_eof155;
case 155:
	if ( (*p) == 58 )
		goto st131;
	goto st0;
st156:
	if ( ++p == pe )
		goto _test_eof156;
case 156:
	switch( (*p) ) {
		case 46: goto st55;
		case 58: goto st131;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st157;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st153;
	} else
		goto st153;
	goto st0;
st157:
	if ( ++p == pe )
		goto _test_eof157;
case 157:
	switch( (*p) ) {
		case 46: goto st55;
		case 58: goto st131;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st158;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st154;
	} else
		goto st154;
	goto st0;
st158:
	if ( ++p == pe )
		goto _test_eof158;
case 158:
	switch( (*p) ) {
		case 46: goto st55;
		case 58: goto st131;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st155;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st155;
	} else
		goto st155;
	goto st0;
st159:
	if ( ++p == pe )
		goto _test_eof159;
case 159:
	switch( (*p) ) {
		case 46: goto st55;
		case 48: goto st160;
		case 53: goto st161;
		case 58: goto st131;
	}
	if ( (*p) < 65 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto st153;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st153;
	} else
		goto st153;
	goto st0;
st160:
	if ( ++p == pe )
		goto _test_eof160;
case 160:
	if ( (*p) == 58 )
		goto st131;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st158;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st154;
	} else
		goto st154;
	goto st0;
st161:
	if ( ++p == pe )
		goto _test_eof161;
case 161:
	switch( (*p) ) {
		case 48: goto st158;
		case 58: goto st131;
	}
	if ( (*p) < 65 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto st154;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st154;
	} else
		goto st154;
	goto st0;
st162:
	if ( ++p == pe )
		goto _test_eof162;
case 162:
	if ( (*p) == 58 )
		goto st131;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st153;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st153;
	} else
		goto st153;
	goto st0;
st163:
	if ( ++p == pe )
		goto _test_eof163;
case 163:
	if ( (*p) < 48 ) {
		if ( 2 <= (*p) && (*p) <= 3 )
			goto st48;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st49;
		} else if ( (*p) >= 65 )
			goto st49;
	} else
		goto st49;
	goto st0;
st164:
	if ( ++p == pe )
		goto _test_eof164;
case 164:
	if ( 2 <= (*p) && (*p) <= 3 )
		goto st48;
	goto st0;
st165:
	if ( ++p == pe )
		goto _test_eof165;
case 165:
	if ( (*p) == 3 )
		goto st48;
	goto st0;
st166:
	if ( ++p == pe )
		goto _test_eof166;
case 166:
	if ( (*p) == 4 )
		goto st48;
	goto st0;
st167:
	if ( ++p == pe )
		goto _test_eof167;
case 167:
	if ( (*p) == 58 )
		goto st168;
	goto st0;
st168:
	if ( ++p == pe )
		goto _test_eof168;
case 168:
	switch( (*p) ) {
		case 49: goto st143;
		case 50: goto st146;
		case 93: goto st61;
	}
	if ( (*p) < 48 ) {
		if ( 2 <= (*p) && (*p) <= 5 )
			goto st48;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st149;
		} else if ( (*p) >= 65 )
			goto st149;
	} else
		goto st127;
	goto st0;
st169:
	if ( ++p == pe )
		goto _test_eof169;
case 169:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st170;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st170;
	} else
		goto st170;
	goto st0;
st170:
	if ( ++p == pe )
		goto _test_eof170;
case 170:
	if ( (*p) == 46 )
		goto st171;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st170;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st170;
	} else
		goto st170;
	goto st0;
st171:
	if ( ++p == pe )
		goto _test_eof171;
case 171:
	switch( (*p) ) {
		case 33: goto st172;
		case 36: goto st172;
		case 61: goto st172;
		case 95: goto st172;
		case 126: goto st172;
	}
	if ( (*p) < 48 ) {
		if ( 38 <= (*p) && (*p) <= 46 )
			goto st172;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st172;
		} else if ( (*p) >= 65 )
			goto st172;
	} else
		goto st172;
	goto st0;
st172:
	if ( ++p == pe )
		goto _test_eof172;
case 172:
	switch( (*p) ) {
		case 33: goto st172;
		case 36: goto st172;
		case 61: goto st172;
		case 93: goto st61;
		case 95: goto st172;
		case 126: goto st172;
	}
	if ( (*p) < 48 ) {
		if ( 38 <= (*p) && (*p) <= 46 )
			goto st172;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st172;
		} else if ( (*p) >= 65 )
			goto st172;
	} else
		goto st172;
	goto st0;
tr10:
#line 37 "/home/vagrant/src/dev/served/src/served/request_parser.rl"
	{
		MARK(mark, p);
	}
	goto st173;
st173:
	if ( ++p == pe )
		goto _test_eof173;
case 173:
#line 2957 "/home/vagrant/src/dev/served/src/served/request_parser.cpp"
	switch( (*p) ) {
		case 32: goto tr35;
		case 33: goto st19;
		case 35: goto tr37;
		case 37: goto st24;
		case 43: goto st173;
		case 47: goto st26;
		case 58: goto st174;
		case 59: goto st19;
		case 61: goto st19;
		case 63: goto tr40;
		case 64: goto st19;
		case 95: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( 36 <= (*p) && (*p) <= 44 )
			goto st19;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st173;
		} else if ( (*p) >= 65 )
			goto st173;
	} else
		goto st173;
	goto st0;
st174:
	if ( ++p == pe )
		goto _test_eof174;
case 174:
	switch( (*p) ) {
		case 32: goto tr4;
		case 33: goto tr201;
		case 35: goto tr6;
		case 37: goto tr202;
		case 47: goto tr8;
		case 61: goto tr201;
		case 63: goto tr9;
		case 95: goto tr201;
		case 126: goto tr201;
	}
	if ( (*p) < 64 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto tr201;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr201;
	} else
		goto tr201;
	goto st0;
st175:
	if ( ++p == pe )
		goto _test_eof175;
case 175:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st176;
	} else if ( (*p) >= 48 )
		goto st176;
	goto st0;
st176:
	if ( ++p == pe )
		goto _test_eof176;
case 176:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st177;
	} else if ( (*p) >= 48 )
		goto st177;
	goto st0;
st177:
	if ( ++p == pe )
		goto _test_eof177;
case 177:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st178;
	} else if ( (*p) >= 48 )
		goto st178;
	goto st0;
st178:
	if ( ++p == pe )
		goto _test_eof178;
case 178:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st179;
	} else if ( (*p) >= 48 )
		goto st179;
	goto st0;
st179:
	if ( ++p == pe )
		goto _test_eof179;
case 179:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st180;
	} else if ( (*p) >= 48 )
		goto st180;
	goto st0;
st180:
	if ( ++p == pe )
		goto _test_eof180;
case 180:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st181;
	} else if ( (*p) >= 48 )
		goto st181;
	goto st0;
st181:
	if ( ++p == pe )
		goto _test_eof181;
case 181:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st182;
	} else if ( (*p) >= 48 )
		goto st182;
	goto st0;
st182:
	if ( ++p == pe )
		goto _test_eof182;
case 182:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st183;
	} else if ( (*p) >= 48 )
		goto st183;
	goto st0;
st183:
	if ( ++p == pe )
		goto _test_eof183;
case 183:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st184;
	} else if ( (*p) >= 48 )
		goto st184;
	goto st0;
st184:
	if ( ++p == pe )
		goto _test_eof184;
case 184:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st185;
	} else if ( (*p) >= 48 )
		goto st185;
	goto st0;
st185:
	if ( ++p == pe )
		goto _test_eof185;
case 185:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st186;
	} else if ( (*p) >= 48 )
		goto st186;
	goto st0;
st186:
	if ( ++p == pe )
		goto _test_eof186;
case 186:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st187;
	} else if ( (*p) >= 48 )
		goto st187;
	goto st0;
st187:
	if ( ++p == pe )
		goto _test_eof187;
case 187:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st188;
	} else if ( (*p) >= 48 )
		goto st188;
	goto st0;
st188:
	if ( ++p == pe )
		goto _test_eof188;
case 188:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st189;
	} else if ( (*p) >= 48 )
		goto st189;
	goto st0;
st189:
	if ( ++p == pe )
		goto _test_eof189;
case 189:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st190;
	} else if ( (*p) >= 48 )
		goto st190;
	goto st0;
st190:
	if ( ++p == pe )
		goto _test_eof190;
case 190:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st191;
	} else if ( (*p) >= 48 )
		goto st191;
	goto st0;
st191:
	if ( ++p == pe )
		goto _test_eof191;
case 191:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st192;
	} else if ( (*p) >= 48 )
		goto st192;
	goto st0;
st192:
	if ( ++p == pe )
		goto _test_eof192;
case 192:
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st193;
	} else if ( (*p) >= 48 )
		goto st193;
	goto st0;
st193:
	if ( ++p == pe )
		goto _test_eof193;
case 193:
	if ( (*p) == 32 )
		goto tr2;
	goto st0;
	}
	_test_eof2: cs = 2; goto _test_eof;
	_test_eof3: cs = 3; goto _test_eof;
	_test_eof4: cs = 4; goto _test_eof;
	_test_eof5: cs = 5; goto _test_eof;
	_test_eof6: cs = 6; goto _test_eof;
	_test_eof7: cs = 7; goto _test_eof;
	_test_eof8: cs = 8; goto _test_eof;
	_test_eof9: cs = 9; goto _test_eof;
	_test_eof10: cs = 10; goto _test_eof;
	_test_eof11: cs = 11; goto _test_eof;
	_test_eof12: cs = 12; goto _test_eof;
	_test_eof13: cs = 13; goto _test_eof;
	_test_eof14: cs = 14; goto _test_eof;
	_test_eof15: cs = 15; goto _test_eof;
	_test_eof16: cs = 16; goto _test_eof;
	_test_eof17: cs = 17; goto _test_eof;
	_test_eof194: cs = 194; goto _test_eof;
	_test_eof18: cs = 18; goto _test_eof;
	_test_eof19: cs = 19; goto _test_eof;
	_test_eof20: cs = 20; goto _test_eof;
	_test_eof21: cs = 21; goto _test_eof;
	_test_eof22: cs = 22; goto _test_eof;
	_test_eof23: cs = 23; goto _test_eof;
	_test_eof24: cs = 24; goto _test_eof;
	_test_eof25: cs = 25; goto _test_eof;
	_test_eof26: cs = 26; goto _test_eof;
	_test_eof27: cs = 27; goto _test_eof;
	_test_eof28: cs = 28; goto _test_eof;
	_test_eof29: cs = 29; goto _test_eof;
	_test_eof30: cs = 30; goto _test_eof;
	_test_eof31: cs = 31; goto _test_eof;
	_test_eof32: cs = 32; goto _test_eof;
	_test_eof33: cs = 33; goto _test_eof;
	_test_eof34: cs = 34; goto _test_eof;
	_test_eof35: cs = 35; goto _test_eof;
	_test_eof36: cs = 36; goto _test_eof;
	_test_eof37: cs = 37; goto _test_eof;
	_test_eof38: cs = 38; goto _test_eof;
	_test_eof39: cs = 39; goto _test_eof;
	_test_eof40: cs = 40; goto _test_eof;
	_test_eof41: cs = 41; goto _test_eof;
	_test_eof42: cs = 42; goto _test_eof;
	_test_eof43: cs = 43; goto _test_eof;
	_test_eof44: cs = 44; goto _test_eof;
	_test_eof45: cs = 45; goto _test_eof;
	_test_eof46: cs = 46; goto _test_eof;
	_test_eof47: cs = 47; goto _test_eof;
	_test_eof48: cs = 48; goto _test_eof;
	_test_eof49: cs = 49; goto _test_eof;
	_test_eof50: cs = 50; goto _test_eof;
	_test_eof51: cs = 51; goto _test_eof;
	_test_eof52: cs = 52; goto _test_eof;
	_test_eof53: cs = 53; goto _test_eof;
	_test_eof54: cs = 54; goto _test_eof;
	_test_eof55: cs = 55; goto _test_eof;
	_test_eof56: cs = 56; goto _test_eof;
	_test_eof57: cs = 57; goto _test_eof;
	_test_eof58: cs = 58; goto _test_eof;
	_test_eof59: cs = 59; goto _test_eof;
	_test_eof60: cs = 60; goto _test_eof;
	_test_eof61: cs = 61; goto _test_eof;
	_test_eof62: cs = 62; goto _test_eof;
	_test_eof63: cs = 63; goto _test_eof;
	_test_eof64: cs = 64; goto _test_eof;
	_test_eof65: cs = 65; goto _test_eof;
	_test_eof66: cs = 66; goto _test_eof;
	_test_eof67: cs = 67; goto _test_eof;
	_test_eof68: cs = 68; goto _test_eof;
	_test_eof69: cs = 69; goto _test_eof;
	_test_eof70: cs = 70; goto _test_eof;
	_test_eof71: cs = 71; goto _test_eof;
	_test_eof72: cs = 72; goto _test_eof;
	_test_eof73: cs = 73; goto _test_eof;
	_test_eof74: cs = 74; goto _test_eof;
	_test_eof75: cs = 75; goto _test_eof;
	_test_eof76: cs = 76; goto _test_eof;
	_test_eof77: cs = 77; goto _test_eof;
	_test_eof78: cs = 78; goto _test_eof;
	_test_eof79: cs = 79; goto _test_eof;
	_test_eof80: cs = 80; goto _test_eof;
	_test_eof81: cs = 81; goto _test_eof;
	_test_eof82: cs = 82; goto _test_eof;
	_test_eof83: cs = 83; goto _test_eof;
	_test_eof84: cs = 84; goto _test_eof;
	_test_eof85: cs = 85; goto _test_eof;
	_test_eof86: cs = 86; goto _test_eof;
	_test_eof87: cs = 87; goto _test_eof;
	_test_eof88: cs = 88; goto _test_eof;
	_test_eof89: cs = 89; goto _test_eof;
	_test_eof90: cs = 90; goto _test_eof;
	_test_eof91: cs = 91; goto _test_eof;
	_test_eof92: cs = 92; goto _test_eof;
	_test_eof93: cs = 93; goto _test_eof;
	_test_eof94: cs = 94; goto _test_eof;
	_test_eof95: cs = 95; goto _test_eof;
	_test_eof96: cs = 96; goto _test_eof;
	_test_eof97: cs = 97; goto _test_eof;
	_test_eof98: cs = 98; goto _test_eof;
	_test_eof99: cs = 99; goto _test_eof;
	_test_eof100: cs = 100; goto _test_eof;
	_test_eof101: cs = 101; goto _test_eof;
	_test_eof102: cs = 102; goto _test_eof;
	_test_eof103: cs = 103; goto _test_eof;
	_test_eof104: cs = 104; goto _test_eof;
	_test_eof105: cs = 105; goto _test_eof;
	_test_eof106: cs = 106; goto _test_eof;
	_test_eof107: cs = 107; goto _test_eof;
	_test_eof108: cs = 108; goto _test_eof;
	_test_eof109: cs = 109; goto _test_eof;
	_test_eof110: cs = 110; goto _test_eof;
	_test_eof111: cs = 111; goto _test_eof;
	_test_eof112: cs = 112; goto _test_eof;
	_test_eof113: cs = 113; goto _test_eof;
	_test_eof114: cs = 114; goto _test_eof;
	_test_eof115: cs = 115; goto _test_eof;
	_test_eof116: cs = 116; goto _test_eof;
	_test_eof117: cs = 117; goto _test_eof;
	_test_eof118: cs = 118; goto _test_eof;
	_test_eof119: cs = 119; goto _test_eof;
	_test_eof120: cs = 120; goto _test_eof;
	_test_eof121: cs = 121; goto _test_eof;
	_test_eof122: cs = 122; goto _test_eof;
	_test_eof123: cs = 123; goto _test_eof;
	_test_eof124: cs = 124; goto _test_eof;
	_test_eof125: cs = 125; goto _test_eof;
	_test_eof126: cs = 126; goto _test_eof;
	_test_eof127: cs = 127; goto _test_eof;
	_test_eof128: cs = 128; goto _test_eof;
	_test_eof129: cs = 129; goto _test_eof;
	_test_eof130: cs = 130; goto _test_eof;
	_test_eof131: cs = 131; goto _test_eof;
	_test_eof132: cs = 132; goto _test_eof;
	_test_eof133: cs = 133; goto _test_eof;
	_test_eof134: cs = 134; goto _test_eof;
	_test_eof135: cs = 135; goto _test_eof;
	_test_eof136: cs = 136; goto _test_eof;
	_test_eof137: cs = 137; goto _test_eof;
	_test_eof138: cs = 138; goto _test_eof;
	_test_eof139: cs = 139; goto _test_eof;
	_test_eof140: cs = 140; goto _test_eof;
	_test_eof141: cs = 141; goto _test_eof;
	_test_eof142: cs = 142; goto _test_eof;
	_test_eof143: cs = 143; goto _test_eof;
	_test_eof144: cs = 144; goto _test_eof;
	_test_eof145: cs = 145; goto _test_eof;
	_test_eof146: cs = 146; goto _test_eof;
	_test_eof147: cs = 147; goto _test_eof;
	_test_eof148: cs = 148; goto _test_eof;
	_test_eof149: cs = 149; goto _test_eof;
	_test_eof150: cs = 150; goto _test_eof;
	_test_eof151: cs = 151; goto _test_eof;
	_test_eof152: cs = 152; goto _test_eof;
	_test_eof153: cs = 153; goto _test_eof;
	_test_eof154: cs = 154; goto _test_eof;
	_test_eof155: cs = 155; goto _test_eof;
	_test_eof156: cs = 156; goto _test_eof;
	_test_eof157: cs = 157; goto _test_eof;
	_test_eof158: cs = 158; goto _test_eof;
	_test_eof159: cs = 159; goto _test_eof;
	_test_eof160: cs = 160; goto _test_eof;
	_test_eof161: cs = 161; goto _test_eof;
	_test_eof162: cs = 162; goto _test_eof;
	_test_eof163: cs = 163; goto _test_eof;
	_test_eof164: cs = 164; goto _test_eof;
	_test_eof165: cs = 165; goto _test_eof;
	_test_eof166: cs = 166; goto _test_eof;
	_test_eof167: cs = 167; goto _test_eof;
	_test_eof168: cs = 168; goto _test_eof;
	_test_eof169: cs = 169; goto _test_eof;
	_test_eof170: cs = 170; goto _test_eof;
	_test_eof171: cs = 171; goto _test_eof;
	_test_eof172: cs = 172; goto _test_eof;
	_test_eof173: cs = 173; goto _test_eof;
	_test_eof174: cs = 174; goto _test_eof;
	_test_eof175: cs = 175; goto _test_eof;
	_test_eof176: cs = 176; goto _test_eof;
	_test_eof177: cs = 177; goto _test_eof;
	_test_eof178: cs = 178; goto _test_eof;
	_test_eof179: cs = 179; goto _test_eof;
	_test_eof180: cs = 180; goto _test_eof;
	_test_eof181: cs = 181; goto _test_eof;
	_test_eof182: cs = 182; goto _test_eof;
	_test_eof183: cs = 183; goto _test_eof;
	_test_eof184: cs = 184; goto _test_eof;
	_test_eof185: cs = 185; goto _test_eof;
	_test_eof186: cs = 186; goto _test_eof;
	_test_eof187: cs = 187; goto _test_eof;
	_test_eof188: cs = 188; goto _test_eof;
	_test_eof189: cs = 189; goto _test_eof;
	_test_eof190: cs = 190; goto _test_eof;
	_test_eof191: cs = 191; goto _test_eof;
	_test_eof192: cs = 192; goto _test_eof;
	_test_eof193: cs = 193; goto _test_eof;

	_test_eof: {}
	_out: {}
	}

#line 252 "/home/vagrant/src/dev/served/src/served/request_parser.rl"

	// ASSERT(p <= pe);

	nread += p - (buffer + d_offset);

	// ASSERT(nread <= len);
	// ASSERT(mark < len);
	// ASSERT(field_len <= len);
	// ASSERT(field_start < len);

	return(nread);
}

request_parser::status
request_parser::get_status()
{
	if ( parser_error() )
	{
		return status::Error;
	}
	else if ( parser_finished() )
	{
		return status::Finished;
	}
	else
	{
		return status::Running;
	}
}

bool
request_parser::parser_error()
{
	return (cs == request_parser_error);
}

bool
request_parser::parser_finished()
{
	return (cs == request_parser_first_final);
}
