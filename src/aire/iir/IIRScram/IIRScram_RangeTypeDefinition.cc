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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "resolution_func.hh"
#include "StandardPackage.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_Declaration.hh"
#include "IIRScram_EnumerationLiteral.hh"
#include "IIRScram_EnumerationLiteralList.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_IntegerSubtypeDefinition.hh"
#include "IIRScram_RangeTypeDefinition.hh"
#include "error_func.hh"
#include "savant.hh"
#include "set.hh"

#include <sstream>
using std::ostringstream;

IIRScram_RangeTypeDefinition::~IIRScram_RangeTypeDefinition() {}

IIRScram_TypeDefinition *
IIRScram_RangeTypeDefinition::_get_new_subtype(){
  ostringstream err;

  err << "Internal error - IIRScram_RangeTypeDefinition::_get_new_subtype() called.";
  err << "This shouldn't happen...";

  report_error( this, err.str() );
  abort();

  return NULL;
}

void 
IIRScram_RangeTypeDefinition::_set_resolution_function( IIRScram_FunctionDeclaration * ){
  ostringstream err;
  err << "Internal error - IIRScram_RangeTypeDefinition::_set_resolution_function was "
      << "called.  Resolution functions can't be associated with an access type and this "
      << "should have been caught earlier.";
  report_error( this, err.str() );
}


visitor_return_type *
IIRScram_RangeTypeDefinition::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_RangeTypeDefinition(this, arg);
};

IIRScram_ScalarTypeDefinition *
IIRScram_RangeTypeDefinition::_determine_discrete_type() {

  if( get_left() == NULL ){
    ostringstream err;
    err << "Internal error in IIRScram_ScalarTypeDefinition::_determine_discrete_type(";
    err << "IIRScram_RangeTypeDefinition *range ) - this problem is most likely due to a known bug ";
    err << "in the intermediate form.  Attempting work around it.";
    report_error( this, err.str(), WARNING );
    return this;
  }

  ASSERT( get_left() != NULL );
  ASSERT( get_right() != NULL );
  ASSERT( get_direction() != NULL );

  // This is the type that this is a subtype of.
  IIRScram_TypeDefinition       *subtype_of = NULL;
  savant::set<IIRScram_TypeDefinition> *left_set = _get_base_type_left()->_get_rval_set();
  if( left_set == NULL ){
    report_undefined_symbol( _get_base_type_left() );
    return NULL;
  }
  
  savant::set<IIRScram_TypeDefinition> *right_set = _get_base_type_right()->_get_rval_set();
  if( right_set == NULL ){
    report_undefined_symbol( _get_base_type_right() );
    return NULL;
  }
  
  ASSERT( left_set != NULL );
  constraint_functor *functor = new is_discrete_type_functor;
  left_set->reduce_set( functor );
  delete functor;
  
  reconcile_sets( left_set, right_set );  
  switch( left_set->size() ){
  case 0:{
    ostringstream err;
    err << "|" << *this << "| is not a proper range in this context.";
    report_error( this, err.str() );
    return NULL;
  }

  case 1:{
    IIRScram_TypeDefinition *left_type = left_set->getElement();
    IIRScram_TypeDefinition *right_type = right_set->getElement();

    ASSERT( left_type->is_scalar_type() == TRUE );
    ASSERT( right_type->is_scalar_type() == TRUE );


    if( left_type->get_bottom_base_type() != right_type->get_bottom_base_type() ){
      subtype_of = _determine_universal_subtype( left_type, right_type );
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
    report_error( this, err.str() );
    report_ambiguous_error( this, left_set->convert_set<IIR_TypeDefinition>() );
    return NULL;
  }
  }

  delete left_set;
  delete right_set;


  // This method is following the rules of page 42, line 350 of the LRM.  
  IIRScram_IntegerSubtypeDefinition *scram_int = 
    dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(get_design_file()->get_standard_package()->get_savant_universal_integer());
  if( subtype_of == scram_int &&
      ( _get_base_type_left()->_is_integer_literal() == TRUE ||
	_get_base_type_left()->_is_attribute() == TRUE ) &&
      ( _get_base_type_right()->_is_integer_literal() == TRUE ||
	_get_base_type_right()->_is_attribute() == TRUE ) ){
    subtype_of = 
      dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(get_design_file()->get_standard_package()->get_integer_type());
  }

  return dynamic_cast<IIRScram_ScalarTypeDefinition *>(subtype_of);
}

IIRScram_ScalarTypeDefinition *
IIRScram_RangeTypeDefinition::_determine_universal_subtype( IIRScram_TypeDefinition *left_type,
							    IIRScram_TypeDefinition *right_type ){
  IIRScram_ScalarTypeDefinition *subtype_of = 0;

  // That means that the two types aren't "naturally" related, so one of
  // them must be a universal type.

  IIRScram_IntegerSubtypeDefinition *scram_int = 
    dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(get_design_file()->get_standard_package()->get_savant_universal_integer());
  ASSERT( (left_type == scram_int) || (right_type == scram_int) );
  
  if( left_type == scram_int ){
    subtype_of = dynamic_cast<IIRScram_ScalarTypeDefinition *>(right_type);
  }
  else{
    ASSERT( right_type == scram_int );
    subtype_of = dynamic_cast<IIRScram_ScalarTypeDefinition *>(left_type);
  }
  return subtype_of;
}

