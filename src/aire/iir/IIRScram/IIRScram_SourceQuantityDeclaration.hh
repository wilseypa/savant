
#ifndef IIRSCRAM_SOURCE_QUANTITY_DECLARATION_HH
#define IIRSCRAM_SOURCE_QUANTITY_DECLARATION_HH

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
#include "IIRBase_SourceQuantityDeclaration.hh"
#include "IIRScram_QuantityDeclaration.hh"

template <class type> class dl_list;
class IIRScram_Declaration;

/** This class describes the Source quantity declaration. A sinusoidal
    equation can be characterized as v(t) = M cos(wt + p). The frequency w
    is chosen by the simulator and values for magnitude M and phase p are
    specified in the declaration.  The magnitude and phase expressions must
    be the same as the source quantity. */    
class IIRScram_SourceQuantityDeclaration : public virtual IIRBase_SourceQuantityDeclaration, public virtual IIRScram_QuantityDeclaration {

public:
  IIRScram_SourceQuantityDeclaration();
  virtual ~IIRScram_SourceQuantityDeclaration();

  /** This method relates to the publishing of C++ code. */

  /** These methods calculate a node's rval_set.Either will return a  set with a 
  bunch of type definitions, or will return NULL if it doesn't have a valid rval. */
  savant::set<IIRScram_TypeDefinition> *_get_rval_set();

  /** This method tells us if a declaration is a an IIR_SourceQuantityDeclaration. */
  IIR_Boolean _is_sourceQ() {
    return TRUE;
  }

  // Helper Functions
  IIRScram *_get_noise_expression();
  IIRScram *_get_phase_expression();
  IIRScram *_get_magnitude_expression();
protected:

private:

};
#endif
