
// Copyright (c) 1996-2000 The University of Cincinnati.  
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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_ArrayTypeDefinition.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_ElementDeclarationList.hh"
#include "IIRScram_ElementDeclaration.hh"
#include "IIRScram_OthersInitialization.hh"
#include "IIRScram_TextLiteral.hh"
#include "resolution_func.hh"
#include "error_func.hh"
#include "symbol_table.hh"
#include "savant.hh"


extern bool parse_error;

savant::set<IIRScram_TypeDefinition> *
IIRScram_OthersInitialization::_build_element_subtype_set( savant::set<IIRScram_TypeDefinition> *context_set ){
  savant::set<IIRScram_TypeDefinition> *retval = new savant::set<IIRScram_TypeDefinition>;
  IIRScram_TypeDefinition *current = context_set->getElement();
  while( current != NULL ){
    if( current->is_array_type() == TRUE ){
      retval->add( current->_get_element_subtype() );
    }
    else{
      // Then the context should be a subtype of an element's record.  We
      // have no way of checking that, so we have to assume it's right.
      retval->add( current );
    }
    current = context_set->getNextElement();
  }
  
  return retval;
}

IIRScram *
IIRScram_OthersInitialization::_semantic_transform( savant::set<IIRScram_TypeDefinition> *context_set ){
  savant::set<IIRScram_TypeDefinition> *element_types = _build_element_subtype_set( context_set );
  set_expression( _get_expression()->_semantic_transform( element_types ) );
  delete element_types;

  return this;
}

void 
IIRScram_OthersInitialization::_type_check( savant::set<IIRScram_TypeDefinition> *context_set ){
  savant::set<IIRScram_TypeDefinition> *element_types = _build_element_subtype_set( context_set );
  _get_expression()->_type_check( element_types );
  delete element_types;
}

IIRScram *
IIRScram_OthersInitialization::_rval_to_decl( IIRScram_TypeDefinition *new_type ){
  if( new_type->is_array_type() == TRUE ){
    IIRScram_TypeDefinition *element_type = new_type->_get_element_subtype();
    // Everything else should have happened in type check.
    set_expression( _get_expression()->_rval_to_decl( element_type ) );
    set_subtype( element_type );
  }
  else{
    set_expression( _get_expression()->_rval_to_decl( new_type ) );
    set_subtype( new_type );
  }

  ASSERT( is_resolved() == TRUE || parse_error == true );
  return this;
}


savant::set<IIRScram_TypeDefinition> *
IIRScram_OthersInitialization::_get_rval_set( constraint_functor * ){
  savant::set<IIRScram_TypeDefinition> *retval = NULL;

  savant::set<IIRScram_ArrayTypeDefinition> *array_types = _get_symbol_table()->get_in_scope_array_types()->convert_set<IIRScram_ArrayTypeDefinition>();
  
  savant::set<IIRScram_TypeDefinition> *actual_rvals = _get_expression()->_get_rval_set();
  if( actual_rvals == NULL ){
    return NULL;
  }

  IIRScram_TypeDefinition *current_array_type; 
  current_array_type = array_types->getElement();
  while( current_array_type != NULL ){
   if( current_array_type->_get_element_subtype() != NULL ){
   }

    IIRScram_TypeDefinition *actual_type = actual_rvals->getElement();

    bool one_matched = false;
    while( actual_type != NULL ){
      if( actual_type->is_compatible( current_array_type->_get_element_subtype() ) != NULL ){
	one_matched = true;
      }
      actual_type = actual_rvals->getNextElement();
    }

    if( one_matched == true ){
      if( retval == NULL ){
	retval = new savant::set<IIRScram_TypeDefinition>;
      }
      retval->add( current_array_type );
    }
	
    current_array_type = array_types->getNextElement();
  }


  return retval;
}

visitor_return_type *
IIRScram_OthersInitialization::_accept_visitor( node_visitor *visitor, 
						visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_OthersInitialization(this, arg);
}

IIRScram *
IIRScram_OthersInitialization::_get_expression() {
  return dynamic_cast<IIRScram *>(get_expression());
}
