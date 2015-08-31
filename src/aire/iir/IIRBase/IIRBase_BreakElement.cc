
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





#include "IIR_Name.hh"
#include "IIRBase_BreakElement.hh"
#include "savant.hh"
 
IIRBase_BreakElement::IIRBase_BreakElement() {
  set_quantity_name(NULL);
  set_selector_quantity_name(NULL);
  set_expression(NULL);
}

IIRBase_BreakElement::~IIRBase_BreakElement() {}

void
IIRBase_BreakElement::set_quantity_name(IIR_Name* quantity_name) {
  this->quantity_name = quantity_name;
}

IIR_Name*
IIRBase_BreakElement::get_quantity_name() {
  return quantity_name;
}
void
IIRBase_BreakElement::set_expression(IIR* value) {
  this->value = value;
}

IIR*
IIRBase_BreakElement::get_expression() {
  return value;
}
 
void
IIRBase_BreakElement::set_selector_quantity_name(IIR_Name* selector_quantity_name) {
  this->selector_quantity_name = selector_quantity_name;
}
  
IIR_Name*
IIRBase_BreakElement::get_selector_quantity_name() {
  return selector_quantity_name;
}

IIR *
IIRBase_BreakElement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_BreakElement *new_node = dynamic_cast<IIRBase_BreakElement *>(IIRBase_Tuple::convert_tree(factory));

  // Process the variables
  new_node->quantity_name = dynamic_cast<IIR_Name *>(convert_node(quantity_name, factory));
  new_node->selector_quantity_name = dynamic_cast<IIR_Name *>(convert_node(selector_quantity_name, factory));
  new_node->value = convert_node(value, factory);

  return new_node;
}

void
IIRBase_BreakElement::publish_vhdl(ostream &vhdl_out) {
  get_quantity_name()->publish_vhdl(vhdl_out);
  vhdl_out << " => " ;
  get_expression()->publish_vhdl(vhdl_out);
}  
