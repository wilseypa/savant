
#ifndef IIRSCRAM_SIMULTANEOUS_IF_STATEMENT_HH
#define IIRSCRAM_SIMULTANEOUS_IF_STATEMENT_HH

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
#include "set.hh"
#include "IIRBase_SimultaneousIfStatement.hh"
#include "IIRScram_SimultaneousStatement.hh"

class IIRScram_ArchitectureStatement;
class IIRScram_ArchitectureStatementList;
class IIRScram_Declaration;
class IIRScram_SimultaneousElsif;

/** This class selects for evaluation one of the enclosed simultaneous
    statement parts depending on the value of one or more conditions. */
class IIRScram_SimultaneousIfStatement : public virtual IIRBase_SimultaneousIfStatement, public virtual IIRScram_SimultaneousStatement {

public:
  IIRScram_SimultaneousIfStatement();
  virtual ~IIRScram_SimultaneousIfStatement();

  /** @name Method for publishing VHDL code. */
  void _type_check();
 
  // Helper Functions
  IIRScram                              *_get_condition();
  IIRScram_ArchitectureStatementList    *_get_then_statement_list();
  IIRScram_ArchitectureStatementList    *_get_else_statement_list();
  IIRScram_SimultaneousElsif            *_get_elsif();
protected:

private:

};
#endif
