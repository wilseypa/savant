
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
//          Radharamanan Radhakrishnan
//          Narayanan Thondugulam
//---------------------------------------------------------------------------

#include "IIRScram_DesignFile.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_VariableAssignmentStatement.hh"

#include "error_func.hh"
#include "set.hh"
#include "resolution_func.hh"
#include "savant.hh"

#include <sstream>
using std::ostringstream;

// This type checking should make sure that any functions are being with
// legal arguments and such...
void 
IIRScram_VariableAssignmentStatement::_type_check(){
  savant::set<IIRScram_TypeDefinition> *target_lvals = _get_target()->_get_rval_set();
  if( target_lvals == NULL ){
    report_undefined_symbol( _get_target() );
    return;
  }
  set_expression( _get_expression()->_semantic_transform( target_lvals ));

  savant::set<IIRScram_TypeDefinition> *expression_rvals = _get_expression()->_get_rval_set();
  if( expression_rvals == NULL ){
    report_undefined_symbol( _get_expression() );
    return;
  }
  set_target( _get_target()->_semantic_transform( expression_rvals ));

  _get_target()->_type_check( expression_rvals );
  
  // Need to recalculate AFTER the transformation...
  delete target_lvals;
  target_lvals = _get_target()->_get_rval_set();
  _get_expression()->_type_check( target_lvals );

  delete expression_rvals;
  delete target_lvals;

  target_lvals = _get_target()->_get_rval_set();
  expression_rvals = _get_expression()->_get_rval_set();

  reconcile_sets( target_lvals, expression_rvals );

  switch( target_lvals->size() ){
  case 0:{
    ostringstream err;

    err << "Incompatible types in assignment: " << *_get_target()
	<< " := " << *_get_expression();

    report_error( this, err.str() );
    break;
  }
  case 1:{
    IIRScram_TypeDefinition *type = target_lvals->getElement(); 
    set_expression( _get_expression()->_rval_to_decl( type ));
    set_target( _get_target()->_rval_to_decl( type ) );

    if( _get_expression()->_is_readable() == FALSE ){
      ostringstream err;
      err << "Expression |" << *_get_expression() << "| cannot be read from.";
      report_error( this, err.str() );
    }

    if( _get_target()->_is_writable() == FALSE ){
      ostringstream err;
      err << "Target |" << *_get_target() << "| is not writable and cannot be assigned to.";
      report_error( this, err.str() );
    }
    
    if( _get_target()->is_variable() == FALSE ){
      ostringstream err;
      err << "Target |" << *_get_target() << "| is not a variable and cannot be assigned"
	  << " through a variable assignment statement.";
      report_error( this, err.str() );
    }

    break;
  }
  default:
    ostringstream err;
    err << "Ambigous assignment - cannot resolve types";
    report_error( this, err.str() );
    break;    
  }

  delete target_lvals;
  delete expression_rvals;
}

IIRScram*
IIRScram_VariableAssignmentStatement::_clone() {
  IIRScram *exprclone = NULL;
  IIRScram_VariableAssignmentStatement *clone = new IIRScram_VariableAssignmentStatement;
  IIRScram_SequentialStatement::_clone(clone);

  clone->set_target(_get_target()->_clone());
  exprclone = _get_expression()->_clone();
  clone->set_expression(exprclone);

  return clone;
}

visitor_return_type *
IIRScram_VariableAssignmentStatement::_accept_visitor( node_visitor *visitor,
						       visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_VariableAssignmentStatement(this, arg);
}

IIRScram *
IIRScram_VariableAssignmentStatement::_get_target() {
  return dynamic_cast<IIRScram *>(get_target());
}

IIRScram*
IIRScram_VariableAssignmentStatement::_get_expression() {
  return dynamic_cast<IIRScram *>(get_expression());
}

