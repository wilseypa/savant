
#ifndef  IIRBASE_CONCURRENT_BREAK_STATEMENT_HH
#define  IIRBASE_CONCURRENT_BREAK_STATEMENT_HH

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
#include "IIR_ConcurrentBreakStatement.hh"
#include "IIRBase_SimultaneousStatement.hh"

class IIR_BreakList;
class IIR_DesignatorList;

/** The extension base for Concurrent Break Statement. This represents a
    process containing a break statement. */
class IIRBase_ConcurrentBreakStatement : public virtual IIR_ConcurrentBreakStatement, public virtual IIRBase_SimultaneousStatement {
  
public:
  // List Accessor(s)
  IIR_BreakList *get_concurrent_break_list();
  IIR_DesignatorList *get_sensitivity_list();
  void set_concurrent_break_list(IIR_BreakList *);
  void set_sensitivity_list(IIR_DesignatorList *);

  /** Returns the IIR_Kind of this node. */
  IIR_Kind get_kind() const {
    return IIR_CONCURRENT_BREAK_STATEMENT;
  }
  
  const IIR_Char *get_kind_text() const {
    return "IIRBase_ConcurrentBreakStatement";
  }
  
  /** The condition in the concurrent break statement would be the
      condition in the equivalent break statement in the process. */
  void set_condition(IIR* condition);
  IIR* get_condition();

  IIR *convert_tree(plugin_class_factory *factory);
  
  void publish_vhdl(ostream &);
protected:
  IIRBase_ConcurrentBreakStatement();
  virtual ~IIRBase_ConcurrentBreakStatement();

private:
  // List Variable(s)
  /** The break list of a concurrent break statement would be the break
      list in the equivalent break statement in the process. */
  IIR_BreakList *concurrent_break_list;
  IIR_DesignatorList *sensitivity_list;

  IIR* condition;

};
#endif
