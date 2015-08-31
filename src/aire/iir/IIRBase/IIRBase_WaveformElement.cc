
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


#include "IIRBase_WaveformElement.hh"
#include "IIR.hh"

IIRBase_WaveformElement::IIRBase_WaveformElement() :
  value(0),
  time(0),
  next(0){}

IIRBase_WaveformElement::~IIRBase_WaveformElement() {
  delete get_value();
  delete get_time();
}

void
IIRBase_WaveformElement::set_value( IIR *new_value ){
  value = new_value;
}

IIR*
IIRBase_WaveformElement::get_value() {
  return value;
}

void
IIRBase_WaveformElement::set_time( IIR *new_time ){
  time = new_time;
}

IIR*
IIRBase_WaveformElement::get_time() {
  return time;
}

void
IIRBase_WaveformElement::set_next( IIR_WaveformElement *new_next ){
  next = new_next;
}

IIR_WaveformElement*
IIRBase_WaveformElement::get_next() {
  return next;
}

IIR_Boolean
IIRBase_WaveformElement::is_above_attribute_found() {
  ASSERT(get_value() != NULL);
  return get_value()->is_above_attribute_found();
}

IIR *
IIRBase_WaveformElement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_WaveformElement *new_node = dynamic_cast<IIRBase_WaveformElement *>(IIRBase_Tuple::convert_tree(factory));

  // Process the variables
  new_node->value = convert_node(value, factory);
  new_node->time = convert_node(time, factory);
  new_node->next = dynamic_cast<IIR_WaveformElement *>(convert_node(next, factory));

  return new_node;
}

IIR_Boolean 
IIRBase_WaveformElement::is_resolved(){
  IIR_Boolean retval = TRUE;

  if( get_value() != NULL && get_value()->is_resolved() == FALSE ){
    retval = FALSE;
  }

  if( get_time() != NULL && get_time()->is_resolved() == FALSE ){
    retval = FALSE;
  }

  return retval;
}

ostream &
IIRBase_WaveformElement::print( ostream &os ) {
  os << *get_value();

  if (get_time() != NULL) {
    os << " after ";
    os << *get_time();
    os << " ";
  }

  return os;
}

void 
IIRBase_WaveformElement::publish_vhdl(ostream &vhdl_out) {
  get_value()->publish_vhdl(vhdl_out);

  if (get_time() != NULL) {
    vhdl_out << " after ";
    get_time()->publish_vhdl(vhdl_out);
  }
}
