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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant.hh"
#include "IIR_Declaration.hh"
#include "IIRBase_EnumerationLiteral.hh"
#include "IIRBase_EnumerationLiteralList.hh"

IIRBase_EnumerationLiteralList::IIRBase_EnumerationLiteralList() {}
IIRBase_EnumerationLiteralList::~IIRBase_EnumerationLiteralList() {}


IIR* 
IIRBase_EnumerationLiteralList::first(){
  IIR_Declaration *retval = dynamic_cast<IIR_Declaration *>(IIRBase_List::first());

  if (retval != NULL)
    ASSERT( retval->get_kind() == IIR_ENUMERATION_LITERAL );

  return retval;
}

IIR* 
IIRBase_EnumerationLiteralList::last(){
  IIR_Declaration *retval = dynamic_cast<IIR_Declaration *>(IIRBase_List::last());

  if (retval != NULL)
    ASSERT( retval->get_kind() == IIR_ENUMERATION_LITERAL );

  return dynamic_cast<IIR_EnumerationLiteral *>(retval);
}


IIR* 
IIRBase_EnumerationLiteralList::successor( IIR_EnumerationLiteral *lit ) { 
  ASSERT( lit->get_kind() == IIR_ENUMERATION_LITERAL );

  IIR_Declaration *retval = dynamic_cast<IIR_Declaration *>(IIRBase_List::successor( lit ));

  return dynamic_cast<IIR_EnumerationLiteral *>(retval);
}


IIR * 
IIRBase_EnumerationLiteralList::predecessor( IIR_EnumerationLiteral *lit ) { 
  ASSERT( lit->get_kind() == IIR_ENUMERATION_LITERAL );

  IIR_Declaration *retval = dynamic_cast<IIR_Declaration *>(IIRBase_List::predecessor( lit ));

  if (retval != NULL)
    ASSERT( retval->get_kind() == IIR_ENUMERATION_LITERAL );

  return dynamic_cast<IIR_EnumerationLiteral *>(retval);
}

ostream&
IIRBase_EnumerationLiteralList::print(ostream& os) {
  IIR_EnumerationLiteral *literal = NULL;
    
  os << "(";
    
  literal = dynamic_cast<IIR_EnumerationLiteral *>(first());
  while (literal != NULL) {
    literal->print(os);
    literal = dynamic_cast<IIR_EnumerationLiteral *>(successor(literal));
    if (literal != NULL) {
      os << ", ";
    }
  }
  os << ")";

  return os;
}


void 
IIRBase_EnumerationLiteralList::publish_vhdl(ostream &vhdl_out) {
  IIRBase_EnumerationLiteral *literal = NULL;
    
  vhdl_out << "(";
    
  literal = dynamic_cast<IIRBase_EnumerationLiteral *>(first());
  while (literal != NULL) {
    literal->publish_vhdl(vhdl_out);
    literal = dynamic_cast<IIRBase_EnumerationLiteral *>(successor(literal));
    if (literal != NULL) {
      vhdl_out << ", ";
    }
  }
  vhdl_out << ")";
}
