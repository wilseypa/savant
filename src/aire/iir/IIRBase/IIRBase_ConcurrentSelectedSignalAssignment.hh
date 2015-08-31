
#ifndef IIRBASE_CONCURRENT_SELECTED_SIGNAL_ASSIGNMENT_HH
#define IIRBASE_CONCURRENT_SELECTED_SIGNAL_ASSIGNMENT_HH

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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_ConcurrentStatement.hh"
#include "IIR_ConcurrentSelectedSignalAssignment.hh"

class IIR_SelectedWaveformList;
class IIRBase_ConcurrentSelectedSignalAssignment : public virtual IIRBase_ConcurrentStatement, public virtual IIR_ConcurrentSelectedSignalAssignment{

public:
  // List Accessor(s)
  IIR_SelectedWaveformList *get_selected_waveforms();
  void                     set_selected_waveforms(IIR_SelectedWaveformList *new_selected_waveforms);

  IIR_Kind get_kind() const { return IIR_CONCURRENT_SELECTED_SIGNAL_ASSIGNMENT; }
  const IIR_Char *get_kind_text() const {return "IIR_ConcurrentSelectedSignalAssignment";}

  void set_postponed(IIR_Boolean);
  IIR_Boolean get_postponed();

  void set_target(IIR *);
  IIR* get_target();

  void set_expression(IIR *);
  IIR* get_expression();

  void set_guarded(IIR_Boolean);
  IIR_Boolean get_guarded();

  void  set_delay_mechanism( IIR_DelayMechanism);
  IIR_DelayMechanism get_delay_mechanism();

  void set_reject_time_expression( IIR *reject_time_expression );
  IIR *get_reject_time_expression();

  IIR_SignalDeclaration *get_guard_signal(){ return my_guard_signal; }
  void set_guard_signal( IIR_SignalDeclaration *gs ){ my_guard_signal =  gs; }

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_resolved();

  void publish_vhdl(ostream &);
protected:
  IIRBase_ConcurrentSelectedSignalAssignment();
  virtual ~IIRBase_ConcurrentSelectedSignalAssignment() = 0;

  IIR_CaseStatementAlternativeList *build_alternative_list(IIR_Boolean);
    
private:
  // List Variable(s)
  IIR_SelectedWaveformList *selected_waveforms;

  IIR_Boolean           postponed;
  IIR                   *target;
  IIR                   *expression;
  IIR_Boolean           guarded;
  IIR_DelayMechanism    delay_mechanism;
  IIR                   *reject_time_expression;

  IIR_SignalDeclaration *my_guard_signal;

};
#endif
