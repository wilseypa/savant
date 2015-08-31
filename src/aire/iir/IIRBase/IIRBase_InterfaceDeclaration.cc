
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




#include "IIR_TypeDefinition.hh"
#include "IIRBase_InterfaceDeclaration.hh"
#include "IIR_TextLiteral.hh"
#include "savant.hh"

IIRBase_InterfaceDeclaration::IIRBase_InterfaceDeclaration() {
  set_mode(IIR_UNKNOWN_MODE);
  set_value(NULL);
}

IIRBase_InterfaceDeclaration::~IIRBase_InterfaceDeclaration() {}

void
IIRBase_InterfaceDeclaration::set_mode( IIR_Mode new_mode ){
  mode = new_mode;
}

IIR_Mode
IIRBase_InterfaceDeclaration::get_mode() {
   return mode;
}


void
IIRBase_InterfaceDeclaration::set_value( IIR *new_value ){
  value = new_value;
}

IIR *
IIRBase_InterfaceDeclaration::get_value() {
  return value;
}

IIR *
IIRBase_InterfaceDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_InterfaceDeclaration *new_node = dynamic_cast<IIRBase_InterfaceDeclaration *>(IIRBase_ObjectDeclaration::convert_tree(factory));

  // Process the variables
  new_node->value = convert_node(value, factory);

  new_node->mode = mode;

  return new_node;
}

ostream &
IIRBase_InterfaceDeclaration::print( ostream &os ){
  os << *get_declarator();
  return os;
}

void
IIRBase_InterfaceDeclaration::publish_vhdl_mode(ostream &vhdl_out){
  switch( get_mode() ) {
  case IIR_IN_MODE:
    vhdl_out << "in";
    break;
  case IIR_OUT_MODE:
    vhdl_out << "out";
    break;
  case IIR_INOUT_MODE:
    vhdl_out << "inout";
    break;
  case  IIR_BUFFER_MODE:
    vhdl_out << "buffer";
    break;
  case  IIR_LINKAGE_MODE:
    vhdl_out << "linkage";
    break;
  case  IIR_UNKNOWN_MODE:
    break;
  default:
    cerr << "Wrong mode specification in" << get_kind_text() << endl;
    break;
  }
  vhdl_out << " ";
}
