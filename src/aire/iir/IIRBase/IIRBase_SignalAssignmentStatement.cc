
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





#include "savant.hh"
#include "IIRBase_SignalAssignmentStatement.hh"
#include "IIR_WaveformList.hh"

IIRBase_SignalAssignmentStatement::IIRBase_SignalAssignmentStatement()  :
  waveform(0) {
   set_target(NULL); 
   set_reject_time_expression(NULL);
}

IIRBase_SignalAssignmentStatement::~IIRBase_SignalAssignmentStatement() {
  delete get_target();
  delete get_reject_time_expression();
}

void
IIRBase_SignalAssignmentStatement::set_target(IIR* target) {
  this->target = target;
}

IIR*
IIRBase_SignalAssignmentStatement::get_target() {
  return target;
}

void
IIRBase_SignalAssignmentStatement::set_delay_mechanism( IIR_DelayMechanism delay_mechanism) {
  this->delay_mechanism =  delay_mechanism;
}

IIR_DelayMechanism
IIRBase_SignalAssignmentStatement::get_delay_mechanism() {
  return delay_mechanism;
}

void
IIRBase_SignalAssignmentStatement::set_reject_time_expression( IIR* reject_time_expression) {
  this->reject_time_expression =  reject_time_expression;
}

IIR*
IIRBase_SignalAssignmentStatement::get_reject_time_expression() {
return  reject_time_expression;
}

// List Accessor(s)
IIR_WaveformList *
IIRBase_SignalAssignmentStatement::get_waveform() {
  ASSERT(waveform != NULL);
  return waveform;
}


void
IIRBase_SignalAssignmentStatement::set_waveform(IIR_WaveformList *new_waveform) {
  ASSERT(new_waveform != NULL);
  delete waveform;
  waveform = new_waveform;
}

IIR *
IIRBase_SignalAssignmentStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_SignalAssignmentStatement *new_node = dynamic_cast<IIRBase_SignalAssignmentStatement *>(IIRBase_SequentialStatement::convert_tree(factory));

  // Process the variables
  new_node->delay_mechanism = delay_mechanism;
  new_node->waveform = dynamic_cast<IIR_WaveformList *>(convert_node(waveform, factory));
  new_node->target = convert_node(target, factory);
  new_node->reject_time_expression = convert_node(reject_time_expression, factory);

  return new_node;
}

IIR_Boolean 
IIRBase_SignalAssignmentStatement::is_resolved(){
  IIR_Boolean retval = TRUE;

  if( get_target() && get_target()->is_resolved() == FALSE ){
    retval = FALSE;
  }
  else if( get_reject_time_expression() && get_reject_time_expression()->is_resolved() == FALSE ){
    retval = FALSE;
  }
  else if ( get_waveform()->is_resolved() == FALSE ){
    retval = FALSE;
  }

  return retval;
}

IIR_Boolean
IIRBase_SignalAssignmentStatement::is_above_attribute_found() {
  return get_waveform()->is_above_attribute_found();
}

void
IIRBase_SignalAssignmentStatement::publish_vhdl(ostream &vhdl_out) {

  publish_vhdl_stmt_label(vhdl_out);

  get_target()->publish_vhdl(vhdl_out);
  vhdl_out << " <= ";

  publish_vhdl_delay_mechanism(vhdl_out, get_delay_mechanism(), get_reject_time_expression());
  get_waveform()->publish_vhdl(vhdl_out);

}
