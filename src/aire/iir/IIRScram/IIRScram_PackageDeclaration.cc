
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
//          Timothy J. McBrayer 
//          Krishnan Subramani  
//          Narayanan Thondugulam
//          Malolan Chetlur     
//          Radharamanan Radhakrishnan
//          Swaminathan Subramanian
//	    Magnus Danielson	cfmd@swipnet.se
//---------------------------------------------------------------------------

#include "IIRScram_AttributeSpecification.hh"
#include "IIRScram_ConstantDeclaration.hh"
#include "IIRScram_DeclarationList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_FileDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_NatureDeclaration.hh"
#include "IIRScram_ObjectDeclaration.hh"
#include "IIRScram_PackageDeclaration.hh"
#include "IIRScram_TerminalDeclaration.hh"
#include "IIRScram_TypeDeclaration.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_ScalarNatureDefinition.hh"
#include "IIRScram_SequentialStatementList.hh"
#include "IIRScram_SubtypeDeclaration.hh"



#include "resolution_func.hh"
#include "symbol_table.hh"


IIRScram_PackageDeclaration::IIRScram_PackageDeclaration(){ 
  set_package_declarative_part(new IIRScram_DeclarationList());
}

IIRScram_PackageDeclaration::~IIRScram_PackageDeclaration() {
  //Release the list memory
  delete get_package_declarative_part();
}

void 
IIRScram_PackageDeclaration::_add_to_declarative_region( savant::set<IIRScram_Declaration> *set_to_add ){
  IIRScram_Declaration::_add_to_declarative_region( _get_package_declarative_part(), set_to_add );
}

void 
IIRScram_PackageDeclaration::_make_interface_visible( symbol_table *sym_tab ){
  ASSERT( sym_tab != NULL );

  sym_tab->make_visible( this );
  _get_context_items()->_make_visible_as_context_list( sym_tab );
  sym_tab->make_visible( _get_package_declarative_part() );
}

void 
IIRScram_PackageDeclaration::_type_check( ){
  _get_package_declarative_part()->_type_check_attribute_specifications( NULL );
  _get_package_declarative_part()->_type_check_configuration_specifications( NULL );
  _get_package_declarative_part()->_type_check_disconnection_specifications(  );
}

visitor_return_type *
IIRScram_PackageDeclaration::_accept_visitor( node_visitor *visitor,
					      visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_PackageDeclaration(this, arg);
}

// IIRBase Function Wrapper(s)
IIRScram_DeclarationList *
IIRScram_PackageDeclaration::_get_package_declarative_part() {
  return dynamic_cast<IIRScram_DeclarationList *>(get_package_declarative_part());
}

IIRScram_Declaration*
IIRScram_PackageDeclaration::_get_package_declaration() {
  return this;
}
