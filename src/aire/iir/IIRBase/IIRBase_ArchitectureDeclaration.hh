
#ifndef IIRBASE_ARCHITECTURE_DECLARATION_HH
#define IIRBASE_ARCHITECTURE_DECLARATION_HH

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
//          Timothy J. McBrayer

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRBase_LibraryUnit.hh"
#include "IIR_ArchitectureDeclaration.hh"

class IIR_DeclarationList;
class IIR_ArchitectureStatementList;
class IIR_EntityDeclaration;
class IIR_ArchitectureStatement;

class IIRBase_ArchitectureDeclaration : public virtual IIRBase_LibraryUnit, public virtual IIR_ArchitectureDeclaration{

public:
  // List Accessor(s)
  IIR_DeclarationList           *get_architecture_declarative_part();
  IIR_ArchitectureStatementList *get_architecture_statement_part();

  void                          set_architecture_declarative_part(IIR_DeclarationList *new_architecture_declarative_part);
  void                          set_architecture_statement_part(IIR_ArchitectureStatementList *new_architecture_statement_part);

  IIR_Kind get_kind() const {return IIR_ARCHITECTURE_DECLARATION;}
  const IIR_Char *get_kind_text() const {return "IIR_ArchitectureDeclaration";}

  void associate(IIR_EntityDeclaration *);
  void set_entity(IIR_EntityDeclaration *);
  IIR_EntityDeclaration* get_entity();

  IIR *convert_tree(plugin_class_factory *factory);

  declaration_type get_declaration_type();
    
  savant::set<IIR_Declaration> *find_declarations( IIR_Name *to_find);
  IIR_Boolean is_architecture_declaration(){ return TRUE; }
  IIR_Boolean is_secondary_unit(){ return TRUE; }

  void publish_vhdl(ostream &);
  void publish_vhdl_decl(ostream &);
  void publish_vhdl_binding_name(ostream &);
  void publish_vhdl_with_library_name(ostream &);
protected:
  IIRBase_ArchitectureDeclaration();
  virtual ~IIRBase_ArchitectureDeclaration() = 0;
    
private:
  // List Variable(s)
  IIR_DeclarationList           *architecture_declarative_part;
  IIR_ArchitectureStatementList *architecture_statement_part;

  IIR_EntityDeclaration* entity;
};
#endif
