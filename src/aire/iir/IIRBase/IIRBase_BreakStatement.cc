
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

// Author: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------




#include "IIR_BreakList.hh"

#include "IIRBase_BreakStatement.hh"
#include "savant.hh"

IIRBase_BreakStatement::IIRBase_BreakStatement(){
  set_condition(NULL);
}

IIRBase_BreakStatement::~IIRBase_BreakStatement(){}

void
IIRBase_BreakStatement::set_condition(IIR* condition){
  this->condition = condition;
}

IIR*
IIRBase_BreakStatement::get_condition(){
  return condition;
}

// List Accessor(s)
IIR_BreakList *
IIRBase_BreakStatement::get_break_list() {
  ASSERT (break_list != NULL);
  return break_list;
}

void
IIRBase_BreakStatement::set_break_list(IIR_BreakList * new_break_list) {
  ASSERT (new_break_list != NULL);

  if (break_list != NULL)
    delete break_list;

  break_list = new_break_list;
}

IIR_Boolean
IIRBase_BreakStatement::is_above_attribute_found() {
  IIR_Boolean retval = FALSE;
  if(get_condition() != NULL) {
    retval = get_condition()->is_above_attribute_found();
  }
  return retval;
}


IIR *
IIRBase_BreakStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_BreakStatement *new_node = dynamic_cast<IIRBase_BreakStatement *>(IIRBase_SequentialStatement::convert_tree(factory));

  // Process the variables
  new_node->break_list = dynamic_cast<IIR_BreakList *>(convert_node(break_list, factory));
  new_node->condition = convert_node(condition, factory);

  return new_node;
}

void
IIRBase_BreakStatement::publish_vhdl(ostream &vhdl_out) {
  publish_vhdl_stmt_label(vhdl_out);
  vhdl_out << " break " ;
  if ( get_break_list()->size() != 0) {
    get_break_list()->publish_vhdl(vhdl_out);
  }
  if ( get_condition() != NULL ) {
    vhdl_out << " when " ;
    get_condition()->publish_vhdl(vhdl_out);
    vhdl_out << " \n" ;
  }
}
