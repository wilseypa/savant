
#ifndef IIRSCRAM_BREAK_STATEMENT_HH
#define IIRSCRAM_BREAK_STATEMENT_HH

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

#include "savant_config.hh"
#include "IIRBase_BreakStatement.hh"
#include "IIRScram_SequentialStatement.hh"

class IIRScram_AboveAttribute;
class IIRScram_BreakList;
class IIRScram_Label;

/** The extension base for Sequential Break Statement. This notifies the
    analog solver that it must determine the discontinuity augmentation set
    for the next analog solution point. */
class IIRScram_BreakStatement : public virtual IIRBase_BreakStatement, public virtual IIRScram_SequentialStatement {

public:
  IIRScram_BreakStatement(){} ;
  virtual ~IIRScram_BreakStatement() {};

  /** @name Method for publishing VHDL code. */
  void _type_check();

  // Help Functions
  IIRScram_BreakList    *_get_break_list();
  IIRScram              *_get_condition();
protected:
private:

};
#endif
