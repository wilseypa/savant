
// Copyright (c) The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
// DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

#include "IIRScram_ConfigurationDeclaration.hh"
#include "IIRScram_BlockConfiguration.hh"
#include "IIRScram_DeclarationList.hh"
#include "IIRScram_EntityDeclaration.hh"
#include "IIRScram_Identifier.hh"

IIRScram_ConfigurationDeclaration::IIRScram_ConfigurationDeclaration() {
  set_configuration_declarative_part(new IIRScram_DeclarationList());
}

IIRScram_ConfigurationDeclaration::~IIRScram_ConfigurationDeclaration() {
  //Release the list memory
  delete get_configuration_declarative_part();
}

void 
IIRScram_ConfigurationDeclaration::_make_interface_visible( symbol_table * ){}

void 
IIRScram_ConfigurationDeclaration::_type_check(){
  if( get_block_configuration() != NULL ){
    _get_block_configuration()->_type_check_configuration_item( NULL, this );
  }
  _get_configuration_declarative_part()->_type_check_configuration_specifications( NULL );
  _get_configuration_declarative_part()->_type_check_attribute_specifications( NULL );
}

visitor_return_type *
IIRScram_ConfigurationDeclaration::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ConfigurationDeclaration(this, arg);
}

IIRScram_BlockConfiguration *
IIRScram_ConfigurationDeclaration::_get_block_configuration() {
  return dynamic_cast<IIRScram_BlockConfiguration *>(get_block_configuration());
}

IIRScram_DeclarationList *
IIRScram_ConfigurationDeclaration::_get_configuration_declarative_part() {
  return dynamic_cast<IIRScram_DeclarationList *>(get_configuration_declarative_part());
}

IIRScram_EntityDeclaration *
IIRScram_ConfigurationDeclaration::_get_entity() {
  return dynamic_cast<IIRScram_EntityDeclaration *>(get_entity());
}
