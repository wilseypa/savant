
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

#include "IIRBase_Statement.hh"
#include "savant.hh"
#include "IIR_Label.hh"

class IIR_Statement;

IIRBase_Statement::IIRBase_Statement() {
  set_label(NULL);
}

IIRBase_Statement::~IIRBase_Statement(){}

void
IIRBase_Statement::set_label( IIR_Label *label) {
  my_label = label;
  if( label != NULL ){
    label->set_statement( (IIR_Statement *) this );
  }
}

IIR_Label *
IIRBase_Statement::get_label() const {
  return my_label;
}

IIR *
IIRBase_Statement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_Statement *new_node = dynamic_cast<IIRBase_Statement *>(IIRBase::convert_tree(factory));

  // Process the variables
  new_node->my_label = dynamic_cast<IIR_Label *>(convert_node(my_label, factory));

  return new_node;
}

savant::set<IIR_Declaration> *
IIRBase_Statement::find_declarations( IIR_Name * ){
  _report_undefined_fn("IIRBase_Statement::_find_declarations( IIR_Name *name )");

  return NULL;
}

void 
IIRBase_Statement::set_assertion_condition( IIR * ){
  _report_undefined_fn(" set_assertion_condition( IIR * )");
  ASSERT(0);
}

void 
IIRBase_Statement::set_report_expression( IIR * ){
  _report_undefined_fn(" set_report_expression( IIR * )");
  ASSERT(0);
}

void 
IIRBase_Statement::set_severity_expression( IIR * ){
  _report_undefined_fn(":set_severity_expression( IIR * )");
  ASSERT(0);
}

ostream &
IIRBase_Statement::print( ostream &os ){
  if( get_label() != NULL ){
    os << *get_label();
  }
  else{
    os << "ANONYMOUS " << get_kind_text();
  }

  return os;
}

IIR_TextLiteral*
IIRBase_Statement::get_declarator(){
  ASSERT (get_label() != NULL);
  return get_label()->get_declarator();
}

void 
IIRBase_Statement::set_reject_time_expression( IIR * ) {
  _report_undefined_fn("set_reject_time_expression(IIR *)");
}

void 
IIRBase_Statement::set_target( IIR * ) {
  _report_undefined_fn("set_target(IIR *)");
}

void 
IIRBase_Statement::publish_vhdl_stmt_label(ostream &vhdl_out) {
  if(get_label() != NULL) {
    get_label()->publish_vhdl(vhdl_out);
    vhdl_out << ": ";
  }
  
}

void 
IIRBase_Statement::publish_vhdl_delay_mechanism( ostream &vhdl_out,
						 IIR_DelayMechanism delay,
						 IIR *time_expression ){ 

  switch(delay) {
  case IIR_TRANSPORT_DELAY:
    vhdl_out << "transport ";
    break;
  case IIR_INERTIAL_DELAY:
    if(time_expression != NULL) {
      vhdl_out << "reject ";
      time_expression->publish_vhdl(vhdl_out);
      vhdl_out << " inertial ";
    }
    break;
  }
}
