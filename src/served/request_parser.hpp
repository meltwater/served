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

/*
 * HTTP 1.1 compatible request parser.
 *
 * This class implements a SAX style HTTP request parser.
 *
 * To use the parser you must create a subclass and inherit the callback methods
 * , then create an instance and call the execute() method with the request
 * string.
 *
 * class request_parser_impl : public request_parser {
 *     // ...
 * }
 *
 * bool parse(const char* req_str) {
 *     request_parser_impl parser;
 *     parser.execute(req_str);
 *     return (parser.parser_error());
 * }
 *
 * This parser is implemented in a SAX style because it provides a sufficient
 * trade-off between performance and usability for the intended use-case. Note
 * that the methods of the parser are not thread-safe.
 */
class request_parser {
	int    cs;
	size_t d_offset;

public:

	enum status { RUNNING = 0, FINISHED, ERROR };

private:
	/*
	 * Check whether the parser encountered an error during parsing.
	 *
	 * This method will check for an error. If a badly formed input string was
	 * given to the execute() method then this function will return true. This
	 * function should only be invoked after the execute() method.
	 *
	 * @return true if an error was encountered, otherwise false.
	 */
	bool parser_error();

	/*
	 * Check whether the parser is finished.
	 *
	 * This method will check whether the parser has finished parsing, or if it
	 * is waiting for more input. If the input given to execute() is correct but
	 * partially formed, then this method will return true.
	 *
	 * @return true if the parser has finished, otherwise false.
	 */
	bool parser_finished();

protected:
	/*
	 * HTTP field callback.
	 *
	 * @param data   pointer to the beginning of the input string
	 * @param field  pointer to the beginning of the matched field
	 * @param flen   length of the matched field string
	 * @param value  pointer to the beginning of the matched value
	 * @param vlen   length of the matched value string
	 */
	virtual void http_field(const char *data, const char *field, size_t flen,
			const char *value, size_t vlen) = 0;

	/*
	 * HTTP request method callback.
	 *
	 * @param data   pointer to the beginning of the input string
	 * @param at     pointer to the beginning of the matched string
	 * @param length length of the matched string data
	 */
	virtual void request_method(const char *data, const char *at,
			size_t length) = 0;

	/*
	 * URI callback.
	 *
	 * @param data   pointer to the beginning of the input string
	 * @param at     pointer to the beginning of the matched string
	 * @param length length of the matched string data
	 */
	virtual void request_uri(const char *data, const char *at,
			size_t length) = 0;

	/*
	 * Fragment callback.
	 *
	 * @param data   pointer to the beginning of the input string
	 * @param at     pointer to the beginning of the matched string
	 * @param length length of the matched string data
	 */
	virtual void fragment(const char *data, const char *at,
			size_t length) = 0;

	/*
	 * Request path callback.
	 *
	 * @param data   pointer to the beginning of the input string
	 * @param at     pointer to the beginning of the matched string
	 * @param length length of the matched string data
	 */
	virtual void request_path(const char *data, const char *at,
			size_t length) = 0;

	/*
	 * Query string callback.
	 *
	 * @param data   pointer to the beginning of the input string
	 * @param at     pointer to the beginning of the matched string
	 * @param length length of the matched string data
	 */
	virtual void query_string(const char *data, const char *at,
			size_t length) = 0;

	/*
	 * HTTP version callback.
	 *
	 * @param data   pointer to the beginning of the input string
	 * @param at     pointer to the beginning of the matched string
	 * @param length length of the matched string data
	 */
	virtual void http_version(const char *data, const char *at,
			size_t length) = 0;

	/*
	 * HTTP header done callback.
	 *
	 * @param data   pointer to the beginning of the input string
	 * @param at     pointer to the beginning of the matched string
	 * @param length length of the matched string data
	 */
	virtual void header_done(const char *data, const char *at,
			size_t length) = 0;

public:
	/*
	 * Default constructor.
	 */
	request_parser();

	/*
	 * Class destructor.
	 */
	virtual ~request_parser();

	/*
	 * Execute the parser.
	 *
	 * Executes the parser with the given input string. Invoking this method
	 * will in turn invoke the callback methods in the order that the sequences
	 * are identified in the input string.
	 *
	 * @param data input string to parse
	 * @param len  length of the input string in bytes
	 */
	size_t execute(const char *data, size_t len);

	/*
	 * Get the parser status.
	 *
	 * Returns the status of the parser. This method should only be called after
	 * execute().
	 *
	 * @return current parser status
	 */
	status get_status();
};

} // served namespace

#endif // SERVED_REQUEST_PARSER_HPP
