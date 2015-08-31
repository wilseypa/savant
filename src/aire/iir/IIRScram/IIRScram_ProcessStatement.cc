
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
//          Malolan Chetlur    
//          Krishnan Subramani 
//          Radharamanan Radhakrishnan
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam
//          Swaminathan Subramanian
//          Magnus Danielson    cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_DeclarationList.hh"
#include "IIRScram_AliasDeclaration.hh"
#include "IIRScram_FileDeclaration.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_ProcessStatement.hh"
#include "IIRScram_SequentialStatementList.hh"
#include "IIRScram_SequentialStatement.hh"
#include "IIRScram_SignalDeclaration.hh"
#include "IIRScram_VariableDeclaration.hh"

IIRScram_ProcessStatement::IIRScram_ProcessStatement(){ 
  set_process_declarative_part(new IIRScram_DeclarationList());
  set_process_statement_part(new IIRScram_SequentialStatementList());
}

IIRScram_ProcessStatement::~IIRScram_ProcessStatement() { 
  //Release the list memory
  delete get_process_declarative_part();
  delete get_process_statement_part();
}

void 
IIRScram_ProcessStatement::_type_check(){
  _get_process_declarative_part()->_type_check_attribute_specifications( _get_process_statement_part() ); 
}

IIRScram_SequentialStatementList *
IIRScram_ProcessStatement::_get_process_statement_part() {
  return dynamic_cast<IIRScram_SequentialStatementList *>(get_process_statement_part());
}

// IIRBase Function Wrapper(s)
IIRScram_DeclarationList *
IIRScram_ProcessStatement::_get_process_declarative_part() {
  return dynamic_cast<IIRScram_DeclarationList *>(get_process_declarative_part());
}

visitor_return_type *
IIRScram_ProcessStatement::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ProcessStatement(this, arg);
}

IIRScram *
IIRScram_ProcessStatement::_clone() {
  IIRScram_Declaration *decl = NULL;
  IIRScram_SequentialStatement *clone,
    *stmt = dynamic_cast<IIRScram_SequentialStatement *>(get_process_statement_part()->first());
  IIRScram_ProcessStatement *newproc = new IIRScram_ProcessStatement;
  IIRScram::_clone( newproc );
  IIRScram_Label *label = _get_label();

  if (label != NULL) {
    label = dynamic_cast<IIRScram_Label*>(label->_clone());
  }
  newproc->set_label(label);

#ifdef DEBUG_ELAB
  cout << "cloning process |";
  if (label == NULL || label->get_declarator() == NULL) {
    cout << "NONAME|" << NL();
  }
  else {
    cout << label->get_declarator() << "|" << NL();;
  }
#endif

  decl = dynamic_cast<IIRScram_Declaration *>(get_process_declarative_part()->first());
  while ( decl != NULL ) {
      // This forces a distinct clone of these node types to be created
      // for this process.
    switch (decl->get_kind()) {
    case IIR_SIGNAL_DECLARATION:
      (dynamic_cast<IIRScram_SignalDeclaration*>(decl))->_clear_clone();
      break;
    case IIR_FILE_DECLARATION:
      (dynamic_cast<IIRScram_FileDeclaration*>(decl))->_clear_clone();
      break;
    case IIR_VARIABLE_DECLARATION:
      (dynamic_cast<IIRScram_VariableDeclaration*>(decl))->_clear_clone();
      break;
    case IIR_ALIAS_DECLARATION:
      (dynamic_cast<IIRScram_AliasDeclaration*>(decl))->_clear_clone();
      break;
    default:
      break;
    }
    newproc->get_process_declarative_part()->append(dynamic_cast<IIRScram_Declaration*>(decl->_clone()));
    decl = dynamic_cast<IIRScram_Declaration *>(get_process_declarative_part()->successor( decl ));
  }

  newproc->set_postponed(get_postponed());
  while (stmt != NULL) {
    clone = dynamic_cast<IIRScram_SequentialStatement*>(stmt->_clone());
    newproc->get_process_statement_part()->append(clone);
    stmt = dynamic_cast<IIRScram_SequentialStatement*>(get_process_statement_part()->successor(stmt));
  }
  return newproc;
}

