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

#include <sstream>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

#include <served/plugins.hpp>

namespace served { namespace plugin {

void access_log(const served::response & res, const served::request & req)
{
	std::stringstream ss;

	boost::posix_time::time_facet *facet = new boost::posix_time::time_facet("%d/%b/%Y:%H:%M:%S");
	ss.imbue(std::locale(ss.getloc(), facet));

	std::string source = req.source();
	if ( source.empty() )
	{
		source = "-";
	}

	ss << source << " - - [" << boost::posix_time::second_clock::local_time() << " -0000]";
	ss << " \"" << method_to_string(req.method()) << " " << req.url().path() << " " << req.HTTP_version() << "\"";
	ss << " " << res.status() << " " << res.body_size();

	std::cout << ss.str() << std::endl;
}

} } // plugin, served
