
#ifndef IIRBASE_BREAK_STATEMENT_HH
#define IIRBASE_BREAK_STATEMENT_HH

// Copyright (c) The University of Cincinnati.
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

#include "savant_config.hh"
#include "IIRBase_SequentialStatement.hh"
#include "IIR_BreakStatement.hh"

class IIR_BreakList;

/** The extension base for Sequential Break Statement. This notifies the
    analog solver that it must determine the discontinuity augmentation set
    for the next analog solution point. */
class IIRBase_BreakStatement : public virtual IIR_BreakStatement, public virtual IIRBase_SequentialStatement {

public:
  // List Accessor(s)
  IIR_BreakList *get_break_list();
  void set_break_list(IIR_BreakList  *);

  /** Returns the IIR_Kind of this node. */
  IIR_Kind get_kind() const {
    return IIR_BREAK_STATEMENT;
  }

  const IIR_Char *get_kind_text() const { return "IIR_BreakStatement"; }

  /** For the execution of a Break Statement, the condition, if present, is
      first evaluated. A break is indicated if the value of the condition
      is TRUE or if there is no condition. [ LRM $ 8.14 - 565 ]. */
  void set_condition(IIR* condition);
  IIR* get_condition();

  IIR_Boolean is_above_attribute_found();  

  /** break_list is a list of break elements in a break statement. In each
      break element the quantity denoted by the quantity name is the "break
      quantity" of the break element. [ LRM $ 8.14 -560 ]. */  

  IIR *convert_tree(plugin_class_factory *factory);
 
  void publish_vhdl(ostream &);
protected:
  IIRBase_BreakStatement();
  virtual ~IIRBase_BreakStatement()= 0;
  
private:
  // List Variable(s)
  IIR_BreakList *break_list;

  IIR* condition;

};
#endif
