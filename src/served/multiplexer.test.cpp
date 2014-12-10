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

#define CATCH_CONFIG_MAIN
#include "../test/catch.hpp"

#include <vector>

#include <served/status.hpp>
#include <served/request_error.hpp>
#include <served/multiplexer.hpp>
#include <served/methods.hpp>
#include <served/parameters.hpp>
#include <served/version.hpp>

struct request_router_story
{
	std::string              pattern;
	std::vector<std::string> expected_200s;
	std::vector<std::string> expected_404s;

	std::vector<std::string> received;

	served::parameters       params;
};

class path_collecting_functor
{
	request_router_story & _story_obj;
public:
	path_collecting_functor(request_router_story & story_obj)
		: _story_obj(story_obj) {}

	void operator()(served::response & response, const served::request & request)
	{
		_story_obj.received.push_back(request.url().path());
		_story_obj.params = request.params;
	}
};

TEST_CASE("multiplexer path routing", "[mux]")
{
	SECTION("request router stories")
	{
		std::vector<request_router_story> stories;

		// static1
		stories.push_back(request_router_story());
		stories.back().pattern = "/static1/foo/bar";
		stories.back().expected_200s = {
			"/static1/foo/bar",
			"/static1/foo/bar/",
			"/static1/foo/bar/bob",
		};
		stories.back().expected_404s = {
			"/static1/bar/foo",
			"/static1/foo/bar2",
		};

		// variable1
		stories.push_back(request_router_story());
		stories.back().pattern = "/variable1/{first}/{second}";
		stories.back().expected_200s = {
			"/variable1/foo/bar",
			"/variable1/bar/bob",
			"/variable1/bob/baz",
			"/variable1/this/variable",
			"/variable1/variable/variable",
			"/variable1/variable/variable/more_ignored_variables",
			"/variable1/test1/test2/test3",
		};
		stories.back().expected_404s = {
			"/variable1//variable",
			"/variable1/test1/",
		};

		// variable2
		stories.push_back(request_router_story());
		stories.back().pattern = "/variable2/{first}/{second}/";
		stories.back().expected_200s = {
			"/variable2/foo/bar/",
			"/variable2/foo/bar/things/test",
			"/variable2/this/variable/wat",
			"/variable2/test1/test2/test3",
		};
		stories.back().expected_404s = {
			"/variable2/this/variable",
			"/variable2//variable",
		};

		// regex1
		stories.push_back(request_router_story());
		stories.back().pattern = "/regex1/{number:[0-9]+}/{text:[a-zA-Z]+}";
		stories.back().expected_200s = {
			"/regex1/343234534/fGSDFGfdsgdfgsdfgfsFGDSF",
			"/regex1/1/f",
			"/regex1/132432/HELLOWORLD",
		};
		stories.back().expected_404s = {
			"/regex1/nan/hello",
			"/regex1/343a/hello",
			"/regex1/343/hello5",
			"/regex1/343/55",
		};

		// regex2
		stories.push_back(request_router_story());
		stories.back().pattern = "/regex2/{number:[0-9]+}/{:[0-9]+}";
		stories.back().expected_200s = {
			"/regex2/5/4353",
			"/regex2/1/3243",
			"/regex2/132432/0",
		};
		stories.back().expected_404s = {
			"/regex2/nan/34k",
			"/regex2/343a/wat",
			"/regex2/wa/4534",
			"/regex2/hey/55",
		};

		// begin stories
		served::multiplexer mux;

		// Register handlers for each story
		for ( auto & story : stories )
		{
			mux.handle(story.pattern)
				.get(path_collecting_functor(story));
		}

		for ( auto & story : stories )
		{
			for ( const auto & path : story.expected_200s )
			{
				served::uri url;
				url.set_path(path);

				served::request req;
				req.set_destination(url);
				req.set_method(served::method::GET);

				served::response res;

				INFO( "checking for 200 at: " << path );
				CHECK_NOTHROW(mux.forward_to_handler(res, req));
			}

			for ( const auto & path : story.expected_404s )
			{
				served::uri url;
				url.set_path(path);

				served::request req;
				req.set_destination(url);
				req.set_method(served::method::GET);

				served::response res;

				INFO( "checking for 404 at: " << path );
				CHECK_THROWS_AS(mux.forward_to_handler(res, req), served::request_error);
			}

			INFO( "comparing size of received for pattern: " << story.pattern );
			CHECK( story.expected_200s.size() == story.received.size() );
			for ( int i = 0; i < story.expected_200s.size(); i++ )
			{
				CHECK( story.expected_200s[i] == story.received[i] );
			}
		}
	}
}

TEST_CASE("multiplexer method routing", "[mux]")
{
	SECTION("Confirm not accept GET")
	{
		request_router_story s1;
		s1.pattern = "/foo/bar";

		// This route should be disregarded in favour of a 405 error from the previous route.
		request_router_story s2;
		s2.pattern = "/foo";

		served::multiplexer mux;
		mux.handle(s1.pattern)
			.post(path_collecting_functor(s1))
			.head(path_collecting_functor(s1))
			.put(path_collecting_functor(s1))
			.del(path_collecting_functor(s1));

		// Should be disregarded even for a /GET
		mux.handle(s2.pattern).get(path_collecting_functor(s2));

		try
		{
			INFO("Confirming exception was 405 NOT ALLOWED");

			served::response res;
			served::request req;
			served::uri url;

			url.set_path(s1.pattern);
			req.set_destination(url);
			req.set_method(served::method::GET);

			mux.forward_to_handler( res, req );

			// Should have thrown by this point.
			CHECK(false);
		}
		catch (const served::request_error & e)
		{
			INFO("Confirming exception was 405 NOT ALLOWED");
			CHECK(e.get_status_code() == served::status_4XX::METHOD_NOT_ALLOWED);
		}

		{
			served::response res;
			served::request req;
			served::uri url;

			url.set_path(s1.pattern);
			req.set_destination(url);

			INFO("Checking accepts PUT");
			req.set_method(served::method::PUT);
			CHECK_NOTHROW(mux.forward_to_handler( res, req ));

			INFO("Checking accepts DEL");
			req.set_method(served::method::DELETE);
			CHECK_NOTHROW(mux.forward_to_handler( res, req ));

			INFO("Checking accepts HEAD");
			req.set_method(served::method::HEAD);
			CHECK_NOTHROW(mux.forward_to_handler( res, req ));

			INFO("Checking accepts POST");
			req.set_method(served::method::POST);
			CHECK_NOTHROW(mux.forward_to_handler( res, req ));

			INFO("Checking for correct routing (4 requests)");
			CHECK(s1.received.size() == 4);
		}
	}
}

TEST_CASE("multiplexer overwriting", "[mux]")
{
	SECTION("Confirm overwrite not accept GET")
	{
		request_router_story s1;
		s1.pattern = "/foo/bar";

		request_router_story s2;
		s2.pattern = "/foo/bar";

		served::multiplexer mux;
		mux.handle(s1.pattern)
			.post(path_collecting_functor(s1))
			.del(path_collecting_functor(s1));

		mux.handle(s2.pattern)
			.get(path_collecting_functor(s2))
			.head(path_collecting_functor(s2))
			.put(path_collecting_functor(s2));

		try
		{
			INFO("Confirming exception was 405 NOT ALLOWED");

			served::response res;
			served::request req;
			served::uri url;

			url.set_path(s1.pattern);
			req.set_destination(url);
			req.set_method(served::method::POST);

			mux.forward_to_handler( res, req );

			// Should have thrown by this point.
			CHECK(false);
		}
		catch (const served::request_error & e)
		{
			INFO("Confirming exception was 405 NOT ALLOWED");
			CHECK(e.get_status_code() == served::status_4XX::METHOD_NOT_ALLOWED);
		}

		{
			served::response res;
			served::request req;
			served::uri url;

			url.set_path(s1.pattern);
			req.set_destination(url);

			INFO("Checking accepts GET");
			req.set_method(served::method::GET);
			CHECK_NOTHROW(mux.forward_to_handler( res, req ));

			INFO("Checking accepts HEAD");
			req.set_method(served::method::HEAD);
			CHECK_NOTHROW(mux.forward_to_handler( res, req ));

			INFO("Checking accepts PUT");
			req.set_method(served::method::PUT);
			CHECK_NOTHROW(mux.forward_to_handler( res, req ));

			INFO("Checking for no routed requests to overridden handler (0 requests)");
			CHECK(s1.received.size() == 0);

			INFO("Checking for all routed requests to override handler (3 requests)");
			CHECK(s2.received.size() == 3);
		}
	}
}

TEST_CASE("multiplexer hierarchy test", "[mux]")
{
	SECTION("shorter pattern first")
	{
		bool correct_call = false;

		auto dummy_call    = [&](served::response & res, const served::request & req) {};
		auto expected_call = [&](served::response & res, const served::request & req) {
			correct_call = true;
		};

		served::multiplexer mux;
		mux.handle("/"            ).get(expected_call);
		mux.handle("/first/second").get(dummy_call);
		mux.handle("/testing"     ).get(dummy_call);

		served::response res;
		served::request req;
		served::uri url;

		url.set_path("/first/second");
		req.set_destination(url);
		req.set_method(served::method::GET);

		mux.forward_to_handler( res, req );

		CHECK(correct_call);
	}

	SECTION("longer pattern first")
	{
		bool correct_call = false;

		auto dummy_call    = [&](served::response & res, const served::request & req) {};
		auto expected_call = [&](served::response & res, const served::request & req) {
			correct_call = true;
		};

		served::multiplexer mux;
		mux.handle("/first/second/third").get(dummy_call);
		mux.handle("/first/second"      ).get(expected_call);
		mux.handle("/testing"           ).get(dummy_call);
		mux.handle("/"                  ).get(dummy_call);

		served::response res;
		served::request req;
		served::uri url;

		url.set_path("/first/second");
		req.set_destination(url);
		req.set_method(served::method::GET);

		mux.forward_to_handler( res, req );

		CHECK(correct_call);
	}
}

TEST_CASE("multiplexer REST params test", "[mux]")
{
	SECTION("Confirm params created")
	{
		request_router_story s;

		served::multiplexer mux;
		mux.handle("/base/{TEST}/end").get(path_collecting_functor(s));

		served::response res;
		served::request req;
		served::uri url;

		url.set_path("/base/expected_123/end");
		req.set_destination(url);
		req.set_method(served::method::GET);

		mux.forward_to_handler( res, req );

		CHECK(s.params.get("TEST") == "expected_123");
	}
}

TEST_CASE("multiplexer test base path", "[mux]")
{
	SECTION("Use base path")
	{
		served::multiplexer mux("/base/path");
		mux.handle("/end").get([](served::response & res, const served::request & req){
			res.set_status(served::status_2XX::ACCEPTED);
		});
		mux.handle("/").get([](served::response & res, const served::request & req){
			res.set_status(served::status_2XX::NO_CONTENT);
		});

		{
			served::response res;
			served::request req;
			served::uri url;

			url.set_path("/base/path/end");
			req.set_destination(url);
			req.set_method(served::method::GET);

			mux.forward_to_handler( res, req );
			CHECK( res.status() == served::status_2XX::ACCEPTED );
		}
		{
			served::response res;
			served::request req;
			served::uri url;

			url.set_path("/base/path/");
			req.set_destination(url);
			req.set_method(served::method::GET);

			mux.forward_to_handler( res, req );
			CHECK( res.status() == served::status_2XX::NO_CONTENT );
		}
		{
			served::response res;
			served::request req;
			served::uri url;

			url.set_path("/base/not/end");
			req.set_destination(url);
			req.set_method(served::method::GET);

			CHECK_THROWS_AS(mux.forward_to_handler(res, req), served::request_error);
		}
	}

	SECTION("Confirm params created")
	{
		served::multiplexer mux("/base/{TEST}");
		mux.handle("/end").get([](served::response & res, const served::request & req) {
			res.set_status(served::status_2XX::OK);
		});

		served::response res;
		served::request req;
		served::uri url;

		url.set_path("/base/expected_123/end");
		req.set_destination(url);
		req.set_method(served::method::GET);

		mux.forward_to_handler( res, req );

		CHECK(req.params["TEST"] == "expected_123");
	}
}

TEST_CASE("multiplexer test plugins", "[mux]")
{
	SECTION("Before plugin")
	{
		int touches = 0;
		served::multiplexer mux;
		mux.handle("/test")
			.get([&](served::response & res, const served::request & req) {
				if ( touches == 1 )
				{
					touches++;
				}
			});
		mux.use_before([&](served::response & res, const served::request & req) {
			if ( touches == 0 )
			{
				touches++;
			}
		});
		mux.use_after([&](served::response & res, const served::request & req) {
			if ( touches == 2 )
			{
				touches++;
			}
		});

		served::response res;
		served::request req;
		served::uri url;

		url.set_path("/test");
		req.set_destination(url);
		req.set_method(served::method::GET);

		mux.forward_to_handler(res, req);
		mux.on_request_handled(res, req);

		CHECK(touches == 3);
	}
}

bool search(std::vector<std::string> & vec, std::string s)
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

TEST_CASE("multiplexer test endpoint list", "[mux]")
{
	SECTION("without base path")
	{
		auto dummy = [](served::response & res, const served::request & req){};

		served::multiplexer mux;
		mux.handle("/first/test", "This is first").get(dummy).post(dummy).del(dummy);
		mux.handle("/second/test", "This is second").get(dummy).del(dummy);
		mux.handle("/third/test", "This is third").put(dummy);

		auto list = mux.get_endpoint_list();

		{
			auto target = list.find("/first/test");
			REQUIRE(target != list.end());

			auto methods = std::get<1>(target->second);
			auto info = std::get<0>(target->second);

			CHECK(methods.size() == 3);
			CHECK(info == "This is first");

			CHECK(search(methods, "GET"));
			CHECK(search(methods, "POST"));
			CHECK(search(methods, "DELETE"));
		}
		{
			auto target = list.find("/second/test");
			REQUIRE(target != list.end());

			auto methods = std::get<1>(target->second);
			auto info = std::get<0>(target->second);

			CHECK(methods.size() == 2);
			CHECK(info == "This is second");

			CHECK(search(methods, "GET"));
			CHECK(search(methods, "DELETE"));
		}
		{
			auto target = list.find("/third/test");
			REQUIRE(target != list.end());

			auto methods = std::get<1>(target->second);
			auto info = std::get<0>(target->second);

			CHECK(methods.size() == 1);
			CHECK(info == "This is third");

			CHECK(search(methods, "PUT"));
		}
	}

	SECTION("with base path")
	{
		auto dummy = [](served::response & res, const served::request & req){};

		served::multiplexer mux("/base/path");
		mux.handle("/first/test", "This is first").get(dummy).post(dummy).del(dummy);
		mux.handle("/second/test", "This is second").get(dummy).del(dummy);
		mux.handle("/third/test", "This is third").put(dummy);

		auto list = mux.get_endpoint_list();

		{
			auto target = list.find("/base/path/first/test");
			REQUIRE(target != list.end());

			auto methods = std::get<1>(target->second);
			auto info = std::get<0>(target->second);

			CHECK(methods.size() == 3);
			CHECK(info == "This is first");

			CHECK(search(methods, "GET"));
			CHECK(search(methods, "POST"));
			CHECK(search(methods, "DELETE"));
		}
		{
			auto target = list.find("/base/path/second/test");
			REQUIRE(target != list.end());

			auto methods = std::get<1>(target->second);
			auto info = std::get<0>(target->second);

			CHECK(methods.size() == 2);
			CHECK(info == "This is second");

			CHECK(search(methods, "GET"));
			CHECK(search(methods, "DELETE"));
		}
		{
			auto target = list.find("/base/path/third/test");
			REQUIRE(target != list.end());

			auto methods = std::get<1>(target->second);
			auto info = std::get<0>(target->second);

			CHECK(methods.size() == 1);
			CHECK(info == "This is third");

			CHECK(search(methods, "PUT"));
		}
	}
}

TEST_CASE("multiplexer endpoint list YAML", "[mux]")
{
	SECTION("request router stories")
	{
		auto dummy = [](served::response & res, const served::request & req){};

		served::multiplexer mux;
		mux.handle("/first/test", "This is first").get(dummy).post(dummy).del(dummy);
		mux.handle("/second/test", "This is second").get(dummy).del(dummy);
		mux.handle("/third/test", "This is third").put(dummy);
		mux.handle("/endpoints", "List all endpoints").get(mux.get_endpoint_list_handler_YAML());

		served::uri url;
		url.set_path("/endpoints");

		served::request req;
		req.set_destination(url);
		req.set_method(served::method::GET);

		served::response res;

		CHECK_NOTHROW(mux.forward_to_handler(res, req));

		const std::string expected =
			"HTTP/1.1 200 OK\r\n"
			"Server: served-v" + std::string(APPLICATION_VERSION_STRING) + "\r\n"
			"Content-Type: text/yaml\r\n"
			"Content-Length: 318\r\n"
			"\r\n"
			"%YAML 1.2\n"
			"---\n"
			"-\n"
			"	endpoint: /endpoints\n"
			"	summary: List all endpoints\n"
			"	methods:\n"
			"		- GET\n"
			"-\n"
			"	endpoint: /first/test\n"
			"	summary: This is first\n"
			"	methods:\n"
			"		- GET\n"
			"		- POST\n"
			"		- DELETE\n"
			"-\n"
			"	endpoint: /second/test\n"
			"	summary: This is second\n"
			"	methods:\n"
			"		- GET\n"
			"		- DELETE\n"
			"-\n"
			"	endpoint: /third/test\n"
			"	summary: This is third\n"
			"	methods:\n"
			"		- PUT";

		REQUIRE(expected == res.to_buffer());
	}
}
