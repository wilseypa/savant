
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

//---------------------------------------------------------------------------

#include "IIRBase_RangeTypeDefinition.hh"
#include "IIR_Declaration.hh"
#include "IIR_TextLiteral.hh"

IIRBase_RangeTypeDefinition::IIRBase_RangeTypeDefinition() {}
IIRBase_RangeTypeDefinition::~IIRBase_RangeTypeDefinition() {}

void 
IIRBase_RangeTypeDefinition::publish_vhdl(ostream &vhdl_out) {
  ASSERT(get_left() != NULL && get_right() != NULL);

  publish_vhdl_constraint(vhdl_out);
}

void 
IIRBase_RangeTypeDefinition::publish_vhdl_decl(ostream &vhdl_out) {
  if (get_left() == NULL && get_right() == NULL) {
    // unconstrained array...
    get_base_type()->get_declaration()->get_declarator()->publish_vhdl(vhdl_out);
    vhdl_out << " range <>";
  }
  else {
    vhdl_out << "range ";
    publish_vhdl_constraint(vhdl_out);
  }
}

void
IIRBase_RangeTypeDefinition::publish_vhdl_constraint(ostream &vhdl_out) {
  if (get_left() == NULL && get_right() == NULL) {
    // unconstrained array...
    get_base_type()->get_declaration()->get_declarator()->publish_vhdl(vhdl_out);
    vhdl_out << " range <>";
  }
  else {
    ASSERT(get_left() != NULL && get_right() != NULL);
    ASSERT(get_direction()->get_kind() == IIR_ENUMERATION_LITERAL);
    
    get_base_type_left()->publish_vhdl(vhdl_out);
    if( is_ascending_range() == TRUE ){
      vhdl_out << " to ";
    }
    else {
      vhdl_out << " downto ";
    }
    get_base_type_right()->publish_vhdl(vhdl_out);
  }
}
