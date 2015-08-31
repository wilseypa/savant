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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------





#include "savant.hh"
#include "IIRBase_IfStatement.hh"
#include "IIR_Elsif.hh"
#include "IIR_SequentialStatementList.hh"

IIRBase_IfStatement::IIRBase_IfStatement()  :
  then_sequence(0),
  else_sequence(0) {
  set_condition(NULL);
  set_elsif(NULL);
}


IIRBase_IfStatement::~IIRBase_IfStatement() {
  if (condition != 0) { 
    delete condition; 
  }

  if (elsif_clause != 0) { 
    delete elsif_clause;
  }
}


void
IIRBase_IfStatement::set_condition(IIR* condition) {
  this->condition = condition;
}


IIR*
IIRBase_IfStatement::get_condition() {
  return condition;
}


void
IIRBase_IfStatement::set_elsif(IIR_Elsif* elsif_clause) {
  this->elsif_clause = elsif_clause;
}


IIR_Elsif*
IIRBase_IfStatement::get_elsif() {
  return elsif_clause;
}

// List Accessor(s)
IIR_SequentialStatementList *
IIRBase_IfStatement::get_then_sequence() {
  ASSERT(then_sequence != NULL);
  return then_sequence;
}

IIR_SequentialStatementList *
IIRBase_IfStatement::get_else_sequence() {
  ASSERT(else_sequence != NULL);
  return else_sequence;
}

void
IIRBase_IfStatement::set_then_sequence(IIR_SequentialStatementList *new_then_sequence) {
  ASSERT(new_then_sequence != NULL);
  delete then_sequence;
  then_sequence = new_then_sequence;
}

void
IIRBase_IfStatement::set_else_sequence(IIR_SequentialStatementList *new_else_sequence) {
  ASSERT(new_else_sequence != NULL);
  delete else_sequence;
  else_sequence = new_else_sequence;
}

IIR_Boolean
IIRBase_IfStatement::is_above_attribute_found() {
  IIR_Boolean retval = FALSE;

  ASSERT(get_condition() != NULL);

  retval = retval || get_condition()->is_above_attribute_found();

  if (get_then_sequence()->num_elements() != 0) {
    retval = retval || get_then_sequence()->is_above_attribute_found();
  }
  if (get_elsif() != NULL) {
    retval = retval || get_elsif()->is_above_attribute_found();
  }
  if (get_else_sequence()->num_elements() != 0) {
    retval = retval || get_else_sequence()->is_above_attribute_found();
  }
  return retval;
}

IIR *
IIRBase_IfStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_IfStatement *new_node = dynamic_cast<IIRBase_IfStatement *>(IIRBase_SequentialStatement::convert_tree(factory));

  // Process the variables
  new_node->then_sequence = dynamic_cast<IIR_SequentialStatementList *>(convert_node(then_sequence, factory));
  new_node->else_sequence = dynamic_cast<IIR_SequentialStatementList *>(convert_node(else_sequence, factory));
  new_node->condition = convert_node(condition, factory);
  new_node->elsif_clause = dynamic_cast<IIR_Elsif *>(convert_node(elsif_clause, factory));

  return new_node;
}


void 
IIRBase_IfStatement::publish_vhdl(ostream &vhdl_out) {

  publish_vhdl_stmt_label(vhdl_out);
    
  vhdl_out << "if (";
  get_condition()->publish_vhdl(vhdl_out);
    
  vhdl_out << ") then\n";
    
  if (get_then_sequence()->size() != 0) {
    get_then_sequence()->publish_vhdl(vhdl_out);
  }
    
  if (get_elsif() != NULL) {
    get_elsif()->publish_vhdl(vhdl_out);
  }
    
  if (get_else_sequence()->size() != 0) {
    vhdl_out << " else\n";
    get_else_sequence()->publish_vhdl(vhdl_out);
  }
  vhdl_out << "end if";
}
