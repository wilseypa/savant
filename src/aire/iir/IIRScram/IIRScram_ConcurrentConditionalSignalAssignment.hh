#ifndef IIRSCRAM_CONCURRENT_CONDITIONAL_SIGNAL_ASSIGNMENT_HH
#define IIRSCRAM_CONCURRENT_CONDITIONAL_SIGNAL_ASSIGNMENT_HH

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
#include "IIRBase_ConcurrentConditionalSignalAssignment.hh"

class IIRScram_ConditionalWaveformList;
class IIRScram_DesignatorList;
class IIRScram_SignalDeclaration;

class IIRScram_ConcurrentConditionalSignalAssignment :
  public virtual IIRScram_ConcurrentStatement,
  public virtual IIRBase_ConcurrentConditionalSignalAssignment{
public:
  IIRScram_ConcurrentConditionalSignalAssignment();
  virtual ~IIRScram_ConcurrentConditionalSignalAssignment();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  void _type_check();
  void _type_check_target_and_waveforms();

  IIRScram_SignalDeclaration *_get_guard_signal();

  IIRScram *_get_target();
  IIRScram *_clone();

  // Helper Functions
  IIRScram *                            _get_reject_time_expression();
  IIR_DelayMechanism                    _get_delay_mechanism();
  IIRScram_ConditionalWaveformList *    _get_conditional_waveforms();

protected:    
private:
};
#endif

