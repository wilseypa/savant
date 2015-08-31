
#ifndef IIRBASE_SOURCE_QUANTITY_DECLARATION_HH
#define IIRBASE_SOURCE_QUANTITY_DECLARATION_HH

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
#include "IIRBase_QuantityDeclaration.hh"
#include "IIR_SourceQuantityDeclaration.hh"
#include "IRBasicDataTypes.hh"
#include "IIR_DesignatorList.hh"

/** This class describes the Source quantity declaration. A sinusoidal
    equation can be characterized as v(t) = M cos(wt + p). The frequency w
    is chosen by the simulator and values for magnitude M and phase p are
    specified in the declaration.  The magnitude and phase expressions must
    be the same as the source quantity. */
class IIRBase_SourceQuantityDeclaration : public virtual IIR_SourceQuantityDeclaration,
					  public virtual IIRBase_QuantityDeclaration {

public:
  /** Returns the IIR_Kind of this node. */
  IIR_Kind 
  get_kind() const {
    return IIR_SOURCE_QUANTITY_DECLARATION ;
  }

  /** Returns the kind of this node in text form */
  const IIR_Char *get_kind_text() const { return "IIR_SourceQuantityDeclaration"; }

  /** Sets the magnitude expression of the source quantity. */
  void set_magnitude_expression(IIR* magnitude_expression);

  /** Returns the magnitude expression of the quantity. */
  IIR* get_magnitude_expression();
  
  /** Sets the phase expression of the source quantity. */
  void set_phase_expression(IIR* phase_expression);

  /** Returns the phase expression of the quantity. */
  IIR* get_phase_expression();

  /** Sets the noise expression of the source quantity. */
  void set_noise_expression(IIR* phase_expression);

  /** Returns the noise expression of the quantity. */
  IIR* get_noise_expression();
  
  IIR *convert_tree(plugin_class_factory *factory);

  void publish_vhdl_decl(ostream&);
protected:
  IIRBase_SourceQuantityDeclaration();
  virtual ~IIRBase_SourceQuantityDeclaration() = 0;

private:
  IIR* magnitude_expression;
  IIR* phase_expression;
  IIR* noise_expression;
};
#endif
