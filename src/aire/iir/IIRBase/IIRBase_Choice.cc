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

// Authors: Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRBase_Choice.hh"
#include "savant.hh"

IIRBase_Choice::IIRBase_Choice() {
  set_value(NULL); 
}

IIRBase_Choice::~IIRBase_Choice() {}

void
IIRBase_Choice::set_value( IIR *value ) {
  my_value = value;
}

IIR*
IIRBase_Choice::get_value() {
  return my_value;
}


IIR *
IIRBase_Choice::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_Choice *new_node = dynamic_cast<IIRBase_Choice *>(IIRBase_Tuple::convert_tree(factory));

  // Process the variables
  new_node->my_value = convert_node(my_value, factory);

  return new_node;
}

IIR_Boolean 
IIRBase_Choice::is_resolved(){
  return get_value()->is_resolved();
}

ostream &
IIRBase_Choice::print( ostream &os ){
  os << *get_value();
  return os;
}


void 
IIRBase_Choice::publish_vhdl(ostream &vhdl_out) {
  get_value()->publish_vhdl(vhdl_out);
}
