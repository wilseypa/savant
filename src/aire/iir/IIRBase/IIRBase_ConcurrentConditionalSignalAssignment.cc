
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

//---------------------------------------------------------------------------


#include "IIRBase_ConcurrentConditionalSignalAssignment.hh"
#include "IIR_ConditionalWaveformList.hh"
#include "IIR_SignalDeclaration.hh"

IIRBase_ConcurrentConditionalSignalAssignment::IIRBase_ConcurrentConditionalSignalAssignment() :
  conditional_waveforms(0) {
  set_postponed( FALSE );
  set_target( NULL );
  set_guarded( FALSE );
  set_delay_mechanism( IIR_INERTIAL_DELAY );
  set_reject_time_expression( NULL );
  set_guard_signal( NULL );
}

IIRBase_ConcurrentConditionalSignalAssignment::~IIRBase_ConcurrentConditionalSignalAssignment(){
}

void 
IIRBase_ConcurrentConditionalSignalAssignment::set_postponed( IIR_Boolean postponed ){
  this->postponed = postponed;
}

IIR_Boolean 
IIRBase_ConcurrentConditionalSignalAssignment::get_postponed(){
  return postponed;
}

void 
IIRBase_ConcurrentConditionalSignalAssignment::set_target( IIR *target ){
  this->target = target;
}

IIR *
IIRBase_ConcurrentConditionalSignalAssignment::get_target(){
  return target;
}

void 
IIRBase_ConcurrentConditionalSignalAssignment::set_guarded( IIR_Boolean guarded ){
  this->guarded = guarded;
}

IIR_Boolean 
IIRBase_ConcurrentConditionalSignalAssignment::get_guarded(){
  return guarded;
}

void 
IIRBase_ConcurrentConditionalSignalAssignment::set_delay_mechanism( IIR_DelayMechanism delay_mechanism ){
  this->delay_mechanism = delay_mechanism;
}

IIR_DelayMechanism 
IIRBase_ConcurrentConditionalSignalAssignment::get_delay_mechanism(){
  return delay_mechanism;
}

void 
IIRBase_ConcurrentConditionalSignalAssignment::set_reject_time_expression( IIR *reject_time_expression ){
  this->reject_time_expression = reject_time_expression;
}

IIR *
IIRBase_ConcurrentConditionalSignalAssignment::get_reject_time_expression(){
  return reject_time_expression;
}

// List Accessor(s)
IIR_ConditionalWaveformList *
IIRBase_ConcurrentConditionalSignalAssignment::get_conditional_waveforms() {
  ASSERT(conditional_waveforms != NULL);
  return conditional_waveforms;
}


void
IIRBase_ConcurrentConditionalSignalAssignment::set_conditional_waveforms(IIR_ConditionalWaveformList *new_conditional_waveforms) {
  ASSERT(new_conditional_waveforms != NULL);
  delete conditional_waveforms;
  conditional_waveforms = new_conditional_waveforms;
}

IIR *
IIRBase_ConcurrentConditionalSignalAssignment::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ConcurrentConditionalSignalAssignment *new_node = dynamic_cast<IIRBase_ConcurrentConditionalSignalAssignment *>(IIRBase_ConcurrentStatement::convert_tree(factory));

  // Process the variables
  new_node->conditional_waveforms = dynamic_cast<IIR_ConditionalWaveformList *>(convert_node(conditional_waveforms, factory));
  new_node->my_guard_signal = dynamic_cast<IIR_SignalDeclaration *>(convert_node(my_guard_signal, factory));

  new_node->postponed = postponed;
  new_node->guarded = guarded;
  new_node->delay_mechanism = delay_mechanism;

  new_node->target = convert_node(target, factory);
  new_node->reject_time_expression = convert_node(reject_time_expression, factory);

  return new_node;
}

IIR_Boolean 
IIRBase_ConcurrentConditionalSignalAssignment::is_resolved(){
  IIR_Boolean retval = TRUE;
  if( get_target() != NULL && get_target()->is_resolved() == FALSE ){
    retval = FALSE;
  }
  else if( get_reject_time_expression() != NULL 
	   && get_reject_time_expression()->is_resolved() == FALSE ){
    retval = FALSE;
  }
  else if( get_conditional_waveforms()->is_resolved() == FALSE ){
    retval = FALSE;
  }
  return retval;
}

void 
IIRBase_ConcurrentConditionalSignalAssignment::publish_vhdl(ostream &vhdl_out) {

  publish_vhdl_stmt_label(vhdl_out);

  if (get_postponed() == true) {
    vhdl_out << "postponed ";
  }
  
  get_target()->publish_vhdl(vhdl_out);
  vhdl_out << " <= ";

  publish_vhdl_delay_mechanism(vhdl_out, get_delay_mechanism(), get_reject_time_expression());

  get_conditional_waveforms()->publish_vhdl(vhdl_out);
  vhdl_out << ";\n";
}
