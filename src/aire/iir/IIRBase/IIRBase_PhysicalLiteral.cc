
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

#include "IIRBase_PhysicalLiteral.hh"
#include "IIR_PhysicalUnit.hh"
#include "IIR_TextLiteral.hh"

#include "savant.hh"

IIRBase_PhysicalLiteral::IIRBase_PhysicalLiteral() {
  set_abstract_literal(NULL);
  set_unit_name(NULL);
}

IIRBase_PhysicalLiteral::~IIRBase_PhysicalLiteral() {}

void 
IIRBase_PhysicalLiteral::set_abstract_literal( IIR* abstract_literal) {
	this->abstract_literal = abstract_literal;
}

IIR* 
IIRBase_PhysicalLiteral::get_abstract_literal() {
  return abstract_literal;
}

void 
IIRBase_PhysicalLiteral::set_unit_name( IIR_PhysicalUnit* unit) {
  this->unit_name = unit;
}

IIR_PhysicalUnit *
IIRBase_PhysicalLiteral::get_unit_name() {
  return unit_name;
}

IIR_Boolean
IIRBase_PhysicalLiteral::is_locally_static(){
  return TRUE;
}

IIR *
IIRBase_PhysicalLiteral::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_PhysicalLiteral *new_node = dynamic_cast<IIRBase_PhysicalLiteral *>(IIRBase_Expression::convert_tree(factory));

  // Process the variables
  new_node->abstract_literal = convert_node(abstract_literal, factory);
  new_node->unit_name = dynamic_cast<IIR_PhysicalUnit *>(convert_node(unit_name, factory));

  return new_node;
}

IIR_Boolean
IIRBase_PhysicalLiteral::is_resolved(){
  if( get_subtype() == NULL ){
    return FALSE;
  }
  else{
    return TRUE;
  }
}

IIR_TypeDefinition *
IIRBase_PhysicalLiteral::get_subtype(){
  ASSERT( get_unit_name() != NULL );
  return get_unit_name()->get_subtype();
}

ostream & 
IIRBase_PhysicalLiteral::print( ostream &os ) {
  if(get_abstract_literal() != NULL) {
    os << *get_abstract_literal();
  }
  os << " ";
  os << *(get_unit_name()->get_declarator());

  return os;
}

void 
IIRBase_PhysicalLiteral::publish_vhdl(ostream &vhdl_out) {
  ASSERT(get_subtype() != NULL);
  if(get_abstract_literal() != NULL) {
    get_abstract_literal()->publish_vhdl(vhdl_out);
  }
  vhdl_out << " ";
  if( get_unit_name() != NULL ){
    get_unit_name()->get_declarator()->publish_vhdl(vhdl_out);
  }
}
