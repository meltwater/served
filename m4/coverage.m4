AC_DEFUN([AC_CHECK_COVERAGE],
[
  AC_ARG_ENABLE([coverage],
                AS_HELP_STRING([--enable-coverage],
                               [enable coverage reporting with lcov [default=no]]),
                [enable_coverage=$enableval],
                [enable_coverage=no])

  if test "x$enable_coverage" = "xyes"; then
    ENABLE_COVERAGE="yes"

    AC_PATH_PROG(LCOV, lcov, no)
    if test "x$LCOV" = "xno"; then
      AC_MSG_ERROR([cannot not find lcov. please install lcov package.])
    fi

    AC_PATH_PROG(GENHTML, genhtml, no)
    if test "x$GENHTML" = "xno"; then
      AC_MSG_ERROR([cannot not find genhtml. please install lcov package.])
    fi

    COVERAGE_CFLAGS="-fprofile-arcs -ftest-coverage"
    COVERAGE_CXXFLAGS="-fprofile-arcs -ftest-coverage"
    COVERAGE_OPTIMIZATION_FLAGS="-O0"
    COVERAGE_LDFLAGS="-lgcov"

    AC_CHECK_PROG(HAVE_CPPFILT, c++filt, yes, no)
    if test "x$HAVE_CPPFILT" = "xyes"; then
      GENHTML_OPTIONS="--demangle-cpp"
    else
      GENHTML_OPTIONS=""
    fi
  else
    ENABLE_COVERAGE="no"
    LCOV="lcov"
    GENHTML="genhtml"
    COVERAGE_CFLAGS=""
    COVERAGE_CXXFLAGS=""
    COVERAGE_OPTIMIZATION_FLAGS=""
    COVERAGE_LDFLAGS=""
    GENHTML_OPTIONS=""
  fi

  AC_SUBST([ENABLE_COVERAGE])
  AC_SUBST([COVERAGE_CFLAGS])
  AC_SUBST([COVERAGE_CXXFLAGS])
  AC_SUBST([COVERAGE_OPTIMIZATION_FLAGS])
  AC_SUBST([COVERAGE_LDFLAGS])
  AC_SUBST([GENHTML_OPTIONS])
])
