
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

#include "savant.hh"
#include "IIRBase_ConcurrentGenerateIfStatement.hh"
#include "IIR_ArchitectureStatementList.hh"
#include "IIRBase_DeclarationList.hh"
#include "IIR_Label.hh"

IIRBase_ConcurrentGenerateIfStatement::IIRBase_ConcurrentGenerateIfStatement() :
  block_declarative_part(0),
  concurrent_statement_part(0),
  condition(0){}

IIRBase_ConcurrentGenerateIfStatement::~IIRBase_ConcurrentGenerateIfStatement(){
  delete block_declarative_part;
  block_declarative_part = 0;
  delete concurrent_statement_part;
  concurrent_statement_part = 0;
  delete condition;
  condition = 0;
}

void 
IIRBase_ConcurrentGenerateIfStatement::set_if_condition( IIR *condition ){
  this->condition = condition;
}

IIR *
IIRBase_ConcurrentGenerateIfStatement::get_if_condition(){
  return condition;
}

// List Accessor(s)
IIR_DeclarationList *
IIRBase_ConcurrentGenerateIfStatement::get_block_declarative_part() {
  ASSERT(block_declarative_part != NULL);
  return block_declarative_part;
}

IIR_ArchitectureStatementList *
IIRBase_ConcurrentGenerateIfStatement::get_concurrent_statement_part() {
  ASSERT(concurrent_statement_part != NULL);
  return concurrent_statement_part;
}

void
IIRBase_ConcurrentGenerateIfStatement::set_block_declarative_part(IIR_DeclarationList *new_block_declarative_part) {
  ASSERT(new_block_declarative_part != NULL);
  block_declarative_part = new_block_declarative_part;
}

void
IIRBase_ConcurrentGenerateIfStatement::set_concurrent_statement_part(IIR_ArchitectureStatementList *new_concurrent_statement_part) {
  ASSERT(new_concurrent_statement_part != NULL);
  delete concurrent_statement_part;
  concurrent_statement_part = new_concurrent_statement_part;
}

IIR *
IIRBase_ConcurrentGenerateIfStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ConcurrentGenerateIfStatement *new_node = dynamic_cast<IIRBase_ConcurrentGenerateIfStatement *>(IIRBase_ConcurrentStatement::convert_tree(factory));

  // Process the variables
  new_node->block_declarative_part = dynamic_cast<IIR_DeclarationList *>(convert_node(block_declarative_part, factory));
  new_node->concurrent_statement_part = dynamic_cast<IIR_ArchitectureStatementList *>(convert_node(concurrent_statement_part, factory));
  new_node->condition = convert_node(condition, factory);

  return new_node;
}

void 
IIRBase_ConcurrentGenerateIfStatement::publish_vhdl(ostream &vhdl_out) {

  publish_vhdl_stmt_label(vhdl_out);

  vhdl_out << " if (";
  get_if_condition()->publish_vhdl(vhdl_out);
  vhdl_out << ") generate\n";

  if(get_block_declarative_part()->size() != 0) {
    dynamic_cast<IIRBase_DeclarationList *>(get_block_declarative_part())->publish_vhdl_decl(vhdl_out);
  }

  vhdl_out << "   begin\n";

  get_concurrent_statement_part()->publish_vhdl(vhdl_out);

  vhdl_out << "   end generate ";
  if(get_label() != NULL) {
    get_label()->publish_vhdl(vhdl_out);
  }
  vhdl_out << ";\n";

}
