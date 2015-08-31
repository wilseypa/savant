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
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_FunctionDeclaration.hh"
#include "IIRScram_IntegerSubtypeDefinition.hh"

IIRScram_IntegerSubtypeDefinition::IIRScram_IntegerSubtypeDefinition(){}

IIRScram_IntegerSubtypeDefinition::~IIRScram_IntegerSubtypeDefinition(){}


IIRScram *
IIRScram_IntegerSubtypeDefinition::_clone(){
  IIRScram_IntegerSubtypeDefinition *my_clone = new IIRScram_IntegerSubtypeDefinition();
  IIRScram_IntegerTypeDefinition::_clone( my_clone );
  my_clone->IIRBase_IntegerSubtypeDefinition::set_resolution_function( _get_resolution_function() );
  return my_clone;
}

void 
IIRScram_IntegerSubtypeDefinition::_type_check(){
  if( _get_resolution_function() != NULL ){
    _get_resolution_function()->_type_check_resolution_function( this );
  }
  IIRScram_IntegerTypeDefinition::_type_check();
}

visitor_return_type *
IIRScram_IntegerSubtypeDefinition::_accept_visitor( node_visitor *visitor,
						    visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_IntegerSubtypeDefinition(this, arg);
};

IIRScram_FunctionDeclaration *
IIRScram_IntegerSubtypeDefinition::_get_resolution_function(){ 
  return dynamic_cast<IIRScram_FunctionDeclaration *>(get_resolution_function()); 
}

void 
IIRScram_IntegerSubtypeDefinition::_set_resolution_function(IIRScram_FunctionDeclaration *new_function ){
  IIRBase_IntegerSubtypeDefinition::set_resolution_function( new_function );
}

// This fixes problems with attempting to call the other version from the IIRScram level
void 
IIRScram_IntegerSubtypeDefinition::set_resolution_function(IIRScram_FunctionDeclaration *new_function ){
  IIRBase_IntegerSubtypeDefinition::set_resolution_function( new_function );
}
