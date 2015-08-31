
// Copyright (c) 2001 The University of Cincinnati.
// All rights reserved. 

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Author: Philip A. Wilsey	philip.wilsey@ieee.org

//---------------------------------------------------------------------------

#include "language_processing_control.hh"
#include "error_func.hh"

bool 
language_processing_control::processing_vhdl_93() {
  return (language_being_processed == VHDL_93);
}

bool
language_processing_control::processing_vhdl_ams() {
  return (language_being_processed == VHDL_AMS);
}

bool  
language_processing_control::processing_vhdl_2001() {
  return (language_being_processed == VHDL_2001);
}

void
language_processing_control::report_not_vhdl_ams(ANTLRToken *token) {
  report_error(token, "Input file appears to have VHDL AMS constructs; invoke analyzer with --vhdl-ams to process.");
}

void
language_processing_control::report_not_vhdl_2001(ANTLRToken *token) {
  report_error(token, "Input file appears to have VHDL 2001 constructs; invoke analyzer with --vhdl-2001 to process.");
}

