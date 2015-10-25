# - Find Intel TBB headers and lib.
# This module defines
#  TBB_INCLUDE_DIR, directory containing headers
#  TBB_LIBRARY, path to libtbb.so
#  TBB_FOUND, whether TBB has been found

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

find_path(TBB_INCLUDE_DIR tbb/tbb.h NO_DEFAULT_PATH PATHS
  /usr/include
  /opt/local/include
  /usr/local/include
)

set(TBB_NAMES ${TBB_NAMES} tbb)

find_library(TBB_LIBRARY NAMES ${TBB_NAMES} NO_DEFAULT_PATH PATHS
  /usr/local/lib
  /opt/local/lib
  /usr/lib
)

if (TBB_INCLUDE_DIR AND TBB_LIBRARY)
  set(TBB_FOUND TRUE)
  set( TBB_LIBRARIES ${TBB_LIBRARY} )
else ()
  set(TBB_FOUND FALSE)
  set( TBB_LIBRARIES )
endif ()

if (TBB_FOUND)
  message(STATUS "Found TBB: ${TBB_LIBRARY}")
else ()
  message(STATUS "Not Found TBB: ${TBB_LIBRARY}")
  if (TBB_FIND_REQUIRED)
    message(STATUS "Looked for TBB libraries named ${TBB_NAMES}.")
    message(FATAL_ERROR "Could NOT find TBB library")
  endif ()
endif ()

mark_as_advanced(
  TBB_LIBRARY
  TBB_INCLUDE_DIR
)