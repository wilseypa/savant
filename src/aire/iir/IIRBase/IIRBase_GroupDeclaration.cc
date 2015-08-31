

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
#include "IIRBase_GroupDeclaration.hh"
#include "IIR_AttributeSpecificationList.hh"
#include "IIR_DesignatorList.hh"
#include "IIRBase_Name.hh"
#include "IIR_TextLiteral.hh"

IIRBase_GroupDeclaration::IIRBase_GroupDeclaration()  :
  group_constituent_list(0),
  attributes(0),
  group_template_name(0){}

IIRBase_GroupDeclaration::~IIRBase_GroupDeclaration(){
  delete group_constituent_list;
  group_constituent_list = 0;
  delete attributes;
  attributes = 0;
  delete group_template_name;
  group_template_name = 0;
}

void
IIRBase_GroupDeclaration:: set_group_template( IIR_Name *group_template_name ){
  this->group_template_name = group_template_name;
}

IIR_Name*
IIRBase_GroupDeclaration::get_group_template_name() {
  return group_template_name;
}


// List Accessor(s)
IIR_DesignatorList *
IIRBase_GroupDeclaration::get_group_constituent_list() {
  ASSERT(group_constituent_list != NULL);
  return group_constituent_list;
}

IIR_AttributeSpecificationList *
IIRBase_GroupDeclaration::get_attributes() {
  ASSERT(attributes != NULL);
  return attributes;
}


void
IIRBase_GroupDeclaration::set_group_constituent_list(IIR_DesignatorList *new_group_constituent_list) {
  ASSERT(new_group_constituent_list != NULL);
  delete group_constituent_list;
  group_constituent_list = new_group_constituent_list;
}

void
IIRBase_GroupDeclaration::set_attributes(IIR_AttributeSpecificationList *new_attributes) {
  ASSERT(new_attributes != NULL);
  delete attributes;
  attributes = new_attributes;
}

IIR *
IIRBase_GroupDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_GroupDeclaration *new_node = dynamic_cast<IIRBase_GroupDeclaration *>(IIRBase_Declaration::convert_tree(factory));

  // Process the variables
  new_node->group_constituent_list = dynamic_cast<IIR_DesignatorList *>(convert_node(group_constituent_list, factory));
  new_node->attributes = dynamic_cast<IIR_AttributeSpecificationList *>(convert_node(attributes, factory));
  new_node->group_template_name = dynamic_cast<IIR_Name *>(convert_node(group_template_name, factory));

  return new_node;
}

IIR_Declaration::declaration_type
IIRBase_GroupDeclaration::get_declaration_type(){
  return GROUP;
}

void 
IIRBase_GroupDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << " group ";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << " : ";
  dynamic_cast<IIRBase_Name *>(get_group_template_name())->publish_vhdl(vhdl_out);
  vhdl_out << " ( ";
  // XXX till it is fixed in aire spec let this be commented
  //  get_group_constituent_list()->publish_vhdl(vhdl_out);
  vhdl_out << " );\n";
}
