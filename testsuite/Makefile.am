
# Copyright (C) Clifton Labs, Inc

# CLIFTON LABS MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY
# OF THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
# PURPOSE, OR NON-INFRINGEMENT.  CLIFTON LABS SHALL NOT BE LIABLE FOR ANY
# DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, RESULT OF USING,
# MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

# By using or copying this Software, Licensee agrees to abide by the
# intellectual property laws, and all other applicable laws of the U.S.,
# and the terms of this license.

# You may modify, distribute, and use the software contained in this
# package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
# version 2, June 1991. A copy of this license agreement can be found in
# the file "LGPL", distributed with this archive.

AUTOMAKE_OPTIONS = dejagnu
#RUNTEST --tool savant DEFAULTFLAGS = -v -v 

#
# Rules for the test cases distributed with savant
#

check-savant-tests:	check-hello-world check-ping-pong

check-hello-world:
	runtest --tool savant savant.hello_world/hello_world.exp 

check-ping-pong:
	runtest --tool savant savant.ping_pong/ping_pong.exp 

#
# Rules for the various testlevels supported by the savant test system. 
#

check-publish-vhdl:
	runtest --tool savant TESTLEVEL=publish-vhdl -ignore "hello_world.exp ping_pong.exp"

check-publish-cc:
	runtest --tool savant TESTLEVEL=publish-cc -ignore "hello_world.exp ping_pong.exp"

check-build:
	runtest --tool savant TESTLEVEL=build -ignore "hello_world.exp ping_pong.exp"

check-simulate:
	runtest --tool savant TESTLEVEL=simulate -ignore "hello_world.exp ping_pong.exp"

#
# Rules to run tests in all or part of the vests test system.
#

check-vests: savant.vests
	runtest --tool savant -ignore "hello_world.exp ping_pong.exp"

#
# Run all tests for a specific language standard
#

check-vhdl-93:	check-ashenden check-billowitch check-cliftonlabs

check-vhdl-ams:	check-ad-hoc

#
# Testsuite specific targets
#

# VHDL-93
check-ashenden: savant.vests
	runtest --tool savant savant.vests/vests/vhdl-93/ashenden/compliant/compliant.exp

check-billowitch: savant.vests
	runtest --tool savant savant.vests/vests/vhdl-93/billowitch/compliant/compliant.exp

check-cliftonlabs: savant.vests
	runtest --tool savant savant.vests/vests/vhdl-93/clifton-labs/compliant/compliant.exp

# VHDL-AMS 
check-ad-hoc: savant.vests
	runtest --tool savant savant.vests/vests/vhdl-ams/ad-hoc/compliant.exp


# the following two do not yet run correctly; there appears to be a problem
# in dejagnu/runtest....

check-compliant: savant.vests
	runtest --tool savant compliant.exp

check-non-compliant: savant.vests
	runtest --tool savant non_compliant.exp

savant.vests:
	rm -rf savant.vests
	rm -rf vests
	mkdir savant.vests
	cvs -d cvs.cliftonlabs.com:/usr/local/cvsroot checkout vests
	mv vests savant.vests
