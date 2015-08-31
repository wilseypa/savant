
#ifndef IIR_SOURCE_QUANTITY_DECLARATION_HH
#define IIR_SOURCE_QUANTITY_DECLARATION_HH

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
#include "IIR_QuantityDeclaration.hh"

class IIR_SourceQuantityDeclaration : public virtual IIR_QuantityDeclaration {

public:
  virtual ~IIR_SourceQuantityDeclaration() {};

  /** Sets the magnitude expression of the source quantity. */
  virtual void set_magnitude_expression(IIR* magnitude_expression) = 0;

  /** Returns the magnitude expression of the quantity. */
  virtual IIR* get_magnitude_expression() = 0;
  
  /** Sets the phase expression of the source quantity. */
  virtual void set_phase_expression(IIR* phase_expression) = 0;

  /** Returns the phase expression of the quantity. */
  virtual IIR* get_phase_expression() = 0;

  /** Sets the noise expression of the source quantity. */
  virtual void set_noise_expression(IIR* phase_expression) = 0;

  /** Returns the noise expression of the quantity. */
  virtual IIR* get_noise_expression() = 0;
  
protected:
private:
};
#endif
