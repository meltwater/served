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

#include <served/request_error.hpp>
#include <served/multiplexer.hpp>
#include <served/methods.hpp>

struct request_router_story
{
	std::string              pattern;
	std::vector<std::string> expected_200s;
	std::vector<std::string> expected_404s;

	std::vector<std::string> received;
};

class path_collecting_functor
{
	request_router_story & _story_obj;
public:
	path_collecting_functor(request_router_story & story_obj)
		: _story_obj(story_obj) {}

	void operator()(served::response & response, const served::request & request)
	{
		_story_obj.received.push_back(request.url().pathname());
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
			"/static1/foo/bar"
		};
		stories.back().expected_404s = {
			"/static1/bar/foo",
			"/static1/foo/bar2",
			"/static1/foo/bar/",
			"/static1/foo/bar/bob"
		};

		// variable1
		stories.push_back(request_router_story());
		stories.back().pattern = "/variable1/{first}/{second}";
		stories.back().expected_200s = {
			"/variable1/foo/bar",
			"/variable1/bar/bob",
			"/variable1/bob/baz",
			"/variable1/this/variable",
			"/variable1/variable/variable"
		};
		stories.back().expected_404s = {
			"/variable1//variable",
			"/variable1/test1/test2/",
			"/variable1/test1/test2/test3"
		};

		// variable2
		stories.push_back(request_router_story());
		stories.back().pattern = "/variable2/{first}/{second}/";
		stories.back().expected_200s = {
			"/variable2/foo/bar/",
			"/variable2/foo/bar/",
			"/variable2/this/variable/",
			"/variable2/test1/test2/test3"
		};
		stories.back().expected_404s = {
			"/variable2/this/variable",
			"/variable2//variable"
		};

		// TODO: Regex

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
				url.set_pathname(path);

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
				url.set_pathname(path);

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
