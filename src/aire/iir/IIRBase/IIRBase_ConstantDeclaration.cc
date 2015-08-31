
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


#include "savant.hh"
#include "IIRBase_ConstantDeclaration.hh"
#include "IIRBase_TypeDefinition.hh"

IIRBase_ConstantDeclaration::IIRBase_ConstantDeclaration() :
  value(0){}

IIRBase_ConstantDeclaration::~IIRBase_ConstantDeclaration(){
  delete value;
}

void 
IIRBase_ConstantDeclaration::set_value( IIR *new_value ){
  value = new_value;
}

IIR *
IIRBase_ConstantDeclaration::get_value(){
  return value;
}

IIR *
IIRBase_ConstantDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ConstantDeclaration *new_node = dynamic_cast<IIRBase_ConstantDeclaration *>(IIRBase_ObjectDeclaration::convert_tree(factory));

  // Process the variables
  new_node->value = convert_node(value, factory);

  return new_node;
}

IIR_Boolean
IIRBase_ConstantDeclaration::is_ascending_range() {
  return get_subtype()->is_ascending_range();
}

IIR_Declaration::declaration_type 
IIRBase_ConstantDeclaration::get_declaration_type(){
  return CONSTANT;
}

IIR_Boolean
IIRBase_ConstantDeclaration::is_locally_static(){
  IIR_Boolean retval = false;
  if( !is_implicit_declaration() ){
    if( get_value() != 0 &&
	get_value()->is_locally_static() ){
      retval = true;
    }
  }
  return retval;
}

void 
IIRBase_ConstantDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << " constant ";
  publish_vhdl_declarator_with_colon(vhdl_out);
  publish_vhdl_subtype_indication_with_expression(vhdl_out);
}

void 
IIRBase_ConstantDeclaration::publish_vhdl_range( ostream &vhdl_out ) {
  dynamic_cast<IIRBase_TypeDefinition *>(get_subtype())->publish_vhdl_range( vhdl_out );
}
