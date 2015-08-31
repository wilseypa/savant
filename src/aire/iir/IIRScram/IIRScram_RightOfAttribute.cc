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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_DesignFile.hh"
#include "IIRScram_FunctionDeclaration.hh"
#include "IIRScram_RightOfAttribute.hh"
#include "IIRScram_ScalarTypeDefinition.hh"

IIRScram_TypeDefinition *
IIRScram_RightOfAttribute::_get_subtype(){
  return _get_prefix_subtype();
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_RightOfAttribute::_get_rval_set(constraint_functor *functor){
  return _get_prefix()->_get_rval_set(functor);
}

void 
IIRScram_RightOfAttribute::_resolve_suffix_special(){
  _resolve_suffix_base_type_of_prefix();
}


visitor_return_type *
IIRScram_RightOfAttribute::_accept_visitor( node_visitor *visitor,
					    visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_RightOfAttribute(this, arg);
}
