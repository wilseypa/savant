
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


#include "set.hh"
#include "savant.hh"
#include "IIRBase_TypeDeclaration.hh"
#include "IIR_AttributeSpecificationList.hh"
#include "IIR_Declaration.hh"
#include "IIRBase_TypeDefinition.hh"
#include "IIR_TextLiteral.hh"

#include <iostream>
using std::cerr;

IIRBase_TypeDeclaration::IIRBase_TypeDeclaration()  :
  attributes(0) {
  type = NULL;
  implicit_declarations = NULL;
}


IIRBase_TypeDeclaration::~IIRBase_TypeDeclaration() {
}

void
IIRBase_TypeDeclaration::set_type( IIR_TypeDefinition *new_type ){
  type = new_type;
}

IIR_TypeDefinition*
IIRBase_TypeDeclaration::get_type() {
  return type;
}

// List Accessor(s)
IIR_AttributeSpecificationList *
IIRBase_TypeDeclaration::get_attributes() {
  ASSERT(attributes != NULL);
  return attributes;
}

void
IIRBase_TypeDeclaration::set_attributes(IIR_AttributeSpecificationList *new_attributes) {
  ASSERT(new_attributes != NULL);
  delete attributes;
  attributes = new_attributes;
}

IIR *
IIRBase_TypeDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_TypeDeclaration *new_node = dynamic_cast<IIRBase_TypeDeclaration *>(IIRBase_Declaration::convert_tree(factory));

  // Process the variables
  new_node->attributes = dynamic_cast<IIR_AttributeSpecificationList *>(convert_node(attributes, factory));
  new_node->type = dynamic_cast<IIR_TypeDefinition *>(convert_node(type, factory));

  return new_node;
}

IIR_TypeDefinition *
IIRBase_TypeDeclaration::get_subtype(){
  return get_type();
}

IIR_Boolean
IIRBase_TypeDeclaration::is_locally_static(){
  return get_type()->is_locally_static();
}

IIR_Boolean
IIRBase_TypeDeclaration::is_incomplete_type_declaration(){
  if( get_type() == NULL || get_type()->is_incomplete_type_definition() == TRUE ){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

IIR_Declaration::declaration_type
IIRBase_TypeDeclaration::get_declaration_type() {
  return IIR_Declaration::TYPE;
}

savant::set<IIR_Declaration> *
IIRBase_TypeDeclaration::find_declarations( IIR_Name *to_find ){
  ASSERT( get_type() != NULL );
  return get_type()->find_declarations( to_find );
}

savant::set<IIR_Declaration> *
IIRBase_TypeDeclaration::find_declarations( IIR_TextLiteral *to_find ){
  ASSERT( get_type() != NULL );
  return get_type()->find_declarations( to_find );
}

savant::set<IIR_Declaration> *
IIRBase_TypeDeclaration::get_implicit_declarations() {
  return implicit_declarations;
}

void 
IIRBase_TypeDeclaration::set_implicit_declarations( savant::set<IIR_Declaration> *new_implicit_declarations) {
  implicit_declarations = new_implicit_declarations;
}

void 
IIRBase_TypeDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << "type ";
  get_declarator()->publish_vhdl(vhdl_out);
  if( get_type() ) {
    vhdl_out << " is ";
    dynamic_cast<IIRBase_TypeDefinition *>(get_type())->publish_vhdl_type_decl(vhdl_out);
  }
  vhdl_out << ";\n";
}

void
IIRBase_TypeDeclaration::publish_vhdl_range(ostream &vhdl_out){
  publish_vhdl(vhdl_out);
}
