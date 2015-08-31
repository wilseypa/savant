
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




#include "set.hh"
#include "IIR_ArchitectureStatementList.hh"
#include "IIRBase_DeclarationList.hh"
#include "IIR_DesignUnitList.hh"
#include "IIR_EntityDeclaration.hh"
#include "IIRBase_ArchitectureDeclaration.hh"
#include "IIR_TextLiteral.hh"

IIRBase_ArchitectureDeclaration::IIRBase_ArchitectureDeclaration() :
  architecture_declarative_part(0),
  architecture_statement_part(0) { }


IIRBase_ArchitectureDeclaration::~IIRBase_ArchitectureDeclaration(){
}

void 
IIRBase_ArchitectureDeclaration::associate( IIR_EntityDeclaration *new_entity ){
  new_entity->get_architectures()->append( this );
}


void
IIRBase_ArchitectureDeclaration::set_entity(IIR_EntityDeclaration *e) {
  entity = e;
}


IIR_EntityDeclaration*
IIRBase_ArchitectureDeclaration::get_entity() {
  return entity;
}


// List Accessor(s)
IIR_DeclarationList *
IIRBase_ArchitectureDeclaration::get_architecture_declarative_part() {
  ASSERT(architecture_declarative_part != NULL);
  return architecture_declarative_part;
}

IIR_ArchitectureStatementList *
IIRBase_ArchitectureDeclaration::get_architecture_statement_part() {
  ASSERT(architecture_statement_part != NULL);
  return architecture_statement_part;
}


void
IIRBase_ArchitectureDeclaration::set_architecture_declarative_part(IIR_DeclarationList *new_architecture_declarative_part) {
  ASSERT(new_architecture_declarative_part != NULL);

  if (architecture_declarative_part != NULL)
    delete architecture_declarative_part;

  architecture_declarative_part = new_architecture_declarative_part;
}

void
IIRBase_ArchitectureDeclaration::set_architecture_statement_part(IIR_ArchitectureStatementList *new_architecture_statement_part) {
  ASSERT(new_architecture_statement_part != NULL);
  delete architecture_statement_part;
  architecture_statement_part = new_architecture_statement_part;
}

IIR *
IIRBase_ArchitectureDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ArchitectureDeclaration *new_node = dynamic_cast<IIRBase_ArchitectureDeclaration *>(IIRBase_LibraryUnit::convert_tree(factory));

  // Process the variables
  new_node->architecture_declarative_part = dynamic_cast<IIR_DeclarationList *>(convert_node(architecture_declarative_part, factory));
  new_node->architecture_statement_part = dynamic_cast<IIR_ArchitectureStatementList *>(convert_node(architecture_statement_part, factory));
  new_node->entity = dynamic_cast<IIR_EntityDeclaration *>(convert_node(entity, factory));

  return new_node;
}

IIR_Declaration::declaration_type 
IIRBase_ArchitectureDeclaration::get_declaration_type(){
  return ARCHITECTURE;
}

savant::set<IIR_Declaration> *
IIRBase_ArchitectureDeclaration::find_declarations( IIR_Name *to_find ){
  savant::set<IIR_Declaration> *retval = new savant::set<IIR_Declaration>;
  savant::set<IIR_Declaration> *current_set = get_architecture_declarative_part()->find_declarations( to_find );
  if( current_set != NULL ){
    retval->add( current_set );
    delete current_set;
  }

  ASSERT( get_entity() != NULL );
  current_set = get_entity()->find_declarations( to_find );
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
IIRBase_ArchitectureDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  get_context_items()->publish_vhdl(vhdl_out);

  vhdl_out << "architecture ";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out  << " of ";
  get_entity()->publish_vhdl(vhdl_out);
  vhdl_out << " is\n";
  dynamic_cast<IIRBase_DeclarationList *>(get_architecture_declarative_part())->publish_vhdl_decl(vhdl_out);
  vhdl_out << "\nbegin\n";
  get_architecture_statement_part()->publish_vhdl(vhdl_out);
  vhdl_out << "end architecture ";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << ";\n\n";
}

void 
IIRBase_ArchitectureDeclaration::publish_vhdl(ostream &vhdl_out) {
  get_declarator()->publish_vhdl(vhdl_out);
}

void
IIRBase_ArchitectureDeclaration::publish_vhdl_binding_name(ostream &vhdl_out){
  vhdl_out << " entity ";
  get_entity()->publish_vhdl(vhdl_out);
  vhdl_out << "(";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << ") ";
}

void
IIRBase_ArchitectureDeclaration::publish_vhdl_with_library_name(ostream &vhdl_out){
  vhdl_out << " entity ";
  ASSERT(get_declarative_region() != NULL);
  ASSERT(get_declarative_region()->get_kind() == IIR_LIBRARY_DECLARATION);
  get_declarative_region()->publish_vhdl(vhdl_out);
  vhdl_out << ".";
  get_entity()->publish_vhdl(vhdl_out);
  vhdl_out << "(";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << ")";
}
