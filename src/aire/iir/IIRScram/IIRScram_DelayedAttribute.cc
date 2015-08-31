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
//          Timothy J. McBrayer tmcrbaye@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu

//---------------------------------------------------------------------------
#include "IIRScram_DelayedAttribute.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_SignalDeclaration.hh"

#include "error_func.hh"
#include "set.hh"
#include "resolution_func.hh"


IIRScram_TypeDefinition *
IIRScram_DelayedAttribute::_get_subtype(){
  constraint_functor *functor = new is_signal_functor;
  return _get_prefix_subtype(functor);
}


void  
IIRScram_DelayedAttribute::_resolve_suffix_special(){
  _resolve_suffix_non_negative_time();
}

visitor_return_type *
IIRScram_DelayedAttribute::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_DelayedAttribute(this, arg);
};

void 
IIRScram_DelayedAttribute::_set_suffix( IIRScram *new_suffix ) {  
  IIRBase_DelayedAttribute::set_suffix( new_suffix ); 
}
IIRScram *
IIRScram_DelayedAttribute::_get_suffix() { 
  return dynamic_cast<IIRScram *>(IIRBase_DelayedAttribute::get_suffix()); 
}
