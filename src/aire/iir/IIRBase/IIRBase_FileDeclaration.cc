
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

#include "IIRBase_FileDeclaration.hh"
#include "savant.hh"

IIRBase_FileDeclaration::IIRBase_FileDeclaration() {
  set_file_open_expression(NULL);
  set_file_logical_name(NULL);
}

IIRBase_FileDeclaration::~IIRBase_FileDeclaration() {}

void
IIRBase_FileDeclaration::set_file_open_expression( IIR *new_file_open_expression ){
  file_open_expression = new_file_open_expression;
}

IIR*
IIRBase_FileDeclaration::get_file_open_expression() {
  return file_open_expression;
}

void
IIRBase_FileDeclaration::set_file_logical_name( IIR *new_file_logical_name ){
  file_logical_name = new_file_logical_name;
}

IIR*
IIRBase_FileDeclaration::get_file_logical_name() {
  return file_logical_name;
}

IIR *
IIRBase_FileDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_FileDeclaration *new_node = dynamic_cast<IIRBase_FileDeclaration *>(IIRBase_ObjectDeclaration::convert_tree(factory));

  // Process the variables
  new_node->file_open_expression = convert_node(file_open_expression, factory);
  new_node->file_logical_name = convert_node(file_logical_name, factory);

  return new_node;
}

IIR_Declaration::declaration_type
IIRBase_FileDeclaration::get_declaration_type() {
  return S_FILE;
}

void 
IIRBase_FileDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << "file ";
  publish_vhdl_declarator_with_colon(vhdl_out);
  publish_vhdl_subtype_indication(vhdl_out);

  if (get_file_open_expression() != NULL) {
    vhdl_out << " open ";
    get_file_open_expression()->publish_vhdl(vhdl_out);
  }
  
  if (get_file_logical_name() != NULL) {
    vhdl_out << " is ";
    get_file_logical_name()->publish_vhdl(vhdl_out);
  }
  vhdl_out << ";\n";
}
