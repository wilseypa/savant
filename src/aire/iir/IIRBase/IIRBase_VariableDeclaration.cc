
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

#include "IIRBase_VariableDeclaration.hh"

IIRBase_VariableDeclaration::IIRBase_VariableDeclaration() : value(0) {}

IIRBase_VariableDeclaration::~IIRBase_VariableDeclaration() {
  delete get_value();
}

void
IIRBase_VariableDeclaration::set_value( IIR *new_value ){
  value = new_value;
}

IIR *
IIRBase_VariableDeclaration::get_value() {
  return value;
}

IIR *
IIRBase_VariableDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_VariableDeclaration *new_node = dynamic_cast<IIRBase_VariableDeclaration *>(IIRBase_ObjectDeclaration::convert_tree(factory));

  // Process the variables
  new_node->value = convert_node(value, factory);

  return new_node;
}

IIR_Declaration::declaration_type 
IIRBase_VariableDeclaration::get_declaration_type() {
  return VARIABLE;
}

void 
IIRBase_VariableDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << "variable ";
  publish_vhdl_declarator_with_colon(vhdl_out);
  publish_vhdl_subtype_indication_with_expression(vhdl_out);
}
