
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
//	    Magnus Danielson	cfmd@swipnet.se
//---------------------------------------------------------------------------

#include "IIRScram_CaseStatement.hh"
#include "IIRScram_CaseStatementAlternative.hh"
#include "IIRScram_CaseStatementAlternativeList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_SequentialStatementList.hh"
#include "IIRScram_TypeDefinition.hh"
#include "error_func.hh"
#include "set.hh"
#include <sstream>
using std::ostringstream;


IIRScram_CaseStatement::IIRScram_CaseStatement(){
  set_case_statement_alternatives(new IIRScram_CaseStatementAlternativeList());
}

IIRScram_CaseStatement::~IIRScram_CaseStatement(){
  //Release the list memory
  delete get_case_statement_alternatives();
}

void
IIRScram_CaseStatement::_type_check(){
  _type_check_case_statement_expression( _get_case_statement_alternatives() );
  ASSERT( is_resolved() == TRUE );
}

IIRScram *
IIRScram_CaseStatement::_handle_reconciliation( savant::set<IIRScram_TypeDefinition> *rval_set, 
                                                IIRScram *node_in_consideration, char *error_part ){
  IIRScram *retval = NULL;

  switch( rval_set->size() ){
  case 0:{
    ostringstream err;
    err << "|" << *node_in_consideration << "| is not a valid " << error_part 
	<< " in a case statement.";
    report_error( this, err.str() );
    break;
  }
  case 1:{
    IIRScram_TypeDefinition *rval =  rval_set->getElement();
    retval = node_in_consideration->_rval_to_decl( rval );
    break;
  }
  default:{
    report_ambiguous_error( node_in_consideration, rval_set->convert_set<IIR_TypeDefinition>() );
    break;
  }
  }
  return retval;
}

IIR_Boolean 
IIRScram_CaseStatement::_type_check_return_statements(savant::set<IIRScram_TypeDefinition> *context_set, 
                                                      IIRScram_SubprogramDeclaration *subprogram_decl ){
  IIR_Boolean retval = FALSE;
  
  IIRScram_CaseStatementAlternative *alternative;
  alternative = dynamic_cast<IIRScram_CaseStatementAlternative *>(get_case_statement_alternatives()->first());
  while( alternative != NULL ){
    IIR_Boolean found_one;
    found_one = alternative->_type_check_return_statements( context_set,
							    subprogram_decl );
    if( found_one == TRUE ){
      retval = TRUE;
    }

    alternative = dynamic_cast<IIRScram_CaseStatementAlternative *>(get_case_statement_alternatives()->successor( alternative ));
  }
  return retval;
}

void 
IIRScram_CaseStatement::_set_case_statement_expression( IIRScram *new_expression ){
  set_expression( new_expression );
}

IIRScram *
IIRScram_CaseStatement::_clone(){
  IIRScram *expr = NULL;
  IIRScram_CaseStatementAlternative *alt = NULL;
  IIRScram_CaseStatementAlternative *altclone = NULL;
  IIRScram_CaseStatement *clone = new IIRScram_CaseStatement();
  IIRScram_SequentialStatement::_clone(clone);

  expr = _get_expression()->_clone();
  clone->set_expression(expr);
  
  alt = dynamic_cast<IIRScram_CaseStatementAlternative *>(get_case_statement_alternatives()->first());
  while (alt != NULL) {
    altclone = dynamic_cast<IIRScram_CaseStatementAlternative *>(alt->_clone());
    clone->get_case_statement_alternatives()->append(altclone);
    alt = dynamic_cast<IIRScram_CaseStatementAlternative *>(get_case_statement_alternatives()->successor(alt));
  }
  return clone;
}

visitor_return_type *
IIRScram_CaseStatement::_accept_visitor( node_visitor *visitor,
					 visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_CaseStatement(this, arg);
}

IIRScram *
IIRScram_CaseStatement::_get_case_statement_expression(){
  return dynamic_cast<IIRScram *>(get_expression());
}

IIRScram *
IIRScram_CaseStatement::_get_expression() {
  return dynamic_cast<IIRScram *>(get_expression());
}

IIRScram_CaseStatementAlternativeList *
IIRScram_CaseStatement::_get_case_statement_alternatives() {
  return dynamic_cast<IIRScram_CaseStatementAlternativeList *>(get_case_statement_alternatives());
}
