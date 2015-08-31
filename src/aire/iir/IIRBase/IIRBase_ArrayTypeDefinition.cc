
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
#include "IIRBase_ArrayTypeDefinition.hh"
#include "IIRBase_ScalarTypeDefinition.hh"
#include "IIR_TextLiteral.hh"

#include "set.hh"

IIRBase_ArrayTypeDefinition::IIRBase_ArrayTypeDefinition() :
  my_index_subtype( 0 ),
  my_element_subtype( 0 ),
  my_is_element( FALSE ){}

IIRBase_ArrayTypeDefinition::~IIRBase_ArrayTypeDefinition(){}

void 
IIRBase_ArrayTypeDefinition::set_index_subtype( IIR_ScalarTypeDefinition *index_subtype ){
  my_index_subtype = index_subtype;
}

IIR_ScalarTypeDefinition *
IIRBase_ArrayTypeDefinition::get_index_subtype(){
  return my_index_subtype;
}

//DRH - Provide base implementation of get_num_indexes for Plugin architecture
IIR_Int32
IIRBase_ArrayTypeDefinition::get_num_indexes(){
  IIR_Int32 num_indexes = 1;

  IIRBase_TypeDefinition *current_subtype = _get_element_subtype();
  ASSERT(current_subtype != NULL);
  while( current_subtype->is_array_type() == TRUE
         && current_subtype->is_element() == FALSE ){
    num_indexes++;
    current_subtype = current_subtype->_get_element_subtype();
    ASSERT(current_subtype != NULL);
  }

  return num_indexes;
}
//DRH - Provide intermediate call for get_num_indexes
IIRBase_TypeDefinition *
IIRBase_ArrayTypeDefinition::_get_element_subtype(){
  return dynamic_cast<IIRBase_TypeDefinition *>(get_element_subtype());
}

void 
IIRBase_ArrayTypeDefinition::set_element_subtype( IIR_TypeDefinition *element_subtype ){
  my_element_subtype = element_subtype;
}

IIR_TypeDefinition *
IIRBase_ArrayTypeDefinition::get_element_subtype(){
  return my_element_subtype;
}

IIR_Boolean 
IIRBase_ArrayTypeDefinition::is_element(){
  return my_is_element;
}

void
IIRBase_ArrayTypeDefinition::set_is_element( IIR_Boolean new_is_element ){
  my_is_element = new_is_element;
}

IIR *
IIRBase_ArrayTypeDefinition::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ArrayTypeDefinition *new_node = dynamic_cast<IIRBase_ArrayTypeDefinition *>(IIRBase_TypeDefinition::convert_tree(factory));

  // Process the variables
  new_node->my_index_subtype = dynamic_cast<IIR_ScalarTypeDefinition *>(convert_node(my_index_subtype, factory));
  new_node->my_element_subtype = dynamic_cast<IIR_TypeDefinition *>(convert_node(my_element_subtype, factory));  
  new_node->my_is_element = my_is_element;

  return new_node;
}

IIR_Boolean 
IIRBase_ArrayTypeDefinition::is_unconstrained_array_type(){
  IIR_ScalarTypeDefinition *index = get_resolved_index_subtype();
  ASSERT(index != 0);
  if( index->get_left() == 0 ){
    ASSERT( index->get_right() == 0 );
    ASSERT( index->get_direction() == 0 );

    return TRUE;
  }
  else{
    return FALSE;
  }
}

savant::set<IIR_Declaration> *
IIRBase_ArrayTypeDefinition::find_declarations( IIR_Name *to_find){
  return get_element_subtype()->find_declarations( to_find );
}

IIR_Boolean
IIRBase_ArrayTypeDefinition::is_discrete_type(){
  if(get_element_subtype()->is_scalar_type() == TRUE){
    return get_element_subtype()->is_discrete_type();
  }
  else {
    return FALSE;
  }
}

IIR_Boolean 
IIRBase_ArrayTypeDefinition::is_character_type(){
  IIR_Boolean retval = FALSE;

  if( get_base_type() != 0 ){
    retval = get_base_type()->is_character_type();
  }
  else{
    if( get_element_subtype()->is_character_type() == TRUE &&
	get_element_subtype()->is_scalar_type() == TRUE ){
      retval = TRUE;
    }
  }
    
  return retval;
}

IIR_Boolean
IIRBase_ArrayTypeDefinition::is_locally_static(){
  IIR_Boolean retval = !is_unconstrained_array_type();

  if( retval ){
    retval = get_index_subtype()->is_locally_static();

    IIR_TypeDefinition *current_index = get_element_subtype();
    while( current_index && 
	   current_index->is_array_type() &&
	   !current_index->is_element() ){
      retval = retval && current_index->is_locally_static();
      current_index =
	dynamic_cast<IIR_ArrayTypeDefinition *>(current_index)->get_element_subtype();
    }
  }

  return retval;
}

ostream&
IIRBase_ArrayTypeDefinition::print(ostream &os) {
  os << "array ( " << *get_resolved_index_subtype(); 
  
  IIR_TypeDefinition *element_type = get_element_subtype();
  
  while( element_type->is_array_type() && element_type->is_anonymous() ){
    os << ", " << *(element_type->get_resolved_index_subtype());
    element_type = element_type->get_element_subtype();
  }
  
  os << " ) of " << *(element_type->get_declarator());

  return os;
}

void
IIRBase_ArrayTypeDefinition::set_declaration( IIR_Declaration *corresponding_decl ){
  IIRBase_TypeDefinition::set_declaration( corresponding_decl );
  if( get_resolved_index_subtype() &&
      get_resolved_index_subtype()->get_declaration() == 0 ){
//     get_resolved_index_subtype()->set_declaration( corresponding_decl );
  }
  if( get_final_subtype() &&
      get_final_subtype()->get_declaration() == 0 ){
//     get_final_subtype()->set_declaration( corresponding_decl );
  }
}

IIR_TypeDefinition*
IIRBase_ArrayTypeDefinition::get_final_subtype() {

  IIR_TypeDefinition* node = get_element_subtype();
  while ( node && 
          ((node->get_kind() == IIR_ARRAY_TYPE_DEFINITION ||
            node->get_kind() == IIR_ARRAY_SUBTYPE_DEFINITION) &&
           node->is_element() == false )){
    node =  node->get_element_subtype();
  }
  return node;
}

void
IIRBase_ArrayTypeDefinition::publish_vhdl_subtype_decl(ostream &vhdl_out){
  if (is_anonymous() == FALSE) {
    if (get_type_mark() != 0) {
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

void 
IIRBase_ArrayTypeDefinition::publish_vhdl_decl(ostream &vhdl_out) {
  IIRBase_TypeDefinition *node = this;
  int max_index = get_num_indexes();

  ASSERT(get_element_subtype() != 0);
  ASSERT(get_resolved_index_subtype() != 0);

  vhdl_out << "array (";
  
  node = this;
  while ((node->is_array_type() == TRUE) && (max_index > 0)) {
    dynamic_cast<IIRBase_ScalarTypeDefinition *>
      (node->get_resolved_index_subtype())->publish_vhdl_index(vhdl_out);
    max_index--;
    node = dynamic_cast<IIRBase_TypeDefinition *>(node->get_element_subtype());
    if (max_index > 0) {
      vhdl_out << ", ";
      ASSERT ( node != 0 );
    }
  }

  ASSERT ( node != 0 );
  vhdl_out << ") of ";
  node->publish_vhdl(vhdl_out);
}

void
IIRBase_ArrayTypeDefinition::publish_vhdl(ostream &vhdl_out){
  ASSERT( get_declaration() != 0 );
  get_declaration()->publish_vhdl(vhdl_out);
}
