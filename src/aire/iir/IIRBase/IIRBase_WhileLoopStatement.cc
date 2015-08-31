
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
//          Malolan Chetlur     mal@ece.uc.edu
//---------------------------------------------------------------------------




#include "savant.hh"
#include "IIRBase_WhileLoopStatement.hh"
#include "IIR_SequentialStatementList.hh"

IIRBase_WhileLoopStatement::IIRBase_WhileLoopStatement()  :
  sequence_of_statements(0),
  while_condition(0) {}

IIRBase_WhileLoopStatement::~IIRBase_WhileLoopStatement() {
  delete get_while_condition();
}

void
IIRBase_WhileLoopStatement::set_while_condition( IIR *new_while_condition ){
  while_condition = new_while_condition;
}

IIR *
IIRBase_WhileLoopStatement::get_while_condition() {
  return while_condition;
}

IIR_Boolean
IIRBase_WhileLoopStatement::is_above_attribute_found() {
  IIR_Boolean retval = FALSE;
  if(get_while_condition() != NULL) {
    retval = retval || get_while_condition()->is_above_attribute_found();
  }
  retval = retval || get_sequence_of_statements()->is_above_attribute_found();
  return retval;
}

// List Accessor(s)
IIR_SequentialStatementList *
IIRBase_WhileLoopStatement::get_sequence_of_statements() {
  ASSERT(sequence_of_statements != NULL);
  return sequence_of_statements;
}

void
IIRBase_WhileLoopStatement::set_sequence_of_statements(IIR_SequentialStatementList *new_sequence_of_statements) {
  ASSERT(new_sequence_of_statements != NULL);
  delete sequence_of_statements;
  sequence_of_statements = new_sequence_of_statements;
}

IIR *
IIRBase_WhileLoopStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_WhileLoopStatement *new_node = dynamic_cast<IIRBase_WhileLoopStatement *>(IIRBase_SequentialStatement::convert_tree(factory));

  // Process the variables
  new_node->sequence_of_statements = dynamic_cast<IIR_SequentialStatementList *>(convert_node(sequence_of_statements, factory));
  new_node->while_condition = convert_node(while_condition, factory);

  return new_node;
}

void
IIRBase_WhileLoopStatement::publish_vhdl(ostream &vhdl_out) {

  publish_vhdl_stmt_label(vhdl_out);

  if(get_while_condition() != NULL) {
    ASSERT(get_while_condition()->is_resolved() == TRUE);
    vhdl_out << "while ";
    get_while_condition()->publish_vhdl(vhdl_out);
    vhdl_out << "  ";
  }
    
  vhdl_out << "loop\n";

  if (get_sequence_of_statements()->size() != 0) {
    get_sequence_of_statements()->publish_vhdl(vhdl_out);
  }
  vhdl_out << "end loop";
}
