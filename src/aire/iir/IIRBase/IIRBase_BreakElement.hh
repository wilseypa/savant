
#ifndef IIRBASE_BREAK_ELEMENT_HH
#define IIRBASE_BREAK_ELEMENT_HH

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
#include "IIR_BreakElement.hh"
#include "IIRBase_Tuple.hh"
#include "IRBasicDataTypes.hh"
  
class IIR_Name;

/** The extension base for Break Element. In each Break Element, the
    quantity denoted by the quantity name is the break quantity of the
    break element. */
class IIRBase_BreakElement : public virtual IIR_BreakElement, public virtual IIRBase_Tuple {
  
public:
  /** Returns the IIR_Kind of this node. */
  IIR_Kind get_kind() {
    return IIR_BREAK_ELEMENT;
  }
  const IIR_Char *get_kind_text() const { return "IIR_BreakElement"; }
  
  /** In each Break Element, the quantity denoted by the quantity name is
      the break quantity of the break element. It is set and returned using
      these functions. */
  void set_quantity_name(IIR_Name* quantity_name);
  IIR_Name* get_quantity_name();
  
  /** Sets and returns the expression for each break element (break
      quantity).  The expression and the break quantity must have the same
      type. */ 
  void set_expression(IIR* value);
  IIR* get_expression();
  
  /** Sets and returns the selector quantity, if present. The Selector
      quantity is the quantity name in the break selector clause. */
  void set_selector_quantity_name(IIR_Name* quantity_name);
  IIR_Name* get_selector_quantity_name();

  IIR *convert_tree(plugin_class_factory *factory);

  void publish_vhdl(ostream &vhdl_out);
protected:
  IIRBase_BreakElement();
  virtual ~IIRBase_BreakElement()= 0;
 
private:
  IIR_Name* quantity_name;
  IIR_Name* selector_quantity_name;
  IIR* value;  
};
#endif
