
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

#include "IIRScram_AttributeSpecificationList.hh"
#include "IIRScram_ComponentDeclaration.hh"
#include "IIRScram_EntityDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_GenericList.hh"
#include "IIRScram_PortList.hh"

#include "symbol_table.hh"

IIRScram_ComponentDeclaration::IIRScram_ComponentDeclaration() {
  set_local_generic_clause(new IIRScram_GenericList());
  set_local_port_clause(new IIRScram_PortList());
  set_attributes(new IIRScram_AttributeSpecificationList());
}

IIRScram_ComponentDeclaration::~IIRScram_ComponentDeclaration(){}

IIRScram_TypeDefinition *
IIRScram_ComponentDeclaration::_get_port_type( int port_num ){
  ASSERT( port_num < get_local_port_clause()->size() );
  IIRScram_Declaration *port_element 
    = dynamic_cast<IIRScram_Declaration *>(get_local_port_clause()->get_nth_element( port_num ));

  ASSERT( port_element->_is_iir_declaration() == TRUE );

  return port_element->_get_subtype();
}

IIRScram_GenericList *
IIRScram_ComponentDeclaration::_get_generic_list(){
  return dynamic_cast<IIRScram_GenericList *>(get_local_generic_clause());
}

void 
IIRScram_ComponentDeclaration::_make_interface_visible( symbol_table *sym_tab ){
  sym_tab->make_visible( _get_local_generic_clause() );
  sym_tab->make_visible( _get_local_port_clause() );
}

visitor_return_type *
IIRScram_ComponentDeclaration::_accept_visitor( node_visitor *visitor,
						visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ComponentDeclaration(this, arg);
}

IIRScram_AttributeSpecificationList*
IIRScram_ComponentDeclaration::_get_attribute_specification_list(){
  return dynamic_cast<IIRScram_AttributeSpecificationList *>(get_attributes());
}

IIRScram_PortList *
IIRScram_ComponentDeclaration::_get_port_list(){
  return dynamic_cast<IIRScram_PortList *>(get_local_port_clause());
}

IIRScram_GenericList *
IIRScram_ComponentDeclaration::_get_local_generic_clause() {
  return dynamic_cast<IIRScram_GenericList *>(get_local_generic_clause());
}

IIRScram_PortList *
IIRScram_ComponentDeclaration::_get_local_port_clause() {
  return dynamic_cast<IIRScram_PortList *>(get_local_port_clause());
}

IIRScram_EntityDeclaration *
IIRScram_ComponentDeclaration::_get_entity() {
  return dynamic_cast<IIRScram_EntityDeclaration *>(get_entity());
}
