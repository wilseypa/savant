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
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram.hh"
#include "IIRScram_AssociationElement.hh"
#include "IIRScram_AssociationElementByExpression.hh"
#include "IIRScram_List.hh"

IIRScram_AssociationElement::~IIRScram_AssociationElement() {}

IIRScram_Declaration *
IIRScram_AssociationElement::_find_formal_declaration(){
  
  // This gets called from _find_formal_declaration in IIRScram_FunctionCall.
  // It gets called directly on the formal originally.  That's why this one
  // has to call it on the actual - NOT the formal.
  
  IIRScram_Declaration *retval = NULL;
  if( _get_actual() != NULL ){
    retval = _get_actual()->_find_formal_declaration();
  }

  return retval;
}

IIR_Boolean 
IIRScram_AssociationElement::_is_positional(){
  // If the formal is NULL and we're not others, we're positional
  return get_formal() == NULL && is_by_others() == FALSE;
}

IIRScram* 
IIRScram_AssociationElement::_get_formal() {
  return dynamic_cast<IIRScram *>(get_formal());
}

IIRScram* 
IIRScram_AssociationElement::_get_actual() {
  return dynamic_cast<IIRScram *>(get_actual());
}


