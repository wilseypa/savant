
#ifndef IIR_BREAK_STATEMENT_HH
#define IIR_BREAK_STATEMENT_HH

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
#include "IIR_SequentialStatement.hh"

class IIR_BreakList;

/** The extension base for Sequential Break Statement. This notifies the
    analog solver that it must determine the discontinuity augmentation set
    for the next analog solution point. */
class IIR_BreakStatement : public virtual IIR_SequentialStatement {

public:
  // List Accessor(s)
  virtual IIR_BreakList *get_break_list() = 0;
  virtual void set_break_list(IIR_BreakList  *) = 0;

  /** For the execution of a Break Statement, the condition, if present, is
      first evaluated. A break is indicated if the value of the condition
      is TRUE or if there is no condition. [ LRM $ 8.14 - 565 ]. */
  virtual void set_condition(IIR* condition) = 0;
  virtual IIR* get_condition() = 0;
  
protected:
public:
};
#endif
