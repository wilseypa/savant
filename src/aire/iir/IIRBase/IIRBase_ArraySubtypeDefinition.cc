
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
#include "IIRBase_ArraySubtypeDefinition.hh"
#include "IIR_FunctionDeclaration.hh"
#include "IIRBase_ScalarTypeDefinition.hh"
#include "IIR_TextLiteral.hh"
#include "IIR_TypeDefinition.hh"

IIRBase_ArraySubtypeDefinition::IIRBase_ArraySubtypeDefinition() :
  resolution_function( 0 ){}

IIRBase_ArraySubtypeDefinition::~IIRBase_ArraySubtypeDefinition(){}

void 
IIRBase_ArraySubtypeDefinition::set_resolution_function(IIR_FunctionDeclaration *res_func){
  resolution_function = res_func;
}

IIR_FunctionDeclaration *
IIRBase_ArraySubtypeDefinition::get_resolution_function(){
  return resolution_function;
}

IIR *
IIRBase_ArraySubtypeDefinition::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ArraySubtypeDefinition *new_node = dynamic_cast<IIRBase_ArraySubtypeDefinition *>(IIRBase_ArrayTypeDefinition::convert_tree(factory));

  // Process the variables
  new_node->resolution_function = dynamic_cast<IIR_FunctionDeclaration *>(convert_node(resolution_function, factory));

  return new_node;
}

IIR_Boolean
IIRBase_ArraySubtypeDefinition::is_subtype() {
  return TRUE;
}

IIR_ScalarTypeDefinition *
IIRBase_ArraySubtypeDefinition::get_resolved_index_subtype(){
  IIR_ScalarTypeDefinition *retval = 0;
  if(get_index_subtype() != NULL) {
    retval = get_index_subtype();
  } 
  else {
    ASSERT(get_base_type() != NULL);
    retval = get_base_type()->get_resolved_index_subtype();
  }
  return retval;
}

ostream&
IIRBase_ArraySubtypeDefinition::print(ostream &os) {
  if( get_base_type()->get_declaration() != NULL ){
    os << *(get_base_type()->get_declaration()->get_declarator());
  }
  else{
    os << "ANONYMOUS";
  }
  return os;
}

void
IIRBase_ArraySubtypeDefinition::publish_vhdl( ostream &vhdl_out ){
  //if( get_declaration() != NULL ){ 
  if( get_declaration() != NULL && get_declaration()->get_kind() != IIR_CONSTANT_INTERFACE_DECLARATION ){ //DRH - HACK: get_declaration publishes "left" for subtype_indication w/ index_constraint - need to evaluate why build_implicit_operator called for STRING(1 TO 4) ref
    get_declaration()->publish_vhdl(vhdl_out);
  } 
  else { 
    ASSERT( get_base_type() != NULL );
    get_base_type()->publish_vhdl(vhdl_out);
    if (get_index_subtype() != NULL) {
      vhdl_out << "(";
      dynamic_cast<IIRBase_ScalarTypeDefinition *>(get_index_subtype())->publish_vhdl_range(vhdl_out);
      vhdl_out << ")";
    }
  }
}

void
IIRBase_ArraySubtypeDefinition::publish_vhdl_type_decl( ostream &vhdl_out ){
  IIRBase_ArrayTypeDefinition *node ;
  IIRBase_ArrayTypeDefinition *base_type =
    dynamic_cast<IIRBase_ArrayTypeDefinition *>(get_base_type());
  int index, max_index ;
  
  ASSERT(get_index_subtype() != NULL );
  ASSERT(get_element_subtype() != NULL );
  
  if ( get_resolution_function() != NULL )  {
    get_resolution_function()->publish_vhdl(vhdl_out);
    vhdl_out << " ";
  }
  
  vhdl_out << "array ";
  ASSERT ( base_type->get_index_subtype() != NULL );
  
  if(( base_type->is_unconstrained_array_type() == TRUE) ||
      (base_type->get_index_subtype()->is_enumeration_type() == TRUE) ){
    
    vhdl_out << " ( ";
    
    index = 1 ;
    max_index = get_num_indexes();
    for( node = this; 
	 index <= max_index;
	 index++, node = dynamic_cast<IIRBase_ArrayTypeDefinition *>(node->get_element_subtype())){
      ASSERT(node->is_array_type() );
      ASSERT(node->get_index_subtype() != NULL );
      ASSERT(node->get_element_subtype() != NULL );
      
      // The next assertion is invalid - what about
      // subtype foo1 is memory (1 to 10);
      //    ASSERT(node->get_index_subtype()->get_type_mark() != NULL);

      if (index > 1) { vhdl_out << ", "; }
      dynamic_cast<IIRBase_ScalarTypeDefinition *>
	(node->get_index_subtype())->publish_vhdl_index(vhdl_out);
    }
    
    vhdl_out << " ) ";
    
  }
  vhdl_out << " of ";
  get_final_subtype()->publish_vhdl(vhdl_out);
}

void 
IIRBase_ArraySubtypeDefinition::publish_vhdl_decl(ostream &vhdl_out) {
  IIRBase_ArrayTypeDefinition *node ;
  IIRBase_ArrayTypeDefinition *base_type =
    dynamic_cast<IIRBase_ArrayTypeDefinition *>(get_base_type());
  int index, max_index ;
  
  ASSERT(get_index_subtype() != NULL );
  ASSERT(get_element_subtype() != NULL );
  
  if ( get_resolution_function() != NULL )  {
    get_resolution_function()->publish_vhdl(vhdl_out);
    vhdl_out << " ";
  }
  
  base_type->publish_vhdl(vhdl_out);
  ASSERT ( base_type->get_index_subtype() != NULL );
  
  if(( base_type->is_unconstrained_array_type() == TRUE &&
	is_unconstrained_array_type() == FALSE ) 
      ||
      base_type->get_index_subtype()->is_enumeration_type() == TRUE ){
    
    vhdl_out << " ( ";
    
    index = 1 ;
    max_index = get_num_indexes();
    for (node = this; (index <= max_index); index++, node = 
	   dynamic_cast<IIRBase_ArrayTypeDefinition *>(node->get_element_subtype()) ){
      ASSERT(node->is_array_type() == TRUE );
      ASSERT(node->get_index_subtype() != NULL );
      ASSERT(node->get_element_subtype() != NULL );
      
      // The next assertion is invalid - what about
      // subtype foo1 is memory (1 to 10);
      //    ASSERT(node->get_index_subtype()->get_type_mark() != NULL);

      if (index > 1) {
	vhdl_out << ", ";
      }
      
      dynamic_cast<IIRBase_ScalarTypeDefinition *>
	(node->get_index_subtype())->publish_vhdl_index(vhdl_out);
    }
    
    vhdl_out << " ) ";
    
    if ( base_type->is_anonymous() == TRUE )  {
      vhdl_out << " of ";
      node->publish_vhdl(vhdl_out);
    }
  }
}

void
IIRBase_ArraySubtypeDefinition::publish_vhdl_subtype_decl(ostream &vhdl_out){
  publish_vhdl_decl(vhdl_out);
}
