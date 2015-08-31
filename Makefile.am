# Process this file with automake to produce Makefile.in

# Copyright (c) 1999-2001 The University of Cincinnati.  
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

include $(top_srcdir)/Makefile.am.common

# This order has us build scram before attempting to process the IEEE libraries
SUBDIRS= src bin lib testsuite
IEEE_DIST_DIR=lib/vhdl/ieee
EXTRA_DIST = \
	Makefile.am.common\
	doc/BUGS\
	doc/README\
	doc/TODO\
	doc/libraryManager/libraryManager.tex\
	doc/programmers/fir-seqStatement.ps.gz\
	doc/programmers/programmers.ps.gz\
	doc/programmers/actual-if.ps.gz\
	doc/programmers/iir-extensible.ps.gz\
	doc/programmers/programmers.tex\
	doc/programmers/broken-derivation.ps.gz\
	doc/programmers/iir-seqStatement.ps.gz\
	doc/programmers/savant-if.ps.gz\
	doc/programmers/extended-declaration.ps.gz\
	doc/programmers/node-implementation.ps.gz\
	doc/programmers/uc-projects.ps.gz\
	doc/programmers/fir-extensible.ps.gz\
	doc/programmers/programmers.pdf.gz\
	doc/scram.1\
	$(IEEE_DIST_DIR)/std_logic_1164.vhd \
	$(IEEE_DIST_DIR)/timing_p.vhd \
	$(IEEE_DIST_DIR)/timing_b.vhd \
	$(IEEE_DIST_DIR)/numeric_std.vhd \
	$(IEEE_DIST_DIR)/prmtvs_p.vhd \
	$(IEEE_DIST_DIR)/prmtvs_b.vhd \
	$(IEEE_DIST_DIR)/memory_p.vhd \
	$(IEEE_DIST_DIR)/memory_b.vhd \
	lib/Makefile.common \
	lib/Makefile.common.in \
	lib/std._savant_lib/textio_package.vhdl \
	src/savant_config.hh.in \
	src/savant.hh \
	src/version.hh \
	src/analyzer/vhdl.gg \
	src/analyzer/VHDLLexer.flex

doc++:
	doc++ --dir doc/html `find -name "*.hh" -print`

doxygen:
	cd doc;	doxygen savant.doxygen-config

