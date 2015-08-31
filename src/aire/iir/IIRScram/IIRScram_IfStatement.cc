
// Copyright (c) 1996-2003 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING
// OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found
// in the file "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer
//          Malolan Chetlur    
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam

//---------------------------------------------------------------------------

#include "IIRScram_DesignFile.hh"
#include "IIRScram_Elsif.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "IIRScram_IfStatement.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_SequentialStatementList.hh"

#include "resolution_func.hh"
#include "IIR_AboveAttribute.hh"
#include "StandardPackage.hh"
#include "set.hh"

#include "plugin_class_factory.hh"

extern bool parse_error;

IIRScram_IfStatement::IIRScram_IfStatement() {
  set_then_sequence(new IIRScram_SequentialStatementList());
  set_else_sequence(new IIRScram_SequentialStatementList());
  _full_statement_list = NULL;
}

IIRScram_IfStatement::~IIRScram_IfStatement(){}

void
IIRScram_IfStatement::_type_check(){
  IIRScram *new_condition = _type_check_and_resolve_boolean_condition( _get_condition() );
  ASSERT( new_condition != NULL );
  if( parse_error == FALSE ){
    ASSERT( new_condition->is_resolved() == TRUE );
    set_condition( new_condition );
  }

  IIRScram_TypeDefinition *bool_type = dynamic_cast<IIRScram_TypeDefinition *>(_get_design_file()->get_standard_package()->get_boolean_type());

  if ( get_elsif() != NULL ){
    _get_elsif()->IIRScram::_type_check( bool_type );
  }
}

IIR_Boolean 
IIRScram_IfStatement::_type_check_return_statements( savant::set<IIRScram_TypeDefinition> *context_set, IIRScram_SubprogramDeclaration *subprogram_decl ){
  IIR_Boolean retval = false;

  IIR_Boolean retval1 = false;
  retval1 = 
    IIRScram_SequentialStatement::_type_check_return_statements( context_set, _get_then_sequence(), subprogram_decl );
  
  IIR_Boolean retval2 = false;
  retval2 = 
    IIRScram_SequentialStatement::_type_check_return_statements( context_set, _get_else_sequence(), subprogram_decl );

  IIR_Boolean retval3 = false;
  if ( _get_elsif() != NULL ){
    retval3 =
      _get_elsif()->_type_check_return_statements(context_set, subprogram_decl);
  }

  if ( retval1 == TRUE || retval2 == TRUE || retval3 == TRUE ){
    retval = TRUE;
  }

  return retval;
}


IIRScram*
IIRScram_IfStatement::_clone() {
  IIRScram_IfStatement *clone = new IIRScram_IfStatement();
  IIRScram::_clone( clone );
  IIRScram *condition = _get_condition();
  IIRScram_SequentialStatement *stmt = NULL;
  IIRScram_SequentialStatement *newstmt = NULL;
  IIRScram_Elsif *elsif;

  clone->set_label(_get_label());
  condition = condition->_clone();
  clone->set_condition(condition);

  stmt = dynamic_cast<IIRScram_SequentialStatement *>(get_then_sequence()->first());
  while (stmt != NULL) {
    newstmt = dynamic_cast<IIRScram_SequentialStatement*>(stmt->_clone());
    clone->get_then_sequence()->append(newstmt);
    stmt = dynamic_cast<IIRScram_SequentialStatement *>(get_then_sequence()->successor(stmt));
  }

  stmt = dynamic_cast<IIRScram_SequentialStatement *>(get_else_sequence()->first());
  while (stmt != NULL) {
    newstmt = dynamic_cast<IIRScram_SequentialStatement*>(stmt->_clone());
    clone->get_else_sequence()->append(newstmt);
    stmt = dynamic_cast<IIRScram_SequentialStatement *>(get_else_sequence()->successor(stmt));
  }

  elsif = _get_elsif();
  if (elsif != NULL) {
    elsif = dynamic_cast<IIRScram_Elsif*>(elsif->_clone());
  }
  clone->set_elsif(elsif);

  return clone;
}

visitor_return_type *IIRScram_IfStatement::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_IfStatement(this, arg);
};

// IIRBase Function Wrapper(s)
IIRScram_SequentialStatementList *
IIRScram_IfStatement::_get_then_sequence() {
  return dynamic_cast<IIRScram_SequentialStatementList *>(get_then_sequence());
}

IIRScram *
IIRScram_IfStatement::_get_condition() {
  return dynamic_cast<IIRScram *>(get_condition());
}

IIRScram_Elsif *
IIRScram_IfStatement::_get_elsif() {
  return dynamic_cast<IIRScram_Elsif *>(get_elsif());
}

IIRScram_SequentialStatementList *
IIRScram_IfStatement::_get_else_sequence() {
  return dynamic_cast<IIRScram_SequentialStatementList *>(get_else_sequence());
}
