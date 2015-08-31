
// Copyright (c) 1996-1999 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
// DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.


// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     mal@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRBase_ReportStatement.hh"
#include "savant.hh"

IIRBase_ReportStatement::IIRBase_ReportStatement() {
  set_report_expression(NULL);
  set_severity_expression(NULL);
}

IIRBase_ReportStatement::~IIRBase_ReportStatement() {
  delete get_report_expression();
  delete get_severity_expression();
}

void 
IIRBase_ReportStatement::set_report_expression( IIR* report_expression) {
  this->report_expression  = report_expression;
}

IIR* 
IIRBase_ReportStatement::get_report_expression() {
  return report_expression;
}

void 
IIRBase_ReportStatement::set_severity_expression( IIR* severity_expression) {
  this->severity_expression = severity_expression;
}

IIR* 
IIRBase_ReportStatement::get_severity_expression() {
  return severity_expression;
}

IIR_Boolean
IIRBase_ReportStatement::is_above_attribute_found() {
  IIR_Boolean retval = FALSE;
  retval = retval || get_report_expression()->is_above_attribute_found();
  if(get_severity_expression() != NULL) {
    retval = retval || get_severity_expression()->is_above_attribute_found();
  }
  return retval;
}

IIR *
IIRBase_ReportStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ReportStatement *new_node = dynamic_cast<IIRBase_ReportStatement *>(IIRBase_SequentialStatement::convert_tree(factory));

  // Process the variables
  new_node->report_expression = convert_node(report_expression, factory);
  new_node->severity_expression = convert_node(severity_expression, factory);

  return new_node;
}

void 
IIRBase_ReportStatement::publish_vhdl(ostream &vhdl_out) {

  publish_vhdl_stmt_label(vhdl_out);

  vhdl_out << "   report ";
  get_report_expression()->publish_vhdl(vhdl_out);

  if(get_severity_expression() != NULL) {
    vhdl_out << "\n";
    vhdl_out << "     severity ";
    get_severity_expression()->publish_vhdl(vhdl_out);
  }
}
