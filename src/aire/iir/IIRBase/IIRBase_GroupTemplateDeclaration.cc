
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


#include "IIRBase_GroupTemplateDeclaration.hh"
#include "IIR_EntityClassEntryList.hh"
#include "IIR_TextLiteral.hh"

IIRBase_GroupTemplateDeclaration::IIRBase_GroupTemplateDeclaration()  :
  entity_class_entry_list(0) { }

IIRBase_GroupTemplateDeclaration::~IIRBase_GroupTemplateDeclaration() {
}

// List Accessor(s)
IIR_EntityClassEntryList *
IIRBase_GroupTemplateDeclaration::get_entity_class_entry_list() {
  ASSERT(entity_class_entry_list != NULL);
  return entity_class_entry_list;
}


void
IIRBase_GroupTemplateDeclaration::set_entity_class_entry_list(IIR_EntityClassEntryList *new_entity_class_entry_list) {
  ASSERT(new_entity_class_entry_list != NULL);
  delete entity_class_entry_list;
  entity_class_entry_list = new_entity_class_entry_list;
}

IIR *
IIRBase_GroupTemplateDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_GroupTemplateDeclaration *new_node = dynamic_cast<IIRBase_GroupTemplateDeclaration *>(IIRBase_Declaration::convert_tree(factory));

  // Process the variables
  new_node->entity_class_entry_list = dynamic_cast<IIR_EntityClassEntryList *>(convert_node(entity_class_entry_list, factory));

  return new_node;
}

void 
IIRBase_GroupTemplateDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << " group ";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << " is ( ";
  get_entity_class_entry_list()->publish_vhdl(vhdl_out);
  vhdl_out << " );\n";
}
