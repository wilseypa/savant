
#ifndef IIRBASE_REFERENCE_ATTRIBUTE_HH
#define IIRBASE_REFERENCE_ATTRIBUTE_HH

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
#include "IIR_ReferenceAttribute.hh"
#include "IIRBase_Attribute.hh"
#include "IRBasicDataTypes.hh"

/** This class describes T'Reference. For a terminal T, the attribute
    T'Reference yields an across quantity, whose plus terminal is T and
    whose minus terminal is the reference terminal of nature of T. */
class IIRBase_ReferenceAttribute : public virtual IIRBase_Attribute, public virtual IIR_ReferenceAttribute {

public:
  /** Returns the IIR_Kind of this node. */
  IIR_Kind get_kind() const {
    return IIR_REFERENCE_ATTRIBUTE;
  }

  const IIR_Char *get_kind_text() const {
    return "IIR_ReferenceAttribute";
  }

 /** This returns an IIR_TextLiteral when a Reference attribute is
     instantiated. */  
  IIR_TextLiteral *build_attribute_name();

  void publish_vhdl(ostream &);
protected:
  IIRBase_ReferenceAttribute();
  virtual ~IIRBase_ReferenceAttribute() = 0;

private:
};
#endif


