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

//---------------------------------------------------------------------------

#include "IIRScram_AscendingAttribute.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_LeftAttribute.hh"
#include "IIRScram_ReverseRangeAttribute.hh"
#include "IIRScram_RightAttribute.hh"
#include "IIRScram_ScalarTypeDefinition.hh"
#include "IIRScram_TypeDeclaration.hh"

#include "error_func.hh"
#include "resolution_func.hh"
#include "set.hh"
#include "savant.hh"


IIRScram_TypeDefinition *
IIRScram_ReverseRangeAttribute::_get_subtype(){
  return _get_subtype_range_attribute();
}



IIRScram_TypeDefinition *
IIRScram_ReverseRangeAttribute::_get_prefix_rval(){
  return _get_prefix_rval_range_attributes();
}


IIRScram *
IIRScram_ReverseRangeAttribute::_get_suffix(){
  return dynamic_cast<IIRScram *>(IIRBase_ReverseRangeAttribute::get_suffix());
}

void 
IIRScram_ReverseRangeAttribute::_resolve_suffix_special(){
  _resolve_suffix_local_static_int();
}

visitor_return_type *
IIRScram_ReverseRangeAttribute::_accept_visitor( node_visitor *visitor, 
						 visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ReverseRangeAttribute(this, arg);
}
