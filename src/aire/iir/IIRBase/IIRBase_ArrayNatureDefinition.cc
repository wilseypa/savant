
// Copyright (c) 2002-2003 The University of Cincinnati.
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

// Author: Sivakumar Gowrisankar             gowriss@ececs.uc.edu

//---------------------------------------------------------------------------

#include "IIRBase_ArrayNatureDefinition.hh"
#include "IIRBase_ScalarTypeDefinition.hh"
#include "IIR_Declaration.hh"
#include "IIR_TextLiteral.hh"

IIRBase_ArrayNatureDefinition::IIRBase_ArrayNatureDefinition() :
  index_subtype(0),
  element_subtype(0),
  my_is_element(false){}

IIRBase_ArrayNatureDefinition::~IIRBase_ArrayNatureDefinition() {}

IIR_TypeDefinition *
IIRBase_ArrayNatureDefinition::get_element_subtype(){
  return element_subtype;
}

IIR_ScalarTypeDefinition *
IIRBase_ArrayNatureDefinition::get_index_subtype(){
  return index_subtype;
}
 
IIR_Boolean
IIRBase_ArrayNatureDefinition::is_element(){
  return my_is_element;
}
 
void
IIRBase_ArrayNatureDefinition::set_element_subtype( IIR_TypeDefinition *new_element_type ){
  element_subtype = dynamic_cast<IIR_NatureDefinition *>(new_element_type);
}
 
void
IIRBase_ArrayNatureDefinition::set_index_subtype( IIR_ScalarTypeDefinition *new_index_type ){
  index_subtype = new_index_type;
}

void
IIRBase_ArrayNatureDefinition::set_is_element( IIR_Boolean is_element ){
  my_is_element = is_element;
}

IIR *
IIRBase_ArrayNatureDefinition::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ArrayNatureDefinition *new_node = dynamic_cast<IIRBase_ArrayNatureDefinition *>(IIRBase_NatureDefinition::convert_tree(factory));

  // Process the variables
  new_node->index_subtype = dynamic_cast<IIR_ScalarTypeDefinition *>(convert_node(index_subtype, factory));
  new_node->element_subtype = dynamic_cast<IIR_NatureDefinition *>(convert_node(element_subtype, factory));
  new_node->my_is_element = my_is_element;

  return new_node;
}

IIR_Boolean 
IIRBase_ArrayNatureDefinition::is_unconstrained_array_type(){
  IIR_ScalarTypeDefinition *index = get_index_subtype();
  ASSERT(index != NULL);
  if( index->get_left() == NULL ){
    ASSERT( index->get_right() == NULL );
    ASSERT( index->get_direction() == NULL );
    return TRUE;
  }
  else{
    return FALSE;
  }
}

IIR_TypeDefinition*
IIRBase_ArrayNatureDefinition::get_final_subtype() {

  IIR_TypeDefinition* node = get_element_subtype();
  while ( node && 
          ((node->get_kind() == IIR_ARRAY_NATURE_DEFINITION ||
            node->get_kind() == IIR_ARRAY_SUBNATURE_DEFINITION) &&
           node->is_element() == false )){
    node =  node->get_element_subtype();
  }
  return node;
}
 

void
IIRBase_ArrayNatureDefinition::publish_vhdl_decl(ostream &vhdl_out) {
  IIRBase_TypeDefinition *node = this;
  int max_index = get_num_indexes();

  ASSERT(get_element_subtype() != NULL);
  ASSERT(get_resolved_index_subtype() != NULL);

  vhdl_out << "array (";

  node = this;
  while ((node->is_array_type() == TRUE) && (max_index > 0)) {
    dynamic_cast<IIRBase_ScalarTypeDefinition *>
      (node->get_resolved_index_subtype())->publish_vhdl_index(vhdl_out);
    max_index--;
    node = dynamic_cast<IIRBase_TypeDefinition *>(node->get_element_subtype());
    if (max_index > 0) {
      vhdl_out << ", ";
      ASSERT ( node != NULL );
    }
  }

  ASSERT ( node != NULL );
  vhdl_out << ") of ";
  node->publish_vhdl(vhdl_out);
}

void
IIRBase_ArrayNatureDefinition::publish_vhdl(ostream &vhdl_out){
  ASSERT( get_declaration() != NULL );
  get_declaration()->publish_vhdl(vhdl_out);
}

void
IIRBase_ArrayNatureDefinition::publish_vhdl_subtype_decl(ostream &vhdl_out){
  if( is_anonymous() == FALSE ){
    if( get_type_mark() != NULL ){
      get_type_mark()->get_declaration()->get_declarator()->publish_vhdl(vhdl_out);
    }
    else {
      get_declaration()->get_declarator()->publish_vhdl(vhdl_out);
    }
  }
  else {
    publish_vhdl_decl(vhdl_out);
  }
}
