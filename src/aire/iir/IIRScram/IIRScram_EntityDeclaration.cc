
// Copyright (c) 1996-2003 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     
//          Timothy J. McBrayer 
//          Narayanan Thondugulam
//          Radharamanan Radhakrishnan
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------
#include "IIRScram_EntityDeclaration.hh"
#include "IIRScram_AliasDeclaration.hh"
#include "IIRScram_ArchitectureDeclaration.hh"
#include "IIRScram_ArchitectureStatementList.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_Attribute.hh"
#include "IIRScram_ComponentInstantiationStatement.hh"
#include "IIRScram_ConstantInterfaceDeclaration.hh"
#include "IIRScram_ConfigurationSpecification.hh"
#include "IIRScram_DesignatorExplicit.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EntityDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_GenericList.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_Name.hh"
#include "IIRScram_PortList.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_ProcessStatement.hh"
#include "IIRScram_SignalInterfaceDeclaration.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_UseClause.hh"
#include "IIRScram_DesignUnitList.hh"
#include "library_manager.hh"
#include "resolution_func.hh"
#include "set.hh"
#include "symbol_table.hh"
#include "language_processing_control.hh"

extern language_processing_control *lang_proc;

IIRScram_EntityDeclaration::IIRScram_EntityDeclaration() {  
  set_generic_clause(new IIRScram_GenericList());
  set_port_clause(new IIRScram_PortList());
  set_entity_declarative_part(new IIRScram_DeclarationList());
  set_entity_statement_part(new IIRScram_ArchitectureStatementList());
  set_architectures(new IIRScram_DesignUnitList());
}

IIRScram_EntityDeclaration::~IIRScram_EntityDeclaration(){}

void 
IIRScram_EntityDeclaration::_make_interface_visible( symbol_table *sym_tab ) {
  ASSERT( sym_tab != NULL );

  _get_context_items()->_make_visible_as_context_list( sym_tab );
  sym_tab->make_visible( this );
  sym_tab->make_visible( _get_generic_clause() );
  sym_tab->make_visible( _get_port_clause() );
  sym_tab->make_visible( _get_entity_declarative_part() );
}

IIRScram_PortList *
IIRScram_EntityDeclaration::_get_port_clause(){
  return dynamic_cast<IIRScram_PortList *>(get_port_clause());
}

IIRScram_GenericList *
IIRScram_EntityDeclaration::_get_generic_list(){
  return _get_generic_clause();
}

void 
IIRScram_EntityDeclaration::_type_check(){
  _get_entity_declarative_part()->_type_check_attribute_specifications( _get_entity_statement_part() );
  _get_entity_declarative_part()->_type_check_disconnection_specifications( );
}

visitor_return_type *
IIRScram_EntityDeclaration::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_EntityDeclaration(this, arg);
}

IIRScram_ArchitectureStatementList *
IIRScram_EntityDeclaration::_get_entity_statement_part() {
  return dynamic_cast<IIRScram_ArchitectureStatementList *>(get_entity_statement_part());
}

// IIRBase Function Wrapper(s)
IIRScram_GenericList *
IIRScram_EntityDeclaration::_get_generic_clause(){
  return dynamic_cast<IIRScram_GenericList *>(get_generic_clause());
}

IIRScram_EntityDeclaration*
IIRScram_EntityDeclaration::_get_entity() {
  return this;
}

IIRScram_DeclarationList *
IIRScram_EntityDeclaration::_get_entity_declarative_part() {
  return dynamic_cast<IIRScram_DeclarationList *>(get_entity_declarative_part());
}

IIRScram_PortList *
IIRScram_EntityDeclaration::_get_port_list(){
  return _get_port_clause();
}
