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
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_DesignFile.hh"
#include "IIRScram_VariableInterfaceDeclaration.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_AttributeSpecification.hh"
#include "IIRScram_AttributeSpecificationList.hh"

#include "error_func.hh"
#include "symbol_table.hh"
#include "savant.hh"

#include <sstream>
using std::ostringstream;

IIRScram_VariableInterfaceDeclaration::~IIRScram_VariableInterfaceDeclaration(){}

IIRScram*
IIRScram_VariableInterfaceDeclaration::_clone() {
  return this;
}

void 
IIRScram_VariableInterfaceDeclaration::_type_check( IIRScram_InterfaceDeclaration::_InterfaceListType ){
  IIRScram_InterfaceDeclaration::_type_check();
  if( get_mode() != IIR_IN_MODE && _get_value() != NULL ){
    ostringstream err;
    err << "Formal variable parameter |" << *_get_declarator() << "| has mode IN and "
	<< "therefore may not have a default expression.";
    report_error( this, err.str() );
  }
}

visitor_return_type *
IIRScram_VariableInterfaceDeclaration::_accept_visitor( node_visitor *visitor, 
							visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_VariableInterfaceDeclaration(this, arg);
}

