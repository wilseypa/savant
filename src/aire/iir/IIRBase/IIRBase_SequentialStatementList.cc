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

//---------------------------------------------------------------------------

#include "IIR_SequentialStatement.hh"
#include "IIRBase_SequentialStatementList.hh"

IIRBase_SequentialStatementList::IIRBase_SequentialStatementList() {}
IIRBase_SequentialStatementList::~IIRBase_SequentialStatementList() {}


IIR_SequentialStatement* 
IIRBase_SequentialStatementList::first() {
  return dynamic_cast<IIR_SequentialStatement*>(IIR_List::first());
}


IIR_SequentialStatement*
IIRBase_SequentialStatementList::successor(IIR_SequentialStatement* node) {
  return dynamic_cast<IIR_SequentialStatement*>(IIR_List::successor((IIR*)node));
}

IIR_Boolean
IIRBase_SequentialStatementList::is_above_attribute_found() {
  IIR_Boolean retval = FALSE;

  IIR_SequentialStatement *stmt = first();
  while (stmt != NULL) {
    retval = stmt->is_above_attribute_found() || retval;
    stmt = successor(stmt);
  }
  return retval;
}



void 
IIRBase_SequentialStatementList::publish_vhdl(ostream &vhdl_out) {
  IIR_SequentialStatement *stmt = NULL;
  for (stmt = first();
       stmt != NULL; 
       stmt = successor(stmt)) {
    stmt->publish_vhdl(vhdl_out);
    vhdl_out << ";\n";
  }
}
