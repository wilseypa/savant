
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
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam
//---------------------------------------------------------------------------

#include "IIRScram_DesignFile.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_SequentialStatementList.hh"
#include "IIRScram_WhileLoopStatement.hh"

#include "savant.hh"


extern bool parse_error;

IIRScram_WhileLoopStatement::IIRScram_WhileLoopStatement() {
  set_sequence_of_statements(new IIRScram_SequentialStatementList());
}

IIRScram_WhileLoopStatement::~IIRScram_WhileLoopStatement(){} 

void 
IIRScram_WhileLoopStatement::_type_check(){
  // Perform transformation on while condition.
  if( _get_while_condition() != NULL ){
    set_while_condition( _type_check_and_resolve_boolean_condition( _get_while_condition() ) );
    if( parse_error == FALSE ){
      ASSERT( _get_while_condition()->is_resolved() == TRUE );
    }
  }
}

IIR_Boolean 
IIRScram_WhileLoopStatement::_type_check_return_statements( savant::set<IIRScram_TypeDefinition> *context_set, IIRScram_SubprogramDeclaration *subprogram_decl ){
  IIR_Boolean retval = 
    IIRScram_SequentialStatement::_type_check_return_statements( context_set, _get_sequence_of_statements(), subprogram_decl );

  return retval;
}

IIRScram *
IIRScram_WhileLoopStatement::_clone() {
  IIRScram_WhileLoopStatement *whilestmt = new IIRScram_WhileLoopStatement();
  IIRScram *condition;
  
  IIRScram_SequentialStatement::_clone(whilestmt);
  condition = _get_while_condition()->_clone();
  whilestmt->set_while_condition(condition);

  IIRScram_SequentialStatement *newstmt = NULL;
  IIRScram_SequentialStatement *seqstmt = 
    dynamic_cast<IIRScram_SequentialStatement *>(get_sequence_of_statements()->first());
  while (seqstmt != NULL) {
    newstmt = dynamic_cast<IIRScram_SequentialStatement*>(seqstmt->_clone());
    whilestmt->get_sequence_of_statements()->append(newstmt);
    seqstmt = dynamic_cast<IIRScram_SequentialStatement *>(get_sequence_of_statements()->successor(seqstmt));
  }

  return whilestmt;
}

visitor_return_type *IIRScram_WhileLoopStatement::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_WhileLoopStatement(this, arg);
};

// IIRBase Function Wrapper(s)
IIRScram_SequentialStatementList *
IIRScram_WhileLoopStatement::_get_sequence_of_statements() {
  return dynamic_cast<IIRScram_SequentialStatementList *>(get_sequence_of_statements());
}

IIRScram *
IIRScram_WhileLoopStatement::_get_while_condition() {
  return dynamic_cast<IIRScram *>(get_while_condition());
}
