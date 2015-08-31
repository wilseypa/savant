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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_DesignFile.hh"
#include "IIRScram_Elsif.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "IIRScram_IfStatement.hh"
#include "IIRScram_SequentialStatement.hh"
#include "IIRScram_SequentialStatementList.hh"

#include "resolution_func.hh"
#include "set.hh"
#include "StandardPackage.hh"


IIRScram_Elsif::IIRScram_Elsif() {
  set_then_sequence_of_statements(new IIRScram_SequentialStatementList());
}

IIRScram_Elsif::~IIRScram_Elsif() {
  //Release the list memory
  delete get_then_sequence_of_statements();
}

void 
IIRScram_Elsif::_type_check( savant::set<IIRScram_TypeDefinition> * ){
  set_condition( IIRScram_Statement::_type_check_and_resolve_boolean_condition( _get_condition() ) );

  if( _get_else_clause() != NULL ){
    savant::set<IIRScram_TypeDefinition> *bool_rvals = new savant::set<IIRScram_TypeDefinition>( dynamic_cast<IIRScram_EnumerationSubtypeDefinition *>(_get_design_file()->get_standard_package()->get_boolean_type() ));
    _get_else_clause()->_type_check( bool_rvals );
    delete bool_rvals;
  }
}

IIR_Boolean 
IIRScram_Elsif::_type_check_return_statements( savant::set<IIRScram_TypeDefinition> *context_set, IIRScram_SubprogramDeclaration *subprogram_decl ){
  IIR_Boolean retval = FALSE;

  IIR_Boolean retval1 = FALSE;
  retval1 = 
    IIRScram_SequentialStatement::_type_check_return_statements(context_set, _get_then_sequence_of_statements(), subprogram_decl );

  IIR_Boolean retval2 = FALSE;
  if( _get_else_clause() != NULL ){
    retval2 =
      _get_else_clause()->_type_check_return_statements( context_set, subprogram_decl );
  }

  if( retval1 == TRUE || retval2 == true ){
    retval = TRUE;
  }

  return retval;
}


IIRScram*
IIRScram_Elsif::_clone() {
  IIRScram *condition = NULL;
  IIRScram_Elsif *elsif = NULL;
  IIRScram_SequentialStatement *stmt, *newstmt;
  IIRScram_Elsif *clone = new IIRScram_Elsif();
  IIRScram::_clone( clone );

  condition = _get_condition()->_clone();
  clone->set_condition(condition);
  elsif = _get_else_clause();
  if (elsif != NULL) {
    elsif = dynamic_cast<IIRScram_Elsif*>(elsif->_clone());
  }
  clone->set_else_clause(elsif);

  stmt = dynamic_cast<IIRScram_SequentialStatement *>(get_then_sequence_of_statements()->first());
  while (stmt != NULL) {
    newstmt = dynamic_cast<IIRScram_SequentialStatement*>(stmt->_clone());
    clone->get_then_sequence_of_statements()->append(newstmt);
    stmt = dynamic_cast<IIRScram_SequentialStatement *>(get_then_sequence_of_statements()->successor(stmt));
  }

  return clone;
}

visitor_return_type *IIRScram_Elsif::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_Elsif(this, arg);
}

// IIRBase Function Wrapper(s)
IIRScram_SequentialStatementList *
IIRScram_Elsif::_get_then_sequence_of_statements() {
  return dynamic_cast<IIRScram_SequentialStatementList *>(get_then_sequence_of_statements());
}

IIRScram *
IIRScram_Elsif::_get_condition() {
  return dynamic_cast<IIRScram *>(get_condition());
}

IIRScram_Elsif*
IIRScram_Elsif::_get_else_clause() {
  return dynamic_cast<IIRScram_Elsif *>(get_else_clause());
}
