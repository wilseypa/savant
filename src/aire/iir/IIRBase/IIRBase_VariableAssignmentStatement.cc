
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
#include "IIRBase_VariableAssignmentStatement.hh"
#include "IIR.hh"

IIRBase_VariableAssignmentStatement::IIRBase_VariableAssignmentStatement() {
  target = NULL;
  rhsexpression  = NULL;
}

IIRBase_VariableAssignmentStatement::~IIRBase_VariableAssignmentStatement() {
  delete get_target();
  delete get_expression();
}

void
IIRBase_VariableAssignmentStatement::set_target( IIR *new_target ){
  target = new_target;
}

IIR *
IIRBase_VariableAssignmentStatement::get_target() {
  return target;
}

void
IIRBase_VariableAssignmentStatement::set_expression( IIR *new_expression ){
  rhsexpression = new_expression;
}

IIR *
IIRBase_VariableAssignmentStatement::get_expression(){
  return rhsexpression;
}

IIR_Boolean
IIRBase_VariableAssignmentStatement::is_above_attribute_found() {
  ASSERT(get_expression() != NULL);
  return get_expression()->is_above_attribute_found();
}

IIR *
IIRBase_VariableAssignmentStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_VariableAssignmentStatement *new_node = dynamic_cast<IIRBase_VariableAssignmentStatement *>(IIRBase_SequentialStatement::convert_tree(factory));

  // Process the variables
  new_node->target = convert_node(target, factory);
  new_node->rhsexpression = convert_node(rhsexpression, factory);

  return new_node;
}

void
IIRBase_VariableAssignmentStatement::publish_vhdl(ostream &vhdl_out) {

  publish_vhdl_stmt_label(vhdl_out);
    
  get_target()->publish_vhdl(vhdl_out);
  vhdl_out << " := ";
  if (get_expression()->get_kind() == IIR_ASSOCIATION_ELEMENT_BY_EXPRESSION) {
    vhdl_out << "(";
  }
  get_expression()->publish_vhdl(vhdl_out);
  if (get_expression()->get_kind() == IIR_ASSOCIATION_ELEMENT_BY_EXPRESSION) {
    vhdl_out << ")";
  }
}
