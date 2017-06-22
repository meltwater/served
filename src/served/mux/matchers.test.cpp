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
#include <test/catch.hpp>

#include <served/mux/matchers.hpp>

TEST_CASE("segment matchers compile and parsing", "[matchers]")
{
	SECTION("compile_to_matcher")
	{
		served::mux::segment_matcher_ptr matcher;

		matcher = served::mux::compile_to_matcher("");
		CHECK(dynamic_cast<served::mux::empty_matcher *>(matcher.get()));

		matcher = served::mux::compile_to_matcher("text");
		CHECK(dynamic_cast<served::mux::static_matcher *>(matcher.get()));

		matcher = served::mux::compile_to_matcher("{variable}");
		CHECK(dynamic_cast<served::mux::variable_matcher *>(matcher.get()));

		matcher = served::mux::compile_to_matcher("{variable:regex}");
		CHECK(dynamic_cast<served::mux::regex_matcher *>(matcher.get()));
	}
	SECTION("empty_matcher")
	{
		std::string segment = "";
		auto matcher = served::mux::compile_to_matcher(segment);

		CHECK(dynamic_cast<served::mux::empty_matcher *>(matcher.get()));

		CHECK(matcher->check_match(""));
		CHECK(matcher->check_match("notempty"));
		CHECK(matcher->check_match(" "));
		CHECK(matcher->check_match("things.html"));
	}
	SECTION("static_matcher")
	{
		std::string segment = "static_text_123";
		auto matcher = served::mux::compile_to_matcher(segment);

		CHECK(dynamic_cast<served::mux::static_matcher *>(matcher.get()));

		CHECK( matcher->check_match("static_text_123"));
		CHECK(!matcher->check_match("not_the_same"));
		CHECK(!matcher->check_match(" "));
		CHECK(!matcher->check_match("static_text_321"));
		CHECK(!matcher->check_match(""));
		CHECK( matcher->check_match("static_text_123"));
	}
	SECTION("variable_matcher")
	{
		std::string segment = "{value}";
		auto matcher = served::mux::compile_to_matcher(segment);

		CHECK(dynamic_cast<served::mux::variable_matcher *>(matcher.get()));

		CHECK( matcher->check_match("static_text_123"));
		CHECK( matcher->check_match("another_text"));
		CHECK( matcher->check_match("this_is_also"));
		CHECK(!matcher->check_match(""));
	}
	SECTION("regex_matcher")
	{
		std::string segment = "{value:[0-9]*}";
		auto matcher = served::mux::compile_to_matcher(segment);

		CHECK(dynamic_cast<served::mux::regex_matcher *>(matcher.get()));

		CHECK( matcher->check_match("1337"));
		CHECK( matcher->check_match("1969"));
		CHECK(!matcher->check_match("11!!oneone"));
		CHECK(!matcher->check_match(" 11 "));
	}
}
