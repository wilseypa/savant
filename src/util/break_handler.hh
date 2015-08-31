
#ifndef BREAK_HANDLER_HH
#define BREAK_HANDLER_HH

// Copyright (c) 2003 The University of Cincinnati.
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

// Author: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_BreakElement.hh"
#include "IIR_Designator.hh"
#include "IIR_BreakList.hh"
#include "IIR_DesignatorList.hh"
  
class IIR;

/** This class records the information necessary for handling the break
    statements. */
class break_handler {
  
public:
  break_handler() {};
  ~break_handler() {};
  
  /** Returns the break list. */
  IIR_BreakList*
  get_break_list() { 
    return break_quantity_list;
  }
  
  /** Returns the sensitivity list present in the sensitivity clause of the
      concurrent Break statement. */
  IIR_DesignatorList*
  get_sensitivity_list() { 
    return break_sensitivity_list;
  }
  
  /** Returns the condition in break statement. */
  IIR *
  get_condition() { 
    return break_condition;
  }

  /** Sets the break condition. */
  void
  set_condition(IIR *condition) {
    break_condition = condition;
  }
  
  /** Sets the break list. */
  void
  set_breaklist(IIR_BreakList *list) {
    break_quantity_list = list;
  }
  
  /** Sets the sensitivity list. */
  void
  set_sensitivitylist(IIR_DesignatorList *designator) {
    break_sensitivity_list = designator;
  }
  
protected:

private:
  IIR_BreakList *break_quantity_list;
  IIR_DesignatorList *break_sensitivity_list;
  IIR* break_condition;
  
};
#endif
