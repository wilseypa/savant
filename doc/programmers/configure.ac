## Process this file with autoconf to produce a configure script.

# Copyright (c) 2004 The University of Cincinnati.  
# All rights reserved.
# 
# UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
# SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
# OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
# LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR DISTRIBUTING
# THIS SOFTWARE OR ITS DERIVATIVES.
# 
# By using or copying this Software, Licensee agrees to abide by the
# intellectual property laws, and all other applicable laws of the U.S.,
# and the terms of this license.
# 
# You may modify, distribute, and use the software contained in this
# package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
# version 2, June 1991. A copy of this license agreement can be found in
# the file "LGPL", distributed with this archive.

AC_INIT([XML], [1.0])
AC_CONFIG_SRCDIR([src/XML/XML.cc])
AM_INIT_AUTOMAKE
AC_PREREQ(2.57)

AM_CONFIG_HEADER( src/XML/XML_config.h )
AC_LANG(C++)
AC_CANONICAL_HOST

# Checks for programs
AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Checks for libraries
CL_LIB_CLUTILS

# Var substitutions
AC_SUBST(CPPFLAGS)
AC_SUBST(CFLAGS)
AC_SUBST(CXXFLAGS)
AC_SUBST(LDFLAGS)
AC_SUBST(LIBS)
AC_SUBST(CXX)

AC_OUTPUT( [ Makefile src/Makefile src/XML/Makefile ] )

rm -rf ./config.cache
