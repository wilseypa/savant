
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
#include "IIRBase_SubtypeDeclaration.hh"
#include "IIR_AttributeSpecificationList.hh"
#include "IIR_TextLiteral.hh"
#include "IIRBase_TypeDefinition.hh"

IIRBase_SubtypeDeclaration::IIRBase_SubtypeDeclaration()  :
  attributes(0){}

IIRBase_SubtypeDeclaration::~IIRBase_SubtypeDeclaration() {
  delete attributes;
  attributes = 0;
}

// List Accessor(s)
IIR_AttributeSpecificationList *
IIRBase_SubtypeDeclaration::get_attributes() {
  ASSERT(attributes != NULL);
  return attributes;
}

void
IIRBase_SubtypeDeclaration::set_attributes(IIR_AttributeSpecificationList *new_attributes) {
  ASSERT(new_attributes != NULL);
  delete attributes;
  attributes = new_attributes;
}

IIR *
IIRBase_SubtypeDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_SubtypeDeclaration *new_node = dynamic_cast<IIRBase_SubtypeDeclaration *>(IIRBase_Declaration::convert_tree(factory));

  // Process the variables
  new_node->attributes = dynamic_cast<IIR_AttributeSpecificationList *>(convert_node(attributes, factory));

  return new_node;
}

IIR_Boolean
IIRBase_SubtypeDeclaration::is_locally_static(){
  return get_subtype()->is_locally_static();
}


IIR_Declaration::declaration_type 
IIRBase_SubtypeDeclaration::get_declaration_type(){
   return SUBTYPE;
}

void 
IIRBase_SubtypeDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  ASSERT(get_subtype() != NULL);
  // This assertion is not true for:
  // type foo is ( red, green, blue );
  // subtype bar is foo;
  // (Or for any other type definition that isn't required to have an
  // anonymous base type.)
  //  ASSERT(get_subtype()->get_base_type() != NULL);
  

  vhdl_out << "subtype ";
  get_declarator()->publish_vhdl(vhdl_out);
  if(get_subtype() != NULL) {
    vhdl_out << " is ";
    dynamic_cast<IIRBase_TypeDefinition *>(get_subtype())->publish_vhdl_subtype_decl(vhdl_out);
  }
  vhdl_out << ";\n";
}

void
IIRBase_SubtypeDeclaration::publish_vhdl_range(ostream &vhdl_out){
  publish_vhdl(vhdl_out);
}
