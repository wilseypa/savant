
// Copyright (c) 1996-2000 The University of Cincinnati.  
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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram.hh"
#include "IIRScram_ArchitectureDeclaration.hh"
#include "IIRScram_AssociationElement.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_BlockConfiguration.hh"
#include "IIRScram_ComponentConfiguration.hh"
#include "IIRScram_ConfigurationDeclaration.hh"
#include "IIRScram_ConfigurationSpecification.hh"
#include "IIRScram_Designator.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_LibraryUnit.hh"
#include "IIRScram_LibraryUnitList.hh"
#include "IIRScram_Name.hh"
#include "IIRScram_TextLiteral.hh"
#include "IIRScram_Statement.hh"
#include "error_func.hh"

#include "symbol_table.hh"



IIRScram_ComponentConfiguration::IIRScram_ComponentConfiguration(){
  set_instantiation_list(new IIRScram_DesignatorList());
  set_generic_map_aspect(new IIRScram_AssociationList());
  set_port_map_aspect(new IIRScram_AssociationList());
}

IIRScram_ComponentConfiguration::~IIRScram_ComponentConfiguration(){}

void
IIRScram_ComponentConfiguration::_type_check_configuration_item( IIRScram_List *statement_list,
								 IIRScram *enclosing_region ){
  ASSERT( enclosing_region != NULL );
  ASSERT( enclosing_region->get_kind() == IIR_BLOCK_CONFIGURATION );
  IIRScram_BlockConfiguration *enclosing_config = dynamic_cast<IIRScram_BlockConfiguration *>(enclosing_region);

  ASSERT( enclosing_config->_get_block_specification() != NULL );
  _type_check_configuration( *_get_port_map_aspect(), 
			     *_get_generic_map_aspect(),
			     IIRScram_ConfigurationSpecification::CONFIG_SPEC );
  
  if( _get_block_configuration() != NULL ){
    _get_block_configuration()->_type_check_configuration_item( statement_list, this );
  }

  _get_instantiation_list()->_type_check_as_instantiation_list( _get_component_name(), 
                                                                statement_list,
                                                                this );
}

IIRScram *
IIRScram_ComponentConfiguration::_get_component_name( ){
  return dynamic_cast<IIRScram *>(get_component_name());
}

void 
IIRScram_ComponentConfiguration::_set_component_name( IIRScram *name ){
  set_component_name( name );
}

IIRScram_LibraryUnit *
IIRScram_ComponentConfiguration::_get_entity_aspect(){
  return dynamic_cast<IIRScram_LibraryUnit *>(get_entity_aspect());
}

visitor_return_type *
IIRScram_ComponentConfiguration::_accept_visitor( node_visitor *visitor,
						  visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ComponentConfiguration(this, arg);
}

IIRScram_DesignatorList *
IIRScram_ComponentConfiguration::_get_instantiation_list() {
  return dynamic_cast<IIRScram_DesignatorList *>(get_instantiation_list());
}

IIRScram_AssociationList *
IIRScram_ComponentConfiguration::_get_generic_map_aspect() {
  return dynamic_cast<IIRScram_AssociationList *>(get_generic_map_aspect());
}

IIRScram_AssociationList *
IIRScram_ComponentConfiguration::_get_port_map_aspect() {
  return dynamic_cast<IIRScram_AssociationList *>(get_port_map_aspect());
}

IIRScram_BlockConfiguration *
IIRScram_ComponentConfiguration::_get_block_configuration() {
  return dynamic_cast<IIRScram_BlockConfiguration *>(get_block_configuration());
}
