
#ifndef IIRBASE_BLOCK_STATEMENT_HH
#define IIRBASE_BLOCK_STATEMENT_HH

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

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIR_BlockStatement.hh"
#include "IIRBase_ConcurrentStatement.hh"

class IIR_GenericList;
class IIR_AssociationList;
class IIR_PortList;
class IIR_DeclarationList;
class IIR_ArchitectureStatementList;
class IIR_SignalDeclaration;

class IIRBase_BlockStatement : public virtual IIRBase_ConcurrentStatement, public virtual IIR_BlockStatement{

public:
  // List Accessor(s)
  IIR_GenericList               *get_generic_clause();
  IIR_AssociationList           *get_generic_map_aspect();
  IIR_PortList                  *get_port_clause();
  IIR_AssociationList           *get_port_map_aspect();
  IIR_DeclarationList           *get_block_declarative_part();
  IIR_ArchitectureStatementList *get_block_statement_part();
  void                          set_generic_clause(IIR_GenericList *new_generic_clause);
  void                          set_generic_map_aspect(IIR_AssociationList *new_generic_map_aspect);
  void                          set_port_clause(IIR_PortList *new_port_clause);
  void                          set_port_map_aspect(IIR_AssociationList *new_port_map_aspect);
  void                          set_block_declarative_part(IIR_DeclarationList *new_block_declarative_part);
  void                          set_block_statement_part(IIR_ArchitectureStatementList *new_block_statement_part);

  IIR_Kind get_kind() const {return IIR_BLOCK_STATEMENT;}
  const IIR_Char *get_kind_text() const {return "IIR_BlockStatement";}

  void                          set_guard_expression( IIR *guard_expression );
  IIR                           *get_guard_expression();

  IIR_SignalDeclaration         *get_implicit_guard_signal(  );
  void                          set_implicit_guard_signal( IIR_SignalDeclaration * );

  IIR *convert_tree(plugin_class_factory *factory);

  savant::set<IIR_Declaration> *find_declarations( IIR_Name * );

  void publish_vhdl(ostream &);
protected:
  IIRBase_BlockStatement();
  virtual ~IIRBase_BlockStatement() = 0;
    
private:
  // List Variable(s)
  IIR_GenericList                       *generic_clause;
  IIR_AssociationList                   *generic_map_aspect;
  IIR_PortList                          *port_clause;
  IIR_AssociationList                   *port_map_aspect;
  IIR_DeclarationList                   *block_declarative_part;
  IIR_ArchitectureStatementList         *block_statement_part;

  IIR                                   *guard_expression;
  IIR_SignalDeclaration                 *implicit_guard_signal;

};
#endif
