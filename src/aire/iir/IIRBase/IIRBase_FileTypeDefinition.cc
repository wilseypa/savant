
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


#include "savant.hh"
#include "IIRBase_FileTypeDefinition.hh"
#include "IIR_Declaration.hh"
#include "IIR_TextLiteral.hh"

IIRBase_FileTypeDefinition::IIRBase_FileTypeDefinition() :
  type_mark(0){}

IIRBase_FileTypeDefinition::~IIRBase_FileTypeDefinition(){
  // Not type_mark
}

void
IIRBase_FileTypeDefinition::set_type_mark( IIR_TypeDefinition* type_mark) {
  this->type_mark = type_mark;
}

IIR_TypeDefinition *
IIRBase_FileTypeDefinition::get_type_mark() {
  return type_mark;
}

IIR_Boolean
IIRBase_FileTypeDefinition::is_locally_static(){
  return TRUE;
}

IIR *
IIRBase_FileTypeDefinition::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_FileTypeDefinition *new_node = dynamic_cast<IIRBase_FileTypeDefinition *>(IIRBase_TypeDefinition::convert_tree(factory));

  // Process the variables
  new_node->type_mark = dynamic_cast<IIR_TypeDefinition *>(convert_node(type_mark, factory));
    
  return new_node;
}

void 
IIRBase_FileTypeDefinition::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << "file of ";
  get_type_mark()->get_declaration()->get_declarator()->publish_vhdl(vhdl_out);
}
