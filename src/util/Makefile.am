# Process this file with automake to produce Makefile.in

# Copyright (c) 1999-2003 The University of Cincinnati.  
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

# Authors: Philip A. Wilsey	philip.wilsey@ieee.org
# 	    Dale E. Martin	dmartin@cliftonlabs.com
#	    Magnus Danielson	cfmd@swipnet.se

#---------------------------------------------------------------------------

include $(top_srcdir)/Makefile.am.common

AM_CPPFLAGS += -I$(PCCTSROOT) \
	-I$(top_builddir)/src/analyzer # for VHDLTokenTypes.hh

lib_LTLIBRARIES = libsavantutils.la

libsavantutils_la_SOURCES = \
	ConePartitioner.cc \
	Makefile.am \
	ProcessCombiner.cc \
	ProcessCombiner.hh \
	break_handler.hh \
	container.hh \
	dl_list.hh \
	elaborate_info.hh \
	error_func.cc \
	error_func.hh \
	fake_ostringstream.hh \
	hash_table.hh \
	include_manager.hh \
	include_manager.cc \
	plugin_interface.hh \
	resolution_func.cc \
	resolution_func.hh \
	savant_plugin_base.cc \
	savant_plugin_base.hh \
	savant_visitor_plugin.cc \
	savant_visitor_plugin.hh \
	set.hh \
	signal_set.hh \
	stack.hh \
	string_utils.cc \
	string_utils.hh \
	PluginStandardPackage.hh \
	PluginStandardPackage.cc

library_includedir=$(includedir)/savant
library_include_HEADERS=  \
	ProcessCombiner.hh \
	break_handler.hh \
	container.hh \
	dl_list.hh \
	elaborate_info.hh \
	error_func.hh \
	fake_ostringstream.hh \
	hash_table.hh \
	include_manager.hh \
	resolution_func.hh \
	savant_plugin_base.hh \
	savant_visitor_plugin.hh \
	set.hh \
	signal_set.hh \
	stack.hh \
	string_utils.hh \
	PluginStandardPackage.hh \
	plugin_class_factory.hh \
	plugin_interface.hh
