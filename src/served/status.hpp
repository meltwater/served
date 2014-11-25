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

#ifndef SERVED_STATUS_HPP
#define SERVED_STATUS_HPP

#include <string>

namespace served {

namespace status_1XX {
	// 1XX - Informational
	const int CONTINUE            = 100;
	const int SWITCHING_PROTOCOLS = 101;
	const int PROCESSING          = 102;
}

namespace status_2XX {
	// 2XX - Success
	const int OK                   = 200;
	const int CREATED              = 201;
	const int ACCEPTED             = 202;
	const int NON_AUTHORITIVE_INFO = 203;
	const int NO_CONTENT           = 204;
	const int RESET_CONTENT        = 205;
	const int PARTIAL_CONTENT      = 206;
	const int MULTI_STATUS         = 207;
	const int ALREADY_REPORTED     = 208;
	const int IM_USED              = 226;
}

namespace status_3XX {
	// 3XX - Redirectional
	const int MULTI_CHOICES     = 300;
	const int MOVED_PERMANENTLY = 301;
	const int FOUND             = 302;
	const int SEE_OTHER         = 303;
	const int NOT_MODIFIED      = 304;
	const int USE_PROXY         = 305;
	const int SWITCH_PROXY      = 306;
	const int TEMP_REDIRECT     = 307;
	const int PERM_REDIRECT     = 308;
}

namespace status_4XX {
	// 4XX - Client error
	const int BAD_REQUEST                 = 400;
	const int UNAUTHORIZED                = 401;
	const int PAYMENT_REQUIRED            = 402;
	const int FORBIDDEN                   = 403;
	const int NOT_FOUND                   = 404;
	const int METHOD_NOT_ALLOWED          = 405;
	const int NOT_ACCEPTABLE              = 406;
	const int PROXY_AUTH_REQUIRED         = 407;
	const int REQUEST_TIMEOUT             = 408;
	const int CONFLICT                    = 409;
	const int GONE                        = 410;
	const int LENGTH_REQUIRED             = 411;
	const int PRECONDITION_FAILED         = 412;
	const int REQ_ENTITY_TOO_LARGE        = 413;
	const int REQ_URI_TOO_LONG            = 414;
	const int UNSUPPORTED_MEDIA_TYPE      = 415;
	const int REQ_RANGE_NOT_SATISFYABLE   = 416;
	const int EXPECTATION_FAILED          = 417;
	const int IM_A_TEAPOT                 = 418;
	const int AUTH_TIMEOUT                = 419; // not in RFC 2616
	const int UNPROCESSABLE_ENTITY        = 422;
	const int LOCKED                      = 423;
	const int FAILED_DEPENDENCY           = 424;
	const int UPGRADE_REQUIRED            = 426;
	const int PRECONDITION_REQUIRED       = 428;
	const int TOO_MANY_REQUESTS           = 429;
	const int REQ_HEADER_FIELDS_TOO_LARGE = 431;
}

namespace status_5XX {
	// 5XX - Server error
	const int INTERNAL_SERVER_ERROR       = 500;
	const int NOT_IMPLEMENTED             = 501;
	const int BAD_GATEWAY                 = 502;
	const int SERVICE_UNAVAILABLE         = 503;
	const int GATEWAY_TIMEOUT             = 504;
	const int HTTP_VERSION_NOT_SUPPORTED  = 505;
	const int VARIANT_ALSO_NEGOTIATES     = 506;
	const int INSUFFICIENT_STORAGE        = 507;
	const int LOOP_DETECTED               = 508;
	const int NOT_EXTENDED                = 510;
	const int NETWORK_AUTH_REQUIRED       = 511;
	const int NETWORK_READ_TIMEOUT_ERR    = 598;
	const int NETWORK_CONNECT_TIMEOUT_ERR = 599;
}

namespace status {

/*
 * Converts an HTTP status code into a known reason string.
 *
 * The reason string is a small line of text that gives a hint as to the underlying meaning of the
 * status code for debugging purposes.
 */
inline const std::string
status_to_reason(int status_code)
{
	switch ( status_code )
	{
	// 1XX - Informational
	case status_1XX::CONTINUE:
		return "CONTINUE";
	case status_1XX::SWITCHING_PROTOCOLS:
		return "SWITCHING PROTOCOLS";
	case status_1XX::PROCESSING:
		return "PROCESSING";
	// 2XX - Success
	case status_2XX::OK:
		return "OK";
	case status_2XX::CREATED:
		return "CREATED";
	case status_2XX::ACCEPTED:
		return "ACCEPTED";
	case status_2XX::NON_AUTHORITIVE_INFO:
		return "NON AUTHORITIVE INFO";
	case status_2XX::NO_CONTENT:
		return "NO CONTENT";
	case status_2XX::RESET_CONTENT:
		return "RESET CONTENT";
	case status_2XX::PARTIAL_CONTENT:
		return "PARTIAL CONTENT";
	case status_2XX::MULTI_STATUS:
		return "MULTI STATUS";
	case status_2XX::ALREADY_REPORTED:
		return "ALREADY REPORTED";
	case status_2XX::IM_USED:
		return "IM USED";
	// 3XX - Redirectional
	case status_3XX::MULTI_CHOICES:
		return "MULTI CHOICES";
	case status_3XX::MOVED_PERMANENTLY:
		return "MOVED PERMANENTLY";
	case status_3XX::FOUND:
		return "FOUND";
	case status_3XX::SEE_OTHER:
		return "SEE OTHER";
	case status_3XX::NOT_MODIFIED:
		return "NOT MODIFIED";
	case status_3XX::USE_PROXY:
		return "USE PROXY";
	case status_3XX::SWITCH_PROXY:
		return "SWITCH PROXY";
	case status_3XX::TEMP_REDIRECT:
		return "TEMP REDIRECT";
	case status_3XX::PERM_REDIRECT:
		return "PERM REDIRECT";
	// 4XX - Client error
	case status_4XX::BAD_REQUEST:
		return "BAD REQUEST";
	case status_4XX::UNAUTHORIZED:
		return "UNAUTHORIZED";
	case status_4XX::PAYMENT_REQUIRED:
		return "PAYMENT REQUIRED";
	case status_4XX::FORBIDDEN:
		return "FORBIDDEN";
	case status_4XX::NOT_FOUND:
		return "NOT FOUND";
	case status_4XX::METHOD_NOT_ALLOWED:
		return "METHOD NOT ALLOWED";
	case status_4XX::NOT_ACCEPTABLE:
		return "NOT ACCEPTABLE";
	case status_4XX::PROXY_AUTH_REQUIRED:
		return "PROXY AUTH REQUIRED";
	case status_4XX::REQUEST_TIMEOUT:
		return "REQUEST TIMEOUT";
	case status_4XX::CONFLICT:
		return "CONFLICT";
	case status_4XX::GONE:
		return "GONE";
	case status_4XX::LENGTH_REQUIRED:
		return "LENGTH REQUIRED";
	case status_4XX::PRECONDITION_FAILED:
		return "PRECONDITION FAILED";
	case status_4XX::REQ_ENTITY_TOO_LARGE:
		return "REQ ENTITY TOO LARGE";
	case status_4XX::REQ_URI_TOO_LONG:
		return "REQ URI TOO LONG";
	case status_4XX::UNSUPPORTED_MEDIA_TYPE:
		return "UNSUPPORTED MEDIA TYPE";
	case status_4XX::REQ_RANGE_NOT_SATISFYABLE:
		return "REQ RANGE NOT SATISFYABLE";
	case status_4XX::EXPECTATION_FAILED:
		return "EXPECTATION FAILED";
	case status_4XX::IM_A_TEAPOT:
		return "IM A TEAPOT";
	case status_4XX::AUTH_TIMEOUT: // not in RFC 2616
		return "AUTH TIMEOUT";
	case status_4XX::UNPROCESSABLE_ENTITY:
		return "UNPROCESSABLE ENTITY";
	case status_4XX::LOCKED:
		return "LOCKED";
	case status_4XX::FAILED_DEPENDENCY:
		return "FAILED DEPENDENCY";
	case status_4XX::UPGRADE_REQUIRED:
		return "UPGRADE REQUIRED";
	case status_4XX::PRECONDITION_REQUIRED:
		return "PRECONDITION REQUIRED";
	case status_4XX::TOO_MANY_REQUESTS:
		return "TOO MANY REQUESTS";
	case status_4XX::REQ_HEADER_FIELDS_TOO_LARGE:
		return "REQ HEADER FIELDS TOO LARGE";
	// 5XX - Server error
	case status_5XX::INTERNAL_SERVER_ERROR:
		return "INTERNAL SERVER ERROR";
	case status_5XX::NOT_IMPLEMENTED:
		return "NOT IMPLEMENTED";
	case status_5XX::BAD_GATEWAY:
		return "BAD GATEWAY";
	case status_5XX::SERVICE_UNAVAILABLE:
		return "SERVICE UNAVAILABLE";
	case status_5XX::GATEWAY_TIMEOUT:
		return "GATEWAY TIMEOUT";
	case status_5XX::HTTP_VERSION_NOT_SUPPORTED:
		return "HTTP VERSION NOT SUPPORTED";
	case status_5XX::VARIANT_ALSO_NEGOTIATES:
		return "VARIANT ALSO NEGOTIATES";
	case status_5XX::INSUFFICIENT_STORAGE:
		return "INSUFFICIENT STORAGE";
	case status_5XX::LOOP_DETECTED:
		return "LOOP DETECTED";
	case status_5XX::NOT_EXTENDED:
		return "NOT EXTENDED";
	case status_5XX::NETWORK_AUTH_REQUIRED:
		return "NETWORK AUTH REQUIRED";
	case status_5XX::NETWORK_READ_TIMEOUT_ERR:
		return "NETWORK READ TIMEOUT ERR";
	case status_5XX::NETWORK_CONNECT_TIMEOUT_ERR:
		return "NETWORK CONNECT TIMEOUT ERR";
	}
	return "-";
}

} } // status served

#endif // SERVED_STATUS_HPP
