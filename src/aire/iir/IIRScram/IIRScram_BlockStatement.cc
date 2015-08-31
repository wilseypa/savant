
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
//          Krishnan Subramani  
//          Narayanan Thondugulam
//          Swaminathan Subramanian
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_BlockStatement.hh"
#include "IIRScram_ArchitectureStatementList.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_DeclarationList.hh"
#include "IIRScram_GenericList.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_PortList.hh"
#include "IIRScram_SignalDeclaration.hh"

#include "set.hh"
#include "resolution_func.hh"
#include "symbol_table.hh"

IIRScram_BlockStatement::IIRScram_BlockStatement() {
  set_generic_clause(new IIRScram_GenericList());
  set_generic_map_aspect(new IIRScram_AssociationList());
  set_port_clause(new IIRScram_PortList());
  set_port_map_aspect(new IIRScram_AssociationList());
  set_block_declarative_part(new IIRScram_DeclarationList());
  set_block_statement_part(new IIRScram_ArchitectureStatementList());
  my_implicit_guard_signal = NULL;
}

IIRScram_BlockStatement::~IIRScram_BlockStatement() {
  //Release the list memory
  delete get_generic_clause();
  delete get_generic_map_aspect();
  delete get_port_clause();
  delete get_port_map_aspect();
  delete get_block_declarative_part();
  delete get_block_statement_part();
}

IIRScram_SignalDeclaration *
IIRScram_BlockStatement::_get_implicit_guard_signal(  ){
  return dynamic_cast<IIRScram_SignalDeclaration *>(get_implicit_guard_signal());
}

IIRScram_GenericList *
IIRScram_BlockStatement::_get_generic_list(){
  return dynamic_cast<IIRScram_GenericList *>(get_generic_clause());
}

void 
IIRScram_BlockStatement::_type_check(){

  // Things we need to check...
  // if we have a guard expression, it must be boolean valued.
  if( _get_guard_expression() != NULL ){
    set_guard_expression( _type_check_and_resolve_boolean_condition( _get_guard_expression()) );

    // Now that we've resolved this, we'll set the default value of the implicit signal to
    // the resolved expression.
    _get_implicit_guard_signal()->IIRBase_SignalDeclaration::set_value( _get_guard_expression() );
  }
  
#ifdef DEVELOPER_ASSERTIONS
  if( _get_guard_expression() == NULL ){
    ASSERT( _get_implicit_guard_signal() == NULL );
  }
  else{
    ASSERT( _get_implicit_guard_signal() != NULL );
  }
#endif

  // We need to type check the port map and generic map if they have stuff in them.
  _get_generic_map_aspect()->_resolve_and_order( _get_generic_clause(), NULL, this);
  _get_port_map_aspect()->_resolve_and_order( _get_port_clause(), NULL, this);  

  _get_symbol_table()->open_scope( this );
  _make_interface_visible(_get_symbol_table() );
  _get_block_declarative_part()->_type_check_disconnection_specifications();
  _get_block_declarative_part()->_type_check_configuration_specifications( _get_block_statement_part() );
  _get_block_declarative_part()->_type_check_attribute_specifications( _get_block_statement_part() );
  _get_symbol_table()->close_scope( this );
}

void 
IIRScram_BlockStatement::_type_check_instantiate_statements(){ 
  _get_symbol_table()->open_scope( this );
  _make_interface_visible( _get_symbol_table() );
  _get_block_statement_part()->_type_check_instantiate_statements();
  _get_symbol_table()->close_scope( this );
}

void 
IIRScram_BlockStatement::_make_interface_visible( symbol_table *sym_tab ){
  sym_tab->make_visible( _get_generic_clause() );
  sym_tab->make_visible( _get_port_clause() );
  sym_tab->make_visible( _get_block_declarative_part() );
  _get_block_statement_part()->_make_interface_visible( sym_tab );
}

visitor_return_type *
IIRScram_BlockStatement::_accept_visitor( node_visitor *visitor, 
					  visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_BlockStatement(this, arg);
}

IIRScram_PortList *
IIRScram_BlockStatement::_get_port_clause() {
  return dynamic_cast<IIRScram_PortList *>(get_port_clause());
}

IIRScram_DeclarationList *
IIRScram_BlockStatement::_get_block_declarative_part() {
  return dynamic_cast<IIRScram_DeclarationList *>(get_block_declarative_part());
}

IIRScram_List *
IIRScram_BlockStatement::_get_statement_list(){
  return dynamic_cast<IIRScram_List *>(get_block_statement_part());
}

IIRScram_AssociationList *
IIRScram_BlockStatement::_get_generic_map_aspect() {
  return dynamic_cast<IIRScram_AssociationList *>(get_generic_map_aspect());
}

IIRScram_AssociationList *
IIRScram_BlockStatement::_get_port_map_aspect() {
  return dynamic_cast<IIRScram_AssociationList *>(get_port_map_aspect());
}

IIRScram *
IIRScram_BlockStatement::_get_guard_expression() {
  return dynamic_cast<IIRScram *>(get_guard_expression());
}

IIRScram_GenericList *
IIRScram_BlockStatement::_get_generic_clause() {
  return dynamic_cast<IIRScram_GenericList *>(get_generic_clause());
}

IIRScram_ArchitectureStatementList *
IIRScram_BlockStatement::_get_block_statement_part() {
  return dynamic_cast<IIRScram_ArchitectureStatementList *>(get_block_statement_part());
}
