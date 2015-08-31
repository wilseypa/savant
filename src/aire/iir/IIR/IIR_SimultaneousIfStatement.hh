
#ifndef IIR_SIMULTANEOUS_IF_STATEMENT_HH
#define IIR_SIMULTANEOUS_IF_STATEMENT_HH

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
#include "IIR_SimultaneousStatement.hh"

class IIR_SimultaneousElsif;
class IIR_ArchitectureStatementList;

class IIR_SimultaneousIfStatement : public virtual IIR_SimultaneousStatement {

public:
  IIR_SimultaneousIfStatement() {};
  virtual ~IIR_SimultaneousIfStatement() {}

  virtual IIR_ArchitectureStatementList *get_then_statement_list() = 0;
  virtual IIR_ArchitectureStatementList *get_else_statement_list() = 0;
  virtual void                          set_then_statement_list(IIR_ArchitectureStatementList *) = 0;
  virtual void                          set_else_statement_list(IIR_ArchitectureStatementList *) = 0;

  virtual void set_elsif(IIR_SimultaneousElsif* elsif_clause) = 0;
  virtual IIR_SimultaneousElsif* get_elsif() = 0;

  virtual void set_condition(IIR *) = 0;
  virtual IIR* get_condition() = 0;

protected:
private:
};
#endif
