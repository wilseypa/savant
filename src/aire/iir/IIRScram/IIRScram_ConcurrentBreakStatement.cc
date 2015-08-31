
// Copyright (c) 2003 The University of Cincinnati.
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

// Author: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_ConcurrentBreakStatement.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_BreakElement.hh"
#include "IIRScram_BreakList.hh"
#include "IIRScram_DesignatorExplicit.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_Label.hh"

#include "break_handler.hh"
#include "error_func.hh"
#include "set.hh"

IIRScram_ConcurrentBreakStatement::IIRScram_ConcurrentBreakStatement() {
  set_concurrent_break_list(new IIRScram_BreakList());
  set_sensitivity_list(new IIRScram_DesignatorList());
}

IIRScram_ConcurrentBreakStatement::~IIRScram_ConcurrentBreakStatement(){}

void
IIRScram_ConcurrentBreakStatement::_build_break_info() {
  break_handler *breakInfo;
  breakInfo = new break_handler;
  breakInfo->set_condition(_get_condition());
  breakInfo->set_breaklist(get_concurrent_break_list());
  breakInfo->set_sensitivitylist(get_sensitivity_list());
}

void
IIRScram_ConcurrentBreakStatement::_type_check() {
  IIRScram *signal_decl = NULL;
  IIRScram *current_name = NULL;
  IIRScram *new_condition = NULL;
  IIRScram_BreakElement *break_element 
    = dynamic_cast<IIRScram_BreakElement *>(get_concurrent_break_list()->first());
  while(break_element != NULL) {
    break_element->_type_check();
    break_element = dynamic_cast<IIRScram_BreakElement *>(get_concurrent_break_list()->successor(break_element));
  }
  IIRScram_Designator *current_designator
    = dynamic_cast<IIRScram_Designator *>(get_sensitivity_list()->first());
  while (current_designator != NULL) {
    ASSERT(current_designator->get_kind() == IIR_DESIGNATOR_EXPLICIT);
    current_name = dynamic_cast<IIRScram_DesignatorExplicit*>(current_designator)->_get_name();
    signal_decl = _resolve_signal_name(current_name);
    if (signal_decl != NULL) {
      dynamic_cast<IIRScram_DesignatorExplicit *>(current_designator)->set_name(signal_decl);
    }
    current_designator 
      = dynamic_cast<IIRScram_Designator *>(get_sensitivity_list()->successor(current_designator));
  }
  if( _get_condition() != NULL ){
    new_condition = _type_check_and_resolve_boolean_condition(_get_condition());
    ASSERT( new_condition != NULL );
    ASSERT( new_condition->is_resolved() == TRUE );
    set_condition( new_condition );
  }
}

IIRScram *
IIRScram_ConcurrentBreakStatement::_resolve_signal_name(IIRScram *sig_name) {
  IIRScram *retval;
  constraint_functor *functor = new is_signal_functor;
  savant::set<IIRScram_TypeDefinition> *signal_rvals = sig_name->_get_rval_set( functor );
  delete functor;
  
  if( signal_rvals == NULL ){
    report_undefined_symbol( sig_name );
    return NULL;
  }
  switch (signal_rvals->size()) {
  case 0: {
    report_undefined_symbol( sig_name );
    return NULL;
    break;
  }
  case 1: {
    IIRScram_TypeDefinition *sig_type = signal_rvals->getElement();
    sig_name = sig_name->_semantic_transform( sig_type );
    sig_name->_type_check( sig_type );
    retval = sig_name->_rval_to_decl( sig_type );
    ASSERT( retval->is_resolved() == TRUE );
    break;
  }
  default:
    report_ambiguous_error( sig_name, signal_rvals->convert_set<IIR_TypeDefinition>() );
    break;
  }
  delete signal_rvals;
  return retval;
}

IIRScram_BreakList *
IIRScram_ConcurrentBreakStatement::_get_concurrent_break_list() {
  return dynamic_cast<IIRScram_BreakList *>(get_concurrent_break_list());
}

IIRScram_DesignatorList *
IIRScram_ConcurrentBreakStatement::_get_sensitivity_list() {
  return dynamic_cast<IIRScram_DesignatorList *>(get_sensitivity_list());
}

IIRScram *
IIRScram_ConcurrentBreakStatement::_get_condition() {
  return dynamic_cast<IIRScram *>(get_condition());
}
