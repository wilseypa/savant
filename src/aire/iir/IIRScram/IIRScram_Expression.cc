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
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_Expression.hh"
#include "IIRScram_ScalarTypeDefinition.hh"
#include "IIRScram_ArrayTypeDefinition.hh"

IIRScram_Expression::~IIRScram_Expression() {}

IIRScram *
IIRScram_Expression::_rval_to_decl( IIRScram_TypeDefinition *my_type ){
  set_subtype( my_type );
  ASSERT( is_resolved() == TRUE );

  return this;
}

void
IIRScram_Expression::_clone( IIRScram *copy_into ){
  ASSERT( copy_into->_is_iir_expression() == TRUE );
  IIRScram_Expression *as_expression = dynamic_cast<IIRScram_Expression *>(copy_into);
  IIRScram::_clone( copy_into );
  // clone IIRScram_Expression info
  as_expression->set_subtype( _get_subtype() );
}
