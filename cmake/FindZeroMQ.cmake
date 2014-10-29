# - Try to find ZeroMQ headers and libraries
#
# Usage of this module as follows:
#
#     find_package(ZeroMQ)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  ZeroMQ_ROOT_DIR  Set this variable to the root installation of
#                            ZeroMQ if the module has problems finding
#                            the proper installation path.
#
# Variables defined by this module:
#
#  ZEROMQ_FOUND              System has ZeroMQ libs/headers
#  ZeroMQ_LIBRARIES          The ZeroMQ libraries
#  ZeroMQ_INCLUDE_DIR        The location of ZeroMQ headers

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

find_path(ZeroMQ_ROOT_DIR
  NAMES include/zmq.h
  )

if(MSVC)
  #add in all the names it can have on windows
  if(CMAKE_GENERATOR_TOOLSET MATCHES "v140" OR MSVC14)
    set(_zmq_TOOLSET "-v140")
  elseif(CMAKE_GENERATOR_TOOLSET MATCHES "v120" OR MSVC12)
    set(_zmq_TOOLSET "-v120")
  elseif(CMAKE_GENERATOR_TOOLSET MATCHES "v110_xp")
    set(_zmq_TOOLSET "-v110_xp")
  elseif(CMAKE_GENERATOR_TOOLSET MATCHES "v110" OR MSVC11)
    set(_zmq_TOOLSET "-v110")
  elseif(CMAKE_GENERATOR_TOOLSET MATCHES "v100" OR MSVC10)
    set(_zmq_TOOLSET "-v100")
  elseif(CMAKE_GENERATOR_TOOLSET MATCHES "v90" OR MSVC90)
    set(_zmq_TOOLSET "-v90")
  endif()

  set(_zmq_versions "4_0_4" "4_0_3" "4_0_2" "4_0_1" "4_0_0"
                    "3_2_5" "3_2_4" "3_2_3" "3_2_2"  "3_2_1" "3_2_0" "3_1_0")
  set(_zmq_release_names)
  set(_zmq_debug_names)
  foreach( ver ${_zmq_versions})
    list(APPEND _zmq_release_names "libzmq${_zmq_TOOLSET}-mt-${ver}")
  endforeach()
  foreach( ver ${_zmq_versions})
    list(APPEND _zmq_debug_names "libzmq${_zmq_TOOLSET}-mt-gd-${ver}")
  endforeach()

  #now try to find the release and debug version
  find_library(ZeroMQ_LIBRARY_RELEASE
    NAMES ${_zmq_release_names} zmq libzmq
    HINTS ${ZeroMQ_ROOT_DIR}/bin
          ${ZeroMQ_ROOT_DIR}/lib
    )

  find_library(ZeroMQ_LIBRARY_DEBUG
    NAMES ${_zmq_debug_names} zmq libzmq
    HINTS ${ZeroMQ_ROOT_DIR}/bin
          ${ZeroMQ_ROOT_DIR}/lib
    )

  if(ZeroMQ_LIBRARY_RELEASE AND ZeroMQ_LIBRARY_DEBUG)
    set(ZeroMQ_LIBRARY
        debug ${ZeroMQ_LIBRARY_DEBUG}
        optimized ${ZeroMQ_LIBRARY_RELEASE}
        )
  elseif(ZeroMQ_LIBRARY_RELEASE)
    set(ZeroMQ_LIBRARY ${ZeroMQ_LIBRARY_RELEASE})
  elseif(ZeroMQ_LIBRARY_DEBUG)
    set(ZeroMQ_LIBRARY ${ZeroMQ_LIBRARY_DEBUG})
  endif()

else()
  find_library(ZeroMQ_LIBRARY
    NAMES zmq libzmq
    HINTS ${ZeroMQ_ROOT_DIR}/lib
    )
endif()

find_path(ZeroMQ_INCLUDE_DIR
  NAMES zmq.h
  HINTS ${ZeroMQ_ROOT_DIR}/include
  )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZeroMQ DEFAULT_MSG
  ZeroMQ_LIBRARY
  ZeroMQ_INCLUDE_DIR
  )

set(ZeroMQ_INCLUDE_DIRS ${ZeroMQ_INCLUDE_DIR})
set(ZeroMQ_LIBRARIES ${ZeroMQ_LIBRARY})

mark_as_advanced(
  ZeroMQ_ROOT_DIR
  ZeroMQ_LIBRARY
  ZeroMQ_LIBRARY_DEBUG
  ZeroMQ_LIBRARY_RELEASE
  ZeroMQ_INCLUDE_DIR
  )