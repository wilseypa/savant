
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

#include "savant.hh"
#include "IIRBase_ConcurrentBreakStatement.hh"
#include "IIR_BreakList.hh"
#include "IIR_DesignatorList.hh"
#include "IIR_Label.hh"

IIRBase_ConcurrentBreakStatement::IIRBase_ConcurrentBreakStatement() :
  concurrent_break_list(0),
  sensitivity_list(0),
  condition(0){}

IIRBase_ConcurrentBreakStatement::~IIRBase_ConcurrentBreakStatement(){
  delete concurrent_break_list;
  concurrent_break_list = 0;
  delete sensitivity_list;
  sensitivity_list = 0;
  delete condition;
  condition = 0;
}

void
IIRBase_ConcurrentBreakStatement::set_condition(IIR* condition){
  this->condition = condition;
}

IIR*
IIRBase_ConcurrentBreakStatement::get_condition(){
  return condition;
}

// List Accessor(s)
IIR_BreakList *
IIRBase_ConcurrentBreakStatement::get_concurrent_break_list() {
  ASSERT (concurrent_break_list != NULL);
  return concurrent_break_list;
}

void
IIRBase_ConcurrentBreakStatement::set_concurrent_break_list(IIR_BreakList * new_concurrent_break_list) {
  ASSERT (new_concurrent_break_list != NULL);

  if (concurrent_break_list != NULL)
    delete concurrent_break_list;

  concurrent_break_list = new_concurrent_break_list;
}

IIR_DesignatorList *
IIRBase_ConcurrentBreakStatement::get_sensitivity_list() {
  ASSERT (sensitivity_list != NULL);
  return sensitivity_list;
}

void
IIRBase_ConcurrentBreakStatement::set_sensitivity_list(IIR_DesignatorList * new_sensitivity_list) {
  ASSERT (new_sensitivity_list != NULL);

  if (sensitivity_list != NULL)
    delete sensitivity_list;

  sensitivity_list = new_sensitivity_list;
}


IIR *
IIRBase_ConcurrentBreakStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ConcurrentBreakStatement *new_node = dynamic_cast<IIRBase_ConcurrentBreakStatement *>(IIRBase_ConcurrentBreakStatement::convert_tree(factory));

  // Process the variables
  new_node->concurrent_break_list = dynamic_cast<IIR_BreakList *>(convert_node(concurrent_break_list,factory));
  new_node->sensitivity_list = dynamic_cast<IIR_DesignatorList *>(convert_node(sensitivity_list,factory));
  new_node->condition = convert_node(condition, factory);

  return new_node;
}

void
IIRBase_ConcurrentBreakStatement::publish_vhdl(ostream &vhdl_out) {
  if (get_label() != NULL ){
    get_label()->publish_vhdl(vhdl_out);
    vhdl_out << " : ";
  }
  vhdl_out << " break " ;
  if ( get_concurrent_break_list()->size() != 0 ) {
    get_concurrent_break_list()->publish_vhdl(vhdl_out);
  }
  if ( get_sensitivity_list()->size() != 0) {
    vhdl_out << " on ";
    get_sensitivity_list()->publish_vhdl(vhdl_out);
  }
  if ( get_condition() != NULL ) {
    vhdl_out << " when " ;
    get_condition()->publish_vhdl(vhdl_out);
  }
  vhdl_out << " ;\n" ;
}
