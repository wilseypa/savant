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
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Timothy J. McBrayer tmcbraye@ececs.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_ArchitectureDeclaration.hh"
#include "IIRScram_AssociationElementByExpression.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_ComponentDeclaration.hh"
#include "IIRScram_ComponentInstantiationStatement.hh"
#include "IIRScram_ConfigurationDeclaration.hh"
#include "IIRScram_ConfigurationSpecification.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_TextLiteral.hh"


IIRScram_ConfigurationSpecification::IIRScram_ConfigurationSpecification() {
  set_instantiation_list(new IIRScram_DesignatorList());
  set_generic_map_aspect(new IIRScram_AssociationList());
  set_port_map_aspect(new IIRScram_AssociationList());
}

IIRScram_ConfigurationSpecification::~IIRScram_ConfigurationSpecification(){}

void 
IIRScram_ConfigurationSpecification::_type_check( IIRScram_List *statement_list,
						  type_check_mode mode ) {
  // This doesn't type check the instantiation list...
  _type_check_configuration( *_get_port_map_aspect(), *_get_generic_map_aspect(), mode );
  // This does.
  _get_instantiation_list()->_type_check_as_instantiation_list( _get_component_name(), 
                                                                statement_list, 
                                                                this );
}



IIRScram *
IIRScram_ConfigurationSpecification::_get_component_name( ){
  return dynamic_cast<IIRScram *>(get_component_name());
}


void 
IIRScram_ConfigurationSpecification::_set_component_name( IIRScram *name  ){
  set_component_name( name );
}

IIRScram_LibraryUnit *
IIRScram_ConfigurationSpecification::_get_entity_aspect(){
  return dynamic_cast<IIRScram_LibraryUnit *>(get_entity_aspect());
}

visitor_return_type *
IIRScram_ConfigurationSpecification::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ConfigurationSpecification(this, arg);
};

IIRScram_DesignatorList *
IIRScram_ConfigurationSpecification::_get_instantiation_list() {
  return dynamic_cast<IIRScram_DesignatorList *>(get_instantiation_list());
}

IIRScram_AssociationList *
IIRScram_ConfigurationSpecification::_get_generic_map_aspect() {
  return dynamic_cast<IIRScram_AssociationList *>(get_generic_map_aspect());
}

IIRScram_AssociationList *
IIRScram_ConfigurationSpecification::_get_port_map_aspect() {
  return dynamic_cast<IIRScram_AssociationList *>(get_port_map_aspect());
}
