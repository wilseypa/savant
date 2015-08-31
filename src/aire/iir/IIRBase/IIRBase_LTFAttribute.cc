
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
#include "IIRBase_LTFAttribute.hh"
#include "savant.hh"

IIRBase_LTFAttribute::IIRBase_LTFAttribute() {
  set_num(NULL);
  set_den(NULL);
}

IIRBase_LTFAttribute::~IIRBase_LTFAttribute() {}

void
IIRBase_LTFAttribute::set_num(IIR* numerator) {
  this->numerator = numerator;
}

IIR*
IIRBase_LTFAttribute::get_num() {
  return numerator;
}

void
IIRBase_LTFAttribute::set_den(IIR *denominator) {
  this->denominator = denominator;
}

IIR*
IIRBase_LTFAttribute::get_den() {
  return denominator;
}

IIR *
IIRBase_LTFAttribute::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_LTFAttribute *new_node = dynamic_cast<IIRBase_LTFAttribute *>(IIRBase_Attribute::convert_tree(factory));

  // Process the variables
  new_node->numerator = convert_node(numerator, factory);
  new_node->denominator = convert_node(denominator, factory);

  return new_node;
}

IIR_TextLiteral *
IIRBase_LTFAttribute::build_attribute_name() {
  const char *name = "ltf";
  return IIRBase_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() );
}

void
IIRBase_LTFAttribute::publish_vhdl(ostream& vhdl_out) {
  get_prefix()->publish_vhdl(vhdl_out);
  vhdl_out << "'LTF ( " ;
  get_num()->publish_vhdl(vhdl_out);
  vhdl_out << " , ";
  get_den()->publish_vhdl(vhdl_out);
  vhdl_out << " ) ";
}
