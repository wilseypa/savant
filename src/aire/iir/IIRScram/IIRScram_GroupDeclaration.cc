
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

//---------------------------------------------------------------------------

#include "IIRScram_GroupDeclaration.hh"
#include "IIRScram_Name.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_AttributeSpecificationList.hh"

IIRScram_GroupDeclaration::IIRScram_GroupDeclaration() {
  set_group_constituent_list(new IIRScram_DesignatorList());
  set_attributes(new IIRScram_AttributeSpecificationList());
}

IIRScram_GroupDeclaration::~IIRScram_GroupDeclaration() {
  //Release the list memory
  delete get_group_constituent_list();
  delete get_attributes();
}

visitor_return_type *
IIRScram_GroupDeclaration::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_GroupDeclaration(this, arg);
}

// IIRBase Function Wrapper(s)
IIRScram_AttributeSpecificationList* 
IIRScram_GroupDeclaration::_get_attribute_specification_list() {
  return dynamic_cast<IIRScram_AttributeSpecificationList *>(get_attributes());
}

