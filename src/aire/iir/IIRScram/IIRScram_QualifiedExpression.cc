
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
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "savant.hh"
#include "IIRScram_ArrayTypeDefinition.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_QualifiedExpression.hh"
#include "set.hh"

void 
IIRScram_QualifiedExpression::_type_check( savant::set<IIRScram_TypeDefinition> * ){
  // The parser originally built this as an IIRScram_UserAttribute...  Then it got
  // transformed into an IIRScram_QualifiedExpression.  When it got trasnformed,
  // an effort was made to make sure that the type and expression were compatible...

  // Whatever is "sitting above" us should complain if we're incompatible with what
  // we're being assigned to, so, we don't have to do anything here...

}

savant::set<IIRScram_TypeDefinition> *
IIRScram_QualifiedExpression::_get_rval_set( constraint_functor * ){
  return new savant::set<IIRScram_TypeDefinition>( _get_type_mark() );
}

IIRScram * 
IIRScram_QualifiedExpression::_rval_to_decl( IIRScram_TypeDefinition *my_rval ){
  ASSERT( _get_type_mark()->is_resolved() == TRUE );
  ASSERT( my_rval->is_compatible( _get_type_mark() ) != NULL );
  
  if( _get_type_mark() != NULL && get_expression() != NULL ){
    set_expression( _get_expression()->_semantic_transform( _get_type_mark() ) );
    _get_expression()->_type_check( _get_type_mark() );
    set_expression( _get_expression()->_rval_to_decl( _get_type_mark() ) );
  }

  return this;
}

visitor_return_type *
IIRScram_QualifiedExpression::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_QualifiedExpression(this, arg);
}

IIRScram*
IIRScram_QualifiedExpression::_get_expression() {
  return dynamic_cast<IIRScram *>(get_expression());
}

IIRScram_TypeDefinition *
IIRScram_QualifiedExpression::_get_type_mark() {
  return dynamic_cast<IIRScram_TypeDefinition *>(get_type_mark());
}
