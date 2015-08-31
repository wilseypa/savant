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
//          Umesh Kumar V. Rajasekaran urajasek@ececs.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_Attribute.hh"
#include "IIRScram_AttributeSpecification.hh"
#include "IIRScram_AttributeSpecificationList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_FileDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_ProcessStatement.hh"
#include "IIRScram_SimpleName.hh"
#include "IIRScram_TypeDefinition.hh"

#include "symbol_table.hh"



IIRScram_FileDeclaration::~IIRScram_FileDeclaration() {}

IIRScram*
IIRScram_FileDeclaration::_clone() {
  if (_my_clone == NULL) {
    _my_clone = new IIRScram_FileDeclaration();
    IIRScram_ObjectDeclaration::_clone(_my_clone);

    _my_clone->set_file_open_expression(_get_file_open_expression());
    _my_clone->set_file_logical_name(_get_file_logical_name());
  }
  return _my_clone;
}

visitor_return_type *
IIRScram_FileDeclaration::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_FileDeclaration(this, arg);
}

IIRScram *
IIRScram_FileDeclaration::_get_file_open_expression() {
  return dynamic_cast<IIRScram *>(get_file_open_expression());
}

IIRScram *
IIRScram_FileDeclaration::_get_file_logical_name() {
  return dynamic_cast<IIRScram *>(get_file_logical_name());
}
