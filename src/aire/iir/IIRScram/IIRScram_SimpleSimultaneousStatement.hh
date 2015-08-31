
#ifndef IIRSCRAM_SIMPLE_SIMULTANEOUS_STATEMENT_HH
#define IIRSCRAM_SIMPLE_SIMULTANEOUS_STATEMENT_HH

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

// Authors: Sivakumar Gowrisankar             gowriss@ececs.uc.edu
//          Kathiresan Nellayappan
//          Vasudevan Shanmugasundaram
//          Venkateswaran Krishna

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_SimultaneousStatement.hh"
#include "IIRBase_SimpleSimultaneousStatement.hh"
#include "symbol_table.hh"

class IIRScram_SimpleSimultaneousStatement : public virtual IIRScram_SimultaneousStatement, public virtual IIRBase_SimpleSimultaneousStatement {
public:
  IIRScram_SimpleSimultaneousStatement();
  virtual ~IIRScram_SimpleSimultaneousStatement();

     
  /** Converts the left and right expressions into its rval, stores them
      and does a type check between left-side and right-side
      expressions.  */
  void _type_check();
  
  // Helper Functions
  IIRScram *_get_left_expression();
  IIRScram *_get_right_expression();
  
protected:
private:
  IIR_Label * _mangled_stmt_label;
};
#endif
