# - Find re2 headers and lib.
# This module defines
#  RE2_INCLUDE_DIR, directory containing headers
#  RE2_LIBRARY, path to re2.a
#  RE2_FOUND, whether RE2 has been found

#  ====================================================================
#  Copyright (C) 2014 MediaSift Ltd.
# 
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
# 
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
# 
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.
#  ====================================================================

find_path(RE2_INCLUDE_DIR re2/re2.h NO_DEFAULT_PATH PATHS
  /usr/include
  /opt/local/include
  /usr/local/include
)

set(RE2_NAMES ${RE2_NAMES} re2)
find_library(RE2_LIBRARY NAMES ${RE2_NAMES} NO_DEFAULT_PATH PATHS
  /usr/local/lib
  /usr/local/re2/lib
  /opt/local/lib
  /usr/lib
)

if (RE2_INCLUDE_DIR AND RE2_LIBRARY)
  set(RE2_FOUND TRUE)
  set( RE2_LIBRARIES ${RE2_LIBRARY} )
else ()
  set(RE2_FOUND FALSE)
  set( RE2_LIBRARIES )
endif ()

if (RE2_FOUND)
  message(STATUS "Found RE2: ${RE2_LIBRARY}")
else ()
  message(STATUS "Not Found RE2: ${RE2_LIBRARY}")
  if (RE2_FIND_REQUIRED)
    message(STATUS "Looked for RE2 libraries named ${RE2_NAMES}.")
    message(FATAL_ERROR "Could NOT find RE2 library")
  endif ()
endif ()

mark_as_advanced(
  RE2_LIBRARY
  RE2_INCLUDE_DIR
)