	
#ifndef IIRSCRAM_ZTF_ATTRIBUTE_HH
#define IIRSCRAM_ZTF_ATTRIBUTE_HH

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
#include "IIRScram_Attribute.hh"
#include "IIRBase_ZTFAttribute.hh"

/** This class describes the 'ztf attribute. For a scalar quantity Q, the
    attribute Q'ztf(numerator, denominator, T, initial_delay) yields a
    quantity whose type is the base type of Q and value is the Z transform
    of Q.num and den are the numerator and denominator polynomials,
    specified as real_vector arrays.  The quantity Q is sampled at the time
    given by intial_delay and at intervals of T thereafter.  */
class IIRScram_ZTFAttribute : public virtual IIRScram_Attribute, public virtual IIRBase_ZTFAttribute {

public:
  IIRScram_ZTFAttribute() {}
  virtual ~IIRScram_ZTFAttribute() {}

  /** @name Method for publishing VHDL code. */
  /** This returns the subtype of the quantity to which the attribute is attached. */
  IIRScram_TypeDefinition * _get_subtype();
  /** Returns a pointer to the Quantity created by the build free quantity declaration. */
  IIRScram_Declaration * _get_implicit_declaration( const string & , IIRScram_TypeDefinition *  );
  
  /** Function for processing the numerator and denominator parts of the attributes's suffix. */
  void _resolve_attribute_parameters();

  // Helper Functions
  IIRScram      *_get_num();
  IIRScram      *_get_den();
  IIRScram      *_get_t();
  IIRScram      *_get_initial_delay();

protected:

private:

};
#endif

