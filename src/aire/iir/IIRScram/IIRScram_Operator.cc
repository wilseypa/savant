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

//---------------------------------------------------------------------------

#include "IIRScram_AssociationElement.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_DyadicOperator.hh"
#include "IIRScram_EnumerationTypeDefinition.hh"
#include "IIRScram_FunctionCall.hh"
#include "IIRScram_FunctionDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_MonadicOperator.hh"
#include "IIRScram_Operator.hh"

#include "error_func.hh"
#include "resolution_func.hh"
#include "symbol_table.hh"

using savant::set;

IIR_Boolean 
IIRScram_Operator::_type_check_user_declared( set<IIRScram_TypeDefinition> *context_set ){
  IIR_Boolean retval = FALSE;

  set<IIRScram_Declaration> *function_declarations = _symbol_lookup();
  if( function_declarations == NULL ){
    return FALSE;
  }

  // Build an argument list for use with the function we have for
  // resolution.
  IIRScram_AssociationList *argument_list = _build_argument_list();
  
  IIRScram_Declaration *current_declaration = function_declarations->getElement();
  while( current_declaration != NULL ){

    if( current_declaration->_num_required_args() != argument_list->size() ){
      function_declarations->remove( current_declaration );
    }

    current_declaration = function_declarations->getNextElement();
  }

  if( function_declarations != NULL ){
    resolve_subprogram_decls( function_declarations, 
                              argument_list,
			      context_set);
    
    // We only need to complain if it's ambiguous.
    switch( function_declarations->size() ){
    case 0:{
      retval = FALSE;
      break;
    }
    case 1:{
      retval = TRUE;

      ASSERT( function_declarations->getElement() != NULL );
      ASSERT( function_declarations->getElement()->get_kind() == IIR_FUNCTION_DECLARATION );

      IIRScram_FunctionDeclaration *my_decl =
        dynamic_cast<IIRScram_FunctionDeclaration *>(function_declarations->getElement());

      set_implementation( my_decl );
      _type_check_operands( );

      break;
    }
    default:{
      // This will guarantee that other type check methods aren't applied
      // to this node.
      retval = TRUE;
      report_ambiguous_error( this, function_declarations->convert_set<IIR_Declaration>());
    }
    }
    
  }
  delete argument_list;
  delete function_declarations;

  return retval;
}

void 
IIRScram_Operator::_type_check( set<IIRScram_TypeDefinition> * ){
  // At the moment, don't to anything at all.  We did it all in semantic_transform.
}


IIRScram *
IIRScram_Operator::_rval_to_decl( IIRScram_TypeDefinition *my_rval ){
  
  set_subtype( my_rval );

  delete my_rvals;
  my_rvals = 0;

  ASSERT( is_resolved() == TRUE );

  return this;
}


set<IIRScram_Declaration> *
IIRScram_Operator::_symbol_lookup(){
  set<IIRScram_Declaration> *retval = NULL;
  
  IIR_Identifier *to_lookup =
    IIRScram_Identifier::get(_get_function_name(), get_design_file()->get_class_factory());

  // Don't delete decls1, it belongs to the symbol table.
  set<IIR_Declaration> *decls1 = _get_symbol_table()->find_set( to_lookup );
  retval = decls1->convert_set<IIRScram_Declaration>();
  to_lookup->release();

  return retval;
}

set<IIRScram_TypeDefinition> *
IIRScram_Operator::_get_rval_set( constraint_functor * ){
  set<IIRScram_TypeDefinition> *retval = NULL;

  // We're caching rval sets here, for performance.
  if( has_been_type_checked == FALSE ){
    // First look for the user overloaded operators.
    retval = _get_user_overloaded_rvals();
    
    if( retval != NULL ){
      my_rvals = new set<IIRScram_TypeDefinition>( *retval );
    }
    
    has_been_type_checked = TRUE;
  }
  else{
    if( my_rvals != 0 ){
      retval = new set<IIRScram_TypeDefinition>( *my_rvals );
    }
    else if ( _get_subtype() != 0 ){
      // This is a bit of a kludge - something that shouldn't happen.  But
      // we do delete my_rvals after we set "my_rval", so it potentially
      // _could_ happen.
      retval = new set<IIRScram_TypeDefinition>( _get_subtype() );
    }
  }

  return retval;
}

set<IIRScram_TypeDefinition> *
IIRScram_Operator::_get_user_overloaded_rvals(){
  set<IIRScram_TypeDefinition> *retval = NULL;
  set<IIRScram_Declaration> *my_decls = _symbol_lookup();  

  if( my_decls == NULL ){
    return NULL;
  }
  else{
    int num_arguments = _get_num_args();
    IIRScram_Declaration *current_decl = my_decls->getElement();
    while( current_decl != NULL ){
      if( current_decl->_num_required_args() != num_arguments ){
	my_decls->remove( current_decl );
      }
      else{
	ASSERT( current_decl->get_kind() == IIR_FUNCTION_DECLARATION );
	IIRScram_FunctionDeclaration *as_function = 
          dynamic_cast<IIRScram_FunctionDeclaration *>(current_decl);
	IIRScram_AssociationList *arg_list = _build_argument_list();
	IIR_Boolean valid_call = 
	  arg_list->_check_valid_arguments( as_function->_get_interface_declarations(), 
                                            NULL);
	if( valid_call == FALSE ){
	  my_decls->remove( current_decl );
	}
	arg_list->_destroy_list();
	delete arg_list;
      }

      current_decl = my_decls->getNextElement();
    }    

    retval = decl_set_to_typedef_set( my_decls );
    delete my_decls;
  }

  return retval;
}

IIRScram *
IIRScram_Operator::_semantic_transform( set<IIRScram_TypeDefinition> *context_set ){
  IIRScram *retval = this;

  if( _type_check_user_declared( context_set ) == TRUE ){
    ASSERT( _get_implementation() != NULL );
    ASSERT( _get_implementation()->is_resolved() == TRUE );
    
    // Only transform this to a function call if the user _explicitly_
    // declared this operator.
    if( _get_implementation()->is_implicit_declaration() == FALSE ){
      IIRScram_FunctionCall *function_call = new IIRScram_FunctionCall();
      copy_location( this, function_call );
      function_call->set_implementation( get_implementation() );
      function_call->set_parameter_association_list( _build_argument_list() );
      function_call->_get_parameter_association_list()->_resolve_and_order( _get_implementation()->_get_interface_declarations(), 
									    NULL,
									    this );
      
#ifdef DEVELOPER_ASSERTIONS
      IIRScram_AssociationElement *current =  
        dynamic_cast<IIRScram_AssociationElement *>(function_call->get_parameter_association_list()->first());
      while( current != NULL ){
	ASSERT( current->is_resolved() == TRUE );
	current =  
          dynamic_cast<IIRScram_AssociationElement *>(function_call->get_parameter_association_list()->successor( current ));
      }
#endif

      retval = function_call;
    }
    // else retval = this already.
  }

  return retval;
}

IIRScram_SubprogramDeclaration *
IIRScram_Operator::_get_implementation() {
  return dynamic_cast<IIRScram_SubprogramDeclaration *>(get_implementation());
}
