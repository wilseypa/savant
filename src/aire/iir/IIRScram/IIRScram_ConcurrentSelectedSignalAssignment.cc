
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
//          Timothy J. McBrayer
//          Narayanan Thondugulam

//---------------------------------------------------------------------------
#include "IIRScram_ConcurrentSelectedSignalAssignment.hh"
#include "IIRScram_CaseStatement.hh"
#include "IIRScram_CaseStatementAlternativeByChoices.hh"
#include "IIRScram_CaseStatementAlternativeByExpression.hh"
#include "IIRScram_CaseStatementAlternativeByOthers.hh"
#include "IIRScram_CaseStatementAlternativeList.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_ProcessStatement.hh"
#include "IIRScram_SelectedWaveform.hh"
#include "IIRScram_SelectedWaveformList.hh"
#include "IIRScram_SequentialStatementList.hh"
#include "IIRScram_SignalAssignmentStatement.hh"
#include "IIRScram_WaitStatement.hh"
#include "error_func.hh"
#include "IIRScram_IfStatement.hh"
#include "IIRScram_StringLiteral.hh"
#include "IIRScram_SignalDeclaration.hh"
#include "IIRScram_WaveformElement.hh"
#include "IIRScram_WaveformList.hh"

using std::cerr;

IIRScram_ConcurrentSelectedSignalAssignment::IIRScram_ConcurrentSelectedSignalAssignment(){
  set_selected_waveforms(new IIRScram_SelectedWaveformList());
}

IIRScram_ConcurrentSelectedSignalAssignment::~IIRScram_ConcurrentSelectedSignalAssignment(){}

void 
IIRScram_ConcurrentSelectedSignalAssignment::_type_check(){
  // We need to do several things here.  First, we'll type check the
  // expression, and the choices.
  _type_check_expression_and_choices();

  // Next, we'll type check the target and the waveforms.
  _type_check_target_and_waveforms();

  if( get_guarded() == TRUE ){
    _resolve_guard_signal( _get_symbol_table() );
  }

  ASSERT( is_resolved() == TRUE );
}

void 
IIRScram_ConcurrentSelectedSignalAssignment::_type_check_expression_and_choices(){
  IIRScram_CaseStatementAlternativeList *temp_alternative_list = 
    dynamic_cast<IIRScram_CaseStatementAlternativeList *>(build_alternative_list(false));
  ASSERT( temp_alternative_list->size() == get_selected_waveforms()->size() );
  _type_check_case_statement_expression( temp_alternative_list );
  _read_alternative_list( temp_alternative_list );
  delete temp_alternative_list;
}

void 
IIRScram_ConcurrentSelectedSignalAssignment::_type_check_target_and_waveforms(){
  IIRScram_SelectedWaveform *current_waveform = dynamic_cast<IIRScram_SelectedWaveform *>(get_selected_waveforms()->first());
  while( current_waveform != NULL ){
    _type_check_target_and_waveform( current_waveform->_get_waveform() );
    _type_check_mechanism_and_time( current_waveform->_get_waveform() );    
    current_waveform = dynamic_cast<IIRScram_SelectedWaveform *>(get_selected_waveforms()->successor( current_waveform ));
  }
}

void 
IIRScram_ConcurrentSelectedSignalAssignment::_read_alternative_list( IIRScram_CaseStatementAlternativeList *alt_list ){
  ASSERT( alt_list != NULL );
  ASSERT( alt_list->size() == get_selected_waveforms()->size() );

  IIRScram_SelectedWaveform *current_waveform = NULL;
  IIRScram_CaseStatementAlternative *current_alt = NULL;

  current_waveform = dynamic_cast<IIRScram_SelectedWaveform *>(get_selected_waveforms()->first());
  current_alt = dynamic_cast<IIRScram_CaseStatementAlternative *>(alt_list->first());
  while( current_waveform != NULL ){
    ASSERT( current_alt != NULL );

    ASSERT( current_alt->_is_iir_case_statement_alternative() == TRUE );
    current_waveform->set_choice( current_alt );

    current_alt = dynamic_cast<IIRScram_CaseStatementAlternative *>(alt_list->successor( current_alt ));
    current_waveform = dynamic_cast<IIRScram_SelectedWaveform *>(get_selected_waveforms()->successor( current_waveform ));    
  }
}



IIRScram *
IIRScram_ConcurrentSelectedSignalAssignment::_clone() {
  IIRScram *cstmt;
  //  cstmt = _transmute();
  cstmt = cstmt->_clone();
  return cstmt;
}


#ifdef PROCESS_COMBINATION
void
IIRScram_ConcurrentSelectedSignalAssignment::
_static_elaborate(IIRScram_ArchitectureDeclaration *arch,
		  IIRScram_DeclarationList *cfglist,
		  char *hier_location) {
  ostringstream newname;
  IIRScram_Label *label;
  IIR_Char *text;
  IIR_Int32 i;

  newname << hier_location;
  label = get_label();
  if (label != NULL) {
    newname << label->get_declarator();
  }
  else {
    newname << "UNKNOWNCSA";
  }
  text = newname.str();
#ifdef DEBUG_ELAB
  cout << "elaborated ConcSelSigAssign |" << text << "|\n";
#endif

  ASSERT(label->get_declarator()->get_kind() == IIR_IDENTIFIER);
  ((IIRScram_Identifier *)label->get_declarator())->release();
  label->set_declarator(IIRScram_Identifier::get(text, strlen(text)));
}
#endif

IIRScram *
IIRScram_ConcurrentSelectedSignalAssignment::_get_target(){
  return dynamic_cast<IIRScram *>(get_target());
}

IIR_DelayMechanism 
IIRScram_ConcurrentSelectedSignalAssignment::_get_delay_mechanism(){
  return get_delay_mechanism();
}

void 
IIRScram_ConcurrentSelectedSignalAssignment::_set_case_statement_expression( IIRScram *new_expression ){
  set_expression( new_expression );
}

visitor_return_type *
IIRScram_ConcurrentSelectedSignalAssignment::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ConcurrentSelectedSignalAssignment(this, arg);
};

IIRScram_SelectedWaveformList *
IIRScram_ConcurrentSelectedSignalAssignment::_get_selected_waveforms() {
  return dynamic_cast<IIRScram_SelectedWaveformList *>(get_selected_waveforms());
}

IIRScram *
IIRScram_ConcurrentSelectedSignalAssignment::_get_case_statement_expression(){
  return dynamic_cast<IIRScram *>(get_expression());
}

IIRScram *
IIRScram_ConcurrentSelectedSignalAssignment::_get_expression() {
  return dynamic_cast<IIRScram *>(get_expression());
}

IIRScram *
IIRScram_ConcurrentSelectedSignalAssignment::_get_reject_time_expression(){
  return dynamic_cast<IIRScram *>(get_reject_time_expression());
}

IIRScram_SignalDeclaration *
IIRScram_ConcurrentSelectedSignalAssignment::_get_guard_signal() { 
  return dynamic_cast<IIRScram_SignalDeclaration *>(get_guard_signal()); 
}
