
#ifndef IIRBASE_LTF_ATTRIBUTE_HH
#define IIRBASE_LTF_ATTRIBUTE_HH

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

// Authors: Prashanth Cherukuri cherukps@ececs.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_Attribute.hh"
#include "IIR_LTFAttribute.hh"
#include "IRBasicDataTypes.hh"

/** This class describes the 'ltf attribute.  For a scalar quantity Q, the
    attribute Q'ltf(num, den) yields a quantity whose type is the base type
    of Q and value is the Laplace transform of Q.num and den are the
    numerator and denominator polynomials, specified as real_vector
    arrays. */
class IIRBase_LTFAttribute  : public virtual IIR_LTFAttribute, public virtual IIRBase_Attribute {

public:
  /** Returns the IIR_Kind of this node. */
  IIR_Kind get_kind() const {
    return IIR_LTF_ATTRIBUTE;
  }
  /** Returns the kind of this node in text form. */
  const IIR_Char *get_kind_text() const {
    return "IIR_LTFAttribute";
  }
  /** Set the numerator coefficients from the static expression.  */
  void set_num(IIR *numerator);
  /** Return the numerator coefficients.  */
  IIR* get_num();
  /* Set the denominator coefficients from the static expression.  */
  void set_den(IIR *denominator);
  /* Return the denominator coefficients.  */
  IIR* get_den();

  IIR *convert_tree(plugin_class_factory *factory);

  /** This returns an IIR_TextLiteral when the LTF attribute is  instantiated. */
  IIR_TextLiteral *build_attribute_name();

  void publish_vhdl(ostream&);
protected:
  IIRBase_LTFAttribute();
  virtual ~IIRBase_LTFAttribute() = 0;

private:
  IIR* numerator;
  IIR* denominator;
};
#endif

