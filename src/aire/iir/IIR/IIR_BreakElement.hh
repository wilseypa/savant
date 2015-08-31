
#ifndef IIR_BREAK_ELEMENT_HH
#define IIR_BREAK_ELEMENT_HH

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
#include "IIR_Tuple.hh"
#include "IRBasicDataTypes.hh"
  
class IIR_Name;

/** The extension base for Break Element. In each Break Element, the
    quantity denoted by the quantity name is the break quantity of the
    break element. */
class IIR_BreakElement : public virtual IIR_Tuple {
  
public:
  /** In each Break Element, the quantity denoted by the quantity name is
      the break quantity of the break element. It is set and returned using
      these functions. */
  virtual void set_quantity_name(IIR_Name* quantity_name) = 0;
  virtual IIR_Name* get_quantity_name() = 0;
  
  /** Sets and returns the expression for each break element (break
      quantity).  The expression and the break quantity must have the same
      type. */ 
  virtual void set_expression(IIR* value) = 0;
  virtual IIR* get_expression() = 0;
  
  /** Sets and returns the selector quantity, if present. The Selector
      quantity is the quantity name in the break selector clause. */
  virtual void set_selector_quantity_name(IIR_Name* quantity_name) = 0;
  virtual IIR_Name* get_selector_quantity_name() = 0;

protected:
};
#endif
