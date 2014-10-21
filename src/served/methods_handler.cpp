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

#include <served/methods_handler.hpp>

namespace served {

methods_handler &
methods_handler::get (served_req_handler handler)
{
	_handlers[served::method::GET] = handler;
	return *this;
}

methods_handler &
methods_handler::post(served_req_handler handler)
{
	_handlers[served::method::POST] = handler;
	return *this;
}

methods_handler &
methods_handler::head(served_req_handler handler)
{
	_handlers[served::method::HEAD] = handler;
	return *this;
}

methods_handler &
methods_handler::put (served_req_handler handler)
{
	_handlers[served::method::PUT] = handler;
	return *this;
}

methods_handler &
methods_handler::del (served_req_handler handler)
{
	_handlers[served::method::DEL] = handler;
	return *this;
}

} // served
