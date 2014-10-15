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

#ifndef SERVED_VERSION_HPP_INCLUDED
#define SERVED_VERSION_HPP_INCLUDED

#include <boost/preprocessor/stringize.hpp>

/*
 * AUTO-GENERATION WARNING: This file has been automatically generated. DO NOT edit 
 * this file, as any changes will be automatically discarded.
 */
 
#cmakedefine APPLICATION_NAME               "@APPLICATION_NAME@"
#cmakedefine APPLICATION_CODENAME           "@APPLICATION_CODENAME@"
#cmakedefine APPLICATION_COPYRIGHT_YEARS    "@APPLICATION_COPYRIGHT_YEARS@"
#cmakedefine APPLICATION_VERSION_MAJOR      @APPLICATION_VERSION_MAJOR@
#cmakedefine APPLICATION_VERSION_MINOR      @APPLICATION_VERSION_MINOR@
#cmakedefine APPLICATION_VERSION_PATCH      @APPLICATION_VERSION_PATCH@
#cmakedefine APPLICATION_VERSION_TYPE       "@APPLICATION_VERSION_TYPE@"
#cmakedefine APPLICATION_VERSION_STRING     "@APPLICATION_VERSION_STRING@"
#cmakedefine APPLICATION_VENDOR_ID          "@APPLICATION_VENDOR_ID@"
#cmakedefine APPLICATION_VENDOR_NAME        "@APPLICATION_VENDOR_NAME@"
#cmakedefine APPLICATION_VENDOR_URL         "@APPLICATION_VENDOR_URL@"
#cmakedefine APPLICATION_ID                 "@APPLICATION_VENDOR_ID@"

#ifndef APPLICATION_NAME
#   error "Please specify the application name in the top-level CMakeLists.txt file."
#endif

#ifndef APPLICATION_CODENAME
#   error "Please specify the application codename in the top-level CMakeLists.txt file."
#endif

#ifndef APPLICATION_COPYRIGHT_YEARS
#   error "Please specify the application copyright years (years during which this application was created, edited, or modified) in the top-level CMakeLists.txt file."
#endif

#ifndef APPLICATION_VERSION_MAJOR
#   define APPLICATION_VERSOIN_MAJOR 0
#endif

#ifndef APPLICATION_VERSION_MINOR
#   define APPLICATION_VERSION_MINOR 0
#endif

#ifndef APPLICATION_VERSION_PATCH
#   define APPLICATION_VERSION_PATCH 0
#endif

#ifndef APPLICATION_VERSION_TYPE
#   define APPLICATION_VERSION_TYPE "SNAPSHOT"
#endif

#ifndef APPLICATION_VERSION_STRING
#   define APPLICATION_VERSION_STRING BOOST_PP_STRINGIZE(APPLICATION_VERSION_MAJOR) "." BOOST_PP_STRINGIZE(APPLICATION_VERSION_MINOR) "." BOOST_PP_STRINGIZE(APPLICATION_VERSION_PATCH) "-" APPLICATION_VERSION_TYPE
#endif

#ifndef APPLICATION_VENDOR_ID
#   error "Please specify the application vendor id in the top-level CMakeLists.txt file."
#endif

#ifndef APPLICATION_VENDOR_NAME
#   error "Please specify the application vendor name in the top-level CMakeLists.txt file."
#endif

#ifndef APPLICATION_VENDOR_URL
#   error "Please specify the application vendor URL in the top-level CMakeLists.txt file."
#endif

#ifndef APPLICATION_ID
#   define APPLICATION_ID APPLICATION_VENDOR_ID "." APPLICATION_CODENAME
#endif

#endif // SERVED_VERSION_HPP_INCLUDED
