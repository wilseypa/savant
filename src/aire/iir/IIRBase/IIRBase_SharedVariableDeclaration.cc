
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

#include "savant.hh"
#include "IIRBase_SharedVariableDeclaration.hh"
#include "IIR_TextLiteral.hh"
#include "IIR_TypeDefinition.hh"

IIRBase_SharedVariableDeclaration::IIRBase_SharedVariableDeclaration() :
  value(0){}

IIRBase_SharedVariableDeclaration::~IIRBase_SharedVariableDeclaration() {}

void
IIRBase_SharedVariableDeclaration::set_value( IIR *new_value ){
  value = new_value;
}

IIR*
IIRBase_SharedVariableDeclaration::get_value() {
  return value;
}


IIR *
IIRBase_SharedVariableDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_SharedVariableDeclaration *new_node = dynamic_cast<IIRBase_SharedVariableDeclaration *>(IIRBase_ObjectDeclaration::convert_tree(factory));

  // Process the variables
  new_node->value = convert_node(value, factory);

  return new_node;
}

IIR_Declaration::declaration_type 
IIRBase_SharedVariableDeclaration::get_declaration_type(){
   return SHARED_VARIABLE;
}

void 
IIRBase_SharedVariableDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << " shared variable ";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << " : ";
  get_subtype()->publish_vhdl(vhdl_out);
  if(IIRBase_SharedVariableDeclaration::get_value() != NULL) {
    vhdl_out << " := ";
    dynamic_cast<IIRBase *>(IIRBase_SharedVariableDeclaration::get_value())->publish_vhdl(vhdl_out);
  }
  vhdl_out << ";\n";
}
