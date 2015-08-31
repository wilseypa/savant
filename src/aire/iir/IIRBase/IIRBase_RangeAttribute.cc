
// Copyright (c) The University of Cincinnati.  
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

#include "IIRBase_DesignFile.hh"
#include "IIRBase_Identifier.hh"
#include "IIRBase_RangeAttribute.hh"
#include "savant.hh"

IIRBase_RangeAttribute::IIRBase_RangeAttribute() {
  set_suffix(NULL);
}

IIRBase_RangeAttribute::~IIRBase_RangeAttribute() {}

void 
IIRBase_RangeAttribute::set_suffix( IIR* suffix) {
  this->suffix = suffix;
}

IIR* 
IIRBase_RangeAttribute::get_suffix() {
  return suffix;
}

IIR *
IIRBase_RangeAttribute::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_RangeAttribute *new_node = dynamic_cast<IIRBase_RangeAttribute *>(IIRBase_Attribute::convert_tree(factory));

  // Process the variables
  new_node->suffix = convert_node(suffix, factory);

  return new_node;
}

IIR_TextLiteral *
IIRBase_RangeAttribute::build_attribute_name() {
  const char *name = "range";
  return IIRBase_Identifier::get( name, strlen(name), get_design_file()->get_class_factory());
}

void 
IIRBase_RangeAttribute::publish_vhdl(ostream &vhdl_out) {
  ASSERT(get_prefix() != NULL);
  get_prefix()->publish_vhdl(vhdl_out);
  vhdl_out << "'RANGE ";
  if (get_suffix() != NULL) {
    vhdl_out << "(";
    get_suffix()->publish_vhdl(vhdl_out);
    vhdl_out << ")";
  }
}

void
IIRBase_RangeAttribute::publish_vhdl_range(ostream &vhdl_out) {
  publish_vhdl(vhdl_out);
}
