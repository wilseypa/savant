
#ifndef IIRSCRAM_ABOVE_ATTRIBUTE_HH
#define IIRSCRAM_ABOVE_ATTRIBUTE_HH

// Copyright (c) The University of Cincinnati.  All rights reserved.

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
#include "IIRBase_AboveAttribute.hh"
#include "IIRScram_Attribute.hh"

/** The IIR node for above attribute of quantities (Q'Above).  For a
    Quantity Q, the attribute Q'Above yields a signal. */
class IIRScram_AboveAttribute : public virtual IIRBase_AboveAttribute, public virtual IIRScram_Attribute {

public:
  IIRScram_AboveAttribute() {};
  virtual ~IIRScram_AboveAttribute() {};

  /** @name Method for publishing VHDL code. */

  /** Returns a pointer to the implicit quantity created using
      build_signal_declaration. */
  IIRScram_Declaration* _get_implicit_declaration(const string &, IIRScram_TypeDefinition *);

  IIR_Boolean has_suffix(){ return TRUE; }
  
  virtual void _resolve_suffix_special();

protected:

private:

};
#endif
