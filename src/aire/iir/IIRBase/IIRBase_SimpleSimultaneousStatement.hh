
#ifndef IIRBASE_SIMPLE_SIMULTANEOUS_STATEMENT_HH
#define IIRBASE_SIMPLE_SIMULTANEOUS_STATEMENT_HH

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
 
//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_SimpleSimultaneousStatement.hh"
#include "IIRBase_SimultaneousStatement.hh"
#include "IRBasicDataTypes.hh"

class IIR;

class IIRBase_SimpleSimultaneousStatement : public virtual IIRBase_SimultaneousStatement, public virtual IIR_SimpleSimultaneousStatement {

public:
  IIR_Kind get_kind() const {
    return IIR_SIMPLE_SIMULTANEOUS_STATEMENT;
  }
  
  const IIR_Char *get_kind_text() const {
    return "IIR_SimpleSimultaneousStatement";
  }

  /** Used to set the left expression of a simultaneous equation */
  void set_left_expression(IIR* left_expression);
  
  /** Used to get the pointer to the left expression of a simultaneous equation */
  IIR* get_left_expression();
  
  /** Used to set the right expression of a simultaneous equation */
  void set_right_expression(IIR* right_expression);
  
  /** Used to get the pointer to the right expression of a simultaneous equation */
  IIR* get_right_expression();
  
  void set_pure(IIR_Pure purity);
  IIR_Pure get_pure();

  /** Sets the tolerance aspect of the simultaneous equation */  
  void set_tolerance_aspect(IIR* tolerance);
  
  /** Returns a pointer to the tolerance aspect of the simultaneous equation */
  IIR* get_tolerance_aspect();

  IIR *convert_tree(plugin_class_factory *factory);
  
  void publish_vhdl(ostream &);
protected:
  IIRBase_SimpleSimultaneousStatement();
  virtual  ~IIRBase_SimpleSimultaneousStatement() = 0;
  
private:
  IIR* left_expression;
  IIR* right_expression;
  IIR_Pure purity;
  IIR* tolerance_aspect;
  
};
#endif

