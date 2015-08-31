
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
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_EnumerationLiteral.hh"
#include "IIRScram_EnumerationLiteralList.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "IIRScram_FunctionDeclaration.hh"

IIRScram_EnumerationSubtypeDefinition::IIRScram_EnumerationSubtypeDefinition(){}

IIRScram_EnumerationSubtypeDefinition::~IIRScram_EnumerationSubtypeDefinition(){}

void 
IIRScram_EnumerationSubtypeDefinition::_type_check(){
  if( _get_resolution_function() != NULL ){
    _get_resolution_function()->_type_check_resolution_function( this );
  }
  IIRScram_EnumerationTypeDefinition::_type_check();
}

IIRScram *
IIRScram_EnumerationSubtypeDefinition::_clone(){
  IIRScram_EnumerationSubtypeDefinition *retval = new IIRScram_EnumerationSubtypeDefinition();
  _clone( retval );
  return retval;
}

void 
IIRScram_EnumerationSubtypeDefinition::_clone( IIRScram *copy_into ){
  ASSERT( copy_into->get_kind() == IIR_ENUMERATION_SUBTYPE_DEFINITION );
  IIRScram_EnumerationSubtypeDefinition *as_enumeration_subtype = 
    dynamic_cast<IIRScram_EnumerationSubtypeDefinition *>(copy_into);
  
  as_enumeration_subtype->_set_resolution_function( _get_resolution_function() );

  IIRScram_EnumerationTypeDefinition::_clone( copy_into );
}

visitor_return_type *IIRScram_EnumerationSubtypeDefinition::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_EnumerationSubtypeDefinition(this, arg);
};

IIRScram_EnumerationSubtypeDefinition *
IIRScram_EnumerationSubtypeDefinition::get( IIRScram_EnumerationTypeDefinition *base_type,
					  IIRScram_EnumerationLiteral *left_limit,
					  IIRScram_EnumerationLiteral *right_limit){

  IIRScram_EnumerationSubtypeDefinition *retval =
    new IIRScram_EnumerationSubtypeDefinition();

  retval->set_base_type( base_type );
  retval->set_left( left_limit );
  retval->set_right( right_limit );
  
  return retval;
}

void 
IIRScram_EnumerationSubtypeDefinition::set_resolution_function(IIRScram_FunctionDeclaration *new_function ) {
  IIRBase_EnumerationSubtypeDefinition::set_resolution_function( new_function );
}

void 
IIRScram_EnumerationSubtypeDefinition::_set_resolution_function(IIRScram_FunctionDeclaration *new_function ) {
  IIRBase_EnumerationSubtypeDefinition::set_resolution_function( new_function );
}

// IIRBase Function Wrapper(s)
IIRScram_FunctionDeclaration *
IIRScram_EnumerationSubtypeDefinition::_get_resolution_function() {
  return dynamic_cast<IIRScram_FunctionDeclaration *>(get_resolution_function());
}

IIRScram_EnumerationLiteralList *
IIRScram_EnumerationSubtypeDefinition::_get_enumeration_literals() {
  return dynamic_cast<IIRScram_EnumerationLiteralList *>(IIRBase_EnumerationSubtypeDefinition::get_enumeration_literals());
}
