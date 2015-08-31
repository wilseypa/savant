
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

#include "IIRBase_AttributeSpecification.hh"




#include "IIR_Declaration.hh"
#include "IIR_DesignatorList.hh"
#include "IIR_Identifier.hh"
#include "savant.hh"

IIRBase_AttributeSpecification::IIRBase_AttributeSpecification() :
  entity_name_list(0),
  attribute_declaration(0)
{
  set_value( NULL );
  set_entity_class( NULL );
}

IIRBase_AttributeSpecification::~IIRBase_AttributeSpecification(){
}

void 
IIRBase_AttributeSpecification::set_value( IIR *new_value ){
  value = new_value;
}

IIR *
IIRBase_AttributeSpecification::get_value(){
  return value;
}

void
IIRBase_AttributeSpecification::set_entity_class( IIR_Identifier *new_entity_class ){
  entity_class = new_entity_class ;
}

IIR_Identifier *
IIRBase_AttributeSpecification::get_entity_class(){
  return entity_class ;
}

// List Accessor(s)
IIR_DesignatorList *
IIRBase_AttributeSpecification::get_entity_name_list() {
  ASSERT(entity_name_list != NULL);
  return entity_name_list;
}

void
IIRBase_AttributeSpecification::set_entity_name_list(IIR_DesignatorList *new_entity_name_list) {
  ASSERT(new_entity_name_list != NULL);
  delete entity_name_list;
  entity_name_list = new_entity_name_list;
}

IIR *
IIRBase_AttributeSpecification::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_AttributeSpecification *new_node = dynamic_cast<IIRBase_AttributeSpecification *>(IIRBase_Declaration::convert_tree(factory));

  // Process the variables
  new_node->entity_name_list = dynamic_cast<IIR_DesignatorList *>(convert_node(entity_name_list, factory));
  new_node->value = convert_node(value, factory);
  new_node->entity_class = dynamic_cast<IIR_Identifier *>(convert_node(entity_class, factory));
  new_node->attribute_declaration = dynamic_cast<IIR_Declaration *>(convert_node(attribute_declaration, factory));

  return new_node;
}

void 
IIRBase_AttributeSpecification::set_declaration( IIR_Declaration *decl ){
  if( decl != NULL ){
    ASSERT( decl->get_kind() == IIR_ATTRIBUTE_DECLARATION );
  }

  attribute_declaration = decl;
}

IIR_TypeDefinition *
IIRBase_AttributeSpecification::get_subtype() {
  return attribute_declaration->get_subtype();
}

IIR_Declaration *
IIRBase_AttributeSpecification::get_declaration(){
  return attribute_declaration;
}

IIR_Declaration::declaration_type 
IIRBase_AttributeSpecification::get_declaration_type(){
   return ATTRIBUTE;
}

void 
IIRBase_AttributeSpecification::publish_vhdl_decl(ostream &vhdl_out) {
  ASSERT(get_value() != NULL);
  ASSERT(get_value()->is_resolved() == TRUE);
  ASSERT(get_declaration() != NULL);
  ASSERT(get_declaration()->is_resolved() == TRUE);
  ASSERT(get_entity_class() != NULL);

  vhdl_out << "attribute ";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << " of ";
  get_entity_name_list()->publish_vhdl(vhdl_out);
  vhdl_out << ": ";
  get_entity_class()->publish_vhdl(vhdl_out);
  vhdl_out << " is ";
  get_value()->publish_vhdl(vhdl_out);
  vhdl_out << ";\n";
}
