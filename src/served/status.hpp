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
 * TBC
 */
inline const std::string
status_to_reason(int status_code)
{
	switch ( status_code )
	{
	case status_1XX::CONTINUE:
		return "CONTINUE";
	case status_2XX::OK:
		return "OK";
	// TODO
	}
	return "-";
}

} } // status served

#endif // SERVED_STATUS_HPP
