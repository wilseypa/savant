# Process this file with automake to produce Makefile.in

# Copyright (c) 1999-2001 The University of Cincinnati.  
# All rights reserved.

# UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
# SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
# OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
# LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
# DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

# By using or copying this Software, Licensee agrees to abide by the
# intellectual property laws, and all other applicable laws of the U.S.,
# and the terms of this license.

# You may modify, distribute, and use the software contained in this
# package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
# version 2, June 1991. A copy of this license agreement can be found in
# the file "LGPL", distributed with this archive.

# Authors: Philip A. Wilsey	phil.wilsey@uc.edu
# 	    Dale E. Martin	dmartin@clifton-labs.com
#	    Magnus Danielson	cfmd@swipnet.se

#---------------------------------------------------------------------------

include $(top_srcdir)/Makefile.am.common

SUBDIRS = aire analyzer util

AM_CPPFLAGS += -I$(PCCTSROOT)

noinst_LTLIBRARIES = libpccts.la

BUILT_SOURCES = \
	ATokenBuffer.cpp		\
	AParser.cpp			

library_includedir=$(includedir)/savant
library_include_HEADERS=  \
	savant.hh \
	savant_config.hh 

libpccts_la_SOURCES = \
	$(BUILT_SOURCES)

ATokenBuffer.cpp: analyzer/vhdl.gg
	cp $(PCCTSROOT)/ATokenBuffer.cpp $(top_builddir)/src

AParser.cpp: analyzer/vhdl.gg
	cp $(PCCTSROOT)/AParser.cpp $(top_builddir)/src
