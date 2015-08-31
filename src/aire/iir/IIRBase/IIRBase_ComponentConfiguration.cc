
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

#include "IIR_AssociationList.hh"
#include "IIR_BlockConfiguration.hh"
#include "IIR_DesignatorList.hh"
#include "IIRBase_LibraryUnit.hh"
#include "IIRBase_ComponentConfiguration.hh"


IIRBase_ComponentConfiguration::IIRBase_ComponentConfiguration() :
  instantiation_list(0),
  generic_map_aspect(0),
  port_map_aspect(0),
  my_component_name(0),
  my_entity_aspect(0),
  my_block_configuration(0){}

IIRBase_ComponentConfiguration::~IIRBase_ComponentConfiguration(){
  delete instantiation_list;
  instantiation_list = 0;
  delete generic_map_aspect;
  generic_map_aspect = 0;
  delete port_map_aspect;
  port_map_aspect = 0;
  delete my_block_configuration;
  my_block_configuration = 0;
}

void 
IIRBase_ComponentConfiguration::set_component_name( IIR *component_name ){
  my_component_name = component_name;
}

IIR *
IIRBase_ComponentConfiguration::get_component_name(){
  return my_component_name;
}

void 
IIRBase_ComponentConfiguration::set_entity_aspect( IIR_LibraryUnit *entity_aspect ){
  my_entity_aspect = entity_aspect;
}

IIR_LibraryUnit *
IIRBase_ComponentConfiguration::get_entity_aspect(){
  return my_entity_aspect;
}

void 
IIRBase_ComponentConfiguration::set_block_configuration( IIR_BlockConfiguration *block_configuration ){
  my_block_configuration = block_configuration;
}

IIR_BlockConfiguration *IIRBase_ComponentConfiguration::get_block_configuration(){
  return my_block_configuration;
}

// List Accessor(s)
IIR_DesignatorList *
IIRBase_ComponentConfiguration::get_instantiation_list() {
  ASSERT(instantiation_list != NULL);
  return instantiation_list;
}

IIR_AssociationList *
IIRBase_ComponentConfiguration::get_generic_map_aspect() {
  ASSERT(generic_map_aspect != NULL);
  return generic_map_aspect;
}

IIR_AssociationList *
IIRBase_ComponentConfiguration::get_port_map_aspect() {
  ASSERT(port_map_aspect != NULL);
  return port_map_aspect;
}


void
IIRBase_ComponentConfiguration::set_instantiation_list(IIR_DesignatorList *new_instantiation_list) {
  ASSERT(new_instantiation_list != NULL);

  if (instantiation_list != NULL)
    delete instantiation_list;

  instantiation_list = new_instantiation_list;
}

void
IIRBase_ComponentConfiguration::set_generic_map_aspect(IIR_AssociationList *new_generic_map_aspect) {
  ASSERT(new_generic_map_aspect != NULL);

  if (generic_map_aspect != NULL)
    delete generic_map_aspect;

  generic_map_aspect = new_generic_map_aspect;
}

void
IIRBase_ComponentConfiguration::set_port_map_aspect(IIR_AssociationList *new_port_map_aspect) {
  ASSERT(new_port_map_aspect != NULL);
  delete port_map_aspect;
  port_map_aspect = new_port_map_aspect;
}

IIR *
IIRBase_ComponentConfiguration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ComponentConfiguration *new_node = dynamic_cast<IIRBase_ComponentConfiguration *>(IIRBase_ConfigurationItem::convert_tree(factory));

  // Process the variables
  new_node->instantiation_list = dynamic_cast<IIR_DesignatorList *>(convert_node(instantiation_list, factory));
  new_node->generic_map_aspect = dynamic_cast<IIR_AssociationList *>(convert_node(generic_map_aspect, factory));
  new_node->port_map_aspect = dynamic_cast<IIR_AssociationList *>(convert_node(port_map_aspect, factory));
  new_node->my_component_name = convert_node(my_component_name, factory);
  new_node->my_entity_aspect = dynamic_cast<IIR_LibraryUnit *>(convert_node(my_entity_aspect, factory));
  new_node->my_block_configuration = dynamic_cast<IIR_BlockConfiguration *>(convert_node(my_block_configuration, factory));

  return new_node;
}

IIR_Boolean 
IIRBase_ComponentConfiguration::is_resolved(){
  IIR_Boolean retval = TRUE;
  if( (get_component_name() != NULL && get_component_name()->is_resolved() == FALSE) ||
      (get_entity_aspect() != NULL && get_entity_aspect()->is_resolved() == FALSE) ||
      (get_block_configuration() != NULL && get_block_configuration()->is_resolved() == FALSE) ||
      get_instantiation_list()->is_resolved() == FALSE ||
      get_generic_map_aspect()->is_resolved() == FALSE ||
      get_port_map_aspect()->is_resolved() == FALSE ){
    retval = FALSE;
  }
  return retval;
}

void 
IIRBase_ComponentConfiguration::publish_vhdl(ostream &vhdl_out) {
  ASSERT(get_component_name()->is_resolved() == TRUE);
  vhdl_out << " for ";
  get_instantiation_list()->publish_vhdl(vhdl_out);
  vhdl_out << " : ";
  get_component_name()->publish_vhdl(vhdl_out);
  vhdl_out << "\n";
  if(get_entity_aspect() != NULL) {
    vhdl_out << " use ";
    dynamic_cast<IIRBase_LibraryUnit *>(get_entity_aspect())->publish_vhdl_with_library_name(vhdl_out);
  }
  if(get_generic_map_aspect()->size() != 0) {
    vhdl_out << "\n generic map ( ";
    get_generic_map_aspect()->publish_vhdl(vhdl_out);
    vhdl_out << " )";
  }
  if(get_port_map_aspect()->size() != 0) {
    vhdl_out << "\n port map ( ";
    get_port_map_aspect()->publish_vhdl(vhdl_out);
    vhdl_out << " )";
  }
  
  if ( get_entity_aspect() != NULL || get_generic_map_aspect()->size() > 0 || get_port_map_aspect()->size() > 0 ){
    vhdl_out << ";\n";
  }
  if (get_block_configuration() != NULL)
    get_block_configuration()->publish_vhdl(vhdl_out);

  vhdl_out << "end for;\n";  
}
