#ifndef IIRSCRAM_CONCURRENT_SELECTED_SIGNAL_ASSIGNMENT_HH
#define IIRSCRAM_CONCURRENT_SELECTED_SIGNAL_ASSIGNMENT_HH

// Copyright (c) 1996-2000 The University of Cincinnati.  
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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Timothy J. McBrayer tmcbraye@ececs.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_ConcurrentStatement.hh"
#include "IIRBase_ConcurrentSelectedSignalAssignment.hh"

class IIRScram_CaseStatementAlternativeList;
class IIRScram_DesignatorList;
class IIRScram_SelectedWaveformList;
class IIRScram_SignalDeclaration;

class IIRScram_ConcurrentSelectedSignalAssignment : public virtual IIRScram_ConcurrentStatement, public virtual IIRBase_ConcurrentSelectedSignalAssignment{
public:
  IIRScram_ConcurrentSelectedSignalAssignment();
  virtual ~IIRScram_ConcurrentSelectedSignalAssignment();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  IIRScram *_clone();

#ifdef PROCESS_COMBINATION
  void _static_elaborate(IIRScram_ArchitectureDeclaration*, IIRScram_DeclarationList*,
			 char*);
#endif

  void _type_check();

  IIRScram *_get_target();
  IIR_DelayMechanism _get_delay_mechanism();
  IIRScram *_get_reject_time_expression();
  IIRScram *_get_case_statement_expression();
  void _set_case_statement_expression( IIRScram *new_expression );

  IIRScram_SignalDeclaration *_get_guard_signal();

  IIRScram *                            _get_expression();
  IIRScram_SelectedWaveformList *       _get_selected_waveforms();
protected:
private:
  // These methods are used to transform our data into and out of case
  // statement alterntives.  They are used during the type checking,
  // should be during transmute, too.  The read method is used during type
  // checking to take a resolved list returned to us, and put it back into
  // the selected waveforms.
  void _read_alternative_list(  IIRScram_CaseStatementAlternativeList * );
  void _type_check_expression_and_choices();
  void _type_check_target_and_waveforms();
};
#endif
