
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
#include "IIRBase_DesignFile.hh"
#include "IIRBase_LeftAttribute.hh"
#include "savant.hh"

IIRBase_LeftAttribute::IIRBase_LeftAttribute() {
  set_suffix(NULL);
}

IIRBase_LeftAttribute::~IIRBase_LeftAttribute() {}

void
IIRBase_LeftAttribute::set_suffix( IIR* suffix) {
  this->suffix = suffix;
}

IIR*
IIRBase_LeftAttribute::get_suffix() {
  return suffix;
}

IIR *
IIRBase_LeftAttribute::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_LeftAttribute *new_node = dynamic_cast<IIRBase_LeftAttribute *>(IIRBase_Attribute::convert_tree(factory));

  // Process the variables
  new_node->suffix = convert_node(suffix, factory);
  return new_node;
}

IIR_Boolean 
IIRBase_LeftAttribute::is_value_attribute(){
  ASSERT( is_resolved() );
  if( get_prefix()->is_scalar_type() ){
    ASSERT( get_suffix() == NULL );
    return TRUE;
  }
  else{
    ASSERT( get_prefix()->is_array_type() );
    return FALSE;
  }
}

IIR_Boolean 
IIRBase_LeftAttribute::is_function_attribute(){
  if( is_value_attribute() ){
    return FALSE;
  }
  else{
    return TRUE;
  }
}

IIR_TextLiteral *
IIRBase_LeftAttribute::build_attribute_name() {
  const char *name = "left";
  return IIRBase_Identifier::get( name, strlen(name), get_design_file()->get_class_factory());
}

void 
IIRBase_LeftAttribute::publish_vhdl(ostream &vhdl_out) {
  ASSERT(get_prefix() != NULL);

  get_prefix()->publish_vhdl(vhdl_out);
  vhdl_out << "'LEFT(";

  if (get_suffix() != NULL) {
    get_suffix()->publish_vhdl(vhdl_out);
  } else {
    vhdl_out << "1";
  }
  vhdl_out << ")";
}
