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

#include <served/served.hpp>

#include <boost/property_tree/json_parser.hpp>

/* json_data example
 *
 * This is a JSON data example of served in action.
 */
int main(int, char const**)
{
	served::multiplexer mux;

	mux.handle("/flat")
		.get([](served::response & res, const served::request &) {
			boost::property_tree::ptree root;
			std::stringstream ss;

			// Populate JSON response
			root.put("bool", true);
			root.put("integer", 123);
			root.put("string", "String");

			// Export JSON response
			boost::property_tree::json_parser::write_json(ss, root, true /* human */);
			res << ss.str();
		});

	mux.handle("/nested")
		.get([](served::response & res, const served::request &) {
			boost::property_tree::ptree root;
			boost::property_tree::ptree arrayTree;
			boost::property_tree::ptree flatTree;
			std::stringstream ss;

			// Populate JSON response
			flatTree.put("bool", true);
			flatTree.put("integer", 123);
			flatTree.put("string", "String");
			arrayTree.push_back(std::make_pair("", flatTree));
			arrayTree.push_back(std::make_pair("", flatTree));
			arrayTree.push_back(std::make_pair("", flatTree));
			root.add_child("node_array", arrayTree);
			root.add_child("node_1", flatTree);

			// Export JSON response
			boost::property_tree::json_parser::write_json(ss, root, true /* human */);
			res << ss.str();
		});

	std::cout << "Try this example with:" << std::endl;
	std::cout << " curl http://localhost:8123/flat" << std::endl;
	std::cout << " curl http://localhost:8123/nested" << std::endl;

	served::net::server server("127.0.0.1", "8123", mux);
	server.run(10); // Run with a pool of 10 threads.

	return 0;
}
