
#ifndef IIRBASE_ZTF_ATTRIBUTE_HH
#define IIRBASE_ZTF_ATTRIBUTE_HH

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
#include "IIR_ZTFAttribute.hh"
#include "IIRBase_Attribute.hh"
#include "IRBasicDataTypes.hh"
 
/** This class describes the 'ztf attribute. For a scalar quantity Q, the
    attribute Q'ztf(numerator, denominator, T, initial_delay) yields a
    quantity whose type is the base type of Q and value is the Z transform
    of Q.num and den are the numerator and denominator polynomials,
    specified as real_vector arrays.  The quantity Q is sampled at the time
    given by intial_delay and at intervals of T thereafter.  */
class IIRBase_ZTFAttribute : public virtual IIRBase_Attribute, public virtual IIR_ZTFAttribute {

public:
  /** Returns the IIR_Kind of this node. */
  IIR_Kind get_kind() const {
    return IIR_ZTF_ATTRIBUTE;
  }
  /** Returns the kind of this node in text form. */
  const IIR_Char *get_kind_text() const {
    return "IIR_ZTF_Attribute";
  }
  /** Set the numerator coefficients from the static expression. */
  void set_num(IIR* numerator);

  /** Return the numerator coefficients. */
  IIR* get_num();

  /** Set the denominator coefficients from the static expression.  */
  void set_den(IIR* denominator);

  /** Return the denominator coefficients.  */
  IIR* get_den();

  /** Set the sampling frequency. */ 
  void set_t(IIR* period);

  /** Return the sampling frequency. */ 
  IIR* get_t();

  /** Set the initial_delay specifying the time of the first sampling. If omitted, it defaults to 0.0. */
  void set_initial_delay(IIR* initial_delay);

  /** Return the initial_delay specifying the time of the first sampling. */
  IIR* get_initial_delay();

  IIR *convert_tree(plugin_class_factory *factory);

  /** This returns an IIR_TextLiteral when the ZTF attribute is  instantiated. */
  IIR_TextLiteral *build_attribute_name();
  void publish_vhdl(ostream &);
protected:
  IIRBase_ZTFAttribute();
  virtual ~IIRBase_ZTFAttribute() = 0;

private:
  IIR* numerator;
  IIR* denominator;
  IIR* period;
  IIR* initial_delay;

};
#endif
