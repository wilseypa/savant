
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

#include "set.hh"
#include "IIRBase_AccessTypeDefinition.hh"
#include "IIR_TypeDefinition.hh"
#include "IIR_TextLiteral.hh"
#include "savant.hh"
#include <iostream>

using std::cerr;

IIRBase_AccessTypeDefinition::IIRBase_AccessTypeDefinition(){
  set_designated_type( NULL );
}

IIRBase_AccessTypeDefinition::~IIRBase_AccessTypeDefinition(){
  delete get_designated_type();
}

IIR_AccessTypeDefinition *
IIRBase_AccessTypeDefinition::get( IIR_TypeDefinition * ){
  cerr << "IIRBase_AccessTypeDefinition::get not yet implemented!\n";
  abort();
  return NULL;
}

void 
IIRBase_AccessTypeDefinition::set_designated_type( IIR_TypeDefinition *designated_type){
  access_for_type = designated_type;
}


IIR_TypeDefinition *
IIRBase_AccessTypeDefinition::get_designated_type(){
  return access_for_type;
}

IIR *
IIRBase_AccessTypeDefinition::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_AccessTypeDefinition *new_node = dynamic_cast<IIRBase_AccessTypeDefinition *>(IIRBase_TypeDefinition::convert_tree(factory));

  // Process the variables
  new_node->access_for_type = dynamic_cast<IIR_TypeDefinition *>(convert_node(access_for_type, factory));

  return new_node;
}

IIR_Boolean
IIRBase_AccessTypeDefinition::is_scalar_type() {
  IIR_TypeDefinition *type = get_designated_type();
  if((type != NULL) && (type != this)) {
    return type->is_scalar_type();
  }
  else{
    return FALSE;
  }
}

IIR_Boolean
IIRBase_AccessTypeDefinition::is_array_type() {
  IIR_TypeDefinition *type = get_designated_type();
  if((type != NULL) && (type != this)) {
    return type->is_array_type();
  }
  else{
    return FALSE;
  }
}

IIR_Boolean
IIRBase_AccessTypeDefinition::is_unconstrained_array_type() {
  IIR_TypeDefinition *type = get_designated_type();
  if((type != NULL) && (type != this)) {
    return type->is_unconstrained_array_type();
  }
  else{
    return FALSE;
  }
}

IIR_Boolean
IIRBase_AccessTypeDefinition::is_record_type() {
  IIR_TypeDefinition *type = get_designated_type();
  if((type != NULL) && (type != this)) {
    return type->is_record_type();
  }
  else{
    return FALSE;
  }
}

IIR_Boolean 
IIRBase_AccessTypeDefinition::is_element(){
  return get_designated_type()->is_element();
}

IIR_ScalarTypeDefinition *
IIRBase_AccessTypeDefinition::get_resolved_index_subtype(){
  IIR_ScalarTypeDefinition *retval = NULL;

  IIR_TypeDefinition *type = get_designated_type();
  if( type != NULL ){
    retval = type->get_resolved_index_subtype();
  }

  return retval;
}

IIR_TypeDefinition *
IIRBase_AccessTypeDefinition::get_element_subtype(){
  return get_designated_type()->get_element_subtype();
}

void 
IIRBase_AccessTypeDefinition::set_element_subtype( IIR_TypeDefinition *new_element_type ){
  IIR_TypeDefinition *type = get_designated_type();
  ASSERT( type != NULL );
  type->set_element_subtype( new_element_type );
}

savant::set<IIR_Declaration> *
IIRBase_AccessTypeDefinition::find_declarations( IIR_Name *to_find){
  IIR_TypeDefinition *type = get_designated_type();
  if( type == NULL ){
    return NULL;
  }
  else{
    return type->find_declarations( to_find );
  }
}

void 
IIRBase_AccessTypeDefinition::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << "access ";
  IIRBase_TypeDefinition *type = dynamic_cast<IIRBase_TypeDefinition *>(get_designated_type());
  ASSERT(type == NULL);

  if ( type->is_anonymous() == FALSE ){
    type->get_declaration()->get_declarator()->publish_vhdl(vhdl_out);
  }
  else {
    type->publish_vhdl_type_decl(vhdl_out);
  }
}

void
IIRBase_AccessTypeDefinition::publish_vhdl_subtype_decl(ostream &vhdl_out){
  ASSERT(get_type_mark() != NULL);
  ASSERT(get_type_mark()->get_declaration() != NULL);
  
  get_type_mark()->get_declaration()->publish_vhdl(vhdl_out);
}
