# For using custom m4 macros
ACLOCAL_AMFLAGS = -I m4

# Compiler build flags
AM_CPPFLAGS = -I${top_srcdir}/src ${BOOST_CPPFLAGS}

# Build rules for served library
pkginclude_HEADERS = \
	src/served/served.hpp

lib_LTLIBRARIES = \
	src/served/libserved.la

src_served_libserved_la_SOURCES =
src_served_libserved_la_LDFLAGS = -version-info 0:0:0
src_served_libserved_la_LIBADD =

# Build rules for pkgconfig
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = served.pc

# Build rules for tests.
# TESTS_ENVIRONMENT: Set environment variables for the test run
# TESTS: Define programs run automatically by "make check"
# UNIT_TESTS: Define programs run automatically by "make check-unit-tests"
# check_PROGRAMS: Define programs built by "make check" but not necessarily run
TESTS_ENVIRONMENT=
TESTS=
UNIT_TESTS=
check_PROGRAMS=

# Define unit tests with catch
UNIT_TESTS += test/served_test
check_PROGRAMS += test/served_test
test_served_test_SOURCES = \
	test/served_test.cpp
test_served_test_CFLAGS = -I$(top_srcdir)/src
test_served_test_LDADD = $(top_builddir)/src/served/libserved.la $(BOOST_ASIO_LIB) $(LDADD)

TESTS += $(UNIT_TESTS)

TESTS_ENVIRONMENT_WITH_VALGRIND="libtool --mode=execute valgrind --leak-check=full"

.PHONY: check-with-valgrind
check-with-valgrind:
	$(MAKE) $(AM_MAKEFLAGS) check TESTS_ENVIRONMENT=$(TESTS_ENVIRONMENT_WITH_VALGRIND)

.PHONY: check-unit-tests
check-unit-tests:
	$(MAKE) $(AM_MAKEFLAGS) check TESTS=$(UNIT_TESTS)

.PHONY: check-unit-tests-with-valgrind
check-unit-tests-with-valgrind:
	$(MAKE) $(AM_MAKEFLAGS) check TESTS=$(UNIT_TESTS) TESTS_ENVIRONMENT=$(TESTS_ENVIRONMENT_WITH_VALGRIND)

if RAGEL_FOUND
.rl.cpp:
	$(AM_V_GEN)$(RAGEL) $(RAGELFLAGS) -C $< -o $@
endif

# Nonstandard package files for distribution
EXTRA_DIST = \
	README.md \
	LICENSE \
	autogen.sh \
	served.pc

include Makefile.am.coverage
