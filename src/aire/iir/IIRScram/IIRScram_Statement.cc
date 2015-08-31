
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

//---------------------------------------------------------------------------

#include "IIRScram_ArraySubtypeDefinition.hh"
#include "IIRScram_AssociationElementByExpression.hh"
#include "IIRScram_CaseStatementAlternative.hh"
#include "IIRScram_CaseStatementAlternativeList.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_PhysicalSubtypeDefinition.hh"
#include "IIRScram_SimpleName.hh"
#include "IIRScram_Statement.hh"
#include "IIRScram_WaveformElement.hh"
#include "IIRScram_WaveformList.hh"
#include "error_func.hh"
#include "resolution_func.hh"
#include "set.hh"
#include "symbol_table.hh"
#include "savant.hh"
#include "StandardPackage.hh"

#include <sstream>
using std::ostringstream;

IIRScram_Statement::~IIRScram_Statement() {}

void 
IIRScram_Statement::_type_check( ) {
  _report_undefined_scram_fn("_type_check()");
}

IIRScram *
IIRScram_Statement::_type_check_and_resolve_boolean_condition( IIRScram *condition ){
  ASSERT( condition != NULL );
  
  if( condition->get_kind() == IIR_ASSOCIATION_ELEMENT_BY_EXPRESSION ){
    IIRScram *tmp = (dynamic_cast<IIRScram_AssociationElementByExpression *>(condition))->_get_actual();
    ASSERT( (dynamic_cast<IIRScram_AssociationElementByExpression *>(condition))->get_formal() != NULL );
    condition = tmp;
  }

  savant::set<IIRScram_TypeDefinition> *bool_rvals = 
    new savant::set<IIRScram_TypeDefinition>(dynamic_cast<IIRScram_EnumerationSubtypeDefinition *>(condition->_get_design_file()->get_standard_package()->get_boolean_type()));

  savant::set<IIRScram_TypeDefinition> *condition_rvals = condition->_get_rval_set();
  if( condition_rvals == NULL ){
    report_undefined_symbol( condition );
    return condition;
  }

  condition = condition->_semantic_transform( bool_rvals );
  condition->_type_check( bool_rvals );
  
  reconcile_sets( bool_rvals, condition_rvals );
  
  switch( condition_rvals->size() ){
  case 0:{
    // Then there are no boolean rvals for condition.
    ostringstream err;
    err <<"|" << *condition << "| does not return a boolean, which makes "
	<< "it invalid as a condition in this context.";
    report_error( condition, err.str() );
    break;
    }
  case 1:{
    condition = condition->_rval_to_decl( condition_rvals->getElement() );
    if( condition->_is_readable() == FALSE ){
      ostringstream err;
      err << "Expression |" << *condition << "| is not readable, and therefore invalid "
	  << "in this context.";
      report_error( condition, err.str() );
    }
    break;
  }
  
  default:{
    report_ambiguous_error( condition, condition_rvals->convert_set<IIR_TypeDefinition>() );
  }
  } // default:
  
  delete condition_rvals;
  delete bool_rvals;

  return condition;
}

void
IIRScram_Statement::_type_check_case_statement_expression( IIRScram_CaseStatementAlternativeList *alternatives ){
  IIRScram_TypeDefinition       *correct_rval = NULL;
  constraint_functor            *functor = NULL;

  ASSERT( _get_case_statement_expression() != NULL );
  savant::set<IIRScram_TypeDefinition> *expression_rvals;
  
  expression_rvals = _get_case_statement_expression()->_get_rval_set();
  if( expression_rvals == NULL ){
    report_undefined_symbol( _get_case_statement_expression() );
    goto finish;
  }

  // Eliminate all of the non-discrete types.  According to the LRM,
  // a discrete type is an enumeration, a range type, or a one
  // dimensional array...
  functor = new is_discrete_type_functor();
  expression_rvals->reduce_set( functor );
  delete functor;

  if( expression_rvals->size() == 0 ){
    ostringstream err;
    err << "|" << *_get_case_statement_expression() << "| is an invalid expression for a "
        << "case statement (or selected signal assignment).";
    report_error( _get_case_statement_expression(), err.str() );
    goto finish;
  }

  IIRScram_CaseStatementAlternative *current_alternative;
  current_alternative = dynamic_cast<IIRScram_CaseStatementAlternative *>(alternatives->first());
  if( current_alternative->get_kind() != IIR_CASE_STATEMENT_ALTERNATIVE_BY_OTHERS ){
    savant::set<IIRScram_TypeDefinition> *first_alt_rvals = current_alternative->_get_rval_set();
    if( first_alt_rvals == NULL ){
      report_undefined_symbol( current_alternative );
      goto finish;
    }
    reconcile_sets( expression_rvals, first_alt_rvals );
    delete first_alt_rvals;
  }
  
  _set_case_statement_expression( _get_case_statement_expression()->_semantic_transform( expression_rvals ) );

  switch( expression_rvals->size() ){
  case 0:{
    ostringstream err;
    err << "|" << *_get_case_statement_expression() << "| and |" << *current_alternative 
	<< "| are " << "incompatible.";
    report_error( _get_case_statement_expression(), err.str() );
    goto finish;
  }
  case 1:{
    correct_rval = expression_rvals->getElement();
    _set_case_statement_expression( _get_case_statement_expression()->_semantic_transform( correct_rval ) );
    _get_case_statement_expression()->_type_check( correct_rval );
    _set_case_statement_expression( _get_case_statement_expression()->_rval_to_decl( correct_rval ) );

    if( _get_case_statement_expression()->_get_subtype() != NULL &&
	_get_case_statement_expression()->_get_subtype()->is_locally_static() == FALSE ){
      ostringstream err;
      err << "When the expression of a case statement is of an array type, the expression "
	  << "must be locally static. |" << *_get_case_statement_expression() <<"| is not.";
      report_error( _get_case_statement_expression(),err.str() );
    }

    break;
  }
  default:{
    report_ambiguous_error( dynamic_cast<IIR *>(_get_case_statement_expression()), expression_rvals->convert_set<IIR_TypeDefinition>() );
    goto finish;
  }
  }

  current_alternative = dynamic_cast<IIRScram_CaseStatementAlternative *>(alternatives->first());
  while( current_alternative != NULL ){
    if( current_alternative->get_kind() != IIR_CASE_STATEMENT_ALTERNATIVE_BY_OTHERS ){
      IIRScram *temp_alternative = current_alternative->_semantic_transform( correct_rval );
      temp_alternative->_type_check( correct_rval );
      temp_alternative = temp_alternative->_rval_to_decl( correct_rval );

      alternatives->_replace( current_alternative, temp_alternative );
    }
    // else do nothing.
    current_alternative = 
      dynamic_cast<IIRScram_CaseStatementAlternative *>(alternatives->successor( current_alternative ));
  }

 finish:
  // The semantic transform and type check might have narrowed the rvals
  // of our expression...
  delete expression_rvals;  
}

void 
IIRScram_Statement::_set_case_statement_expression( IIRScram * ){
  _report_undefined_scram_fn("_set_case_statement_expression( IIRScram * )");
}

void 
IIRScram_Statement::_type_check_target_and_waveform( IIRScram_WaveformList *waveform_list ){
  savant::set<IIRScram_TypeDefinition> *waveform_rvals = dynamic_cast<IIRScram_WaveformElement *>(waveform_list->first())->_get_rval_set();
  if( waveform_rvals == NULL ){
    report_undefined_symbol( dynamic_cast<IIRScram_WaveformElement *>(waveform_list->first()) );
    return;
  }
  
  set_target( _get_target()->_semantic_transform( waveform_rvals ) );
  _get_target()->_type_check( waveform_rvals );

  savant::set<IIRScram_TypeDefinition> *target_lvals = _get_target()->_get_rval_set();
  if( target_lvals == NULL ){
    report_undefined_symbol( _get_target() );
    return;
  }

  IIRScram_TypeDefinition *target_lval = NULL;

  reconcile_sets( target_lvals, waveform_rvals );  
  switch( target_lvals->size() ){
  case 0:{
    ostringstream err;
    err << "Incompatible types in assignment: " << *_get_target() <<
      " <= " << *dynamic_cast<IIRScram_WaveformElement *>(waveform_list->first());
    report_error( _get_target(), err.str() );
    return;
    break;
  }
  case 1:{
    target_lval = target_lvals->getElement();
    set_target( _get_target()->_rval_to_decl( target_lval ) );
    if( _get_target()->is_signal() == FALSE ){
      ostringstream err;
      err << "|" << *_get_target() << "| is not signal valued, and therefore may not be"
	  << " the target of a signal assignment statement.";
      report_error( this, err.str() );
      return;
    }
    if( _get_target()->_is_writable() == FALSE ){
      ostringstream err;
      err << "|" << *_get_target() << "| is not writable, and therefore may not be"
	  << " the target of a signal assignment statement.";
      report_error( this, err.str() );
      delete target_lvals;
      return;
    }
    break;
  }
  default:{
    report_ambiguous_error( _get_target(), target_lvals->convert_set<IIR_TypeDefinition>() );
    return;
  }
  }
 
  delete target_lvals;
  delete waveform_rvals;

  // We have a whole list of waveforms that we need to check against...
  IIRScram_WaveformElement *current_waveform = dynamic_cast<IIRScram_WaveformElement *>(waveform_list->first());
  IIRScram_WaveformElement *temp_waveform = current_waveform;
  while( current_waveform != NULL ){
    temp_waveform =
      dynamic_cast<IIRScram_WaveformElement *>(current_waveform->IIRScram::_semantic_transform( target_lval ));

    temp_waveform->IIRScram::_type_check( target_lval );
    
    waveform_list->_replace( current_waveform, temp_waveform );
    current_waveform = temp_waveform;
    current_waveform = dynamic_cast<IIRScram_WaveformElement *>(current_waveform->_rval_to_decl( target_lval ) );
    ASSERT( current_waveform == temp_waveform );
    //    waveform_list->_replace( current_waveform, temp_waveform );

    if( current_waveform->_is_readable() == FALSE ){
      ostringstream err;
      err << "|" << *current_waveform << "| is not readable, and therefore may not be"
	  << " an expression of a signal assignment statement.";
      report_error( current_waveform, err.str() );
      return;      
    }

    current_waveform = dynamic_cast<IIRScram_WaveformElement *>(waveform_list->successor( current_waveform ));
  }

}

void 
IIRScram_Statement::_type_check_mechanism_and_time( IIRScram_WaveformList *waveform ){
  
  if( _get_delay_mechanism() == IIR_INERTIAL_DELAY ){
    // Either a reject time was specified, or not...
    if( _get_reject_time_expression() == NULL ){
      IIRScram_WaveformElement *first_waveform = dynamic_cast<IIRScram_WaveformElement *>(waveform->first());
      ASSERT( first_waveform != NULL );
      IIRScram *time_expression = dynamic_cast<IIRScram *>(first_waveform->get_time());
      if( time_expression != NULL ){
	ASSERT( time_expression->is_resolved() == TRUE );
	set_reject_time_expression( time_expression );
      }
    }
    else{
      StandardPackage *package = _get_design_file()->get_standard_package();
      IIRScram_TypeDefinition *time_rval = dynamic_cast<IIRScram_TypeDefinition *>(package->get_time_type());
      set_reject_time_expression(_get_reject_time_expression()->_semantic_transform( time_rval ));
      _get_reject_time_expression()->_type_check( time_rval );
      set_reject_time_expression( _get_reject_time_expression()->_rval_to_decl( time_rval ) );
    }
  }  
}

IIRScram *
IIRScram_Statement::_get_target(){
  _report_undefined_scram_fn("_get_target()");
  return NULL;
}

IIR_DelayMechanism
IIRScram_Statement::_get_delay_mechanism(){
  _report_undefined_scram_fn("_get_delay_mechanism");
  return IIR_INERTIAL_DELAY;
}

void 
IIRScram_Statement::_type_check_assertion_condition(){
  set_assertion_condition( _type_check_and_resolve_boolean_condition( _get_assertion_condition()) );
}

void 
IIRScram_Statement::_type_check_report_expression(){
  // This code was copied too IIRScram_ConcurrentAssertionStatement.
  // Any changes here need to be made there, too.

  StandardPackage       *package = _get_design_file()->get_standard_package();
  // Type check the expression  
  savant::set<IIRScram_TypeDefinition> *string_rvals = new savant::set<IIRScram_TypeDefinition>( dynamic_cast<IIRScram_TypeDefinition *>(package->get_string_type()) );
  set_report_expression( _get_report_expression()->_semantic_transform( string_rvals ));
  _get_report_expression()->_type_check( string_rvals );
  
  savant::set<IIRScram_TypeDefinition> *expression_rvals = _get_report_expression()->_get_rval_set();
  if( expression_rvals == NULL ){
    report_undefined_symbol( _get_report_expression() );
  }
  else{
    reconcile_sets( expression_rvals, string_rvals );
    
    switch( expression_rvals->size() ){
    case 0:{
      ostringstream err;
      
      err << "|" << *_get_report_expression() << "| must have a string "
	  << "return value";
      report_error( this, err.str() );
      
      break;
    }
    case 1:{
      IIRScram_TypeDefinition *my_rval = expression_rvals->getElement();
      set_report_expression( _get_report_expression()->_rval_to_decl( my_rval ) );
      break;
    }
    default:{
      report_ambiguous_error( _get_report_expression(), expression_rvals->convert_set<IIR_TypeDefinition>() );
    }
    }
  }
  delete string_rvals;
  delete expression_rvals;
}

void 
IIRScram_Statement::_type_check_severity_expression(){  
  // This code was copied too IIRScram_ConcurrentAssertionStatement.
  // Any changes here need to be made there, too.
  StandardPackage       *package = _get_design_file()->get_standard_package();

  savant::set<IIRScram_TypeDefinition> *severity_rvals =
    new savant::set<IIRScram_TypeDefinition>(dynamic_cast<IIRScram_EnumerationSubtypeDefinition *>(package->get_severity_level_type()));
  set_severity_expression( _get_severity_expression()->_semantic_transform( severity_rvals ));
  _get_severity_expression()->_type_check( severity_rvals );
  
  savant::set<IIRScram_TypeDefinition> *expression_rvals = _get_severity_expression()->_get_rval_set();
  if( expression_rvals == NULL ){
    report_undefined_symbol( _get_severity_expression() );
    return;
  }
  
  reconcile_sets( expression_rvals, severity_rvals );
  switch( expression_rvals->size() ){
  case 0:{
    ostringstream err;

    err << "|" << *_get_severity_expression() << "| must have a severity_leval "
	<< "return value";
    report_error( this, err.str() );

    break;
  }
  case 1:{
    set_severity_expression( _get_severity_expression()->_rval_to_decl( expression_rvals->getElement() ) );
    break;
  }
  default:{
    report_ambiguous_error( this, expression_rvals->convert_set<IIR_TypeDefinition>() );
  }
  }

  delete severity_rvals;
  delete expression_rvals;
}

IIRScram_Label *
IIRScram_Statement::_find_instantiate_label( IIRScram_SimpleName * ){
  return NULL;
}

void 
IIRScram_Statement::_make_interface_visible( symbol_table *add_to ){
  if( _get_label() != NULL ){
    add_to->make_visible( _get_label() );
  }
}

IIRScram_Label*
IIRScram_Statement::_get_label() const {
  return dynamic_cast<IIRScram_Label *>(get_label());
}

IIRScram *
IIRScram_Statement::_get_case_statement_expression(){
  _report_undefined_scram_fn("_get_case_statement_expression()");
  return NULL;
}

IIRScram *
IIRScram_Statement::_get_reject_time_expression(){
  _report_undefined_scram_fn("_get_reject_time_expression");
  return NULL;
}
