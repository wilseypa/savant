
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
//          Krishnan Subramani 
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam

//---------------------------------------------------------------------------

#include "IIRScram_AliasDeclaration.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_SignalAssignmentStatement.hh"
#include "IIRScram_WaveformElement.hh"
#include "IIRScram_WaveformList.hh"

#include "error_func.hh"
#include "resolution_func.hh"
#include "set.hh"
#include "symbol_table.hh"
#include "savant.hh"


IIRScram_SignalAssignmentStatement::IIRScram_SignalAssignmentStatement() {
  set_waveform(new IIRScram_WaveformList());
}

IIRScram_SignalAssignmentStatement::~IIRScram_SignalAssignmentStatement(){}

void 
IIRScram_SignalAssignmentStatement::_type_check(){
  _type_check_target_and_waveform( _get_waveform() );
  _type_check_mechanism_and_time( _get_waveform() );
}

IIRScram *
IIRScram_SignalAssignmentStatement::_clone() {
  IIRScram_SignalAssignmentStatement *stmt = NULL;
  IIRScram *target = NULL;
  IIRScram_WaveformElement *newwave, *oldwave;

  stmt = new IIRScram_SignalAssignmentStatement();
  IIRScram_SequentialStatement::_clone(stmt);

  target = _get_target();
  target = target->_clone();
  stmt->set_target(target);
  stmt->set_delay_mechanism(get_delay_mechanism());
  stmt->set_reject_time_expression(get_reject_time_expression());

  oldwave = dynamic_cast<IIRScram_WaveformElement *>(get_waveform()->first());
  while(oldwave != NULL) {
    newwave = dynamic_cast<IIRScram_WaveformElement*>(oldwave->_clone());
    stmt->get_waveform()->append(newwave);
    oldwave = dynamic_cast<IIRScram_WaveformElement *>(get_waveform()->successor(oldwave));
  }
  return stmt;
}

IIRScram *
IIRScram_SignalAssignmentStatement::_get_target(){
  return dynamic_cast<IIRScram *>(get_target());
}

IIR_DelayMechanism 
IIRScram_SignalAssignmentStatement::_get_delay_mechanism(){
  return get_delay_mechanism();
}

visitor_return_type *
IIRScram_SignalAssignmentStatement::_accept_visitor( node_visitor *visitor, 
						     visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_SignalAssignmentStatement(this, arg);
}

// IIRBase Function Wrapper(s)
IIRScram_WaveformList *
IIRScram_SignalAssignmentStatement::_get_waveform() {
  return dynamic_cast<IIRScram_WaveformList *>(get_waveform());
}

IIRScram *
IIRScram_SignalAssignmentStatement::_get_reject_time_expression(){
  return dynamic_cast<IIRScram *>(get_reject_time_expression());
}
