/*
 * Copyright (C) MediaSift Ltd.
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

#include <test/catch.hpp>

#include <served/methods_handler.hpp>

bool search_method(std::vector<std::string> & vec, std::string s)
{
	for ( auto & v : vec )
	{
		if ( v == s )
		{
			return true;
		}
	}
	return false;
}

TEST_CASE("test methods handling", "[methods_handler]")
{
	SECTION("create handlers")
	{
		auto dummy = [](served::response &, const served::request &) {};

		served::methods_handler h("/dummy");
		h.post(dummy).get(dummy).method(served::method::CONNECT, dummy).put(dummy);

		CHECK(h.method_supported(served::method::POST) == true);
		CHECK(h.method_supported(served::method::GET) == true);
		CHECK(h.method_supported(served::method::CONNECT) == true);
		CHECK(h.method_supported(served::method::PUT) == true);

		CHECK(h.method_supported(served::method::DELETE) == false);
		CHECK(h.method_supported(served::method::HEAD) == false);
		CHECK(h.method_supported(served::method::BREW) == false);
	}

	SECTION("check endpoint propagation no description")
	{
		auto dummy = [](served::response &, const served::request &) {};

		served::methods_handler h("/this/path/is/great");
		h.post(dummy).get(dummy).method(served::method::CONNECT, dummy).put(dummy);

		served::served_endpoint_list list;
		h.propagate_endpoint(list);

		auto target = list.find("/this/path/is/great");
		REQUIRE(target != list.end());

		auto methods = target->second;

		CHECK(std::get<1>(methods).size() == 4);
		CHECK(std::get<0>(methods).empty());

		CHECK(search_method(std::get<1>(methods), "POST"));
		CHECK(search_method(std::get<1>(methods), "GET"));
		CHECK(search_method(std::get<1>(methods), "CONNECT"));
		CHECK(search_method(std::get<1>(methods), "PUT"));
	}

	SECTION("check endpoint propagation with description")
	{
		auto dummy = [](served::response &, const served::request &) {};

		served::methods_handler h("/this/path/is/great", "This is an endpoint for great stuff");
		h.get(dummy).put(dummy).del(dummy);

		served::served_endpoint_list list;
		h.propagate_endpoint(list);

		auto target = list.find("/this/path/is/great");
		REQUIRE(target != list.end());

		auto methods = target->second;

		CHECK(3 == std::get<1>(methods).size());
		CHECK("This is an endpoint for great stuff" == std::get<0>(methods));

		CHECK(search_method(std::get<1>(methods), "GET"));
		CHECK(search_method(std::get<1>(methods), "PUT"));
		CHECK(search_method(std::get<1>(methods), "DELETE"));
	}
}
