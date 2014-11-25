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

#ifndef SERVED_PLUGINS_HPP
#define SERVED_PLUGINS_HPP

#include <served/response.hpp>
#include <served/request.hpp>
#include <functional>

namespace served { namespace plugin {

/*
 * A plug in for logging HTTP requests to stdout.
 *
 * In order to log each request and the responses given you should register this plugin with
 * use_after.
 *
 * @param res the response object for the HTTP connection
 * @param request the request object for the HTTP connection
 */
void access_log(served::response & res, const served::request & request);

/*
 * NOT IMPLEMENTED: Generates a static file handler.
 *
 * Provide a file directory and an optional base path to trim from request resources and a static
 * file server for that directory is generated.
 *
 * @param file_directory the path to search for files within
 * @param base_path an optional string to trim from the start of request resource paths
 * @return the static file handler to register
 */
/*
std::function<void(served::response &, const served::request &)>
file_server(const std::string & file_directory, const std::string & base_path = "");
*/

} } // plugin, served

#endif // SERVED_PLUGINS_HPP
