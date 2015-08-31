#ifndef IIRSCRAM_BLOCK_STATEMENT_HH
#define IIRSCRAM_BLOCK_STATEMENT_HH

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
//          Swaminathan Subramanian ssubrama@ececs.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_ConcurrentStatement.hh"
#include "IIRBase_BlockStatement.hh"

class IIRScram_AssociationElement;
class IIRScram_AssociationList;
class IIRScram_GenericList;
class IIRScram_Label;
class IIRScram_List;
class IIRScram_Name;
class IIRScram_SignalDeclaration;

class IIRScram_BlockStatement : public virtual IIRScram_ConcurrentStatement, public virtual IIRBase_BlockStatement {

public:
  IIRScram_BlockStatement();
  virtual ~IIRScram_BlockStatement();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  void _type_check();

  IIRScram_SignalDeclaration            *_get_implicit_guard_signal();
  IIRScram_List                         *_get_statement_list();
  IIRScram_GenericList                  *_get_generic_list();
  IIRScram                              *_get_guard_expression();
  IIRScram_GenericList                  *_get_generic_clause();
  IIRScram_PortList                     *_get_port_clause();
  IIRScram_AssociationList              *_get_port_map_aspect();
  IIRScram_DeclarationList              *_get_block_declarative_part();
  IIRScram_ArchitectureStatementList    *_get_block_statement_part();

  IIRScram_AssociationList *_get_generic_map_aspect();

  void _make_interface_visible(symbol_table *sym_tab );
  void _type_check_instantiate_statements();

protected:    
private:
  IIRScram_SignalDeclaration *my_implicit_guard_signal;
};

#endif
