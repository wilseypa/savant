
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


#include "IIR_DeclarationList.hh"
#include "IIR_ConfigurationItemList.hh"
#include "IIRBase_BlockConfiguration.hh"

IIRBase_BlockConfiguration::IIRBase_BlockConfiguration() :
  use_clause_list(0),
  configuration_item_list(0) {
  set_block_specification( NULL );
}

IIRBase_BlockConfiguration::~IIRBase_BlockConfiguration(){}

void 
IIRBase_BlockConfiguration::set_block_specification(IIR *block_specification){
  this->block_specification = block_specification;
}
 
IIR* 
IIRBase_BlockConfiguration::get_block_specification(){
  return block_specification;
}

// List Accessor(s)
IIR_DeclarationList *
IIRBase_BlockConfiguration::get_use_clause_list() {
  ASSERT(use_clause_list != NULL);
  return use_clause_list;
}

IIR_ConfigurationItemList *
IIRBase_BlockConfiguration::get_configuration_item_list() {
  ASSERT(configuration_item_list != NULL); 
  return configuration_item_list;
}

void
IIRBase_BlockConfiguration::set_use_clause_list(IIR_DeclarationList *new_use_clause_list) {
  ASSERT(new_use_clause_list != NULL);
  
  if (use_clause_list != NULL)
    delete use_clause_list;

  use_clause_list = new_use_clause_list;
}

void
IIRBase_BlockConfiguration::set_configuration_item_list(IIR_ConfigurationItemList *new_configuration_item_list) {
  ASSERT(new_configuration_item_list != NULL);
  delete configuration_item_list;
  configuration_item_list = new_configuration_item_list;
}

IIR *
IIRBase_BlockConfiguration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_BlockConfiguration *new_node = dynamic_cast<IIRBase_BlockConfiguration *>(IIRBase_ConfigurationItem::convert_tree(factory));

  // Process the variables
  new_node->use_clause_list = dynamic_cast<IIR_DeclarationList *>(convert_node(use_clause_list, factory));
  new_node->configuration_item_list = dynamic_cast<IIR_ConfigurationItemList *>(convert_node(configuration_item_list, factory));
  new_node->block_specification = convert_node(block_specification, factory);

  return new_node;
}

ostream &
IIRBase_BlockConfiguration::print( ostream &os ){
  if( get_block_specification() != NULL ){
    os << *get_block_specification();
  }
  else{
    os << "<ANONYMOUS>";
  }

  return os;
}

void 
IIRBase_BlockConfiguration::publish_vhdl(ostream &vhdl_out) {
  vhdl_out << " for ";
  get_block_specification()->publish_vhdl(vhdl_out);
  vhdl_out << "\n";
  get_use_clause_list()->publish_vhdl(vhdl_out);
  get_configuration_item_list()->publish_vhdl(vhdl_out);
  vhdl_out << " end for;\n";
}
