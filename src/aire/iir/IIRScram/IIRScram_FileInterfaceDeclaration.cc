
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

#include "IIRScram_FileInterfaceDeclaration.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_AttributeSpecification.hh"
#include "IIRScram_AttributeSpecificationList.hh"
#include "error_func.hh"
#include <sstream>
using std::ostringstream;

void
IIRScram_FileInterfaceDeclaration::_type_check(IIRScram_InterfaceDeclaration::_InterfaceListType ){
  if( dynamic_cast<IIRScram_TypeDefinition *>(IIRBase_ObjectDeclaration::get_subtype())->is_file_type() == FALSE ){
    ostringstream err;
    err << "File interface declaration |" << *_get_declarator() << "| must have a subtype "
	<< "indication that defines a subtype that is a file type.";
    report_error( this, err.str() );
  }

  IIRScram_InterfaceDeclaration::_type_check();
}

visitor_return_type *IIRScram_FileInterfaceDeclaration::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_FileInterfaceDeclaration(this, arg);
};
