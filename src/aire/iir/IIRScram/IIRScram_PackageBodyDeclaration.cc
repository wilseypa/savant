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
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_PackageBodyDeclaration.hh"
#include "IIRScram_DeclarationList.hh"
#include "IIRScram_Identifier.hh"

IIRScram_PackageBodyDeclaration::IIRScram_PackageBodyDeclaration(){
  set_package_declarative_part(new IIRScram_DeclarationList());
}

IIRScram_PackageBodyDeclaration::~IIRScram_PackageBodyDeclaration() {
  //Release the list memory
  delete get_package_declarative_part();
}

visitor_return_type *
IIRScram_PackageBodyDeclaration::_accept_visitor( node_visitor *visitor, 
						  visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_PackageBodyDeclaration(this, arg);
}

// IIRBase Function Wrapper(s)
IIRScram_DeclarationList *
IIRScram_PackageBodyDeclaration::_get_package_declarative_part() {
  return dynamic_cast<IIRScram_DeclarationList *>(get_package_declarative_part());
}
