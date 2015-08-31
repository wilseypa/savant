
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
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------


#include "IIRScram_WaitStatement.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_DesignatorExplicit.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "IIRScram_PhysicalSubtypeDefinition.hh"
#include "StandardPackage.hh"
#include "resolution_func.hh"
#include "error_func.hh"
#include "set.hh"

#include <sstream>
using std::ostringstream;

IIRScram_WaitStatement::IIRScram_WaitStatement() {
  set_sensitivity_list(new IIRScram_DesignatorList());
}

IIRScram_WaitStatement::~IIRScram_WaitStatement() {}

void
IIRScram_WaitStatement::_type_check() {
  IIRScram        *signal_decl;
  IIRScram        *current_name;
  StandardPackage *package = _get_design_file()->get_standard_package();

  IIRScram_Designator *current_designator = dynamic_cast<IIRScram_Designator *>(get_sensitivity_list()->first());
  while (current_designator != NULL) {
    ASSERT(current_designator->get_kind() == IIR_DESIGNATOR_EXPLICIT);
    current_name = (dynamic_cast<IIRScram_DesignatorExplicit*>(current_designator))->_get_name();

    // If a signal in the sensitivity list can't be resolved, it will
    // complain about it in this function call...
    signal_decl = _resolve_signal_name(current_name);
    if (signal_decl != NULL) {
      // This might leak a name...
      (dynamic_cast<IIRScram_DesignatorExplicit *>(current_designator))->set_name(signal_decl);
    }
    current_designator = dynamic_cast<IIRScram_Designator *>(get_sensitivity_list()->successor(current_designator));
  }
  
  if( _get_condition_clause() != NULL ){
    IIRScram_TypeDefinition *boolean_type = 
      dynamic_cast<IIRScram_EnumerationSubtypeDefinition *>(package->get_boolean_type());

    savant::set<IIRScram_TypeDefinition> *boolean_set = new savant::set<IIRScram_TypeDefinition>( boolean_type );
    savant::set<IIRScram_TypeDefinition> *condition_clause_types = _get_condition_clause()->_get_rval_set();

    reconcile_sets( condition_clause_types, boolean_set );
    if( condition_clause_types->size() != 0 ){
      set_condition_clause( _get_condition_clause()->_semantic_transform( boolean_type ) );
      _get_condition_clause()->_type_check( boolean_type );
      set_condition_clause( _get_condition_clause()->_rval_to_decl( boolean_type ) );
    }
    else{
      ostringstream err;
      err << "A condition clause must have a subtype of |boolean|.";
      report_error( this, err.str() );
    }

    delete boolean_set;
    delete condition_clause_types;
  }

  if( _get_timeout_clause() != NULL ){
    IIRScram_TypeDefinition *time_type = 
      dynamic_cast<IIRScram_PhysicalSubtypeDefinition *>(package->get_time_type());
    savant::set<IIRScram_TypeDefinition> *time_set = new savant::set<IIRScram_TypeDefinition>( time_type );
    savant::set<IIRScram_TypeDefinition> *timeout_clause_types = _get_timeout_clause()->_get_rval_set();
    
    reconcile_sets( timeout_clause_types, time_set );
    if( timeout_clause_types->size() != 0 ){
      set_timeout_clause( _get_timeout_clause()->_semantic_transform( time_type ) );
      _get_timeout_clause()->_type_check( time_type );
      set_timeout_clause( _get_timeout_clause()->_rval_to_decl( time_type ) );
    }
    else{
      ostringstream err;
      err << "A timeout clause must have a subtype of |time|.";
      report_error( this, err.str() );
    }
    delete time_set;
    delete timeout_clause_types;
  }
}

IIRScram *
IIRScram_WaitStatement::_resolve_signal_name(IIRScram *sig_name) {
  IIRScram *retval = NULL;
  constraint_functor *functor = new is_signal_functor;
  savant::set<IIRScram_TypeDefinition> *signal_rvals = sig_name->_get_rval_set(functor);
  delete functor;

  if( signal_rvals == NULL ){
    report_undefined_symbol( sig_name );
    return NULL;
  }

  switch (signal_rvals->size()) {
  case 0: {
    ostringstream err;
    err << "Signal " << *sig_name << " is undeclared in this scope.";
    report_error( this, err.str() );
    break;
  }
  case 1: {
    IIRScram_TypeDefinition *sig_type = signal_rvals->getElement();

    IIRScram *sig_name_transformed = sig_name->_semantic_transform( sig_type );
    sig_name_transformed->_type_check( sig_type );
    retval = sig_name_transformed->_rval_to_decl( sig_type );

    ASSERT( retval->is_resolved() == TRUE );
    break;
  }
  default:
    ostringstream err;
    report_ambiguous_error( sig_name, signal_rvals->convert_set<IIR_TypeDefinition>() );
    break;    
  }

  delete signal_rvals;
  return retval;
}

IIRScram*
IIRScram_WaitStatement::_clone() {
  IIRScram_WaitStatement *stmt = NULL;
  IIRScram *condition = NULL, *timeout = NULL;
  IIRScram_Designator *oldname = NULL, *newname = NULL;

  stmt = new IIRScram_WaitStatement();
  IIRScram_SequentialStatement::_clone(stmt);

  condition = _get_condition_clause();
  if (condition != NULL) {
    condition = condition->_clone();
  }
  stmt->set_condition_clause(condition);

  timeout = _get_timeout_clause();
  if (timeout != NULL) {
    timeout = timeout->_clone();
  }
  stmt->set_timeout_clause(timeout);

  oldname = dynamic_cast<IIRScram_Designator *>(get_sensitivity_list()->first());
  while (oldname != NULL) {
    newname = dynamic_cast<IIRScram_Designator*>(oldname->_clone());
    stmt->get_sensitivity_list()->append(newname);
    oldname = dynamic_cast<IIRScram_Designator *>(get_sensitivity_list()->successor(oldname));
  }

  return stmt;
}

visitor_return_type *
IIRScram_WaitStatement::_accept_visitor( node_visitor *visitor, 
					 visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_WaitStatement(this, arg);
}

// IIRBase Function Wrapper(s)
IIRScram_DesignatorList *
IIRScram_WaitStatement::_get_sensitivity_list() {
  return dynamic_cast<IIRScram_DesignatorList *>(get_sensitivity_list());
}

IIRScram*
IIRScram_WaitStatement::_get_condition_clause() {
  return dynamic_cast<IIRScram *>(get_condition_clause());
}

IIRScram *
IIRScram_WaitStatement::_get_timeout_clause() {
  return dynamic_cast<IIRScram *>(get_timeout_clause());
}
