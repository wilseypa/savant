
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
//          Malolan Chetlur     
//          Krishnan Subramani  
//          Umesh Kumar V. Rajasekaran
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram.hh"
#include "IIRScram_AssertionStatement.hh"

IIRScram_AssertionStatement::~IIRScram_AssertionStatement(){}

void 
IIRScram_AssertionStatement::_type_check(){
  // This code was copied too IIRScram_ConcurrentAssertionStatement.
  // Any changes here need to be made there, too.

  if( get_assertion_condition() != NULL ){
    _type_check_assertion_condition();
  }

  if( get_report_expression() != NULL ){
    _type_check_report_expression();
  }

  if( get_severity_expression() != NULL ){
    _type_check_severity_expression();
  }
}

IIRScram*
IIRScram_AssertionStatement::_clone() {
  IIRScram_AssertionStatement *clone = new IIRScram_AssertionStatement();
  IIRScram_SequentialStatement::_clone( clone );

  clone->set_assertion_condition( _get_assertion_condition()->_clone() );
  clone->set_report_expression( _get_report_expression()->_clone() );
  clone->set_severity_expression( _get_severity_expression()->_clone() );

  return clone;
}

visitor_return_type *
IIRScram_AssertionStatement::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_AssertionStatement(this, arg);
};

IIRScram *
IIRScram_AssertionStatement::_get_assertion_condition(){ 
  return dynamic_cast<IIRScram *>(get_assertion_condition()); 
}
  
IIRScram *
IIRScram_AssertionStatement::_get_report_expression(){ 
  return dynamic_cast<IIRScram *>(get_report_expression()); 
}
  
IIRScram *
IIRScram_AssertionStatement::_get_severity_expression(){ 
  return dynamic_cast<IIRScram *>(get_severity_expression()); 
}
