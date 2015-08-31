
// Copyright (c) The University of Cincinnati.  All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
// DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

#include "IIRBase_AssociationElementOpen.hh"

IIRBase_AssociationElementOpen::IIRBase_AssociationElementOpen(){}
IIRBase_AssociationElementOpen::~IIRBase_AssociationElementOpen(){}

ostream&
IIRBase_AssociationElementOpen::print(ostream& os) {
  if (get_formal() != NULL) {
    os << *get_formal();
    os << " => ";
  }
  
  os << "open";
  
  return os;
}

void 
IIRBase_AssociationElementOpen::publish_vhdl(ostream &vhdl_out) {
  if (get_formal() != NULL) {
    if( get_formal()->get_kind() == IIR_INTEGER_SUBTYPE_DEFINITION ){
      dynamic_cast<IIRBase *>(get_formal())->publish_vhdl_range(vhdl_out);
    }
    else {
      get_formal()->publish_vhdl(vhdl_out);
    }
    vhdl_out << " => ";
  }

  vhdl_out << "open";
}

void
IIRBase_AssociationElementOpen::publish_vhdl_without_formals(ostream &vhdl_out) {
  if (get_formal() != NULL) {
    if (get_formal()->get_kind() == IIR_FUNCTION_CALL) {
      get_formal()->publish_vhdl(vhdl_out);
      vhdl_out << "=>";
    }
  }

  vhdl_out << "open";
}
