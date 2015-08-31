
#ifndef IIRBASE_SIMULTANEOUS_ELSIF_HH
#define IIRBASE_SIMULTANEOUS_ELSIF_HH

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
#include "IIRBase_Tuple.hh"
#include "IIR_SimultaneousElsif.hh"
#include "IRBasicDataTypes.hh"

/** This class selects for evaluation one of the enclosed simultaneous
    statement parts depending on the value of one or more conditions. */
class IIRBase_SimultaneousElsif : public virtual IIRBase_Tuple, public virtual IIR_SimultaneousElsif {

public:
  // List Accessor
  IIR_ArchitectureStatementList *get_then_sequence_of_statements();
  void                          set_then_sequence_of_statements(IIR_ArchitectureStatementList *);

  /** Returns the IIR_Kind of this node. */
  IIR_Kind get_kind(){
    return IIR_SIMULTANEOUS_ELSIF;
  }
  
  const IIR_Char *get_kind_text() const { return "IIR_SimultaneousElsif"; }

  /** The condition specified here is evaluated and if it is TRUE, the
      corresponding simultaneous statement part is evaluated. */
  void set_condition(IIR* condition);
  IIR* get_condition();

  /** The condition specified after if and elsif (if any) are evaluated in
      succession until one evaluates to TRUE or all conditions are
      evaluated and yield FALSE. LRM [ 15.2 - 75 ] */
  void set_else_clause(IIR_SimultaneousElsif* else_clause);
  IIR_SimultaneousElsif* get_else_clause();

  IIR *convert_tree(plugin_class_factory *factory);
  
  void publish_vhdl(ostream &);
protected:
  IIRBase_SimultaneousElsif();
  virtual ~IIRBase_SimultaneousElsif() = 0;

private:
  IIR* condition;
  IIR_SimultaneousElsif* else_clause;

  IIR_ArchitectureStatementList *then_sequence_of_statements;
};
#endif

