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
//          Malolan Chetlur     mal@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_AscendingAttribute.hh"

void 
IIRScram_AscendingAttribute::_resolve_suffix_special(){
  _resolve_suffix_local_static_int();
}

visitor_return_type *
IIRScram_AscendingAttribute::_accept_visitor( node_visitor *visitor,
					      visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_AscendingAttribute(this, arg);
}
