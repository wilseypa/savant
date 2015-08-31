
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

#include "IIRBase_PackageBodyDeclaration.hh"
#include "IIRBase_DeclarationList.hh"
#include "IIR_TextLiteral.hh"

IIRBase_PackageBodyDeclaration::IIRBase_PackageBodyDeclaration()  :
  package_declarative_part(0){}

IIRBase_PackageBodyDeclaration::~IIRBase_PackageBodyDeclaration() {
  delete package_declarative_part;
  package_declarative_part = 0;
}

// List Accessor(s)
IIR_DeclarationList *
IIRBase_PackageBodyDeclaration::get_package_declarative_part() {
  ASSERT(package_declarative_part != NULL);
  return package_declarative_part;
}


void
IIRBase_PackageBodyDeclaration::set_package_declarative_part(IIR_DeclarationList *new_package_declarative_part) {
  ASSERT(new_package_declarative_part != NULL);
  delete package_declarative_part;
  package_declarative_part = new_package_declarative_part;
}

IIR *
IIRBase_PackageBodyDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_PackageBodyDeclaration *new_node = dynamic_cast<IIRBase_PackageBodyDeclaration *>(IIRBase_LibraryUnit::convert_tree(factory));

  // Process the variables
  new_node->package_declarative_part = dynamic_cast<IIR_DeclarationList *>(convert_node(package_declarative_part, factory));

  return new_node;
}

IIR_Declaration::declaration_type 
IIRBase_PackageBodyDeclaration::get_declaration_type(){
   return IIR_Declaration::PACKAGE_BODY;
}

void 
IIRBase_PackageBodyDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  get_context_items()->publish_vhdl(vhdl_out);
  
  vhdl_out << "package body ";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << " is\n";
  dynamic_cast<IIRBase_DeclarationList *>(get_package_declarative_part())->publish_vhdl_decl(vhdl_out);
  vhdl_out << "end package body ";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << ";\n";
}
