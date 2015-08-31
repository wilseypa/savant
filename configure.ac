## Process this file with autoconf to produce a configure script.

# Copyright (c) 2001 The University of Cincinnati.  
# All rights reserved.

# UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
# SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
# OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
# LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR DISTRIBUTING
# THIS SOFTWARE OR ITS DERIVATIVES.

# By using or copying this Software, Licensee agrees to abide by the
# intellectual property laws, and all other applicable laws of the U.S.,
# and the terms of this license.

# You may modify, distribute, and use the software contained in this
# package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
# version 2, June 1991. A copy of this license agreement can be found in
# the file "LGPL", distributed with this archive.

AC_INIT([savant],[2.0-pre040909])
AC_CONFIG_SRCDIR([src/analyzer/scram.cc])
AM_INIT_AUTOMAKE
AC_PREREQ(2.57)

AC_CONFIG_HEADERS( [src/savant_config.hh:src/savant_config.hh.in] )
AC_LANG(C++)
AC_SUBST(SAVANT_VERSION,[2.0-pre040909])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CXXCPP
AM_PROG_LEX
AC_PROG_INSTALL
AC_PROG_LIBTOOL
CL_PROG_PCCTS
CL_LIB_CLUTILS

AC_CANONICAL_HOST

# cxx on Alpha requires __USE_STD_IOSTREAM to be defined.
case "$host" in
  alpha*) test "$CXX" = "cxx" && AC_DEFINE(__USE_STD_IOSTREAM) ;;
esac

AH_TEMPLATE([__USE_STD_IOSTREAM],
	[cxx on alpha requires the CPP flag __USE_STD_IOSTREAM.])

AH_TEMPLATE([BUILD_SAVANTROOT],
	[This is where SAVANTROOT was specified at build time.])

# If we have a prefix
if test x"$prefix" != x"NONE"; then
  AC_DEFINE_UNQUOTED([BUILD_SAVANTROOT], "$prefix/lib")
else
  AC_DEFINE_UNQUOTED([BUILD_SAVANTROOT], "/usr/local/lib")
fi

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(unistd.h)

# Check for sstream
AC_CHECK_HEADERS( sstream )

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_MODE_T
AC_STRUCT_TM

AC_CHECK_SIZEOF(long, 4)

# Checks for library functions.
AC_FUNC_MEMCMP
AC_TYPE_SIGNAL
AC_CHECK_FUNCS(mkdir strdup)

AC_SUBST(prefix)
AC_SUBST(CPPFLAGS)
AC_SUBST(CFLAGS)
AC_SUBST(CXXFLAGS)
AC_SUBST(LDFLAGS)
AC_SUBST(LIBS)
AC_SUBST(CXX)
AC_SUBST(MAKEDEPEND)
AC_CONFIG_FILES([Makefile \
	src/Makefile \
	src/aire/Makefile \
	src/aire/iir/Makefile \
	src/aire/iir/visitor/Makefile \
	src/analyzer/Makefile \
	src/util/Makefile \
	lib/Makefile \
	lib/vhdl/Makefile \
	lib/vhdl/ieee/Makefile \
	lib/Makefile.common \
	bin/Makefile \
	testsuite/Makefile ])
AC_OUTPUT

echo "You have now configured the savant system for building with\
 flex, antlr, and a C++ compiler. Issuing the command \"make\" should\
 build the \"scram\" parser in the \"savant/bin\" directory."

#target os for dejagnu
target_abbrev=unix

# rm -f ./config.cache
