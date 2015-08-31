
// Copyright (c) 2003 The University of Cincinnati.
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

// Authors: Sivakumar Gowrisankar             gowriss@ececs.uc.edu
//          Kathiresan Nellayappan
//          Vasudevan Shanmugasundaram

//---------------------------------------------------------------------------

#include "savant.hh"
#include "IIRBase_SimpleSimultaneousStatement.hh"
#include "IIR_Label.hh"

IIRBase_SimpleSimultaneousStatement::IIRBase_SimpleSimultaneousStatement() :
  left_expression(0),
  right_expression(0),
  purity(IIR_PURE_FUNCTION),
  tolerance_aspect(0){}

IIRBase_SimpleSimultaneousStatement::~IIRBase_SimpleSimultaneousStatement(){
  delete left_expression;
  left_expression = 0;
  delete right_expression;
  right_expression = 0;
  delete tolerance_aspect;
  tolerance_aspect = 0;
}

void
IIRBase_SimpleSimultaneousStatement::set_left_expression(IIR* my_left_expression){
  left_expression = my_left_expression;
}

void
IIRBase_SimpleSimultaneousStatement::set_right_expression(IIR* my_right_expression){
  right_expression = my_right_expression;
}

IIR*
IIRBase_SimpleSimultaneousStatement::get_left_expression(){
  return left_expression;
}

IIR*
IIRBase_SimpleSimultaneousStatement::get_right_expression(){
  return right_expression;
}

void
IIRBase_SimpleSimultaneousStatement::set_pure(IIR_Pure my_purity) {
  purity = my_purity;
}

IIR_Pure
IIRBase_SimpleSimultaneousStatement::get_pure() {
  return purity;
}

void 
IIRBase_SimpleSimultaneousStatement::set_tolerance_aspect(IIR* my_tolerance) {
  tolerance_aspect = my_tolerance;
}

IIR*
IIRBase_SimpleSimultaneousStatement::get_tolerance_aspect() {
  return tolerance_aspect;
}

IIR *
IIRBase_SimpleSimultaneousStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_SimpleSimultaneousStatement *new_node = dynamic_cast<IIRBase_SimpleSimultaneousStatement *>(IIRBase_SimultaneousStatement::convert_tree(factory));

  // Process the variables
  new_node->purity = purity;
  new_node->left_expression = convert_node(left_expression, factory);
  new_node->right_expression = convert_node(right_expression, factory);
  new_node->tolerance_aspect = convert_node(tolerance_aspect, factory);

  return new_node;
}

void
IIRBase_SimpleSimultaneousStatement::publish_vhdl(ostream &vhdl_out) {
  if( get_label() != NULL ){
    get_label()->publish_vhdl(vhdl_out);
    vhdl_out << " : ";
  }
  get_left_expression()->publish_vhdl(vhdl_out);
  vhdl_out << " == ";
  get_right_expression()->publish_vhdl(vhdl_out);
  vhdl_out << " ;\n";
}
