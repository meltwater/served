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

#include <served/multiplexer.hpp>

namespace served {

//  -----  constructors  -----

multiplexer::multiplexer()
	: _base_path("")
{
}

multiplexer::multiplexer(std::string const& base_path)
	: _base_path(base_path)
{
}

//  -----  plugin injection  -----

void
multiplexer::use_plugin(served_plugin_req_handler plugin)
{
	_plugin_handlers.push_back(plugin);
}

//  -----  http request handlers  -----

void
multiplexer::get(std::string const& path, served_req_handler handler)
{
}

void
multiplexer::head(std::string const& path, served_req_handler handler)
{
}

void
multiplexer::post(std::string const& path, served_req_handler handler)
{
}

void
multiplexer::put(std::string const& path, served_req_handler handler)
{
}

//  -----  server control  -----

void
multiplexer::listen(std::string const& address, std::string const& port)
{
}

void
multiplexer::stop()
{
}

} // served
