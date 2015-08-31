
// Copyright (c) 1996-2003 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
// NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S., and
// the terms of this license.

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2, June
// 1991. A copy of this license agreement can be found in the file "LGPL",
// distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam

//---------------------------------------------------------------------------

#include "IIRScram_Signature.hh"
#include "IIRScram_DesignatorList.hh"

IIRScram_Signature::IIRScram_Signature() {
  set_argument_type_list(new IIRScram_DesignatorList());
}

IIRScram_Signature::~IIRScram_Signature(){}

visitor_return_type *IIRScram_Signature::_accept_visitor( node_visitor *visitor,
							  visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_Signature(this, arg);
}

// IIRBase Function Wrapper(s)
IIRScram_DesignatorList *
IIRScram_Signature::_get_argument_type_list() {
  return dynamic_cast<IIRScram_DesignatorList *>(get_argument_type_list());
}
