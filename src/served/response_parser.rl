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

#include <served/response_parser.hpp>
#include <cstdlib> // strtol

#define LEN(AT, FPC) (FPC - data - AT)
#define MARK(M, FPC) (M = FPC - data)
#define PTR_TO(F)    (data + F)

using namespace served;
using namespace std;

/** machine **/
%%{
    machine response_parser;

    action mark { 
        MARK(mark, fpc);
    }

    action start_field { 
        MARK(field_start, fpc); 
    }

    action write_field {
        field_len = LEN(field_start, fpc);
    }

    action start_value { 
        MARK(mark, fpc); 
    }

    action write_content_len {
        content_len = strtol(PTR_TO(mark), NULL, 10);
    }

    action write_connection_close {
        //close = 1;
    }

    action write_value {
        http_field(data, PTR_TO(field_start), field_len, PTR_TO(mark), LEN(mark, fpc));
    }

    action reason_phrase {
        phrase_element(data, PTR_TO(mark), LEN(mark, fpc));
    }

    action status_code {
        //status = strtol(PTR_TO(mark), NULL, 10);
        status_code_element(data, PTR_TO(mark), LEN(mark, fpc));
    }

    action http_version {
        http_version_element(data, PTR_TO(mark), LEN(mark, fpc));
    }

    action chunk_size {
        //chunked = 1;
        content_len = strtol(PTR_TO(mark), NULL, 16);
        chunks_done = content_len <= 0;

        if(chunks_done) {
            last_chunk_element(data, PTR_TO(mark), LEN(mark, fpc));
        }
        else {
            chunk_size_element(data, PTR_TO(mark), LEN(mark, fpc));
        }
    }

    action trans_chunked {
        //chunked = 1;
    }

    action done {
        body_start = fpc - data + 1;
        header_done_element(data, fpc + 1, pe - fpc - 1);
        fbreak;
    }

	# line endings
    CRLF = ("\r\n" | "\n");

	# character types
    CTL = (cntrl | 127);
    tspecials = ("(" | ")" | "<" | ">" | "@" | "," | ";" | ":" | "\\" | "\"" | "/" | "[" | "]" | "?" | "=" | "{" | "}" | " " | "\t");

	# elements
    token = (ascii -- (CTL | tspecials));

    Reason_Phrase = (any -- CRLF)+ >mark %reason_phrase;
    Status_Code = digit+ >mark %status_code;
    http_number = (digit+ "." digit+) ;
    HTTP_Version = ("HTTP/" http_number) >mark %http_version ;
    Status_Line = HTTP_Version " " Status_Code " " Reason_Phrase :> CRLF;

    field_name = token+ >start_field %write_field;
    field_value = any* >start_value %write_value;
    fields = field_name ":" space* field_value :> CRLF;

    content_length = (/Content-Length/i >start_field %write_field ":" space *
            digit+ >start_value %write_content_len %write_value) CRLF;

    conn_close = (/Connection/i ":" space* /close/i) CRLF %write_connection_close;

    transfer_encoding_chunked = (/Transfer-Encoding/i >start_field %write_field
            ":" space* /chunked/i >start_value %write_value) CRLF @trans_chunked;

    message_header = transfer_encoding_chunked | conn_close | content_length | fields;

    Response = 	Status_Line (message_header)* CRLF;

    chunk_ext_val = token+;
    chunk_ext_name = token+;
    chunk_extension = (";" chunk_ext_name >start_field %write_field %start_value ("=" chunk_ext_val >start_value)? %write_value )*;
    chunk_size = xdigit+;
    Chunked_Header = chunk_size >mark %chunk_size chunk_extension :> CRLF;

    write data;

    main := (Response | Chunked_Header) @done;
}%%

response_parser::response_parser()
    : cs(0)
    , d_offset(0)
{
    %% write init;
}

response_parser::~response_parser()
{}

size_t 
response_parser::execute(const char *data, size_t len)  {
	size_t body_start  = 0;
	int    content_len = -1;
	int    chunks_done = 0;
	size_t mark        = 0;
	size_t field_start = 0;
	size_t field_len   = 0;
	size_t nread       = 0;
	
    const char *p  = data+d_offset;
    const char *pe = data+len;

    // ASSERT(*pe == '\0');

    %% write exec;

    nread += p - (data + d_offset);

    // ASSERT(p <= pe);
    // ASSERT(nread <= len);
    // ASSERT(body_start <= len);

    if (mark < len) {
        return -1;
    }
    if (field_len <= len) {
        return -1;
    }
    if (field_start < len) {
        return -1;
    }

    if(body_start) {
        /* final \r\n combo encountered so stop right here */
        nread++;
    }

	d_offset += nread;
    return(nread);
}

response_parser::status 
response_parser::get_status() {
    if (parser_error() ) {
        return ERROR;
    } else if (parser_finished() ) {
        return FINISHED;
    } else {
        return RUNNING;
    }
}

bool 
response_parser::parser_error() {
    return (cs == response_parser_error);
}

bool 
response_parser::parser_finished() {
    return (cs == response_parser_first_final);
}