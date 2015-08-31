
#ifndef  IIR_CONCURRENT_BREAK_STATEMENT_HH
#define  IIR_CONCURRENT_BREAK_STATEMENT_HH

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
#include "IIR_SimultaneousStatement.hh"

class IIR_BreakList;
class IIR_DesignatorList;

/** The extension base for Concurrent Break Statement. This represents a
    process containing a break statement. */
class IIR_ConcurrentBreakStatement : public virtual IIR_SimultaneousStatement{
  
public:
  // List Accessor(s)
  virtual IIR_BreakList *get_concurrent_break_list() = 0;
  virtual IIR_DesignatorList *get_sensitivity_list() = 0;
  virtual void set_concurrent_break_list(IIR_BreakList  *) = 0;
  virtual void set_sensitivity_list(IIR_DesignatorList  *) = 0;

  /** The condition in the concurrent break statement would be the
      condition in the equivalent break statement in the process. */
  virtual void set_condition(IIR* condition) = 0;
  virtual IIR* get_condition() = 0;
  
protected:
public:
};
#endif
