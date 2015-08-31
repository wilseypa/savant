
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
//          Umesh Kumar V. Rajasekaran
//---------------------------------------------------------------------------

#include "savant.hh"
#include "IIRScram_ReportStatement.hh"

void 
IIRScram_ReportStatement::_type_check(){
  if( get_report_expression() != NULL ){
    _type_check_report_expression();
  }

  if( get_severity_expression() != NULL ){
    _type_check_severity_expression();
  }
}

// IIR_Boolean
// IIRScram_ReportStatement::_is_above_attribute_found() {
//   IIR_Boolean retval = FALSE;
//   retval = retval || get_report_expression()->_is_above_attribute_found();
//   if(get_severity_expression() != NULL) {
//     retval = retval || get_severity_expression()->_is_above_attribute_found();
//   }
//   return retval;
// }

// void
// IIRScram_ReportStatement::_build_above_attribute_set(savant::set<IIR_AboveAttribute> *to_build) {
//   get_report_expression()->_build_above_attribute_set(to_build);
//   if(get_severity_expression() != NULL) {
//     get_severity_expression()->_build_above_attribute_set(to_build);
//   }
// }

visitor_return_type *
IIRScram_ReportStatement::_accept_visitor( node_visitor *visitor, 
					   visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ReportStatement(this, arg);
}

IIRScram *
IIRScram_ReportStatement::_get_report_expression(){ 
  return dynamic_cast<IIRScram *>(get_report_expression());
}

IIRScram *
IIRScram_ReportStatement::_get_severity_expression(){ 
  return dynamic_cast<IIRScram *>(get_severity_expression()); 
}
