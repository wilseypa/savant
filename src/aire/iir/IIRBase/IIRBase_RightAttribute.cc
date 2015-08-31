
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
#include "IIRBase_RightAttribute.hh"
#include "savant.hh"

IIRBase_RightAttribute::IIRBase_RightAttribute() {
  my_suffix = NULL;
}

IIRBase_RightAttribute::~IIRBase_RightAttribute() {}

void
IIRBase_RightAttribute::set_suffix( IIR *suffix ){
  my_suffix = suffix;
}

IIR* 
IIRBase_RightAttribute::get_suffix() {
  return my_suffix;
}

IIR *
IIRBase_RightAttribute::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_RightAttribute *new_node = dynamic_cast<IIRBase_RightAttribute *>(IIRBase_Attribute::convert_tree(factory));

  // Process the variables
  new_node->my_suffix = convert_node(my_suffix, factory);

  return new_node;
}

IIR_Boolean 
IIRBase_RightAttribute::is_value_attribute(){
  ASSERT( is_resolved() == TRUE );
  if( get_prefix()->is_scalar_type() == TRUE ){
    ASSERT( get_suffix() == NULL );
    return TRUE;
  }
  else{
    ASSERT( get_prefix()->is_array_type() == TRUE );
    return FALSE;
  }
}

IIR_Boolean 
IIRBase_RightAttribute::is_function_attribute(){
  if( is_value_attribute() == TRUE ){
    return FALSE;
  }
  else{
    return TRUE;
  }
}

IIR_TextLiteral *
IIRBase_RightAttribute::build_attribute_name() {
  const char *name = "right";
  return IIRBase_Identifier::get( name, strlen(name), get_design_file()->get_class_factory());
}

void 
IIRBase_RightAttribute::publish_vhdl(ostream &vhdl_out) {
  ASSERT(get_prefix() != NULL);
  ASSERT(get_prefix()->is_resolved() == TRUE);

  get_prefix()->publish_vhdl(vhdl_out);
  vhdl_out << "'RIGHT(";

  if (get_suffix() != NULL) {
    get_suffix()->publish_vhdl(vhdl_out);
  } else {
    vhdl_out << "1";
  }
  vhdl_out << ") ";
}
