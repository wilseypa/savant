
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

#include "savant.hh"
#include "IIRBase_ConfigurationSpecification.hh"
#include "IIR_AssociationList.hh"
#include "IIR_DesignatorList.hh"
#include "IIRBase_LibraryUnit.hh"

IIRBase_ConfigurationSpecification::IIRBase_ConfigurationSpecification() :
  instantiation_list(0),
  generic_map_aspect(0),
  port_map_aspect(0),
  my_component_name(0),
  my_entity_aspect(0){}

IIRBase_ConfigurationSpecification::~IIRBase_ConfigurationSpecification(){
  delete instantiation_list;
  instantiation_list = 0;
  delete generic_map_aspect;
  generic_map_aspect = 0;
  delete port_map_aspect;
  port_map_aspect = 0;
  // Not component name or entity aspect
}

void 
IIRBase_ConfigurationSpecification::set_component_name(IIR *component_name){
  my_component_name = component_name;
}

IIR *
IIRBase_ConfigurationSpecification::get_component_name(){
  return my_component_name;
}

void 
IIRBase_ConfigurationSpecification::set_entity_aspect(IIR_LibraryUnit *entity_aspect){
  my_entity_aspect = entity_aspect;
}

IIR_LibraryUnit *
IIRBase_ConfigurationSpecification::get_entity_aspect(){
  return my_entity_aspect;
}

// List Accessor(s)
IIR_DesignatorList *
IIRBase_ConfigurationSpecification::get_instantiation_list() {
  ASSERT(instantiation_list != NULL);
  return instantiation_list;
}

IIR_AssociationList *
IIRBase_ConfigurationSpecification::get_generic_map_aspect() {
  ASSERT(generic_map_aspect != NULL);
  return generic_map_aspect;
}

IIR_AssociationList *
IIRBase_ConfigurationSpecification::get_port_map_aspect() {
  ASSERT(port_map_aspect != NULL);
  return port_map_aspect;
}

void
IIRBase_ConfigurationSpecification::set_instantiation_list(IIR_DesignatorList *new_instantiation_list) {
  ASSERT(new_instantiation_list != NULL);
  delete instantiation_list;
  instantiation_list = new_instantiation_list;
}

void
IIRBase_ConfigurationSpecification::set_generic_map_aspect(IIR_AssociationList *new_generic_map_aspect) {
  ASSERT(new_generic_map_aspect != NULL);
  delete generic_map_aspect;
  generic_map_aspect = new_generic_map_aspect;
}

void
IIRBase_ConfigurationSpecification::set_port_map_aspect(IIR_AssociationList *new_port_map_aspect) {
  ASSERT(new_port_map_aspect != NULL);
  delete port_map_aspect;
  port_map_aspect = new_port_map_aspect;
}

IIR *
IIRBase_ConfigurationSpecification::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ConfigurationSpecification *new_node = dynamic_cast<IIRBase_ConfigurationSpecification *>(IIRBase_Declaration::convert_tree(factory));

  // Process the variables
  new_node->instantiation_list = dynamic_cast<IIR_DesignatorList *>(convert_node(instantiation_list, factory));
  new_node->generic_map_aspect = dynamic_cast<IIR_AssociationList *>(convert_node(generic_map_aspect, factory));
  new_node->port_map_aspect = dynamic_cast<IIR_AssociationList *>(convert_node(port_map_aspect, factory));
  new_node->my_component_name = convert_node(my_component_name, factory);
  new_node->my_entity_aspect = dynamic_cast<IIR_LibraryUnit *>(convert_node(my_entity_aspect, factory));

  return new_node;
}

void 
IIRBase_ConfigurationSpecification::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << "for ";

  if (get_instantiation_list()->first() != NULL) {
    get_instantiation_list()->publish_vhdl(vhdl_out);
  }
  else {
    vhdl_out << "all";
    // This can happen if we have a configuration specification with for all
    // clause but there is no component instantiation for this component.
  }
  
  vhdl_out << ": ";
  get_component_name()->publish_vhdl(vhdl_out);
  vhdl_out << " use";
  if(get_entity_aspect() != NULL) {
    dynamic_cast<IIRBase_LibraryUnit *>(get_entity_aspect())->publish_vhdl_with_library_name(vhdl_out);
  }
  else{
    vhdl_out << " open";
  }

  if(get_generic_map_aspect()->size() != 0) {
    vhdl_out << "\n  generic map ( ";
    get_generic_map_aspect()->publish_vhdl(vhdl_out);
    vhdl_out << " )";    
  }
  if(get_port_map_aspect()->size() != 0) {
    vhdl_out << "\n  port map ( ";
    get_port_map_aspect()->publish_vhdl(vhdl_out);
    vhdl_out << " )";
  }
  vhdl_out << ";\n";
}  

void 
IIRBase_ConfigurationSpecification::publish_vhdl(ostream &vhdl_out) {
  vhdl_out << "for ";
  get_instantiation_list()->publish_vhdl(vhdl_out);
  vhdl_out << " : ";
  get_component_name()->publish_vhdl(vhdl_out);
  if(get_entity_aspect() != NULL) {
    vhdl_out << " use ";
    get_entity_aspect()->publish_vhdl(vhdl_out);
  }
  if(get_generic_map_aspect()->size() != 0) {
    vhdl_out << "\n  generic map ( ";
    get_generic_map_aspect()->publish_vhdl(vhdl_out);
    vhdl_out << " )";    
  }
  if(get_port_map_aspect()->size() != 0) {
    vhdl_out << "\n  port map ( ";
    get_port_map_aspect()->publish_vhdl(vhdl_out);
    vhdl_out << " )";
  }
}
