
#ifndef IIRBASE_ABOVE_ATTRIBUTE_HH
#define IIRBASE_ABOVE_ATTRIBUTE_HH

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

// Authors: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_AboveAttribute.hh"
#include "IIRBase_Attribute.hh"
#include "IRBasicDataTypes.hh"

class IIR;

/** The IIR node for above attribute of quantities (Q'Above).  For a
    Quantity Q, the attribute Q'Above yields a signal. */
class IIRBase_AboveAttribute : public virtual IIRBase_Attribute, public virtual IIR_AboveAttribute {

public:
  /** Returns the IIR_Kind of this node. */
  IIR_Kind get_kind() const {
    return IIR_ABOVE_ATTRIBUTE;
  }
  
  const IIR_Char *get_kind_text() const {
    return "IIR_AboveAttribute";
   }
  
  /** This returns an IIR_TextLiteral when a Dot attribute is
      instantiated. */
  IIR_TextLiteral *build_attribute_name();

  /** Sets the value of the expression whose type 
      is the same as that of Q. */
  void set_suffix(IIR* suffix);
  
  /** Returns the value of the expression. */
  IIR* get_suffix();
  
  /** Returns the type of the signal created. */
  IIR_TypeDefinition *get_subtype();

  IIR_Boolean is_signal() { return TRUE; }
  IIR_Boolean has_suffix(){ return TRUE; }

  IIR *convert_tree(plugin_class_factory *factory);

  /** Returns TRUE if above attribute is found. */
  IIR_Boolean is_above_attribute_found() { return TRUE; }
  IIR_Boolean is_above_attribute() { return TRUE; }
  void publish_vhdl(ostream &);
protected:
  IIRBase_AboveAttribute();
  virtual ~IIRBase_AboveAttribute() = 0;
  
private:
  IIR* suffix;

};
#endif
