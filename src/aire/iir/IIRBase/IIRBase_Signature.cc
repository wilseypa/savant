
// Copyright (c) 1996-2003 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
// NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S., and
// the terms of this license.

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2, June
// 1991. A copy of this license agreement can be found in the file "LGPL",
// distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     

//---------------------------------------------------------------------------





#include "savant.hh"
#include "IIRBase_Signature.hh"
#include "IIR_DesignatorList.hh"

IIRBase_Signature::IIRBase_Signature()  :
  argument_type_list(0) {
  set_return_type(NULL);
}

IIRBase_Signature::~IIRBase_Signature() {
}

void
IIRBase_Signature:: set_return_type( IIR_TypeDefinition* return_type) {
  this->return_type = return_type;
}

IIR_TypeDefinition*
IIRBase_Signature::get_return_type() {
  return return_type;
}

// List Accessor(s)
IIR_DesignatorList *
IIRBase_Signature::get_argument_type_list() {
  ASSERT(argument_type_list != NULL);
  return argument_type_list;
}


void
IIRBase_Signature::set_argument_type_list(IIR_DesignatorList *new_argument_type_list) {
  ASSERT(new_argument_type_list != NULL);
  delete argument_type_list;
  argument_type_list = new_argument_type_list;
}

IIR *
IIRBase_Signature::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_Signature *new_node = dynamic_cast<IIRBase_Signature *>(IIRBase_TypeDefinition::convert_tree(factory));

  // Process the variables
  new_node->argument_type_list = dynamic_cast<IIR_DesignatorList *>(convert_node(argument_type_list, factory));
  new_node->return_type = dynamic_cast<IIR_TypeDefinition *>(convert_node(return_type, factory));

  return new_node;
}

void 
IIRBase_Signature::publish_vhdl(ostream &vhdl_out) {
  get_argument_type_list()->publish_vhdl(vhdl_out);
  vhdl_out << " return ";
  dynamic_cast<IIRBase_TypeDefinition *>(get_return_type())->publish_vhdl(vhdl_out);
}
