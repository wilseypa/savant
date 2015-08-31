
#ifndef IIRSCRAM_LTF_ATTRIBUTE_HH
#define IIRSCRAM_LTF_ATTRIBUTE_HH

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
#include "IIRBase_LTFAttribute.hh"
#include "IIRScram_Attribute.hh"

class IIR_Declaration;
template <class type> class dl_list;

/** This class describes the 'ltf attribute.  For a scalar quantity Q, the
    attribute Q'ltf(num, den) yields a quantity whose type is the base type
    of Q and value is the Laplace transform of Q.num and den are the
    numerator and denominator polynomials, specified as real_vector
    arrays. */
class IIRScram_LTFAttribute : public virtual IIRBase_LTFAttribute, public virtual IIRScram_Attribute {

public:
  IIRScram_LTFAttribute() {} ;
  virtual ~IIRScram_LTFAttribute();

  /** @name Method for publishing VHDL code. */

  /** This returns the subtype of the quantity to which the attribute is attached. */
  IIRScram_TypeDefinition * _get_subtype();

  /** Returns a pointer to the Quantity created by the build free quantity declaration. */  
  IIRScram_Declaration * _get_implicit_declaration( const string & , IIRScram_TypeDefinition *  );

  /** Function for processing the numerator and denominator parts of the attributes's suffix. */
  void _resolve_attribute_parameters();

  // Helper functions
  IIRScram *_get_num();
  IIRScram *_get_den();
protected:
private:
  
};
#endif
