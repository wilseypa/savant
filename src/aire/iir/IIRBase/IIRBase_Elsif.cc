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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu

//---------------------------------------------------------------------------


#include "savant.hh"
#include "IIRBase_Elsif.hh"
#include "IIR_SequentialStatementList.hh"
#include "IIR_Elsif.hh"

IIRBase_Elsif::IIRBase_Elsif()  :
  then_sequence_of_statements(0) {
  set_condition(NULL);
  set_else_clause(NULL);
}

IIRBase_Elsif::~IIRBase_Elsif() {
  if (condition != NULL) { delete condition;} 

  if (else_clause != NULL) { delete else_clause; }
}

void
IIRBase_Elsif::set_condition( IIR* condition) {
  this->condition = condition;
}

IIR*
IIRBase_Elsif::get_condition() {
  return condition;
}

void
IIRBase_Elsif::set_else_clause( IIR_Elsif* else_clause) {
  this->else_clause = else_clause;
}

IIR_Elsif*
IIRBase_Elsif::get_else_clause() {
  return else_clause;
}


// List Accessor(s)
IIR_SequentialStatementList *
IIRBase_Elsif::get_then_sequence_of_statements() {
  ASSERT(then_sequence_of_statements != NULL);
  return then_sequence_of_statements;
}


void
IIRBase_Elsif::set_then_sequence_of_statements(IIR_SequentialStatementList *new_then_sequence_of_statements) {
  ASSERT(new_then_sequence_of_statements != NULL);
  delete then_sequence_of_statements;
  then_sequence_of_statements = new_then_sequence_of_statements;
}

IIR *
IIRBase_Elsif::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_Elsif *new_node = dynamic_cast<IIRBase_Elsif *>(IIRBase_Tuple::convert_tree(factory));

  // Process the variables
  new_node->then_sequence_of_statements = dynamic_cast<IIR_SequentialStatementList *>(convert_node(then_sequence_of_statements, factory));
  new_node->condition = convert_node(condition, factory);
  new_node->else_clause = dynamic_cast<IIR_Elsif *>(convert_node(else_clause, factory));

  return new_node;
}

void 
IIRBase_Elsif::publish_vhdl(ostream &vhdl_out) {
  ASSERT(get_condition()->is_resolved() == TRUE);

  vhdl_out << "elsif ";
  get_condition()->publish_vhdl(vhdl_out);
    
  vhdl_out << " then\n";
    
  if (get_then_sequence_of_statements()->size() != 0) {
    get_then_sequence_of_statements()->publish_vhdl(vhdl_out);
  }
    
  if (get_else_clause() != NULL) {
    get_else_clause()->publish_vhdl(vhdl_out);
  }
}
