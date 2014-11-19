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

%%{
	machine request_parser;

	action mark
	{
		MARK(mark, fpc);
	}

	action start_field
	{
		MARK(field_start, fpc);
	}

	action write_field
	{
		field_len = LEN(field_start, fpc);
	}

	action start_value
	{
		MARK(mark, fpc);
	}

	action write_value
	{
		http_field(buffer, PTR_TO(field_start), field_len, PTR_TO(mark), LEN(mark, fpc));
	}

	action request_method
	{
		request_method(buffer, PTR_TO(mark), LEN(mark, fpc));
	}

	action request_uri
	{
		request_uri(buffer, PTR_TO(mark), LEN(mark, fpc));
	}

	action fragment
	{
		fragment(buffer, PTR_TO(mark), LEN(mark, fpc));
	}

	action start_query
	{
		MARK(query_start, fpc);
	}

	action query_string
	{
		query_string(buffer, PTR_TO(query_start), LEN(query_start, fpc));
	}

	action http_version
	{
		http_version(buffer, PTR_TO(mark), LEN(mark, fpc));
	}

	action request_path
	{
		request_path(buffer, PTR_TO(mark), LEN(mark,fpc));
	}

	action done
	{
		header_done(buffer, fpc + 1, pe - fpc - 1);
		fbreak;
	}

	#### HTTP PROTOCOL GRAMMAR

	CRLF = ( "\r\n" | "\n" ) ;

	# URI description as per RFC 3986.

	sub_delims    = ( "!" | "$" | "&" | "'" | "(" | ")" | "*"
	                | "+" | "," | ";" | "=" ) ;
	gen_delims    = ( ":" | "/" | "?" | "#" | "[" | "]" | "@" ) ;
	reserved      = ( gen_delims | sub_delims ) ;
	unreserved    = ( alpha | digit | "-" | "." | "_" | "~" ) ;

	pct_encoded   = ( "%" xdigit xdigit ) ;

	pchar         = ( unreserved | pct_encoded | sub_delims | ":" | "@" ) ;

	fragment      = ( ( pchar | "/" | "?" )* ) >mark %fragment ;

	query         = ( ( pchar | "/" | "?" )* ) %query_string ;

	# non_zero_length segment without any colon ":" ) ;
	segment_nz_nc = ( ( unreserved | pct_encoded | sub_delims | "@" )+ ) ;
	segment_nz    = ( pchar+ ) ;
	segment       = ( pchar* ) ;

	path_empty    = ( pchar{0} ) ;
	path_rootless = ( segment_nz ( "/" segment )* ) ;
	path_noscheme = ( segment_nz_nc ( "/" segment )* ) ;
	path_absolute = ( "/" ( segment_nz ( "/" segment )* )? ) ;
	path_abempty  = ( ( "/" segment )* ) ;

	path          = ( path_abempty    # begins with "/" or is empty
	                | path_absolute   # begins with "/" but not "//"
	                | path_noscheme   # begins with a non-colon segment
	                | path_rootless   # begins with a segment
	                | path_empty      # zero characters
	                ) ;

	reg_name      = ( unreserved | pct_encoded | sub_delims )* ;

	dec_octet     = ( digit                 # 0-9
	                | ("1"-"9") digit         # 10-99
	                | "1" digit{2}          # 100-199
	                | "2" ("0"-"4") digit # 200-249
	                | "25" ("0"-"5")      # 250-255
	                ) ;

	IPv4address   = ( dec_octet "." dec_octet "." dec_octet "." dec_octet ) ;
	h16           = ( xdigit{1,4} ) ;
	ls32          = ( ( h16 ":" h16 ) | IPv4address ) ;

	IPv6address   = (                               6( h16 ":" ) ls32
	                |                          "::" 5( h16 ":" ) ls32
	                | (                 h16 )? "::" 4( h16 ":" ) ls32
	                | ( ( h16 ":" ){1,} h16 )? "::" 3( h16 ":" ) ls32
	                | ( ( h16 ":" ){2,} h16 )? "::" 2( h16 ":" ) ls32
	                | ( ( h16 ":" ){3,} h16 )? "::"    h16 ":"   ls32
	                | ( ( h16 ":" ){4,} h16 )? "::"              ls32
	                | ( ( h16 ":" ){5,} h16 )? "::"              h16
	                | ( ( h16 ":" ){6,} h16 )? "::"
	                ) ;

	IPvFuture     = ( "v" xdigit+ "." ( unreserved | sub_delims | ":" )+ ) ;

	IP_literal    = ( "[" ( IPv6address | IPvFuture  ) "]" ) ;

	port          = ( digit* ) ;
	host          = ( IP_literal | IPv4address | reg_name ) ;
	userinfo      = ( ( unreserved | pct_encoded | sub_delims | ":" )* ) ;
	authority     = ( ( userinfo "@" )? host ( ":" port )? ) ;

	scheme        = ( alpha ( alpha | digit | "+" | "-" | "." )* ) ;

	relative_part = ( "//" authority path_abempty
	                | path_absolute
	                | path_noscheme
	                | path_empty
	                ) ;


	hier_part     = ( "//" authority path_abempty
	                | path_absolute
	                | path_rootless
	                | path_empty
	                ) ;

	absolute_URI  = ( scheme ":" hier_part ( "?" query )? ) ;

	relative_ref  = ( (relative_part %request_path ( "?" %start_query query )?) >mark %request_uri ( "#" fragment )? ) ;
	URI           = ( scheme ":" (hier_part  %request_path ( "?" %start_query query )?) >mark %request_uri ( "#" fragment )? ) ;

	URI_reference = ( URI | relative_ref ) ;

	# HTTP header parsing
	Method = ( upper | digit ){1,20} >mark %request_method;

	http_number  = ( "1." ("0" | "1") ) ;
	HTTP_Version = ( "HTTP/" http_number ) >mark %http_version ;
	Request_Line = ( Method " " URI_reference " " HTTP_Version CRLF ) ;

	HTTP_CTL = (0 - 31) | 127 ;
	HTTP_separator = ( "(" | ")" | "<" | ">" | "@"
	                 | "," | ";" | ":" | "\\" | "\""
	                 | "/" | "[" | "]" | "?" | "="
	                 | "{" | "}" | " " | "\t"
	                 ) ;

	lws = CRLF? (" " | "\t")+ ;
	token = ascii -- ( HTTP_CTL | HTTP_separator ) ;
	content = ((any -- HTTP_CTL) | lws);

	field_name = ( token )+ >start_field %write_field;

	field_value = content* >start_value %write_value;

	message_header = field_name ":" lws* field_value :> CRLF;

	Request = Request_Line ( message_header )* ( CRLF );

	write data;

	main := Request @done;
}%%

request_parser::request_parser()
	: cs(0)
	, d_offset(0)
{
	%% write init;
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

	%% write exec;

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
		return ERROR;
	}
	else if ( parser_finished() )
	{
		return FINISHED;
	}
	else
	{
		return RUNNING;
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
