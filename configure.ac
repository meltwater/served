# Initialise Autoconf with package name, version number and bug report address
AC_INIT([served], [0.1.0], [chris.gilbert@datasift.com])

# Use custom m4 macros
AC_CONFIG_MACRO_DIR([m4])

# Auxiliary scripts such as install-sh and depcomp should be in following directory.
AC_CONFIG_AUX_DIR([build-aux])

# Initialize Automake.
# There are useful options.
#   -Werror: Report warnings as errors.
#   foreign: ignores some GNU Coding Standards.
#   subdirs-objects: Create objects in sub-direcotories
AM_INIT_AUTOMAKE([-Werror foreign subdir-objects])

# AM_PROG_AR is a new feature since automake 1.12,
# make AM_PROG_AR work before automake 1.12
# Libtool(LT_INIT) should use AM_PROG_AR internally,
# newer libtool may not need to enable AM_PROG_AR explicitly.
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])

# Initialise libtool
LT_INIT

# Check for a C compiler
AC_PROG_CC

# Check for a C++ compiler
AC_PROG_CXX

AC_LANG([C++], [C])

# Check for ragel
AC_CHECK_PROG([RAGEL_FOUND], [ragel], [yes], [no])

# Checks for existence of coverage tools and define variables for reporting coverage
AC_CHECK_COVERAGE

# Check for C++11 support
#   ext: use extended mode (e.g. -std=gnu++11)
#   noext: use non-extended mode (e.g. -std=c++11)
AX_CXX_COMPILE_STDCXX_11([noext])

# Check for Boost
AX_BOOST_BASE([1.48],, [AC_MSG_ERROR([This library requires Boost, but it was not found in your system])])
AX_BOOST_ASIO

# Check for the existance of a file in the source directory.
AC_CONFIG_SRCDIR([src])

# Output files.
# AC_CONFIG_HEADERS(HEADERS...)
# Create Header for all HEADER.in Use only one such header unless you know what you are doing.
# Declare config.hpp as output header.
AC_CONFIG_HEADERS([config.hpp])

# Declare output files.
AC_CONFIG_FILES([Makefile served.pc])

# Actually output all declared files.
AC_OUTPUT

AC_MSG_RESULT([
Configure Information:
  C Compiler        : $CC
    DEFS            :   $DEFS
    CPPFLAGS        :   $CPPFLAGS
    CFLAGS          :   $CFLAGS
  C++ Compiler      : $CXX
    DEFS            :   $DEFS
    CPPFLAGS        :   $CPPFLAGS
    CXXFLAGS        :   $CXXFLAGS
  Linker            : $LD
    LDFLAGS         :   $LDFLAGS
    LIBS            :   $LIBS
  Coverage Reports  : $ENABLE_COVERAGE
Third Party Dependencies:
  Boost
    CPPFLAGS        : $BOOST_CPPFLAGS
    LDFLAGS         : $BOOST_LDFLAGS
    LIBS            : $BOOST_ASIO_LIB
  Ragel             : $RAGEL_FOUND
])