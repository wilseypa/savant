
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
//          Umesh Kumar V. Rajasekaran
//          Krishnan Subramani 
//          Narayanan Thondugulam

//---------------------------------------------------------------------------

#include "IIRScram_AboveAttribute.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_ProcedureCallStatement.hh"
#include "IIRScram_ReturnStatement.hh"
#include "IIRScram_SequentialStatementList.hh"
#include "IIRScram_SubprogramDeclaration.hh"
#include "savant.hh"

#include "IIR_Label.hh"

IIRScram_SequentialStatement::~IIRScram_SequentialStatement() {}

IIR_Boolean
IIRScram_SequentialStatement::_type_check_return_statements( savant::set<IIRScram_TypeDefinition> *, 
                                                             IIRScram_SubprogramDeclaration * ) {
  _report_undefined_scram_fn("_type_check_return_statements( savant::set<IIRScram_TypeDefinition> *, IIRScram_SubprogramDeclaration *)");

  return FALSE;
}

IIR_Boolean 
IIRScram_SequentialStatement::_type_check_return_statements(savant::set<IIRScram_TypeDefinition> *context_set, IIRScram_SequentialStatementList *list, IIRScram_SubprogramDeclaration *subprogram_decl ){

  IIR_Boolean retval = FALSE;

  IIRScram_SequentialStatement *current_statement = NULL;
  current_statement = dynamic_cast<IIRScram_SequentialStatement *>(list->first());
  while( current_statement != NULL ){
    if( current_statement->get_kind() == IIR_RETURN_STATEMENT ){
      (dynamic_cast<IIRScram_ReturnStatement *>(current_statement))->set_enclosing_subprogram( subprogram_decl );
      (dynamic_cast<IIRScram_ReturnStatement *>(current_statement))->_type_check( context_set );
      retval = TRUE;
    }
    else if( current_statement->has_statement_list() == TRUE ){
      IIR_Boolean found_one;
      found_one = 
	current_statement->_type_check_return_statements( context_set, subprogram_decl );
      if( found_one == TRUE ){
	retval = TRUE;
      }
    }
    current_statement = dynamic_cast<IIRScram_SequentialStatement *>(list->successor( current_statement ));
  }

  return retval;
}

IIRScram *
IIRScram_SequentialStatement::_clone() {
  return IIRScram::_clone();
}


void
IIRScram_SequentialStatement::_clone( IIRScram *clone ){
  ASSERT( clone->_is_iir_sequential_statement() == TRUE );

  IIRScram::_clone( clone );
  // clone IIRScram_SequentialStatement info

  IIRScram_SequentialStatement *as_statement = dynamic_cast<IIRScram_SequentialStatement *>(clone);

  as_statement->set_label( get_label() );
}

IIR_Label *
IIRScram_SequentialStatement::_get_process_stmt_label(){
  return 0;
}

void
IIRScram_SequentialStatement::_set_process_stmt_label(IIR_Label *) {
}
