
// Copyright (c) 2002-2003 The University of Cincinnati.
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

// Authors: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------

#include "savant.hh"
#include "IIR_ArchitectureStatementList.hh"
#include "IIR_SimultaneousElsif.hh"
#include "IIRBase_SimultaneousElsif.hh"

IIRBase_SimultaneousElsif::IIRBase_SimultaneousElsif() :
  then_sequence_of_statements(0)
{
  set_condition(NULL);
  set_else_clause(NULL);
}

IIRBase_SimultaneousElsif::~IIRBase_SimultaneousElsif() {
   delete condition;
   delete else_clause;
}

void
IIRBase_SimultaneousElsif::set_condition( IIR *new_condition ){
  condition = new_condition;
}

IIR*
IIRBase_SimultaneousElsif::get_condition() {
  return condition;
}

void
IIRBase_SimultaneousElsif::set_else_clause( IIR_SimultaneousElsif *new_else_clause ){
  else_clause = new_else_clause;
}

IIR_SimultaneousElsif*
IIRBase_SimultaneousElsif::get_else_clause() {
  return else_clause;
}

// List Accessor
IIR_ArchitectureStatementList *
IIRBase_SimultaneousElsif::get_then_sequence_of_statements() {
  ASSERT(then_sequence_of_statements != NULL);
  return then_sequence_of_statements;
}

void                          
IIRBase_SimultaneousElsif::set_then_sequence_of_statements(IIR_ArchitectureStatementList *new_list) {
  ASSERT(new_list != NULL);

  if (then_sequence_of_statements != NULL)
    delete then_sequence_of_statements;

  then_sequence_of_statements = new_list;
}

IIR *
IIRBase_SimultaneousElsif::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_SimultaneousElsif *new_node = dynamic_cast<IIRBase_SimultaneousElsif *>(IIRBase_Tuple::convert_tree(factory));

  // Process the variables
  new_node->condition = convert_node(condition, factory);
  new_node->else_clause = dynamic_cast<IIR_SimultaneousElsif *>(convert_node(else_clause, factory));

  new_node->then_sequence_of_statements = dynamic_cast<IIR_ArchitectureStatementList *>(then_sequence_of_statements->convert_tree(factory));

  return new_node;
}

void
IIRBase_SimultaneousElsif::publish_vhdl(ostream &vhdl_out) {
  vhdl_out << " elsif ";
  get_condition()->publish_vhdl(vhdl_out);
  vhdl_out << " use\n";
  if(get_then_sequence_of_statements()->size() != 0) {
    get_then_sequence_of_statements()->publish_vhdl(vhdl_out);
  }
  if (get_else_clause() != NULL) {
    get_else_clause()->publish_vhdl(vhdl_out);
  }
}
