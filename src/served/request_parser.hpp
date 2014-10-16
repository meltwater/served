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

#ifndef SERVED_REQUEST_PARSER_HPP
#define SERVED_REQUEST_PARSER_HPP

#include <sys/types.h> // size_t

namespace served {

class request_parser {
		int    cs;
		size_t d_offset;

	public:
		enum status { RUNNING = 0, FINISHED, ERROR };

	private:
		bool parser_error();

		bool parser_finished();

	protected:
		virtual void http_field(const char *data, const char *field, size_t flen,
				const char *value, size_t vlen) = 0;

		virtual void request_method(const char *data, const char *at,
				size_t length) = 0;

		virtual void request_uri(const char *data, const char *at,
				size_t length) = 0;

		virtual void fragment(const char *data, const char *at,
				size_t length) = 0;

		virtual void request_path(const char *data, const char *at,
				size_t length) = 0;

		virtual void query_string(const char *data, const char *at,
				size_t length) = 0;

		virtual void http_version(const char *data, const char *at,
				size_t length) = 0;

		virtual void header_done(const char *data, const char *at,
				size_t length) = 0;

	public:
		request_parser();

		virtual ~request_parser();

		size_t execute(const char *data, size_t len);

		status get_status();
};

} // served namespace

#endif // SERVED_REQUEST_PARSER_HPP
