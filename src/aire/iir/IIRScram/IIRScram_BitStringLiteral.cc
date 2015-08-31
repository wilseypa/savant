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
//          Krishnan Subramani  skrish@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_BitStringLiteral.hh"
#include "set.hh"

IIRScram_BitStringLiteral::~IIRScram_BitStringLiteral() {}  

savant::set<IIRScram_TypeDefinition> *
IIRScram_BitStringLiteral::_get_rval_set(constraint_functor *functor ){
  savant::set<IIRScram_TypeDefinition> *retval = _get_rval_set_for_string();
  retval->reduce_set( functor );
  return retval;
}


void
IIRScram_BitStringLiteral::_type_check( savant::set<IIRScram_TypeDefinition> * ){}


IIRScram *
IIRScram_BitStringLiteral::_clone() {
  return this;
}

visitor_return_type *
IIRScram_BitStringLiteral::_accept_visitor( node_visitor *visitor,
					    visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_BitStringLiteral(this, arg);
}


IIRScram_BitStringLiteral *
IIRScram_BitStringLiteral::get( IIR_Char *new_text, IIR_Int32 new_length){
  ASSERT( new_text != NULL);
  ASSERT( new_length > 3 );

  IIRScram_BitStringLiteral *retval = new IIRScram_BitStringLiteral();
  retval->set_text( new_text, new_length );

  return retval;
}

