
// Copyright (c) 1996-1999 The University of Cincinnati.  
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

//---------------------------------------------------------------------------

#include "set.hh"
#include "IIR_ArchitectureStatementList.hh"
#include "IIR_GenericList.hh"
#include "IIR_AssociationList.hh"
#include "IIR_PortList.hh"
#include "IIRBase_DeclarationList.hh"
#include "IIR_Label.hh"
#include "IIR_SignalDeclaration.hh"
#include "IIRBase_BlockStatement.hh"

IIRBase_BlockStatement::IIRBase_BlockStatement() :
  generic_clause(0),
  generic_map_aspect(0),
  port_clause(0),
  port_map_aspect(0),
  block_declarative_part(0),
  block_statement_part(0),
  guard_expression(0),
  implicit_guard_signal(0){}

IIRBase_BlockStatement::~IIRBase_BlockStatement(){
  delete generic_clause;
  generic_clause = 0;
  delete generic_map_aspect;
  generic_map_aspect = 0;
  delete port_clause;
  port_clause = 0;
  delete port_map_aspect;
  port_map_aspect = 0;
  delete block_declarative_part;
  block_declarative_part = 0;
  delete block_statement_part;
  block_statement_part = 0;
  delete guard_expression;
  guard_expression = 0;
  delete implicit_guard_signal;
  implicit_guard_signal = 0;
}

void 
IIRBase_BlockStatement::set_guard_expression( IIR *new_guard_expression ){
  delete guard_expression;
  guard_expression = new_guard_expression;
}

IIR *
IIRBase_BlockStatement::get_guard_expression(){
  return guard_expression;
}

// List Accessor(s)
IIR_GenericList *
IIRBase_BlockStatement::get_generic_clause() {
  ASSERT(generic_clause != NULL);
  return generic_clause;
}

IIR_AssociationList *
IIRBase_BlockStatement::get_generic_map_aspect() {
  ASSERT(generic_map_aspect != NULL);
  return generic_map_aspect;
}

IIR_PortList *
IIRBase_BlockStatement::get_port_clause() {
  ASSERT(port_clause != NULL);
  return port_clause;
}

IIR_AssociationList *
IIRBase_BlockStatement::get_port_map_aspect() {
  ASSERT(port_map_aspect != NULL);
  return port_map_aspect;
}

IIR_DeclarationList *
IIRBase_BlockStatement::get_block_declarative_part() {
  ASSERT(block_declarative_part != NULL);
  return block_declarative_part;
}

IIR_ArchitectureStatementList *
IIRBase_BlockStatement::get_block_statement_part() {
  ASSERT(block_statement_part != NULL);
  return block_statement_part;
}

void
IIRBase_BlockStatement::set_generic_clause(IIR_GenericList *new_generic_clause) {
  ASSERT(new_generic_clause != NULL);
  delete generic_clause;
  generic_clause = new_generic_clause;
}

void
IIRBase_BlockStatement::set_generic_map_aspect(IIR_AssociationList *new_generic_map_aspect) {
  ASSERT(new_generic_map_aspect != NULL);
  delete generic_map_aspect;
  generic_map_aspect = new_generic_map_aspect;
}

void
IIRBase_BlockStatement::set_port_clause(IIR_PortList *new_port_clause) {
  ASSERT(new_port_clause != NULL);
  delete port_clause;
  port_clause = new_port_clause;
}

void
IIRBase_BlockStatement::set_port_map_aspect(IIR_AssociationList *new_port_map_aspect) {
  ASSERT(new_port_map_aspect != NULL);
  delete port_map_aspect;
  port_map_aspect = new_port_map_aspect;
}

void
IIRBase_BlockStatement::set_block_declarative_part(IIR_DeclarationList *new_block_declarative_part) {
  ASSERT(new_block_declarative_part != NULL);
  delete block_declarative_part;
  block_declarative_part = new_block_declarative_part;
}

void
IIRBase_BlockStatement::set_block_statement_part(IIR_ArchitectureStatementList *new_block_statement_part) {
  ASSERT(new_block_statement_part != NULL);
  delete block_statement_part;
  block_statement_part = new_block_statement_part;
}

IIR *
IIRBase_BlockStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_BlockStatement *new_node = dynamic_cast<IIRBase_BlockStatement *>(IIRBase_ConcurrentStatement::convert_tree(factory));

  // Process the variables
  new_node->generic_clause =
    dynamic_cast<IIR_GenericList *>(convert_node(generic_clause, factory));
  new_node->generic_map_aspect =
    dynamic_cast<IIR_AssociationList *>(convert_node(generic_map_aspect, factory));
  new_node->port_clause =
    dynamic_cast<IIR_PortList *>(convert_node(port_clause, factory));
  new_node->port_map_aspect =
    dynamic_cast<IIR_AssociationList *>(convert_node(port_map_aspect, factory));
  new_node->block_declarative_part =
    dynamic_cast<IIR_DeclarationList *>(convert_node(block_declarative_part, factory));
  new_node->block_statement_part =
    dynamic_cast<IIR_ArchitectureStatementList *>(convert_node(block_statement_part, factory));
  new_node->guard_expression =
    convert_node(guard_expression, factory);
  new_node->implicit_guard_signal =
    dynamic_cast<IIR_SignalDeclaration *>(convert_node(implicit_guard_signal, factory));

  return new_node;
}

void 
IIRBase_BlockStatement::set_implicit_guard_signal(IIR_SignalDeclaration *new_implicit_guard_signal ){
  implicit_guard_signal = new_implicit_guard_signal;
}

IIR_SignalDeclaration *
IIRBase_BlockStatement::get_implicit_guard_signal(  ){
  return implicit_guard_signal;
}

savant::set<IIR_Declaration> *
IIRBase_BlockStatement::find_declarations( IIR_Name *to_find){
  savant::set<IIR_Declaration> *retval = new savant::set<IIR_Declaration>;
  
  savant::set<IIR_Declaration> *current_set = get_port_clause()->find_declarations(to_find );
  
  if( current_set != NULL ){
    retval->add( current_set );
    delete current_set;
  }

  current_set = get_generic_clause()->find_declarations(to_find );
  if( current_set != NULL ){
    retval->add( current_set );
    delete current_set;
  }

  current_set = get_block_declarative_part()->find_declarations(to_find );
  if( current_set != NULL ){
    retval->add( current_set );
    delete current_set;
  }

  if( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }

  return retval;
}

void 
IIRBase_BlockStatement::publish_vhdl(ostream &vhdl_out) {

  publish_vhdl_stmt_label(vhdl_out);

  vhdl_out << "  block ";
  if( get_guard_expression() != NULL) {
    vhdl_out << "(";
    get_guard_expression()->publish_vhdl(vhdl_out);
    vhdl_out << ")";
    vhdl_out << " is\n";
  }

  if(get_generic_clause()->size() != 0) {
    vhdl_out << "   generic ( ";
    get_generic_clause()->publish_vhdl(vhdl_out);
    vhdl_out << " );\n";

    if(get_generic_map_aspect()->size() != 0) {
      vhdl_out << "   generic map ( ";
      get_generic_map_aspect()->publish_vhdl(vhdl_out);
      vhdl_out << " );\n";
    }
  }

  if(get_port_clause()->size() != 0) {
    vhdl_out << "   port ( ";
    get_port_clause()->publish_vhdl(vhdl_out);
    vhdl_out << " );\n";

    if(get_port_map_aspect()->size() != 0) {
      vhdl_out << "   port map ( ";
      get_port_map_aspect()->publish_vhdl(vhdl_out);
      vhdl_out << " );\n";
    }
  }

  dynamic_cast<IIRBase_DeclarationList *>
    (get_block_declarative_part())->publish_vhdl_decl(vhdl_out);

  vhdl_out << " begin\n";
  get_block_statement_part()->publish_vhdl(vhdl_out);
  vhdl_out << " end block ";

  if (get_label() != NULL) {
    get_label()->publish_vhdl(vhdl_out);
  }  
  vhdl_out << ";\n";
}
