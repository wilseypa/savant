
// Copyright (c) The University of Cincinnati.  
// All rights reserved.

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

#include "set.hh"
#include "IIR_AttributeSpecificationList.hh"
#include "IIR_EntityDeclaration.hh"
#include "IIR_GenericList.hh"
#include "IIR_PortList.hh"
#include "IIR_TextLiteral.hh"
#include "IIRBase_ComponentDeclaration.hh"

using savant::set;

IIRBase_ComponentDeclaration::IIRBase_ComponentDeclaration() :
  entity(0),
  local_generic_clause(0),
  local_port_clause(0),
  attributes(0) {
}

IIRBase_ComponentDeclaration::~IIRBase_ComponentDeclaration(){
}

// List Accessor(s)
IIR_GenericList *
IIRBase_ComponentDeclaration::get_local_generic_clause() {
  ASSERT(local_generic_clause != NULL);
  return local_generic_clause;
}

IIR_PortList *
IIRBase_ComponentDeclaration::get_local_port_clause() {
  ASSERT(local_port_clause != NULL);
  return local_port_clause;
}

IIR_AttributeSpecificationList *
IIRBase_ComponentDeclaration::get_attributes() {
  ASSERT(attributes != NULL);
  return attributes;
}

void
IIRBase_ComponentDeclaration::set_local_generic_clause(IIR_GenericList *new_local_generic_clause) {
  ASSERT(new_local_generic_clause != NULL);

  if (local_generic_clause != NULL)
    delete local_generic_clause;

  local_generic_clause = new_local_generic_clause;
}

void
IIRBase_ComponentDeclaration::set_local_port_clause(IIR_PortList *new_local_port_clause) {
  ASSERT(new_local_port_clause != NULL);

  if (local_port_clause != NULL)
    delete local_port_clause;

  local_port_clause = new_local_port_clause;
}

void
IIRBase_ComponentDeclaration::set_attributes(IIR_AttributeSpecificationList *new_attributes) {
  ASSERT(new_attributes != NULL);
  delete attributes;
  attributes = new_attributes;
}

IIR *
IIRBase_ComponentDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ComponentDeclaration *new_node = dynamic_cast<IIRBase_ComponentDeclaration *>(IIRBase_Declaration::convert_tree(factory));

  // Process the variables
  new_node->entity = dynamic_cast<IIR_EntityDeclaration *>(convert_node(entity, factory));
  new_node->local_generic_clause = dynamic_cast<IIR_GenericList *>(convert_node(local_generic_clause, factory));
  new_node->local_port_clause = dynamic_cast<IIR_PortList *>(convert_node(local_port_clause, factory));
  new_node->attributes = dynamic_cast<IIR_AttributeSpecificationList *>(convert_node(attributes, factory));

  return new_node;
}

IIR_Declaration::declaration_type
IIRBase_ComponentDeclaration::get_declaration_type(){
   return COMPONENT;
}

set<IIR_Declaration> *
IIRBase_ComponentDeclaration::find_declarations( IIR_Name *to_find ){
  set<IIR_Declaration> *retval = new set<IIR_Declaration>;
  set<IIR_Declaration> *current_set = get_local_generic_clause()->find_declarations( to_find );
  if( current_set != NULL ){
    retval->add( current_set );
  } 
  current_set = get_local_port_clause()->find_declarations( to_find );
  if( current_set != NULL ){
    retval->add( current_set );
  }
  if ( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }
  return retval;
}

void 
IIRBase_ComponentDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << " component ";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << " is\n";

  if(get_local_generic_clause()->size() != 0) {
    vhdl_out << " generic( ";
    get_local_generic_clause()->publish_vhdl(vhdl_out);
    vhdl_out << " );\n";
  }
  if(get_local_port_clause()->size() != 0) {
    vhdl_out << " port( ";
    get_local_port_clause()->publish_vhdl(vhdl_out);
    vhdl_out << " );\n";
  }
  vhdl_out << " end component ";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << ";\n";
}

void 
IIRBase_ComponentDeclaration::set_entity( IIR_EntityDeclaration *entity ){
  this->entity = entity;
}

IIR_EntityDeclaration *
IIRBase_ComponentDeclaration::get_entity(){
  return entity;
}


