
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
#include "IIRBase_HighAttribute.hh"
#include "savant.hh"

IIRBase_HighAttribute::IIRBase_HighAttribute() {
  my_suffix = NULL;
}

IIRBase_HighAttribute::~IIRBase_HighAttribute() {}

void 
IIRBase_HighAttribute::set_suffix( IIR *suffix ){
  my_suffix = suffix;
}

IIR *
IIRBase_HighAttribute::get_suffix( ){
  return my_suffix;
}

IIR *
IIRBase_HighAttribute::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_HighAttribute *new_node = dynamic_cast<IIRBase_HighAttribute *>(IIRBase_Attribute::convert_tree(factory));

  // Process the variables
  new_node->my_suffix = convert_node(my_suffix, factory);
  return new_node;
}

IIR_Boolean 
IIRBase_HighAttribute::is_value_attribute(){
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
IIRBase_HighAttribute::is_function_attribute(){
  if( is_value_attribute() == TRUE ){
    return FALSE;
  }
  else{
    return TRUE;
  }
}

IIR_TextLiteral *
IIRBase_HighAttribute::build_attribute_name() {
  const char *name = "high";
  return IIRBase_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() );
}

void 
IIRBase_HighAttribute::publish_vhdl(ostream &vhdl_out) {
  ASSERT(get_prefix() != NULL);
  ASSERT(get_prefix()->is_resolved() == TRUE);
  get_prefix()->publish_vhdl(vhdl_out);
  vhdl_out << "'HIGH(";
  if(get_suffix() != NULL) {
    ASSERT(get_suffix()->is_resolved() == TRUE);
    get_suffix()->publish_vhdl(vhdl_out);
  } else {
    vhdl_out << "1";
  }
  vhdl_out << ")";
}
