
// Copyright (c) 1996-2003 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur
//          Timothy J. McBrayer
//          Krishnan Subramani
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_ArraySubtypeDefinition.hh"
#include "IIRScram_ScalarTypeDefinition.hh"
#include "IIRScram_FunctionDeclaration.hh"

IIRScram_ArraySubtypeDefinition::~IIRScram_ArraySubtypeDefinition() {}

void 
IIRScram_ArraySubtypeDefinition::_type_check(){
  if( _get_resolution_function() != NULL ){
    _get_resolution_function()->_type_check_resolution_function( this );
  }
  IIRScram_ArrayTypeDefinition::_type_check();
}

IIRScram *
IIRScram_ArraySubtypeDefinition::_clone(){
  IIRScram_ArraySubtypeDefinition *my_clone = new IIRScram_ArraySubtypeDefinition();
  IIRScram::_clone( my_clone );

  my_clone->set_resolution_function( get_resolution_function() );

  IIRScram_ArrayTypeDefinition::_clone( my_clone );

  return my_clone;
}

IIR_Boolean 
IIRScram_ArraySubtypeDefinition::is_locally_static(){
  IIR_Boolean retval = TRUE;

  if( is_unconstrained_array_type() == TRUE ){
    retval = FALSE;
  }
  else{
    IIRScram_ScalarTypeDefinition *current_index = _get_index_subtype();
    if( current_index->is_locally_static() == FALSE ){
      retval = FALSE;
    }
    IIRScram_TypeDefinition *current_element_type = _get_element_subtype();
    ASSERT( current_element_type != NULL );
    while( current_element_type->_is_iir_array_type_definition() == TRUE && 
	   current_element_type->is_element() == FALSE ){
      IIRScram_ArrayTypeDefinition *as_array_type = dynamic_cast<IIRScram_ArrayTypeDefinition *>(current_element_type);
      ASSERT( as_array_type->get_index_subtype() != NULL );
      if( as_array_type->_get_index_subtype()->is_locally_static() == FALSE ){
	retval = FALSE;
	break;
      }
      current_element_type = as_array_type->_get_element_subtype();
      ASSERT( current_element_type != NULL );
    }
  }

  return retval;
}


visitor_return_type *
IIRScram_ArraySubtypeDefinition::_accept_visitor( node_visitor *visitor,
						  visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ArraySubtypeDefinition(this, arg);
}

IIRScram_ArraySubtypeDefinition *
IIRScram_ArraySubtypeDefinition::get(IIRScram_ArrayTypeDefinition *bt,
                                     IIRScram_ScalarTypeDefinition *is,
                                     IIRScram_FunctionDeclaration *res_func) {
  IIRScram_ArraySubtypeDefinition *retval = new IIRScram_ArraySubtypeDefinition();
  retval->set_base_type(bt);
  retval->set_index_subtype(is);
  retval->set_resolution_function(res_func);
  return retval;
}
