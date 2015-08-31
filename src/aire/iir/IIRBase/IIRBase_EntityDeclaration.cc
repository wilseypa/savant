
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

#include "IIR_ArchitectureStatementList.hh"
#include "IIR_GenericList.hh"
#include "IIR_PortList.hh"
#include "IIRBase_DeclarationList.hh"
#include "IIR_DesignUnitList.hh"
#include "IIR_TextLiteral.hh"
#include "IIRBase_EntityDeclaration.hh"

IIRBase_EntityDeclaration::IIRBase_EntityDeclaration() :
  generic_clause(0),
  port_clause(0),
  entity_declarative_part(0),
  entity_statement_part(0),
  architectures(0){}

IIRBase_EntityDeclaration::~IIRBase_EntityDeclaration(){
  delete generic_clause;
  generic_clause = 0;
  delete port_clause;
  port_clause = 0;
  delete entity_declarative_part;
  entity_declarative_part = 0;
  delete entity_statement_part;
  entity_statement_part = 0;
  delete architectures;
  architectures = 0;
}

// List Accessor(s)
IIR_GenericList *
IIRBase_EntityDeclaration::get_generic_clause() {
  ASSERT(generic_clause != NULL);
  return generic_clause;
}

IIR_PortList *
IIRBase_EntityDeclaration::get_port_clause() {
  ASSERT(port_clause != NULL);
  return port_clause;
}

IIR_DeclarationList *
IIRBase_EntityDeclaration::get_entity_declarative_part() {
  ASSERT(entity_declarative_part != NULL);
  return entity_declarative_part;
}

IIR_ArchitectureStatementList *
IIRBase_EntityDeclaration::get_entity_statement_part() {
  ASSERT(entity_statement_part != NULL);
  return entity_statement_part;
}

IIR_DesignUnitList *
IIRBase_EntityDeclaration::get_architectures() {
  ASSERT(architectures != NULL);
  return architectures;
}

void
IIRBase_EntityDeclaration::set_generic_clause(IIR_GenericList *new_generic_clause) {
  ASSERT(new_generic_clause != NULL);
  delete generic_clause;
  generic_clause = new_generic_clause;
}

void
IIRBase_EntityDeclaration::set_port_clause(IIR_PortList *new_port_clause) {
  ASSERT(new_port_clause != NULL);
  delete port_clause;
  port_clause = new_port_clause;
}

void
IIRBase_EntityDeclaration::set_entity_declarative_part(IIR_DeclarationList *new_entity_declarative_part) {
  ASSERT(new_entity_declarative_part != NULL);
  delete entity_declarative_part;
  entity_declarative_part = new_entity_declarative_part;
}

void
IIRBase_EntityDeclaration::set_entity_statement_part(IIR_ArchitectureStatementList *new_entity_statement_part) {
  ASSERT(new_entity_statement_part != NULL);
  delete entity_statement_part;
  entity_statement_part = new_entity_statement_part;
}

void
IIRBase_EntityDeclaration::set_architectures(IIR_DesignUnitList *new_architectures) {
  ASSERT(new_architectures != NULL);
  delete architectures;
  architectures = new_architectures;
}

IIR *
IIRBase_EntityDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_EntityDeclaration *new_node = dynamic_cast<IIRBase_EntityDeclaration *>(IIRBase_LibraryUnit::convert_tree(factory));

  // Process the variables
  new_node->generic_clause = dynamic_cast<IIR_GenericList *>(convert_node(generic_clause, factory));
  new_node->port_clause = dynamic_cast<IIR_PortList *>(convert_node(port_clause, factory));
  new_node->entity_declarative_part = dynamic_cast<IIR_DeclarationList *>(convert_node(entity_declarative_part, factory));
  new_node->entity_statement_part = dynamic_cast<IIR_ArchitectureStatementList *>(convert_node(entity_statement_part, factory));
  new_node->architectures = dynamic_cast<IIR_DesignUnitList *>(convert_node(architectures, factory));

  return new_node;
}

IIR_Declaration::declaration_type 
IIRBase_EntityDeclaration::get_declaration_type() {
  return ENTITY;
}

savant::set<IIR_Declaration> *
IIRBase_EntityDeclaration::find_declarations( IIR_Name *to_find ) {
  savant::set<IIR_Declaration> *retval = new savant::set<IIR_Declaration>;

  savant::set<IIR_Declaration> *current_set = get_port_clause()->find_declarations( to_find );
  if( current_set != NULL ){
    retval->add( current_set );
    delete current_set;
  }

  current_set = get_generic_clause()->find_declarations( to_find );
  if( current_set != NULL ){
    retval->add( current_set );
    delete current_set;
  }

  current_set = get_entity_declarative_part()->find_declarations( to_find );
  if( current_set != NULL ){
    retval->add( current_set );
    delete current_set;
  }
  if( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }
  return retval;
}

void 
IIRBase_EntityDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  get_context_items()->publish_vhdl(vhdl_out);
  vhdl_out << "\nentity ";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << " is\n";

  if(get_generic_clause()->size() != 0) {
    vhdl_out << "generic (\n";
    get_generic_clause()->publish_vhdl(vhdl_out);
    vhdl_out << ");\n";
  }

  if(get_port_clause()->size() != 0) {
    vhdl_out << " port (\n";
    get_port_clause()->publish_vhdl(vhdl_out);
    vhdl_out << ");\n";
  }

  dynamic_cast<IIRBase_DeclarationList *>
    (get_entity_declarative_part())->publish_vhdl_decl(vhdl_out);

  if( get_entity_statement_part()->size() != 0) {
    vhdl_out << "begin\n";
    get_entity_statement_part()->publish_vhdl(vhdl_out);
  }
  vhdl_out << "end entity ";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << ";\n\n";
}

void 
IIRBase_EntityDeclaration::publish_vhdl(ostream &vhdl_out) {
  get_declarator()->publish_vhdl(vhdl_out);
}

void
IIRBase_EntityDeclaration::publish_vhdl_binding_name(ostream &vhdl_out){
  vhdl_out << " entity ";
  get_declarator()->publish_vhdl(vhdl_out);
}

void
IIRBase_EntityDeclaration::publish_vhdl_with_library_name(ostream &vhdl_out){
  vhdl_out << " entity ";
  ASSERT(get_declarative_region() != NULL);
  ASSERT(get_declarative_region()->get_kind() == IIR_LIBRARY_DECLARATION);
  get_declarative_region()->publish_vhdl(vhdl_out);
  vhdl_out << ".";
  get_declarator()->publish_vhdl(vhdl_out);
}
