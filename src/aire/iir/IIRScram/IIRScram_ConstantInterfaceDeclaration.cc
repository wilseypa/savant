
// Copyright (c) 1996-2003 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
// DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     
//          Krishnan Subramani  
//          Narayanan Thondugulam
//          Timothy J. McBrayer 
//	    Magnus Danielson	cfmd@swipnet.se
//---------------------------------------------------------------------------

#include "IIRScram_ConstantInterfaceDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_TypeDefinition.hh"
#include "error_func.hh"
#include "set.hh"

#include <sstream>
using std::ostringstream;

IIRScram_ConstantInterfaceDeclaration::~IIRScram_ConstantInterfaceDeclaration(){}

IIR_Boolean
IIRScram_ConstantInterfaceDeclaration::is_locally_static_primary(){
  return false;
}

IIRScram *
IIRScram_ConstantInterfaceDeclaration::_clone() {
  return this;
}

void 
IIRScram_ConstantInterfaceDeclaration::_type_check( IIRScram_InterfaceDeclaration::_InterfaceListType ){
  if( _get_subtype()->is_access_type() == TRUE || _get_subtype()->is_file_type() == TRUE ){
    ostringstream err;
    err << "Constant interface declaration |" << *_get_declarator() << "| must have a subtype "
	<< "indication that defines a subtype that is neither an access type or a file type.";
    report_error( this, err.str() );
  }
  
  IIRScram_InterfaceDeclaration::_type_check();
}

visitor_return_type *
IIRScram_ConstantInterfaceDeclaration::_accept_visitor( node_visitor *visitor,
							visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ConstantInterfaceDeclaration(this, arg);
}

void
IIRScram_ConstantInterfaceDeclaration::_build_generic_parameter_set(savant::set<IIRScram_Declaration> *to_build) {
  to_build->add(this);
}

IIRScram *
IIRScram_ConstantInterfaceDeclaration::_get_value() {
  return dynamic_cast<IIRScram *>(IIRBase_InterfaceDeclaration::get_value());
}
