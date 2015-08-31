
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

// Authors: Sivakumar Gowrisankar             gowriss@ececs.uc.edu
//          Kathiresan Nellayappan
//          Vasudevan Shanmugasundaram

//---------------------------------------------------------------------------

#include "IIRScram_SimpleSimultaneousStatement.hh"
#include "IIRScram_Label.hh"

#include "set.hh"
#include "resolution_func.hh"
#include "error_func.hh"

#include <iostream>
using std::endl;
#include <sstream>
using std::ostringstream;

IIRScram_SimpleSimultaneousStatement::IIRScram_SimpleSimultaneousStatement(){}

IIRScram_SimpleSimultaneousStatement::~IIRScram_SimpleSimultaneousStatement() {}

void
IIRScram_SimpleSimultaneousStatement::_type_check() {
  savant::set<IIRScram_TypeDefinition> *lexp_lvals = _get_left_expression()->_get_rval_set();
  if( lexp_lvals == NULL ){
    report_undefined_symbol( _get_left_expression() );
    return;
  }
  set_right_expression(_get_right_expression()->_semantic_transform(lexp_lvals));

  savant::set<IIRScram_TypeDefinition> *rexp_rvals= _get_right_expression()->_get_rval_set();

  if( rexp_rvals == NULL ){
    report_undefined_symbol( get_right_expression() );
    return;
  }

  set_left_expression( _get_left_expression()->_semantic_transform( rexp_rvals ));

  delete lexp_lvals;
  delete rexp_rvals;

  lexp_lvals = _get_left_expression()->_get_rval_set();
  rexp_rvals= _get_right_expression()->_get_rval_set();

  reconcile_sets( lexp_lvals, rexp_rvals);
  switch ( lexp_lvals->size() ){
  case 0: {
    ostringstream err;
    err << "Incompatible types in simultaneous statement : " << *_get_left_expression()
        << " == " << *_get_right_expression();
    report_error( this, err.str());
    break;
  }
  case 1: {
    set_right_expression( _get_right_expression()->_rval_to_decl(rexp_rvals->getElement() ) );
    set_left_expression( _get_left_expression()->_rval_to_decl(lexp_lvals->getElement() ) );
    break;
  }
  default:
    ostringstream err;
    err << "Ambiguous assignment - cannot resolve types";
    report_error(this, err.str());
    break;
  }
  delete lexp_lvals;
  delete rexp_rvals;
}

IIRScram *
IIRScram_SimpleSimultaneousStatement::_get_left_expression() {
  return dynamic_cast<IIRScram *>(get_left_expression());
}

IIRScram *
IIRScram_SimpleSimultaneousStatement::_get_right_expression() {
  return dynamic_cast<IIRScram *>(get_right_expression());
}
