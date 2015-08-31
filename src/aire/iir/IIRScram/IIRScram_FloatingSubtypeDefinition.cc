
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
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Magnus Danielson    cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_FloatingSubtypeDefinition.hh"
#include "IIRScram_SubtypeDeclaration.hh"
#include "IIRScram_FloatingPointLiteral.hh"
#include "IIRScram_FunctionDeclaration.hh"
#include <iostream>

IIRScram_FloatingSubtypeDefinition::~IIRScram_FloatingSubtypeDefinition(){}

void 
IIRScram_FloatingSubtypeDefinition::_type_check(){
  if( get_resolution_function() != NULL ){
    _get_resolution_function()->_type_check_resolution_function( this );
  }
  IIRScram_FloatingTypeDefinition::_type_check();
}


visitor_return_type *
IIRScram_FloatingSubtypeDefinition::_accept_visitor( node_visitor *visitor, 
						     visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_FloatingSubtypeDefinition(this, arg);
}

IIRScram_FloatingSubtypeDefinition * 
IIRScram_FloatingSubtypeDefinition::get(
				       IIRScram_FloatingTypeDefinition* base_type, IIRScram* left_limit,
				       IIRScram* direction, IIRScram* right_limit) {

  IIRScram_FloatingSubtypeDefinition* retval = new IIRScram_FloatingSubtypeDefinition;
  retval->set_base_type(base_type);
  retval->set_left(left_limit);
  retval->set_right(right_limit);
  retval->set_direction(direction);

  return retval;
}

void
IIRScram_FloatingSubtypeDefinition::_set_resolution_function(IIRScram_FunctionDeclaration *function) {
  IIRBase_FloatingSubtypeDefinition::set_resolution_function(function);
}

IIRScram_FunctionDeclaration *
IIRScram_FloatingSubtypeDefinition::_get_resolution_function() {
  return dynamic_cast<IIRScram_FunctionDeclaration *>(IIRBase_FloatingSubtypeDefinition::get_resolution_function());
}
