
#ifndef IIR_SIMPLE_SIMULTANEOUS_STATEMENT_HH
#define IIR_SIMPLE_SIMULTANEOUS_STATEMENT_HH

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
#include "IIR_SimultaneousStatement.hh"

class IIR_SimpleSimultaneousStatement : public virtual IIR_SimultaneousStatement {
public:
  IIR_SimpleSimultaneousStatement() {};
  virtual ~IIR_SimpleSimultaneousStatement() {}; 

  /** Used to set the left expression of a simultaneous equation */
  virtual void set_left_expression(IIR* left_expression) = 0;
  
  /** Used to get the pointer to the left expression of a simultaneous equation */
  virtual IIR* get_left_expression() = 0;
  
  /** Used to set the right expression of a simultaneous equation */
  virtual void set_right_expression(IIR* right_expression) = 0;
  
  /** Used to get the pointer to the right expression of a simultaneous equation */
  virtual IIR* get_right_expression() = 0;
  
  virtual void set_pure(IIR_Pure purity) = 0;
  virtual IIR_Pure get_pure() = 0;

  /** Sets the tolerance aspect of the simultaneous equation */  
  virtual void set_tolerance_aspect(IIR* tolerance) = 0;
  
  /** Returns a pointer to the tolerance aspect of the simultaneous equation */
  virtual IIR* get_tolerance_aspect() = 0;  
};
#endif





