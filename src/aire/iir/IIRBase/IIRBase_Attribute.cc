
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

//---------------------------------------------------------------------------

#include "IIRBase_Attribute.hh"
#include "IIR_TypeDefinition.hh"
#include "IIR_TextLiteral.hh"
#include "error_func.hh"
#include <sstream>

IIRBase_Attribute::IIRBase_Attribute() {
  my_attribute_name = NULL;
}

IIRBase_Attribute::~IIRBase_Attribute(){}

void
IIRBase_Attribute::set_suffix(IIR *) {
  ostringstream err;
  err << "Internal error - IIRBase_Attribute::set_suffix called."
      << "The instantiated node"
      << " was a " << get_kind_text() << ", which apparently has no suffix.";
	
  report_error( this, err.str() );
  abort();
}

IIR_Boolean 
IIRBase_Attribute::is_resolved(){
  IIR_Boolean retval = TRUE;
  if( get_prefix()->is_resolved() == FALSE || 
      ( get_suffix() != NULL && get_suffix()->is_resolved() == FALSE ) ){
    retval = FALSE;
  }
  return retval;
}

IIR_Boolean 
IIRBase_Attribute::is_locally_static(){
  IIR_Boolean retval = false;

  ASSERT( get_prefix()->is_resolved() );
  if( is_value_attribute() &&
      get_kind() != IIR_USER_ATTRIBUTE && 
      get_kind() != IIR_PATH_NAME_ATTRIBUTE &&
      get_prefix()->is_locally_static() ){
    retval = true;
  }
  else if( is_function_attribute() ){
    switch( get_kind() ){
    case IIR_EVENT_ATTRIBUTE:
    case IIR_ACTIVE_ATTRIBUTE:
    case IIR_LAST_EVENT_ATTRIBUTE:
    case IIR_LAST_ACTIVE_ATTRIBUTE:
    case IIR_LAST_VALUE_ATTRIBUTE:
    case IIR_DRIVING_ATTRIBUTE:
    case IIR_DRIVING_VALUE_ATTRIBUTE:
      break;
    default:
      retval = true;
    }
    if( retval ){
      if( get_prefix()->is_type() ){
	retval = get_prefix()->is_locally_static();
      }
      else if( get_prefix()->is_object() ){
	retval = get_prefix()->get_subtype()->is_locally_static();
      }
      if( retval && get_suffix() ){
	retval = get_suffix()->is_locally_static();
      }
    }
  }
  return retval;
}

ostream &
IIRBase_Attribute::print( ostream &os ){
  get_prefix()->print( os );
  os << "'";
  IIR_TextLiteral *attribute_name = build_attribute_name();
  if( attribute_name != 0 ){
    os << *attribute_name;
    delete attribute_name;
  }

  if( get_suffix() != 0 ){
    os << "(" << *get_suffix() << ")";
  }

  return os;
}

IIR_TextLiteral *
IIRBase_Attribute::build_attribute_name(){
  _report_undefined_fn("build_attribute_name()");
  return NULL;
}

IIR_TextLiteral *
IIRBase_Attribute::get_attribute_name(){
  if( my_attribute_name == NULL ){
    my_attribute_name = build_attribute_name();
    copy_location( this, my_attribute_name );
  }
  
  return my_attribute_name;
}

IIR *
IIRBase_Attribute::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_Attribute *new_node = dynamic_cast<IIRBase_Attribute *>(IIRBase_Name::convert_tree(factory));

  // Process the variables
  new_node->my_attribute_name = dynamic_cast<IIR_TextLiteral *>(convert_node(my_attribute_name, factory));

  return new_node;
}
