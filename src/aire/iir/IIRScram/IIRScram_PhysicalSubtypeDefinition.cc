
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
#include "IIRScram_PhysicalSubtypeDefinition.hh"
#include "IIRScram_PhysicalUnit.hh"
#include "IIRScram_PhysicalLiteral.hh"
#include "IIRScram_FunctionDeclaration.hh"

void 
IIRScram_PhysicalSubtypeDefinition::_type_check(){
  if( _get_resolution_function() != NULL ){
    _get_resolution_function()->_type_check_resolution_function( this );
  }
  IIRScram_PhysicalTypeDefinition::_type_check();
}

IIRScram *
IIRScram_PhysicalSubtypeDefinition::_clone(){
  IIRScram_PhysicalSubtypeDefinition *retval = new IIRScram_PhysicalSubtypeDefinition();
  _clone( retval );
  return retval;
}

void 
IIRScram_PhysicalSubtypeDefinition::_clone( IIRScram *copy_into ){
  ASSERT( copy_into->_is_iir_physical_subtype_definition() == TRUE );
  IIRScram_PhysicalSubtypeDefinition *as_physical_subtype = 
    dynamic_cast<IIRScram_PhysicalSubtypeDefinition *>(copy_into);
  
  as_physical_subtype->IIRBase_PhysicalSubtypeDefinition::set_resolution_function( get_resolution_function() );

  IIRScram_PhysicalTypeDefinition::_clone( copy_into );
}



visitor_return_type *
IIRScram_PhysicalSubtypeDefinition::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_PhysicalSubtypeDefinition(this, arg);
};

void 
IIRScram_PhysicalSubtypeDefinition::_set_resolution_function(IIRScram_FunctionDeclaration *function) {
  IIRBase_PhysicalSubtypeDefinition::set_resolution_function(function);
}

IIRScram_FunctionDeclaration *
IIRScram_PhysicalSubtypeDefinition::_get_resolution_function(){ 
  return dynamic_cast<IIRScram_FunctionDeclaration *>(get_resolution_function()); 
}
