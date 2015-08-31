
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

#include "savant.hh"
#include "IIRBase_EnumerationLiteral.hh"
#include "IIRBase_TextLiteral.hh"
#include "IIR_AttributeSpecificationList.hh"

IIRBase_EnumerationLiteral::IIRBase_EnumerationLiteral() :
  attributes(0),
  my_position(0){}

IIRBase_EnumerationLiteral::~IIRBase_EnumerationLiteral(){
}

void 
IIRBase_EnumerationLiteral::set_position( IIR *position ){
  my_position = position;
}

IIR *
IIRBase_EnumerationLiteral::get_position(){
  return my_position;
}

// List Accessor(s)
IIR_AttributeSpecificationList *
IIRBase_EnumerationLiteral::get_attributes() {
  ASSERT(attributes != NULL);
  return attributes;
}

void
IIRBase_EnumerationLiteral::set_attributes(IIR_AttributeSpecificationList *new_attributes) {
  ASSERT(new_attributes != NULL);
  delete attributes;
  attributes = new_attributes;
}

IIR *
IIRBase_EnumerationLiteral::convert_tree(plugin_class_factory *factory) {
  // Get the node itself

  IIRBase_EnumerationLiteral *new_node = dynamic_cast<IIRBase_EnumerationLiteral *>(IIRBase_Declaration::convert_tree(factory));

  // Process the variables
  new_node->attributes = dynamic_cast<IIR_AttributeSpecificationList *>(convert_node(attributes, factory));
  new_node->my_position = convert_node(my_position, factory);

  return new_node;
}

IIR_Boolean
IIRBase_EnumerationLiteral::is_ascending_range() {
  if(IIRBase_TextLiteral::cmp(get_declarator(), "true") == 0) {
    return TRUE;		// Temporary solution -- SK.
  } 
  else if(IIRBase_TextLiteral::cmp(get_declarator(), "false") == 0) {
    return FALSE;
  } else {
    cerr << "Unknown enumeration literal " << *get_declarator() 
	 << " in IIRBase_EnumerationLiteral::"
	 << "_is_ascending_range()" << endl;
    abort();
    return FALSE;
  }
}

IIR_Boolean 
IIRBase_EnumerationLiteral::is_resolved(){
  if( get_subtype() == NULL ){
    return FALSE;
  }
  else{
    return TRUE;
  }
}

IIR_Declaration::declaration_type 
IIRBase_EnumerationLiteral::get_declaration_type() {
  return LITERAL;
}

// According to the LRM Section 13.5, a character literal is
//   character_literal ::= 'graphic_character'
IIR_Boolean 
IIRBase_EnumerationLiteral::is_character_literal() {
  IIR_TextLiteral *my_text_lit = get_declarator();

  if(my_text_lit->get_text_length() == 3 &&
     (*my_text_lit)[0] == '\'' && (*my_text_lit)[2] == '\'') {
    return TRUE;
  }
  return FALSE;
}

IIR_Boolean
IIRBase_EnumerationLiteral::is_locally_static(){
  return TRUE;
}

ostream &
IIRBase_EnumerationLiteral::print( ostream &os ){
  os << *get_declarator();

  return os;
}

void 
IIRBase_EnumerationLiteral::publish_vhdl(ostream &vhdl_out) {
  get_declarator()->publish_vhdl(vhdl_out);
}

void 
IIRBase_EnumerationLiteral::publish_vhdl_decl(ostream &vhdl_out) {
  publish_vhdl(vhdl_out);
}
