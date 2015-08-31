
// Copyright (c) 1996-1999 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
// DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.


// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     mal@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRBase_DesignatorByAll.hh"
#include "savant.hh"

IIRBase_DesignatorByAll::IIRBase_DesignatorByAll() {
}

IIRBase_DesignatorByAll::~IIRBase_DesignatorByAll() {}

IIR_Boolean 
IIRBase_DesignatorByAll::is_resolved(){
  return TRUE;
}

ostream &
IIRBase_DesignatorByAll::print( ostream &os ){
  os << "all";
  return os;
}

void 
IIRBase_DesignatorByAll::publish_vhdl(ostream &vhdl_out) {
  vhdl_out << "all";
}

void 
IIRBase_DesignatorByAll::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << "all";
}
