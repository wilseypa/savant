
// Copyright (c) 1996-2001 The University of Cincinnati.  
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
//          Malolan Chetlur     
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam

//---------------------------------------------------------------------------
#include "IIRScram_ConcurrentAssertionStatement.hh"

void 
IIRScram_ConcurrentAssertionStatement::_type_check(){
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

visitor_return_type *
IIRScram_ConcurrentAssertionStatement::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ConcurrentAssertionStatement(this, arg);
};

IIRScram *
IIRScram_ConcurrentAssertionStatement::_get_assertion_condition(){ 
  return dynamic_cast<IIRScram *>(get_assertion_condition()); 
}

IIRScram *
IIRScram_ConcurrentAssertionStatement::_get_report_expression(){ 
  return dynamic_cast<IIRScram *>(get_report_expression());
}

IIRScram *
IIRScram_ConcurrentAssertionStatement::_get_severity_expression() { 
  return dynamic_cast<IIRScram *>(get_severity_expression()); 
}
