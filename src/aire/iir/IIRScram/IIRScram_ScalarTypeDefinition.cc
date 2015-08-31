
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
//          Timothy J. McBrayer
//          Malolan Chetlur    
//          Krishnan Subramani 
//          Radharamanan Radhakrishnan
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam
//          Magnus Danielson    cfmd@swipnet.se
//---------------------------------------------------------------------------

#include "savant.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EnumerationLiteral.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "IIRScram_FloatingSubtypeDefinition.hh"
#include "IIRScram_FunctionDeclaration.hh"
#include "IIRScram_IntegerSubtypeDefinition.hh"
#include "IIRScram_LeftAttribute.hh"
#include "IIRScram_RangeTypeDefinition.hh"
#include "IIRScram_ScalarTypeDefinition.hh"
#include "IIRScram_SignalDeclaration.hh"
#include "IIRScram_SignalInterfaceDeclaration.hh"
#include "IIRScram_TextLiteral.hh"
#include "StandardPackage.hh"

#include "symbol_table.hh"
#include "error_func.hh"
#include "resolution_func.hh"

#include <sstream>
using std::ostringstream;

IIRScram_ScalarTypeDefinition::IIRScram_ScalarTypeDefinition(){}

IIRScram_ScalarTypeDefinition::~IIRScram_ScalarTypeDefinition() {}

IIRScram *
IIRScram_ScalarTypeDefinition::_get_left() {
  return dynamic_cast<IIRScram *>(get_left());
}

IIRScram *
IIRScram_ScalarTypeDefinition::_get_right() {
  return dynamic_cast<IIRScram *>(get_right());
}

IIRScram_ScalarTypeDefinition *
IIRScram_ScalarTypeDefinition::_determine_discrete_type( IIRScram_RangeTypeDefinition *range ){
  if( range->_get_base_type_left() == NULL ){
    ostringstream err;
    err << "Internal error in IIRScram_ScalarTypeDefinition::_determine_discrete_type(";
    err << "IIR_RangeTypeDefinition *range ) - this problem is most likely due to a known bug ";
    err << "in the intermediate form.  Attempting work around it.";
    report_error( range, err.str(), WARNING );
    return range;
  }

  ASSERT( range->_get_base_type_left() != NULL );
  ASSERT( range->_get_base_type_right() != NULL );
  ASSERT( range->get_direction() != NULL );

  // This is the type that this is a subtype of.
  IIRScram_TypeDefinition *subtype_of = NULL;
  
  savant::set<IIRScram_TypeDefinition> *left_set = range->_get_base_type_left()->_get_rval_set();
  if( left_set == NULL ){
    report_undefined_symbol( range->_get_base_type_left() );
    return NULL;
  }
  
  savant::set<IIRScram_TypeDefinition> *right_set = range->_get_base_type_right()->_get_rval_set();
  if( right_set == NULL ){
    report_undefined_symbol( range->_get_base_type_right() );
    return NULL;
  }
  
  ASSERT( left_set != NULL );
  constraint_functor *functor = new is_discrete_type_functor;
  left_set->reduce_set( functor );
  delete functor;
  
  reconcile_sets( left_set, right_set );  

  StandardPackage *package = range->get_design_file()->get_standard_package();
  switch( left_set->size() ){

  case 0:{
    ostringstream err;
    err << "|" << *range << "| is not a proper range in this context.";
    report_error( range, err.str() );
    return NULL;
  }

  case 1:{
    IIRScram_TypeDefinition *left_type = left_set->getElement();
    IIRScram_TypeDefinition *right_type = right_set->getElement();

    ASSERT( left_type->is_scalar_type() == TRUE );
    ASSERT( right_type->is_scalar_type() == TRUE );


    if( left_type->get_bottom_base_type() != right_type->get_bottom_base_type() ){
      // That means that the two types aren't "naturally" related, so one of them must be
      // a universal type.
      ASSERT( left_type == dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(package->get_savant_universal_integer()) ||
	      right_type == dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(package->get_savant_universal_integer()) );

      if( left_type == dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(package->get_savant_universal_integer()) ){
	subtype_of = dynamic_cast<IIRScram_ScalarTypeDefinition *>(right_type);
      }
      else{
	ASSERT( right_type == dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(package->get_savant_universal_integer()) );
	subtype_of = dynamic_cast<IIRScram_ScalarTypeDefinition *>(left_type);
      }

    }
    else{
      // The types are naturally compatible, and "reconcile_sets" should
      // have handed us the correct type back in the left set.
      subtype_of = dynamic_cast<IIRScram_ScalarTypeDefinition *>(left_set->getElement());
    }

    ASSERT( subtype_of->is_scalar_type() == TRUE );
    break;
  }
  default:{
    ostringstream err;
    err << "The type of a range used in this manner must be "
	<< "determinable without context.";
    report_error( range, err.str() );
    report_ambiguous_error( range, left_set->convert_set<IIR_TypeDefinition>() );
    return NULL;
  }
  }

  delete left_set;
  delete right_set;

  // This method is following the rules of page 42, line 350 of the LRM.  
  if( subtype_of == dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(package->get_savant_universal_integer()) &&
      ( range->_get_base_type_left()->_is_integer_literal() == TRUE ||
	range->_get_base_type_left()->_is_attribute() == TRUE ) &&
      ( range->_get_base_type_right()->_is_integer_literal() == TRUE ||
	range->_get_base_type_right()->_is_attribute() == TRUE ) ){
    subtype_of = dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(package->get_integer_type());
  }

  return dynamic_cast<IIRScram_ScalarTypeDefinition *>(subtype_of);
}

IIRScram_TypeDefinition *
IIRScram_ScalarTypeDefinition::_construct_new_subtype( IIRScram_Name *resolution_function,
						       IIRScram_ScalarTypeDefinition *new_constraint){
  IIRScram_FunctionDeclaration *resolution_function_decl = NULL;

  IIRScram_TypeDefinition *subtype = _get_new_subtype();
  ASSERT( subtype->is_scalar_type_definition() == TRUE );
  IIRScram_ScalarTypeDefinition *scalar_subtype =
    dynamic_cast<IIRScram_ScalarTypeDefinition *>(subtype);
  
  if( resolution_function != NULL ){
    resolution_function_decl = _resolve_resolution_function( resolution_function );
    scalar_subtype->set_resolution_function( resolution_function_decl );
  }
  
   // Enumeration types don't have anonymous base types unlike the
  // other scalar types - hence all of the special cases here.
  if( is_subtype() == TRUE ){
    // If we are a subtype, and we're NOT an enumeration type:
    // 1) base type isn't null
    // 2) base type is a type - not a subtype, and it's anonymous.
    ASSERT( _get_base_type() != NULL );
    ASSERT( _get_base_type()->is_subtype() == FALSE ||
            _get_base_type()->is_enumeration_type() == TRUE );
    ASSERT( _get_base_type()->is_anonymous() == FALSE );

    scalar_subtype->set_base_type( _get_base_type() );
  }
  else{
    // We are a type.  If we're not an enumeration type, we must:
    // 1) have a NULL base type.
    // 2) be anonymous
    ASSERT( get_base_type() == NULL );
    scalar_subtype->set_base_type( this );
  }
    
  if( new_constraint != NULL ){
//     scalar_subtype->set_declaration( new_constraint->get_declaration() );
    copy_location( new_constraint, scalar_subtype );

    if( new_constraint->_get_left() != NULL ){
      ASSERT( new_constraint->_get_base_type_right() != NULL );
      ASSERT( new_constraint->_get_direction() != NULL );

      // Resolve the left side, if needed
      if( new_constraint->_get_left()->is_resolved() == FALSE ){
	new_constraint->set_left( new_constraint->_get_left()->_semantic_transform( this ) );
	new_constraint->_get_left()->_type_check( this );
	new_constraint->set_left( new_constraint->_get_left()->_rval_to_decl( this ) );	
      }
      // Modified by SK -- Begin
      // set the subtype of left if it is an enumeration literal.
      if(new_constraint->_get_left()->_is_enumeration_literal() == TRUE) {
	if(new_constraint->_get_left()->_get_subtype() == NULL) {
	  ASSERT(is_enumeration_type() == TRUE);
	  (dynamic_cast<IIRScram_EnumerationLiteral *>( new_constraint->_get_left()))->set_subtype(dynamic_cast<IIRScram_EnumerationTypeDefinition*>(this));
	}
      }
      // Modified by SK -- End      
      scalar_subtype->set_left( new_constraint->_get_left() );

      // No resolution need for direction...
      scalar_subtype->set_direction( new_constraint->_get_direction() );

      // Resolve the right side, if needed
      if( new_constraint->_get_right()->is_resolved() == FALSE ){
	new_constraint->set_right( new_constraint->_get_right()->_semantic_transform( this ) );
	new_constraint->_get_right()->_type_check( this );
	new_constraint->set_right( new_constraint->_get_right()->_rval_to_decl( this ) );	
      }

      // Modified by SK -- Begin
      // set the subtype of right if it is an enumeration literal.
      if(new_constraint->_get_right()->_is_enumeration_literal() == TRUE) {
	if(new_constraint->_get_right()->_get_subtype() == NULL) {
	  ASSERT(is_enumeration_type() == TRUE);
	  (dynamic_cast<IIRScram_EnumerationLiteral *>( new_constraint->_get_right()))->set_subtype(dynamic_cast<IIRScram_EnumerationTypeDefinition*>(this));
	}
      }
      // Modified by SK -- End
      scalar_subtype->set_right( new_constraint->_get_right() );
    }
#ifdef DEVELOPER_ASSERTIONS
    else{
      ASSERT( new_constraint->_get_direction() == NULL );
      ASSERT( new_constraint->_get_right() == NULL );
    }
#endif
  }
  else{
    // No new constraint 
    copy_location( this, scalar_subtype );
    scalar_subtype->set_left( _get_left() );
    scalar_subtype->set_direction( _get_direction() );
    scalar_subtype->set_right( _get_right() );
  }

  scalar_subtype->_set_design_file( _get_design_file() );
  return scalar_subtype;
}

void 
IIRScram_ScalarTypeDefinition::set_resolution_function( IIRScram_FunctionDeclaration * ){
  _report_undefined_scram_fn("set_resolution_function");  
}

void 
IIRScram_ScalarTypeDefinition::_clone( IIRScram *copy_into ){
  ASSERT( copy_into->is_scalar_type_definition() == TRUE );
  
  IIRScram_ScalarTypeDefinition *as_scalar_type = dynamic_cast<IIRScram_ScalarTypeDefinition *>(copy_into);
  
  as_scalar_type->set_left( _get_base_type_left() );
  as_scalar_type->set_right( _get_base_type_right() );
  as_scalar_type->set_direction( _get_direction() );

  IIRScram_TypeDefinition::_clone( copy_into );
}

void 
IIRScram_ScalarTypeDefinition::_build_implicit_operators( savant::set<IIRScram_Declaration> *add_to){
  IIRScram_TypeDefinition::_build_implicit_operators( add_to );
  _build_ordering_operators( add_to );
}

void 
IIRScram_ScalarTypeDefinition::_init_scalar_type( IIRScram_RangeTypeDefinition   *init_info,
						  IIRScram_ScalarTypeDefinition  *base_type,
						  IIRScram_ScalarTypeDefinition  *subtype,
						  IIRScram_TypeDeclaration       *type_decl) {

  ASSERT( base_type != 0 );
  ASSERT( !base_type->is_subtype() );
  subtype->set_base_type( base_type );

  IIRScram *left = init_info->_get_base_type_left();
  left = left->_semantic_transform( subtype );
  left->_type_check( subtype );
  left = left->_rval_to_decl( subtype );

  IIRScram *right = init_info->_get_base_type_right();
  right = right->_semantic_transform( subtype );
  right->_type_check( subtype );
  right = right->_rval_to_decl( subtype );

  subtype->set_left( left );
  subtype->set_right( right );
  subtype->set_direction( init_info->_get_direction() );
  subtype->set_declaration( type_decl );
  init_info->copy_location( subtype );

  base_type->set_left( left );
  base_type->set_right( right );
  base_type->set_direction( init_info->_get_direction() );
  base_type->set_declaration( type_decl );
  init_info->copy_location( base_type );
}

IIRScram*
IIRScram_ScalarTypeDefinition::_get_direction(){
  return dynamic_cast<IIRScram *>(get_direction());
}
