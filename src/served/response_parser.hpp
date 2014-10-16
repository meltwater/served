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

#ifndef SERVED_RESPONSE_PARSER_HPP
#define SERVED_RESPONSE_PARSER_HPP

#include <sys/types.h> // size_t

namespace served {

class response_parser {
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

		virtual void phrase_element(const char *data, const char *at,
				size_t length) = 0;

		virtual void status_code_element(const char *data, const char *at,
				size_t length) = 0;

		virtual void chunk_size_element(const char *data, const char *at,
				size_t length) = 0;

		virtual void http_version_element(const char *data, const char *at,
				size_t length) = 0;

		virtual void header_done_element(const char *data, const char *at,
				size_t length) = 0;

		virtual void last_chunk_element(const char *data, const char *at,
				size_t length) = 0;

	public:
		response_parser();

		virtual ~response_parser();

		size_t execute(const char *data, size_t len);

		status get_status();
};

} // served namespace

#endif // SERVED_RESPONSE_PARSER_HPP
