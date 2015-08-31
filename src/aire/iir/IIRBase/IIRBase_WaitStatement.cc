
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



#include "IIRBase_WaitStatement.hh"
#include "IIR_DesignatorList.hh"

IIRBase_WaitStatement::IIRBase_WaitStatement() :
  sensitivity_list(0),
  condition_clause(0),
  timeout_clause(0) {}

IIRBase_WaitStatement::~IIRBase_WaitStatement(){
  delete get_condition_clause();
  delete get_timeout_clause();
}

void 
IIRBase_WaitStatement::set_condition_clause( IIR *new_condition_clause) {
  condition_clause = new_condition_clause;
}

IIR *
IIRBase_WaitStatement::get_condition_clause(){
  return condition_clause;
}

void 
IIRBase_WaitStatement::set_timeout_clause( IIR *new_timeout_clause) {
  timeout_clause = new_timeout_clause;
}

IIR*
IIRBase_WaitStatement:: get_timeout_clause() {
  return timeout_clause;
}

// List Accessor(s)
IIR_DesignatorList *
IIRBase_WaitStatement::get_sensitivity_list() {
  ASSERT(sensitivity_list != NULL);
  return sensitivity_list;
}

void
IIRBase_WaitStatement::set_sensitivity_list(IIR_DesignatorList *new_sensitivity_list) {
  ASSERT(new_sensitivity_list != NULL);
  delete sensitivity_list;
  sensitivity_list = new_sensitivity_list;
}

IIR_Boolean
IIRBase_WaitStatement::is_above_attribute_found() {
  IIR_Boolean retval = FALSE;

  retval = retval || get_sensitivity_list()->is_above_attribute_found();

  if (get_condition_clause() != NULL) {
    retval = retval || get_condition_clause()->is_above_attribute_found();
  }

  return retval;
}

IIR *
IIRBase_WaitStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_WaitStatement *new_node = dynamic_cast<IIRBase_WaitStatement *>(IIRBase_SequentialStatement::convert_tree(factory));

  // Process the variables
  new_node->sensitivity_list = dynamic_cast<IIR_DesignatorList *>(convert_node(sensitivity_list, factory));
  new_node->condition_clause = convert_node(condition_clause, factory);
  new_node->timeout_clause = convert_node(timeout_clause, factory);

  return new_node;
}

void 
IIRBase_WaitStatement::publish_vhdl(ostream &vhdl_out) {

  publish_vhdl_stmt_label(vhdl_out);

  vhdl_out << "wait";
    
  if (get_sensitivity_list()->size() != 0) {
    vhdl_out << " on ";
    get_sensitivity_list()->publish_vhdl(vhdl_out);
  }
    
  if (get_condition_clause() != NULL) {
    vhdl_out << " until ";
    get_condition_clause()->publish_vhdl(vhdl_out);
  }
    
  if (get_timeout_clause() != NULL) {
    vhdl_out << " for ";
    get_timeout_clause()->publish_vhdl(vhdl_out);
  }
}
