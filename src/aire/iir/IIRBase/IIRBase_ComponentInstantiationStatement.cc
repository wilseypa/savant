
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
#include "IIR_AssociationList.hh"
#include "IIR_Declaration.hh"
#include "IIRBase_ComponentInstantiationStatement.hh"

IIRBase_ComponentInstantiationStatement::IIRBase_ComponentInstantiationStatement() : 
  generic_map_aspect(0),
  port_map_aspect(0),
  my_instantiated_unit( NULL ),
  my_configuration( NULL ) {
}

IIRBase_ComponentInstantiationStatement::~IIRBase_ComponentInstantiationStatement(){
}

void 
IIRBase_ComponentInstantiationStatement::set_instantiated_unit( IIR *instantiated_unit ){
  my_instantiated_unit = instantiated_unit;
}

IIR *
IIRBase_ComponentInstantiationStatement::get_instantiated_unit(){
  return my_instantiated_unit;
}

// List Accessor(s)
IIR_AssociationList *
IIRBase_ComponentInstantiationStatement::get_generic_map_aspect() {
  ASSERT(generic_map_aspect != NULL);
  return generic_map_aspect;
}

IIR_AssociationList *
IIRBase_ComponentInstantiationStatement::get_port_map_aspect() {
  ASSERT(port_map_aspect != NULL);
  return port_map_aspect;
}


void
IIRBase_ComponentInstantiationStatement::set_generic_map_aspect(IIR_AssociationList *new_generic_map_aspect) {
  ASSERT(new_generic_map_aspect != NULL);
  delete generic_map_aspect;
  generic_map_aspect = new_generic_map_aspect;
}

void
IIRBase_ComponentInstantiationStatement::set_port_map_aspect(IIR_AssociationList *new_port_map_aspect) {
  ASSERT(new_port_map_aspect != NULL);
  delete port_map_aspect;
  port_map_aspect = new_port_map_aspect;
}

IIR *
IIRBase_ComponentInstantiationStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ComponentInstantiationStatement *new_node = dynamic_cast<IIRBase_ComponentInstantiationStatement *>(IIRBase_ConcurrentStatement::convert_tree(factory));

  // Process the variables
  new_node->generic_map_aspect = dynamic_cast<IIR_AssociationList *>(convert_node(generic_map_aspect, factory));
  new_node->port_map_aspect = dynamic_cast<IIR_AssociationList *>(convert_node(port_map_aspect, factory));
  new_node->my_instantiated_unit = convert_node(my_instantiated_unit, factory);
  new_node->my_configuration = convert_node(my_configuration, factory);

  return new_node;
}

IIR *
IIRBase_ComponentInstantiationStatement::get_configuration(){ return my_configuration; }

void 
IIRBase_ComponentInstantiationStatement::set_configuration( IIR *new_config ){ 
  if( my_configuration != 0 ){
    if( dynamic_cast<IIR_Declaration *>(my_configuration) != NULL){
      // Then we generated it, we need to delete it.
      delete my_configuration;
    }
  }
  my_configuration = new_config; 
}


void 
IIRBase_ComponentInstantiationStatement::publish_vhdl(ostream &vhdl_out) {

  ASSERT( get_instantiated_unit() != NULL );
  
  publish_vhdl_stmt_label(vhdl_out);

  if( get_instantiated_unit()->is_entity_declaration() ){
    vhdl_out << "entity ";
  }
  else if( get_instantiated_unit()->is_configuration_declaration() ){
    vhdl_out << "configuration ";
  }
  else if( get_instantiated_unit()->is_component_declaration() ){
    vhdl_out << "component ";
  }
  
  get_instantiated_unit()->publish_vhdl(vhdl_out);
  if(get_generic_map_aspect()->size() != 0) {
    vhdl_out << " generic map ( ";
    get_generic_map_aspect()->publish_vhdl(vhdl_out);
    vhdl_out << " )";    
  }
  if(get_port_map_aspect()->size() != 0) {
    vhdl_out << "\n port map ( ";
    get_port_map_aspect()->publish_vhdl(vhdl_out);
    vhdl_out << " )";
  }
  vhdl_out << ";\n";
}
