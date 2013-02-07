#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([AST-TEST], [1], [bielern@ethz.ch])
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([src/test.cc])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile src/parser/Makefile])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LEX
AC_PROG_YACC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([inttypes.h libintl.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset])

# Change flags
AC_SUBST([AM_CXXFLAGS], [-Wall -g])
AC_SUBST([AM_LEXFLAGS], [-Wall])
AC_SUBST([AM_YFLAGS], [-Wall])
AC_SUBST([AM_YACC], [bison])
AC_OUTPUT


