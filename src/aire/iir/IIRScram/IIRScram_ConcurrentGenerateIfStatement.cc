
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
//          Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_ConcurrentGenerateIfStatement.hh"
#include "IIRScram_DeclarationList.hh"
#include "IIRScram_ArchitectureStatementList.hh"
#include "IIRScram_Label.hh"

IIRScram_ConcurrentGenerateIfStatement::IIRScram_ConcurrentGenerateIfStatement(){
  set_block_declarative_part(new IIRScram_DeclarationList());
  set_concurrent_statement_part(new IIRScram_ArchitectureStatementList());
}

IIRScram_ConcurrentGenerateIfStatement::~IIRScram_ConcurrentGenerateIfStatement(){
  //Release the list memory
  delete get_block_declarative_part();
  delete get_concurrent_statement_part();
}

void 
IIRScram_ConcurrentGenerateIfStatement::_type_check(){
  set_if_condition( _type_check_and_resolve_boolean_condition( _get_if_condition() ) );
  _get_block_declarative_part()->_type_check_attribute_specifications( _get_concurrent_statement_part() );
}

IIRScram_DeclarationList*
IIRScram_ConcurrentGenerateIfStatement::_get_declaration_list() {
  return dynamic_cast<IIRScram_DeclarationList *>(get_block_declarative_part());
}

IIRScram_Label *
IIRScram_ConcurrentGenerateIfStatement::_find_instantiate_label( IIRScram_SimpleName *to_find ){
  return _get_concurrent_statement_part()->_find_instantiate_label( to_find );
}
visitor_return_type *
IIRScram_ConcurrentGenerateIfStatement::_accept_visitor( node_visitor *visitor,
							 visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ConcurrentGenerateIfStatement(this, arg);
}

IIRScram_List *
IIRScram_ConcurrentGenerateIfStatement::_get_statement_list() {
  return dynamic_cast<IIRScram_List *>(get_concurrent_statement_part());
}

IIRScram *
IIRScram_ConcurrentGenerateIfStatement::_get_if_condition() {
  return dynamic_cast<IIRScram *>(get_if_condition());
}

IIRScram_DeclarationList *
IIRScram_ConcurrentGenerateIfStatement::_get_block_declarative_part() {
  return dynamic_cast<IIRScram_DeclarationList *>(get_block_declarative_part());
}

IIRScram_ArchitectureStatementList *
IIRScram_ConcurrentGenerateIfStatement::_get_concurrent_statement_part() {
  return dynamic_cast<IIRScram_ArchitectureStatementList *>(get_concurrent_statement_part());
}
