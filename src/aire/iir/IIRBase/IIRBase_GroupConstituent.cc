
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

#include "IIRBase_GroupConstituent.hh"
#include "savant.hh"

IIRBase_GroupConstituent::IIRBase_GroupConstituent() {
  set_name(NULL);
}

IIRBase_GroupConstituent::~IIRBase_GroupConstituent() {}

void
IIRBase_GroupConstituent::set_name( IIR* name) {
  this->name = name;
}

IIR*
IIRBase_GroupConstituent::get_name() {
  return name;
}

IIR *
IIRBase_GroupConstituent::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_GroupConstituent *new_node = dynamic_cast<IIRBase_GroupConstituent *>(IIRBase_Tuple::convert_tree(factory));

  // Process the variables
  new_node->name = convert_node(name, factory);

  return new_node;
}

void 
IIRBase_GroupConstituent::publish_vhdl(ostream &vhdl_out) {
  dynamic_cast<IIRBase *>(get_name())->publish_vhdl(vhdl_out);
}
