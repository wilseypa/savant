
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

#include "IIRBase_Identifier.hh"
#include "IIRBase_ImageAttribute.hh"
#include "IIR_ArraySubtypeDefinition.hh"
#include "IIR_DesignFile.hh"
#include "IIR_TypeDefinition.hh"
#include "savant.hh"
#include "StandardPackage.hh"

IIRBase_ImageAttribute::IIRBase_ImageAttribute() {
  my_suffix = NULL;
}

IIRBase_ImageAttribute::~IIRBase_ImageAttribute() {}

void
IIRBase_ImageAttribute::set_suffix( IIR *suffix ){
  my_suffix = suffix;
}

IIR *
IIRBase_ImageAttribute::get_suffix() {
  return my_suffix;
}

IIR *
IIRBase_ImageAttribute::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ImageAttribute *new_node = dynamic_cast<IIRBase_ImageAttribute *>(IIRBase_Attribute::convert_tree(factory));

  // Process the variables
  new_node->my_suffix = convert_node(my_suffix, factory);
  return new_node;
}

IIR_TypeDefinition *
IIRBase_ImageAttribute::get_subtype(){
  return get_design_file()->get_standard_package()->get_string_type();
}

IIR_TextLiteral *
IIRBase_ImageAttribute::build_attribute_name() {
  const char *name = "image";
  return IIRBase_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() );
}


void 
IIRBase_ImageAttribute::publish_vhdl(ostream &vhdl_out) {
  ASSERT(get_prefix() != NULL && get_suffix() != NULL);
  get_prefix()->publish_vhdl(vhdl_out);
  vhdl_out << "'IMAGE ";
  vhdl_out << "(";
  get_suffix()->publish_vhdl(vhdl_out);
  vhdl_out << ") ";
}
