
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
//          Krishnan Subramani 
//          Umesh Kumar V. Rajasekaran
//          Timothy J. McBrayer 
//          Narayanan Thondugulam

//---------------------------------------------------------------------------
#include "IIRScram_ConcurrentConditionalSignalAssignment.hh"
#include "IIRScram_ConditionalWaveform.hh"
#include "IIRScram_ConditionalWaveformList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_Elsif.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_IfStatement.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_ProcessStatement.hh"
#include "IIRScram_SequentialStatementList.hh"
#include "IIRScram_SignalAssignmentStatement.hh"
#include "IIRScram_WaitStatement.hh"
#include "IIRScram_WaveformElement.hh"
#include "IIRScram_WaveformList.hh"
#include "error_func.hh"
#include "IIRScram_StringLiteral.hh"
#include "IIRScram_SignalDeclaration.hh"
#include "IIRBase_StringLiteral.hh"

using std::cerr;

extern bool parse_error;

IIRScram_ConcurrentConditionalSignalAssignment::IIRScram_ConcurrentConditionalSignalAssignment(){
  set_conditional_waveforms(new IIRScram_ConditionalWaveformList());
}

IIRScram_ConcurrentConditionalSignalAssignment::~IIRScram_ConcurrentConditionalSignalAssignment(){}

void 
IIRScram_ConcurrentConditionalSignalAssignment::_type_check(){
  _type_check_target_and_waveforms();
  ASSERT( is_resolved() == TRUE || parse_error == TRUE );
  if( get_guarded() == TRUE ){
    _resolve_guard_signal( _get_symbol_table() );
  }
}

void 
IIRScram_ConcurrentConditionalSignalAssignment::_type_check_target_and_waveforms(){
  IIRScram_ConditionalWaveform *current_waveform = dynamic_cast<IIRScram_ConditionalWaveform *>(get_conditional_waveforms()->first());
  while( current_waveform != NULL ){
    if( current_waveform->get_condition() != NULL ){
      IIRScram *resolved_condition;
      resolved_condition =
	_type_check_and_resolve_boolean_condition( current_waveform->_get_condition());
      current_waveform->set_condition( resolved_condition );
    }
    
    _type_check_target_and_waveform( current_waveform->_get_waveform() );
    _type_check_mechanism_and_time( current_waveform->_get_waveform() );    
    current_waveform = dynamic_cast<IIRScram_ConditionalWaveform *>(_get_conditional_waveforms()->successor( current_waveform ));
  }
}

IIRScram *
IIRScram_ConcurrentConditionalSignalAssignment::_clone() {
  IIRScram *cstmt;
  //  cstmt = _transmute();
  cstmt = cstmt->_clone();
  return cstmt;
}

IIRScram *
IIRScram_ConcurrentConditionalSignalAssignment::_get_target(){
  return dynamic_cast<IIRScram *>(get_target());
}
  
IIR_DelayMechanism 
IIRScram_ConcurrentConditionalSignalAssignment::_get_delay_mechanism(){
  return get_delay_mechanism();
}

visitor_return_type *
IIRScram_ConcurrentConditionalSignalAssignment::_accept_visitor( node_visitor *visitor,
								 visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ConcurrentConditionalSignalAssignment(this, arg);
}

IIRScram_ConditionalWaveformList *
IIRScram_ConcurrentConditionalSignalAssignment::_get_conditional_waveforms() {
  return dynamic_cast<IIRScram_ConditionalWaveformList *>(get_conditional_waveforms());
}

IIRScram *
IIRScram_ConcurrentConditionalSignalAssignment::_get_reject_time_expression(){
  return dynamic_cast<IIRScram *>(get_reject_time_expression());
}

IIRScram_SignalDeclaration *
IIRScram_ConcurrentConditionalSignalAssignment::_get_guard_signal() { 
  return dynamic_cast<IIRScram_SignalDeclaration *>(get_guard_signal()); 
}
