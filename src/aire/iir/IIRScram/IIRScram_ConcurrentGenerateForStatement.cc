
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
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_ConcurrentGenerateForStatement.hh"
#include "IIRScram_AliasDeclaration.hh"
#include "IIRScram_ArchitectureStatementList.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_BlockStatement.hh"
#include "IIRScram_ComponentDeclaration.hh"
#include "IIRScram_ComponentInstantiationStatement.hh"
#include "IIRScram_ConfigurationSpecification.hh"
#include "IIRScram_ConstantDeclaration.hh"
#include "IIRScram_DeclarationList.hh"
#include "IIRScram_Designator.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EntityDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_LibraryDeclaration.hh"
#include "IIRScram_PortList.hh"
#include "IIRScram_ProcessStatement.hh"
#include "IIRScram_ScalarTypeDefinition.hh"
#include "IIRScram_SignalDeclaration.hh"
#include "symbol_table.hh"
#include "set.hh"


IIRScram_ConcurrentGenerateForStatement::IIRScram_ConcurrentGenerateForStatement(){
  set_block_declarative_part(new IIRScram_DeclarationList());
  set_concurrent_statement_part(new IIRScram_ArchitectureStatementList());
}

IIRScram_ConcurrentGenerateForStatement::~IIRScram_ConcurrentGenerateForStatement(){
  //Release the list memory
  delete get_block_declarative_part();
  delete get_concurrent_statement_part();
}

void 
IIRScram_ConcurrentGenerateForStatement::_type_check(){
  _get_block_declarative_part()->_type_check_attribute_specifications( _get_concurrent_statement_part() );
  ASSERT( get_generate_parameter_specification() != NULL );  
  _get_generate_parameter_specification()->set_subtype( _type_check_iteration_scheme( _get_generate_parameter_specification() ) );
}

void 
IIRScram_ConcurrentGenerateForStatement::_type_check_instantiate_statements(){
  // Put our declarations back into scope.
  ASSERT( _get_generate_parameter_specification() != NULL );
  _get_symbol_table()->open_scope( this );
  _get_symbol_table()->make_visible( _get_generate_parameter_specification() );
  _get_concurrent_statement_part()->_type_check_instantiate_statements();
  _get_symbol_table()->close_scope( this );
}

IIRScram_DeclarationList*
IIRScram_ConcurrentGenerateForStatement::_get_declaration_list() {
  return dynamic_cast<IIRScram_DeclarationList *>(get_block_declarative_part());
}

IIRScram_List *
IIRScram_ConcurrentGenerateForStatement::_get_statement_list() {
  return dynamic_cast<IIRScram_List *>(get_concurrent_statement_part());
}

IIRScram_ConstantDeclaration *
IIRScram_ConcurrentGenerateForStatement::_get_generate_parameter_specification() {
  return dynamic_cast<IIRScram_ConstantDeclaration *>(get_generate_parameter_specification());
}

IIRScram_DeclarationList *
IIRScram_ConcurrentGenerateForStatement::_get_block_declarative_part() {
  return dynamic_cast<IIRScram_DeclarationList *>(get_block_declarative_part());
}

IIRScram_ArchitectureStatementList *
IIRScram_ConcurrentGenerateForStatement::_get_concurrent_statement_part() {
  return dynamic_cast<IIRScram_ArchitectureStatementList *>(get_concurrent_statement_part());
}
IIRScram_Label *
IIRScram_ConcurrentGenerateForStatement::_find_instantiate_label( IIRScram_SimpleName *to_find ){
  return _get_concurrent_statement_part()->_find_instantiate_label( to_find );
}

visitor_return_type *
IIRScram_ConcurrentGenerateForStatement::_accept_visitor( node_visitor *visitor,
							  visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ConcurrentGenerateForStatement(this, arg);
}


