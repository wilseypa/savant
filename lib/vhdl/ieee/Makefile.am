# Process this file with automake to produce Makefile.in

# Copyright (c) 1999-2007 The University of Cincinnati.  
# All rights reserved.

# UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
# SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
# PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES
# SUFFERED BY LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING
# OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

# By using or copying this Software, Licensee agrees to abide by the
# intellectual property laws, and all other applicable laws of the U.S.,
# and the terms of this license.

# You may modify, distribute, and use the software contained in this
# package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
# version 2, June 1991. A copy of this license agreement can be found in
# the file "LGPL", distributed with this archive.

# Authors: Philip A. Wilsey	philip.wilsey@ieee.org
# 	   Dale E. Martin	dmartin@cliftonlabs.com
#	   Magnus Danielson	cfmd@swipnet.se

#---------------------------------------------------------------------------

include $(top_srcdir)/Makefile.am.common

IEEE_INPUT_DIR=$(top_srcdir)/lib/vhdl/ieee
IEEE_OUTPUT_DIR = $(top_builddir)/lib/vhdl/ieee/ieee._savant_lib

install-data-local: ieee._savant_lib
	$(INSTALL) -d $(libdir)/savant
	$(INSTALL) -d $(libdir)/savant/lib
	$(INSTALL) -d $(libdir)/savant/lib/ieee._savant_lib 
	$(INSTALL_DATA) $(IEEE_OUTPUT_DIR)/numeric_bit_package.vhdl \
                $(IEEE_OUTPUT_DIR)/numeric_std_package.vhdl \
		$(IEEE_OUTPUT_DIR)/std_logic_1164_package.vhdl \
		$(IEEE_OUTPUT_DIR)/vital_memory_package.vhdl \
		$(IEEE_OUTPUT_DIR)/vital_primitives_package.vhdl \
		$(IEEE_OUTPUT_DIR)/vital_timing_package.vhdl \
		$(IEEE_OUTPUT_DIR)/std_logic_arith_package.vhdl \
		$(IEEE_OUTPUT_DIR)/std_logic_unsigned_package.vhdl \
		$(IEEE_OUTPUT_DIR)/std_logic_signed_package.vhdl \
		$(IEEE_OUTPUT_DIR)/std_logic_textio_package.vhdl \
		$(IEEE_OUTPUT_DIR)/attributes_package.vhdl \
		$(IEEE_OUTPUT_DIR)/std_logic_misc_package.vhdl \
		$(IEEE_OUTPUT_DIR)/math_real_package.vhdl \
		$(IEEE_OUTPUT_DIR)/math_complex_package.vhdl \
		$(libdir)/savant/lib/ieee._savant_lib


	$(INSTALL_DATA) $(IEEE_INPUT_DIR)/std_logic_1164.vhd \
		$(IEEE_INPUT_DIR)/timing_p.vhd \
		$(IEEE_INPUT_DIR)/timing_b.vhd \
		$(IEEE_INPUT_DIR)/numeric_bit.vhd \
		$(IEEE_INPUT_DIR)/numeric_std.vhd \
		$(IEEE_INPUT_DIR)/prmtvs_p.vhd \
		$(IEEE_INPUT_DIR)/prmtvs_b.vhd \
		$(IEEE_INPUT_DIR)/memory_p.vhd \
		$(IEEE_INPUT_DIR)/memory_b.vhd \
		$(IEEE_INPUT_DIR)/std_logic_arith.vhd \
		$(IEEE_INPUT_DIR)/std_logic_unsigned.vhd \
		$(IEEE_INPUT_DIR)/std_logic_signed.vhd \
		$(IEEE_INPUT_DIR)/std_logic_textio.vhd \
		$(IEEE_INPUT_DIR)/attributes.vhd \
		$(IEEE_INPUT_DIR)/std_logic_misc.vhd \
		$(IEEE_INPUT_DIR)/math_real.vhd \
		$(IEEE_INPUT_DIR)/math_complex.vhd \
		$(libdir)/savant/lib/ieee._savant_lib

IEEE_VHDL_FILES = \
	$(IEEE_INPUT_DIR)/std_logic_1164.vhd \
	$(IEEE_INPUT_DIR)/timing_p.vhd \
	$(IEEE_INPUT_DIR)/timing_b.vhd \
	$(IEEE_INPUT_DIR)/numeric_std.vhd \
	$(IEEE_INPUT_DIR)/numeric_bit.vhd \
	$(IEEE_INPUT_DIR)/prmtvs_p.vhd \
	$(IEEE_INPUT_DIR)/prmtvs_b.vhd \
	$(IEEE_INPUT_DIR)/memory_p.vhd \
	$(IEEE_INPUT_DIR)/memory_b.vhd \
	$(IEEE_INPUT_DIR)/std_logic_arith.vhd \
	$(IEEE_INPUT_DIR)/std_logic_unsigned.vhd \
	$(IEEE_INPUT_DIR)/std_logic_signed.vhd \
	$(IEEE_INPUT_DIR)/std_logic_textio.vhd \
	$(IEEE_INPUT_DIR)/attributes.vhd \
	$(IEEE_INPUT_DIR)/std_logic_misc.vhd \
	$(IEEE_INPUT_DIR)/math_real.vhd \
	$(IEEE_INPUT_DIR)/math_complex.vhd

SCRAMFLAGS= --design-library-name ieee

all-local: $(IEEE_OUTPUT_DIR)

clean-local:
	rm -rf $(IEEE_OUTPUT_DIR)

$(IEEE_OUTPUT_DIR): $(top_builddir)/bin/scram $(IEEE_FILES)
	SAVANTROOT=$(top_srcdir) $(top_builddir)/bin/scram $(SCRAMFLAGS) $(IEEE_VHDL_FILES)
