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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu

//---------------------------------------------------------------------------
#include "IIRScram_AccessTypeDefinition.hh"
#include "IIRScram_ArrayTypeDefinition.hh"
#include "IIRScram_AssociationElementByExpression.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_ConcurrentStatement.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_FunctionCall.hh"
#include "IIRScram_IndexedName.hh"
#include "IIRScram_ScalarTypeDefinition.hh"
#include "IIRScram_SignalDeclaration.hh"
#include "IIRScram_SliceName.hh"
#include "IIRScram_SubprogramDeclaration.hh"
#include "IIRScram_TypeConversion.hh"
#include "IIRScram_TypeDeclaration.hh"

#include "error_func.hh"
#include "resolution_func.hh"
#include "set.hh"

#include <sstream>
using std::ostringstream;

using std::cerr;
extern bool parse_error;

void 
IIRScram_IndexedName::_set_my_rval( IIRScram_TypeDefinition *new_rval ){
  set_subtype(new_rval);
  if( new_rval != 0 ){
    delete _my_rval_set;
    _my_rval_set = 0;
  }
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_IndexedName::_my_type_given_array_prefix_type( IIRScram_TypeDefinition *prefix_rval ){
  savant::set<IIRScram_TypeDefinition> *retval = new savant::set<IIRScram_TypeDefinition>;

  // This function should only be called on array types - that's it's point..
  ASSERT( prefix_rval->is_array_type() == TRUE );
  if( _get_suffix()->_is_iir_type_definition() == TRUE && _get_suffix()->is_scalar_type() == TRUE ){
    // This is a slice.
    retval->add(prefix_rval);
    if( prefix_rval->is_access_type() == TRUE ){
      retval->add( (dynamic_cast<IIRScram_AccessTypeDefinition *>(prefix_rval))->_get_designated_type() );
    }
  }
  else if ( _get_suffix()->_is_attribute() == TRUE ){
    if( _get_suffix()->get_kind() == IIR_RANGE_ATTRIBUTE ||
	_get_suffix()->get_kind() == IIR_REVERSE_RANGE_ATTRIBUTE){
      // Slice
      retval->add(prefix_rval);
    }
    else{
      // Not slice
      retval->add( prefix_rval->_get_type_of_element( get_num_indexes() ) );
    }
  }
  else if ( _get_suffix()->is_name() == TRUE ){
    savant::set<IIRScram_Declaration> *suffix_decls = _get_suffix()->_symbol_lookup();
    if( suffix_decls != NULL ){
      IIRScram_Declaration *current_decl = suffix_decls->getElement();
      while( current_decl != NULL ){
	if( current_decl->is_type() == FALSE ||
	    current_decl->is_scalar_type() == FALSE ){
	  suffix_decls->remove( current_decl );
	}
	current_decl = suffix_decls->getNextElement();
      }

      switch( suffix_decls->size() ){
      case 0:{
	// It's not a slice.
	retval->add( prefix_rval->_get_type_of_element( get_num_indexes() ) );
	break;
      }
      case 1:{
	// It's a slice.
	retval->add( prefix_rval );
	break;
      }
      default:{
	// Can't tell.  This should be able to return both.
	report_ambiguous_error( this, suffix_decls->convert_set<IIR_Declaration>() );
	break;
      }
      }
    }
    else{
      // So, we have an array valued prefix, and the suffix is a name,
      // and we can't look it up.  So, the suffix is another indexed name.
      // If the suffix is a discrete range (if it's a slice or a constrained
      // subtype indication like integer(1 to 7), this is a slice.  If it's
      // something else, this is an array access.  So, we're going to punt
      // and return both possiblilities.
      retval->add( prefix_rval );
      retval->add( prefix_rval->_get_type_of_element( prefix_rval->get_num_indexes() ) );
    }
    delete suffix_decls;
  }
  else{
    // It's an array access
    retval->add( prefix_rval->_get_type_of_element( get_num_indexes() ) );
  }
  
  if( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }
  
  return retval;
}

//This works only for single dimension arrays and indexed names for single
//dimension arrays
IIRScram_TypeDefinition*
IIRScram_IndexedName::_get_name_type(){

  IIRScram_Declaration* decl = _get_prefix_declaration();
  IIRScram_TypeDefinition* type_def = decl->_get_subtype();
  IIRScram_TypeDefinition* element_type = NULL;

  // This case is not handled yet.
  ASSERT(get_suffix()->get_kind() != IIR_ASSOCIATION_LIST);

  if(type_def->is_array_type() == TRUE) {
    IIRScram_ArrayTypeDefinition* array_type_def = dynamic_cast<IIRScram_ArrayTypeDefinition*>( type_def);
    element_type = array_type_def->_get_element_subtype();
  }

  if(element_type != NULL) {
    return element_type;
  }
  else {
    return NULL;
  }
}

savant::set<IIRScram_Declaration> *
IIRScram_IndexedName::_symbol_lookup(){
  return NULL;
}


savant::set<IIRScram_Declaration> *
IIRScram_IndexedName::_symbol_lookup( savant::set<IIRScram_Declaration> *look_in ){
  savant::set<IIRScram_Declaration> *retval = new savant::set<IIRScram_Declaration>;

  IIRScram_Declaration *current_decl;

  current_decl = look_in->getElement();
  while( current_decl != NULL ){
    if( current_decl->find_declarations( this ) != NULL ){
      retval->add( current_decl->find_declarations( this)->convert_set<IIRScram_Declaration>() );
    }
    current_decl = look_in->getNextElement();
  }

  if( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }

  return retval;
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_IndexedName::_return_type_given_prefix_declaration( IIRScram_Declaration *prefix_decl ){
  savant::set<IIRScram_TypeDefinition> *retval = new savant::set<IIRScram_TypeDefinition>;
  
  IIRScram_TypeDefinition *current_rval = prefix_decl->_get_subtype();

  switch( prefix_decl->get_declaration_type() ){
  case IIR_Declaration::ALIAS:
  case IIR_Declaration::ATTRIBUTE:
  case IIR_Declaration::ELEMENT:
  case IIR_Declaration::VARIABLE:
  case IIR_Declaration::SHARED_VARIABLE:
  case IIR_Declaration::SIGNAL:
  case IIR_Declaration::INTERFACE:
  case IIR_Declaration::CONSTANT:
  case IIR_Declaration::INTERFACE_VARIABLE:
  case IIR_Declaration::INTERFACE_SIGNAL:
  case IIR_Declaration::INTERFACE_CONSTANT:{
    if( current_rval->is_array_type() == TRUE ){
      savant::set<IIRScram_TypeDefinition> *type_set = _my_type_given_array_prefix_type( current_rval );
      if( type_set != NULL ){
	retval->add( type_set );
	delete type_set;
      }
    }
    break;
  }

  case IIR_Declaration::PROCEDURE:{
    int num_args = 0;
    if( _get_suffix()->get_kind() == IIR_ASSOCIATION_LIST ){
      num_args = (dynamic_cast<IIRScram_AssociationList *>(_get_suffix()))->size();
    }
    else{
      num_args = 1;
    }

    if( prefix_decl->_num_required_args() <= num_args ){
      retval->add( current_rval );
    }
	  
    break;
  }

  case IIR_Declaration::FUNCTION:{
    IIRScram_SubprogramDeclaration *as_subprogram = dynamic_cast<IIRScram_SubprogramDeclaration *>(prefix_decl);
    // Functions are strange - they can return arrays, which can
    // be indexed.  so I could have x := foo( argument )( array_index );
    // They can return non-arrays, but take parameters-
    // x := foo( argument ), or they can take no parameters,
    // but return an array!  x := foo( array_index )
    //     if( current_rval->is_array_type() == TRUE ){
    //     if( _get_prefix()->get_kind() == IIR_FUNCTION_CALL ){ 
    //       // then we definitely need to treat this as an array access...
    //       int index_num;
    //       if( get_suffix()->get_kind() == IIR_ASSOCIATION_LIST ){
    // 	index_num = (dynamic_cast<IIRScram_AssociationList *>(get_suffix())->size();
    //       }
    //       else{
    // 	index_num = 1;
    //       }
    //       retval->add( current_rval->_get_type_of_element( index_num ) );	  
    //     }
    //     else{
    // Let's try to determine the exact function being called.
    IIR_Boolean add_rval = FALSE;
    if( _get_suffix()->get_kind() == IIR_ASSOCIATION_LIST ){
      IIRScram_AssociationList *as_list = dynamic_cast<IIRScram_AssociationList *>(_get_suffix());
      add_rval = as_list->_check_valid_arguments( as_subprogram->_get_interface_declarations(), NULL);
    }
    else{
      IIRScram_AssociationList *new_list = new IIRScram_AssociationList();
      //      copy_location( this, new_list );
      ASSERT( dynamic_cast<IIRScram_AssociationElement *>(_get_suffix()) == NULL );
      IIRScram_AssociationElementByExpression *new_element;
      
      new_element = new IIRScram_AssociationElementByExpression();
      copy_location( _get_suffix(), new_element );
      new_element->set_actual( _get_suffix() );
      
      new_list->append( new_element );
      add_rval = 
	new_list->_check_valid_arguments( as_subprogram->_get_interface_declarations(), NULL);
      delete new_list;
      
      delete new_element;
    }

    if( add_rval == TRUE ){
      retval->add( prefix_decl->_get_subtype() );
    }
    break;
  }

  case IIR_Declaration::TYPE:
  case IIR_Declaration::SUBTYPE:{
    // There are two cases, treated the same way.  subtyping,
    // subtype foo is bar( 1 to 3 ), or conversion functions.
    // x := foo( .34 );  In either case, the type is returned -
    // it's not an array access.
    retval->add( current_rval );
    break;
  }

  default:
    // Nothing else can be accessed that way...
    break;
  }

  if( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }

  return retval;
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_IndexedName::_get_rval_set(constraint_functor *functor){
  savant::set<IIRScram_TypeDefinition> *retval = NULL;
  
  if( _get_subtype() != NULL ){
    // We already know the type.
    retval = new savant::set<IIRScram_TypeDefinition>( _get_subtype() );
  }
  else if( _have_rval_set == TRUE ){
    // We've already calculated the possibilities once, use that.
    if( _my_rval_set != NULL ){
      retval = new savant::set<IIRScram_TypeDefinition>(*_my_rval_set);
    }
  }
  else{
    // We need to figure out what this might be.
    retval = new savant::set<IIRScram_TypeDefinition>;

    // If the parser encounters something like foo(1)(2)(3), it will build:
    //                          *
    //                        *   3
    //                      *   2
    //                    foo 1
    
    // (Each * is an indexed name)
    
    ASSERT( _get_suffix() != NULL );
    ASSERT( _get_prefix() != NULL );
    
    // If this indexed name is already resolved, we shouldn't need to do anything...
    if( is_resolved() == TRUE ){
      retval->add( _get_subtype() );
      return retval;
    }
    
    savant::set<IIRScram_Declaration> *prefix_decls = _get_prefix()->_symbol_lookup();
    if( prefix_decls != NULL ){
      // We have the declaration to figure it out with...
      IIRScram_Declaration *current_decl = prefix_decls->getElement();
      while( current_decl != NULL ){
	savant::set<IIRScram_TypeDefinition> *return_type = 
          _return_type_given_prefix_declaration( current_decl );
	if( return_type != NULL ){
	  retval->add( return_type );
	  delete return_type;
	}
	current_decl = prefix_decls->getNextElement();
      }
    }
    else{
      // We can only go on the type of the prefix then.
      savant::set<IIRScram_TypeDefinition> *prefix_types = _get_prefix()->_get_rval_set(functor);
      if( prefix_types == NULL ){
	return NULL;
      }
      IIRScram_TypeDefinition *current_prefix_rval = prefix_types->getElement();
      while( current_prefix_rval != NULL ){
	if( current_prefix_rval->is_array_type() == TRUE ){
	  // Then it's an array access or a slice...  It's not a function call, 
	  savant::set<IIRScram_TypeDefinition> *tmp = _my_type_given_array_prefix_type( current_prefix_rval );
	  retval->add( tmp );
	  delete tmp;
	}
	else{
	  // Then it must be a function call or something...
	  retval->add(  current_prefix_rval );
	}
	current_prefix_rval = prefix_types->getNextElement();
      }
      delete prefix_types;
    }
    
    delete prefix_decls;
    
    if( retval->size() == 0 ){
      delete retval;
      retval = NULL;
    }
    else{
      _my_rval_set = new savant::set<IIRScram_TypeDefinition>(*retval);
    }

    _have_rval_set = TRUE;
  }
  

  return retval;
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_IndexedName::_get_rval_set( savant::set<IIRScram_Declaration> *look_in,
				     constraint_functor * ){
  savant::set<IIRScram_TypeDefinition> *retval = new savant::set<IIRScram_TypeDefinition>;
  /* This is the case where we have something like:
     
            foo.bar( 1 to 3 );

                 S
                / \
              foo  I
                  / \
	        bar  1 to 3
                   
    We're passed the possible declarations of foo... */

  ASSERT( _get_prefix()->is_name() == TRUE );
  IIRScram_Declaration *current_decl = look_in->getElement();
  while( current_decl != NULL ){
    savant::set<IIRScram_Declaration> *prefix_decls = NULL;
    
    if (current_decl->find_declarations( dynamic_cast<IIRScram_Name *>(_get_prefix()) ) != NULL) {
      prefix_decls = current_decl->find_declarations( dynamic_cast<IIRScram_Name *>(_get_prefix()) )->convert_set<IIRScram_Declaration>();
    }
    if( prefix_decls != NULL ){
      IIRScram_Declaration *current_prefix = prefix_decls->getElement();
      while( current_prefix != NULL ){
	savant::set<IIRScram_TypeDefinition> *return_type;
	return_type = _return_type_given_prefix_declaration( current_prefix );
	if( return_type != NULL ){
	  retval->add( return_type );
	}
	current_prefix = prefix_decls->getNextElement();
      }
      delete prefix_decls;
    }
    current_decl = look_in->getNextElement();
  }
  
  if( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }

  return retval;
}

IIR_Boolean 
IIRScram_IndexedName::_is_readable(){
  ASSERT( is_resolved() == TRUE );

  return _get_prefix()->_is_readable();
}

IIR_Boolean 
IIRScram_IndexedName::_is_writable(){
  ASSERT( is_resolved() == TRUE );

  return _get_prefix()->_is_writable();
}


IIR_Boolean 
IIRScram_IndexedName::_is_array_access(){
  // Note - not using accessor function _get_my_rval on purpose.  That function
  // asserts that this indexed name is resolved, and THIS function might get called
  // as part of the resolution process...

  ASSERT( _get_subtype() != NULL );
  if( (_get_suffix()->is_scalar_type() == TRUE && 
       _get_suffix()->_is_iir_type_definition() == TRUE) || 
      (_get_suffix()->is_scalar_type() == TRUE && _get_suffix()->is_type() == TRUE) ){
    return FALSE;
  }
  else{
    return TRUE;
  }
}

IIRScram *
IIRScram_IndexedName::_process_as_function_call( savant::set<IIRScram_TypeDefinition> *context_set ){
  IIRScram_FunctionCall *retval = NULL;
  
  constraint_functor *functor = new is_subprogram_functor;
  savant::set<IIRScram_Declaration> *func_decls = _get_prefix()->_symbol_lookup(functor);
  delete functor;

  if( func_decls != NULL ){
    if( func_decls->size() == 0 ){
      return retval;
    }

    IIRScram_AssociationList *arg_list = NULL;

    IIR_Boolean need_to_delete;
    if( _get_suffix()->get_kind() == IIR_ASSOCIATION_LIST ){
      arg_list = dynamic_cast<IIRScram_AssociationList *>(_get_suffix() );
      need_to_delete = FALSE;
    }
    else{
      arg_list = new IIRScram_AssociationList();
      copy_location( this, arg_list );
      need_to_delete = TRUE;
      if( _get_suffix()->_is_association() == TRUE ){
	arg_list->append( dynamic_cast<IIRScram_AssociationElement *>(_get_suffix() ));
      }
      else{
	IIRScram_AssociationElementByExpression *temp_assoc = new IIRScram_AssociationElementByExpression();
        copy_location( this, temp_assoc );
	temp_assoc->set_actual( _get_suffix() );
	arg_list->append( temp_assoc );
      }
    }

    // This call returns func_decls with ONLY the matching function calls
    // in it.
    resolve_subprogram_decls( func_decls, arg_list, context_set );

    switch ( func_decls->size() ){
    case 0:{
      retval = NULL;
      break;
    }
    case 1:{
      // Then we have the EXACT declaration we need as the sole element of 
      // our set...
      IIRScram_SubprogramDeclaration *subprogram_decl = 
	dynamic_cast<IIRScram_SubprogramDeclaration *>(func_decls->getElement()); 

      // Generate a function call
      retval = new IIRScram_FunctionCall();
      copy_location( this, retval );

      ASSERT( subprogram_decl != NULL );
      ASSERT( subprogram_decl->is_subprogram() == TRUE );

      retval->set_implementation( subprogram_decl );
      
      arg_list->_resolve_and_order( subprogram_decl->_get_interface_declarations(), NULL, this);
      
      retval->set_parameter_association_list(arg_list);
      need_to_delete = false;

      break;
    }
    default:{
      report_ambiguous_error( _get_prefix(), func_decls->convert_set<IIR_Declaration>() );
      retval = NULL;
      break;
    }
    }
    
    if( need_to_delete == TRUE ){
      delete arg_list;
    }
  }

  return retval;
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_IndexedName::_get_array_prefixes(){
  
  savant::set<IIRScram_TypeDefinition> *prefix_rvals = _get_prefix()->_get_rval_set();
  if( prefix_rvals == NULL ){
    return NULL;
  }

  // If there isn't a list of indexes, then there is only one...
  int num_indexes = 1;
  if( _get_suffix()->get_kind() == IIR_ASSOCIATION_LIST ){
    IIRScram_AssociationList *index_list = dynamic_cast<IIRScram_AssociationList *>(_get_suffix());
    num_indexes = index_list->size();
  }
  
  IIRScram_TypeDefinition *current_prefix_rval = prefix_rvals->getElement();
  while( current_prefix_rval != NULL ){
    if( current_prefix_rval->is_array_type() == FALSE || 
	current_prefix_rval->get_num_indexes() < num_indexes ){
      prefix_rvals->remove( current_prefix_rval );
    }
    current_prefix_rval = prefix_rvals->getNextElement();
  }

  if( prefix_rvals->size() == 0 ){
    delete prefix_rvals;
    prefix_rvals = NULL;
  }

  return prefix_rvals;
}

IIRScram_SliceName *
IIRScram_IndexedName::_build_slice( IIRScram_TypeDefinition *my_prefix_type ){

  ASSERT( my_prefix_type->is_array_type() == TRUE );
  ASSERT( _get_suffix() != NULL );

  IIRScram_ScalarTypeDefinition *constraint = NULL;

  if( _get_suffix()->is_scalar_type_definition() == TRUE ){
    constraint = dynamic_cast<IIRScram_ScalarTypeDefinition *>(_get_suffix());
  }
  else if( _get_suffix()->_is_attribute() == TRUE ){
    ASSERT( _get_suffix()->get_kind() == IIR_RANGE_ATTRIBUTE ||
	    _get_suffix()->get_kind() == IIR_REVERSE_RANGE_ATTRIBUTE );
    ASSERT( _get_suffix()->_get_subtype() != NULL );
    ASSERT( _get_suffix()->_get_subtype()->is_scalar_type_definition() == TRUE );
    constraint = dynamic_cast<IIRScram_ScalarTypeDefinition *>(_get_suffix()->_get_subtype());
    
    set_suffix( _get_suffix()->_semantic_transform( constraint ) );
    _get_suffix()->_type_check( constraint );
    set_suffix( _get_suffix()->_rval_to_decl( constraint) );   
  }  
  else if ( _get_suffix()->get_kind() == IIR_TYPE_DECLARATION || 
	    _get_suffix()->get_kind() == IIR_SUBTYPE_DECLARATION ){
    IIRScram_TypeDefinition *temp_constraint =  (dynamic_cast<IIRScram_Declaration *>(_get_suffix())->_get_subtype() );
    ASSERT( temp_constraint->is_scalar_type_definition() == TRUE );
    constraint = dynamic_cast<IIRScram_ScalarTypeDefinition *>(temp_constraint);
  }
  else{
    ostringstream err;
    err << "Internal error in IIRScram_IndexedName::_build_slice - don't know what to do"
	<< " with suffix of type " << *_get_suffix()->get_kind_text();
    report_error( this, err.str() );
    abort();
  }

  IIRScram_TypeDefinition *my_type = my_prefix_type->_construct_new_subtype( NULL, constraint);
  my_type->set_type_mark( my_prefix_type->_get_type_mark() );
  my_type->set_declaration( my_prefix_type->_get_declaration() );
  my_type->set_element_subtype( my_prefix_type->_get_element_subtype() );

  IIRScram_SliceName *retval = NULL;
  
  retval = new IIRScram_SliceName();
  copy_location( this, retval );

  set_prefix( _get_prefix()->_semantic_transform( my_prefix_type ) );
  _get_prefix()->_type_check( my_prefix_type );
  set_prefix( _get_prefix()->_rval_to_decl( my_prefix_type ) );    
  
  retval->set_prefix( _get_prefix() );
  retval->set_suffix( _get_suffix() );

  if( my_type->is_access_type() == TRUE ){
    retval->set_subtype( (dynamic_cast<IIRScram_AccessTypeDefinition *>(my_type))->_get_designated_type() );    
  }
  else{
    retval->set_subtype( my_type );
  }

  return retval;
}

IIRScram *
IIRScram_IndexedName::_process_as_slice( savant::set<IIRScram_TypeDefinition> *context_set ){
  IIRScram_SliceName            *retval = NULL;
  IIRScram_TypeDefinition       *my_prefix_type = NULL;
  savant::set<IIRScram_TypeDefinition>  temp_context( *context_set );
  
  // Check for array valued prefixes...
  savant::set<IIRScram_TypeDefinition> *prefix_rvals = _get_array_prefixes();
  IIRScram_TypeDefinition *current_prefix_type = NULL;
  if( prefix_rvals == NULL ){
    goto finish;
  }

  if( get_num_indexes() != 1 ){
    goto finish;
  }

  current_prefix_type = prefix_rvals->getElement();
  while( current_prefix_type != NULL ){
    bool one_matched = FALSE;
    IIRScram_TypeDefinition *to_consider;
    if( current_prefix_type->is_access_type() == TRUE ){
      to_consider = (dynamic_cast<IIRScram_AccessTypeDefinition *>(current_prefix_type))->_get_designated_type();
    }
    else{
      to_consider = current_prefix_type;
    }

    IIRScram_TypeDefinition *current_context_type = dynamic_cast<IIRScram_TypeDefinition *>(context_set->getElement());
    while( current_context_type != NULL ){
      if( to_consider->is_compatible( current_context_type) != NULL ){
	one_matched = TRUE;
	break;
      }
      current_context_type = dynamic_cast<IIRScram_TypeDefinition *>(context_set->getNextElement());
    }

    if( one_matched == FALSE ){
      prefix_rvals->remove( current_prefix_type );
    }
    current_prefix_type = prefix_rvals->getNextElement();
  }

  switch( prefix_rvals->size() ){
  case 0:{
    goto finish;
  }
  case 1:{
    my_prefix_type = prefix_rvals->getElement();
    break;
  }
  default:{
    report_ambiguous_error( _get_prefix(), prefix_rvals->convert_set<IIR_Declaration>() );
  }
  }

  // Check for a suffix that would be possible for this to be a slice.
  if( _get_suffix()->is_scalar_type_definition() == TRUE ||
      _get_suffix()->_is_attribute() == TRUE ){
    retval = _build_slice( my_prefix_type );
  }
  else if ( _get_suffix()->is_name() == TRUE ){
    savant::set<IIRScram_Declaration> *suffix_decls = _get_suffix()->_symbol_lookup();
    if( suffix_decls == NULL ){
      goto finish;
    }
    else{
      IIRScram_Declaration *current_decl = suffix_decls->getElement();
      while( current_decl != NULL ){
	if( current_decl->is_type() == FALSE ||
	    current_decl->is_scalar_type() == FALSE ){
	  suffix_decls->remove( current_decl );
	}
	current_decl = suffix_decls->getNextElement();
      }

      switch( suffix_decls->size() ){
      case 0:{
	goto finish;
      }
      case 1:{
	IIRScram_TypeDefinition *suffix_type = suffix_decls->getElement()->_get_subtype();

	set_suffix( _get_suffix()->_semantic_transform( suffix_type ) );
	_get_suffix()->_type_check( suffix_type );
	set_suffix( _get_suffix()->_rval_to_decl( suffix_type ) );

	retval = _build_slice( my_prefix_type );
	break;
      }
      default:{
	report_ambiguous_error( this, suffix_decls->convert_set<IIR_Declaration>() );
	break;
      }
      }
      delete suffix_decls;
    }
  }
  else{
    retval = NULL;
  }

 finish:
  delete prefix_rvals;
  return retval;
}


IIRScram *
IIRScram_IndexedName::_process_as_array( savant::set<IIRScram_TypeDefinition> *context_set ){
  IIRScram              *retval = NULL;

  savant::set<IIRScram_TypeDefinition> *prefix_rvals = _get_array_prefixes();
  if( prefix_rvals == NULL ){
    return NULL;
  }

  // Now, we need to match up possible array types and our context set.
  IIRScram_TypeDefinition *current_array_type = prefix_rvals->getElement();
  while( current_array_type != NULL ){
    IIR_Boolean one_matched = FALSE;
    IIRScram_TypeDefinition *current_context_type = context_set->getElement();
    while( current_context_type != NULL ){
      if( current_array_type->_get_type_of_element( get_num_indexes() )->is_compatible( current_context_type ) != NULL ){
	one_matched = TRUE;
	break;
      }
      current_context_type = context_set->getNextElement();
    }
    
    if( one_matched == FALSE ){
      prefix_rvals->remove( current_array_type );
    }

    current_array_type = prefix_rvals->getNextElement();
  }

  // We should check the type of each index here.  Not doing this yet, which
  // will cause an assertion to fail on bad code rather than generating an
  // appropriate error message.  I will fix this in the near future...
  
  switch( prefix_rvals->size() ){
  case 0:{
      
    retval = NULL;
    break;
  }
    
  case 1:{
    IIRScram_TypeDefinition *my_prefix_type = prefix_rvals->getElement();
    int prefix_num_indexes = my_prefix_type->get_num_indexes();
    ASSERT( prefix_num_indexes == get_num_indexes() );
    
    int i;

    set_prefix( _get_prefix()->_semantic_transform( my_prefix_type ) );
    _get_prefix()->_type_check( my_prefix_type );
    set_prefix( _get_prefix()->_rval_to_decl( my_prefix_type ) );    
    
    IIRScram_TypeDefinition *index_type;
    IIRScram_TypeDefinition *current_element_type = my_prefix_type;
    if( get_num_indexes() == 1 ){
      index_type = current_element_type->_get_resolved_index_subtype( );
      set_suffix( _get_suffix( )->_semantic_transform( index_type ) );
      _get_suffix()->_type_check( index_type );
      set_suffix( _get_suffix( )->_rval_to_decl( index_type ) );            
    }
    else{
      for( i = 0 ; i < get_num_indexes(); i++ ){
	index_type = current_element_type->_get_resolved_index_subtype( );
	ASSERT( index_type->is_element() == FALSE );
	set_index( i + 1, _get_index( i + 1 )->_semantic_transform( index_type ) );
	_get_index( i + 1 )->_type_check( index_type );
	set_index( i + 1, _get_index( i + 1 )->_rval_to_decl( index_type ) );      
	current_element_type = current_element_type->_get_element_subtype();
      }
    }
    
    _set_my_rval( my_prefix_type->_get_type_of_element( get_num_indexes() ) );

    retval = this;

    break;
  }
  
  default:{
    report_ambiguous_error( _get_prefix(), prefix_rvals->convert_set<IIR_Declaration>() );
    retval = NULL;
  }
  }

  delete prefix_rvals;

  return retval;
}

IIRScram *
IIRScram_IndexedName::_process_as_type_conversion( savant::set<IIRScram_TypeDefinition> *context_set ){
  IIRScram              *retval = NULL;

  if( get_num_indexes() != 1 ){
    return NULL;
  }

  // Eliminate all non-type (or subtype) declarations from the possiblilites.
  constraint_functor *functor = new is_type_functor;
  savant::set<IIRScram_Declaration> *my_decls = _get_prefix()->_symbol_lookup(functor);
  delete functor;
  
  if( my_decls != NULL ){
    if( my_decls->size() == 0 ){
      delete my_decls;
      return NULL;
    }

    savant::set<IIRScram_TypeDefinition> context_copy( *context_set );
    reconcile_sets( my_decls, &context_copy );
    IIRScram *original_suffix_element = NULL;

    switch( my_decls->size() ){
    case 0:{
      // Not a valid type conversion...
      break;
    }
    case 1:{
      // Since this is a type conversion, the suffix must be resolvable with NO
      // CONTEXT.  (See LRM, pg 105)  Note that we checked above that there was
      // only one element in the list.
      original_suffix_element = _get_index( 1 );
      savant::set<IIRScram_TypeDefinition> *suffix_rvals = original_suffix_element->_get_rval_set();
      if( suffix_rvals == NULL ){
	report_undefined_symbol( original_suffix_element );
	return NULL;
      }
      
      ASSERT( suffix_rvals->size() != 0 );

      switch(  suffix_rvals->size() ){
      case 1:{
	// We need to make sure the expression is a valid type for a conversion.  
	// Dale, add this please!
	ASSERT( get_num_indexes() == 1 );

	IIRScram *suffix_expression;
	suffix_expression =
	  original_suffix_element->_semantic_transform( suffix_rvals->getElement() );
	suffix_expression->_type_check( suffix_rvals->getElement() );
	suffix_expression = suffix_expression->_rval_to_decl( suffix_rvals->getElement() );

	// Everything resolved correctly
	IIRScram_TypeConversion *type_convert = new IIRScram_TypeConversion();
	copy_location( this, type_convert );
	type_convert->set_type_mark( my_decls->getElement()->_get_subtype() );

	type_convert->set_expression( suffix_expression );

	retval = type_convert;
	break;
      }
      default:{
	ostringstream err;
	err << "The expression in a type conversion must be resolvable without context:";
	report_error( this, err.str() );
	report_ambiguous_error( _get_suffix(), suffix_rvals->convert_set<IIR_Declaration>() );
	break;
      }
      }

      break;
    }
    default:{
    
      break;
    }

    }

  }
  
  delete my_decls;

  return retval;
}


IIRScram *
IIRScram_IndexedName::_semantic_transform( savant::set<IIRScram_TypeDefinition> *context_set ){

  IIRScram *retval = NULL;
  
  ASSERT( _get_suffix() != NULL );   
  // OK, here's the story...  We have an indexed_name, something in
  // the form of foo(x, y, z)...  Or foo( x(2), y(1,2), z(x(1))) for
  // that matter.  We need to decide whether "foo" is a function or
  // procedure, or if it's an array access...  Note too, that we might
  // have an invalid call at this point - we're the one doing this
  // checking.  After deciding what "foo" is, we need to transform it
  // into the right type of "thing" - for instance, if it's a function
  // call, we need to transform the indexed name into an
  // IIRScram_FunctionCall, and make the transformations on the paramters.
  
#ifdef DEVELOPER_ASSERTIONS
  int context_size = context_set->size();
  IIRScram *orig_prefix = _get_prefix();
  IIRScram *orig_suffix = _get_suffix();
#endif

  // We're going to initially assume it's a function call.  If not,
  // we'll get back a NULL return value and try some other uses.
  retval = _process_as_function_call( context_set );


  if( retval == NULL ){
    ASSERT( context_size == context_set->size() );
    ASSERT( _get_prefix() == orig_prefix );
    ASSERT( _get_suffix() == orig_suffix );
    retval = _process_as_type_conversion( context_set );
  }

  if( retval == NULL ){
    ASSERT( context_size == context_set->size() );
    ASSERT( _get_prefix() == orig_prefix );
    ASSERT( _get_suffix() == orig_suffix );
    retval = _process_as_slice( context_set );
  }
   

  // If retval is NULL, then there was no matching function declaration,
  // which means we're an array (or completely invalid)...
  if( retval == NULL ){
    ASSERT( context_size == context_set->size() );
    ASSERT( _get_prefix() == orig_prefix );
    ASSERT( _get_suffix() == orig_suffix );
    retval = _process_as_array( context_set );
  }

  if( retval == NULL ){
    ostringstream err;

    err << "Umm, don't know what this |" << *this << "| is refering to. (Doesn't seem to"
	<< " be a function call, slice, type conversion, or array access).";

    report_error( this, err.str() );
  }

  _been_transformed = TRUE;

  if( retval == NULL ){
    retval = this;
  }
  else{
    if( retval != this ){
      delete this;
    }
  }
  
  ASSERT( parse_error == TRUE || retval->is_resolved() == TRUE );
  
  return retval;
}

IIRScram *
IIRScram_IndexedName::_rval_to_decl( IIRScram_TypeDefinition *new_rval ){
  ASSERT( is_resolved() == TRUE );
  ASSERT( new_rval != 0 );
  ASSERT( new_rval->is_compatible( _get_subtype() ) != NULL );

  return this;
}


IIRScram *
IIRScram_IndexedName::_rval_to_decl( IIRScram_Declaration *declaration, IIRScram_TypeDefinition *my_rval ){
  /* This is the case where we have something like:

            foo.bar( 1 to 3 );

                 S
                / \
              foo  I
                  / \
                bar  1 to 3
                   
  We're passed the declaration of foo... */

  ASSERT( _get_prefix()->is_name() == TRUE );

  savant::set<IIRScram_Declaration> *prefix_decls = NULL;

  if ( declaration->find_declarations( dynamic_cast<IIRScram_Name *>(_get_prefix())) != NULL ){
    prefix_decls = declaration->find_declarations( dynamic_cast<IIRScram_Name *>(_get_prefix()))->convert_set<IIRScram_Declaration>();
  }

  if( prefix_decls != NULL ){
    IIRScram_Declaration *prefix_decl = prefix_decls->getElement();
    while( prefix_decl != NULL ){
      savant::set<IIRScram_TypeDefinition> *return_set = _return_type_given_prefix_declaration( prefix_decl );
      ASSERT( return_set == NULL || return_set->size() == 1 );
      if( return_set != NULL ){
	IIRScram_TypeDefinition *return_type = return_set->getElement();
	if( return_type == my_rval ){
	  set_prefix( prefix_decl );
	  // The suffix might be a slice or something already resolved...
	  if( _get_suffix()->is_resolved() == FALSE ){
	    // We definitely should be array valued, as function calls, type conversions,
	    // etc should have been semantic transformed away by now...
	    IIRScram_TypeDefinition *prefix_rval = prefix_decl->_get_subtype();
	    ASSERT( prefix_rval != NULL );
	    if( prefix_rval->is_array_type() == TRUE ){
	      IIRScram_TypeDefinition *index_subtype = prefix_rval->_get_resolved_index_subtype();
	      set_suffix( _get_suffix()->_semantic_transform( index_subtype ) );
	      _get_suffix()->_type_check( index_subtype  );
	      set_suffix( _get_suffix()->_rval_to_decl( index_subtype ) );
	      return this;
	    }
	    else if (prefix_rval->is_record_type() == TRUE ){
	      // We'll figure this out later...
	    }
	    else{
	      ostringstream err;
	      err << "Internal error in IIRScram_IndexedName::"
		  << "_rval_to_decl( IIRScram_Declaration *declaration, IIRScram_TypeDefinition *my_rval )"
		  << "- unrecognized type " << prefix_rval->get_kind_text();
	      report_error( this, err.str() );
	      abort();
	    
	    }
	  }
	  else{
	    // The suffix is already resolved....
	    return this;
	  }
	}
      }
      prefix_decl = prefix_decls->getNextElement();
    }
  }

  ostringstream err;
  err << "Internal error in IIRScram_IndexedName::_rval_to_decl( IIRScram_Declaration *declaration,"
      <<" IIRScram_TypeDefinition *my_rval )";
  report_error( this, err.str() );
  abort();
  return 0;
}

void
IIRScram_IndexedName::_type_check( savant::set<IIRScram_TypeDefinition> *){}

// Only indexed names with a "explicit" constant declaration need to be
// added to the list.  If it is an implicit const. decl., it's prefix
// should be added.
IIRScram_Declaration *
IIRScram_IndexedName::_determine_decl_in_set( savant::set<IIRScram_Declaration> *look_in,
					      IIRScram_TypeDefinition *my_rval ){
  ASSERT( _get_prefix()->is_name() == TRUE );
  IIRScram_Declaration *current_decl = look_in->getElement();
  while( current_decl != NULL ){
    savant::set<IIRScram_Declaration> *prefix_decls = NULL;

    if (current_decl->find_declarations( dynamic_cast<IIRScram_Name *>(_get_prefix())) != NULL) {
      prefix_decls = current_decl->find_declarations( dynamic_cast<IIRScram_Name *>(_get_prefix()))->convert_set<IIRScram_Declaration>();
    }

    if( prefix_decls != NULL ){
      IIRScram_Declaration *prefix_decl = prefix_decls->getElement();
      while( prefix_decl != NULL ){
	if( prefix_decl != NULL ){
	  savant::set<IIRScram_TypeDefinition> *return_set = _return_type_given_prefix_declaration( prefix_decl );
	  ASSERT( return_set == NULL || return_set->size() == 1 );	  
	  if( return_set != NULL ){
	    IIRScram_TypeDefinition *return_type = return_set->getElement();
	    if( return_type == my_rval ){
	      return current_decl;
	    }
	  }
	} 
	prefix_decl = prefix_decls->getNextElement();
      }
    }
    current_decl = look_in->getNextElement();
  }

  
  // If we made it here, something bad happened...
  ostringstream err;
  err << "Internal error in IIRScram_IndexedName::_determine_decl_in_set";
  report_error( this, err.str() );
  abort();
  return 0;
}

IIRScram_Declaration *
IIRScram_IndexedName::_find_formal_declaration(){
  ASSERT( is_resolved() == TRUE );
  ASSERT( _get_suffix() != NULL );
//   ASSERT( _get_suffix()->get_kind() != IIR_ASSOCIATION_LIST || 
// 	  (dynamic_cast<IIRScram_AssociationList *>(_get_suffix())->size() == 1 );
  return _get_prefix()->_find_formal_declaration();
}

visitor_return_type *IIRScram_IndexedName::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_IndexedName(this, arg);
};

IIRScram *
IIRScram_IndexedName::_get_prefix(){
  ASSERT( get_prefix() != NULL );
  return dynamic_cast<IIRScram *>(get_prefix());
}

IIRScram_GenericList *
IIRScram_IndexedName::_get_generic_list(){
  // This assumes that we have something like entity(arch)
  ASSERT( _get_prefix() != NULL );
  return _get_prefix()->_get_generic_list();
}

IIRScram_PortList *
IIRScram_IndexedName::_get_port_list(){
  // This assumes that we have something like entity(arch)
  ASSERT( _get_prefix() != NULL );
  return _get_prefix()->_get_port_list();
}
  
IIR_Mode
IIRScram_IndexedName::_get_mode() {
  return _get_prefix()->_get_mode();
}

IIRScram_Declaration*
IIRScram_IndexedName::_get_package_declaration() {
  return _get_prefix()->_get_package_declaration();
}

IIRScram *
IIRScram_IndexedName::_get_suffix(){
  ASSERT( get_suffix() != NULL );

  return dynamic_cast<IIRScram *>(get_suffix());
}

IIRScram *
IIRScram_IndexedName::_get_index(int index_num) {
  return dynamic_cast<IIRScram *>(get_index(index_num));
}

IIRScram*
IIRScram_IndexedName::_clone() {
  IIRScram_IndexedName *clone = new IIRScram_IndexedName();
  IIRScram_Name::_clone(clone);
  clone->set_suffix(_get_suffix()->_clone());

  clone->_been_transformed = _been_transformed;
  clone->_my_rval_set = 0;
  clone->_have_rval_set = FALSE;

  return clone;
}
