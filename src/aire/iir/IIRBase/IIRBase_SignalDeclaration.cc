
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


#include "IIRBase_SignalDeclaration.hh"
#include "IIRBase_TextLiteral.hh"

#include "IIR_Attribute.hh"

#include "savant.hh"

IIRBase_SignalDeclaration::IIRBase_SignalDeclaration() {
  set_value(NULL);
  set_signal_kind(IIR_NO_SIGNAL_KIND);
}

IIRBase_SignalDeclaration::~IIRBase_SignalDeclaration() {}

void
IIRBase_SignalDeclaration::set_value( IIR *new_value ){
  value = new_value;
}

IIR*
IIRBase_SignalDeclaration::get_value() {
  return value;
}

void
IIRBase_SignalDeclaration::set_signal_kind( IIR_SignalKind new_signal_kind ){
  signal_kind = new_signal_kind;
}

IIR_SignalKind
IIRBase_SignalDeclaration::get_signal_kind() {
  return signal_kind;
}


IIR *
IIRBase_SignalDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_SignalDeclaration *new_node = dynamic_cast<IIRBase_SignalDeclaration *>(IIRBase_ObjectDeclaration::convert_tree(factory));

  // Process the variables
  new_node->value = convert_node(value, factory);
  new_node->signal_kind = signal_kind;

  return new_node;
}

IIR_Boolean
IIRBase_SignalDeclaration::is_guard_signal() {
  ASSERT ( get_declarator() != NULL );
  if (IIRBase_TextLiteral::cmp( get_declarator(), "guard") == 0) {
    return TRUE;
  }

  return FALSE;
}

IIR_Boolean
IIRBase_SignalDeclaration::is_above_attribute_found() {
  if(is_implicit_declaration() == TRUE && get_attribute_name() != NULL) {
    if(get_attribute_name()->is_above_attribute() == TRUE) {
      return TRUE;
    }
    else
      return FALSE;
  }
  else
    return FALSE;
}

IIR_Declaration::declaration_type 
IIRBase_SignalDeclaration::get_declaration_type(){
  return SIGNAL;
}

void 
IIRBase_SignalDeclaration::publish_vhdl_decl(ostream &vhdl_out) {

  ASSERT ( get_declarative_region() != NULL );
  
  vhdl_out << "signal ";
  publish_vhdl_declarator_with_colon(vhdl_out);
  publish_vhdl_subtype_indication(vhdl_out);
  publish_vhdl_signal_kind(vhdl_out);
  publish_vhdl_expression(vhdl_out);
  vhdl_out << ";\n";
}
