
#ifndef IIR_SIMULTANEOUS_ELSIF_HH
#define IIR_SIMULTANEOUS_ELSIF_HH

// Copyright (c) 2002-2003 The University of Cincinnati.
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

// Authors: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_Tuple.hh"

class IIR_ArchitectureStatementList;

class IIR_SimultaneousElsif : public virtual IIR_Tuple {
public:
  IIR_SimultaneousElsif() {}
  virtual ~IIR_SimultaneousElsif() {}

  virtual IIR_ArchitectureStatementList *get_then_sequence_of_statements() = 0;
  virtual void                          set_then_sequence_of_statements(IIR_ArchitectureStatementList *) = 0;

  /** The condition specified here is evaluated and if it is TRUE, the
      corresponding simultaneous statement part is evaluated. */
  virtual void set_condition(IIR* condition) = 0;
  virtual IIR* get_condition() = 0;

  /** The condition specified after if and elsif (if any) are evaluated in
      succession until one evaluates to TRUE or all conditions are
      evaluated and yield FALSE. LRM [ 15.2 - 75 ] */
  virtual void set_else_clause(IIR_SimultaneousElsif* else_clause) = 0;
  virtual IIR_SimultaneousElsif* get_else_clause() = 0;

protected:
private:
};
#endif
