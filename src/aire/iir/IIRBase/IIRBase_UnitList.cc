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
//          Timothy J. McBrayer tmcrbaye@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIR_PhysicalUnit.hh"
#include "IIRBase_UnitList.hh"
#include "IIR_Declaration.hh"

IIRBase_UnitList::IIRBase_UnitList() {}
IIRBase_UnitList::~IIRBase_UnitList() {}


IIR * 
IIRBase_UnitList::first() {
  IIR *retval = IIRBase_DeclarationList::first();

  return retval;
}


IIR*
IIRBase_UnitList::successor(IIR_PhysicalUnit *node) {
  IIR *retval = IIRBase_DeclarationList::successor( node );
  return retval;
}

IIR*
IIRBase_UnitList::predecessor(IIR_PhysicalUnit* node) {
  IIR *retval = IIRBase_DeclarationList::successor( node );
  ASSERT( retval != NULL );

  return retval;
}


void 
IIRBase_UnitList::publish_vhdl(ostream &vhdl_out) {
  publish_vhdl_decl( vhdl_out );
}
