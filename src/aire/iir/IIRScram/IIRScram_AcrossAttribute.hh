
#ifndef IIRSCRAM_ACROSS_ATTRIBUTE_HH
#define IIRSCRAM_ACROSS_ATTRIBUTE_HH

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
#include "IIRBase_AcrossAttribute.hh"
#include "IIRScram_Attribute.hh"

/** The extension base of Across attribute of Nature (N'across).  This
    class describes N'Across. For a nature N , the attribute N'across
    returns the across type of the nature N. */
class IIRScram_AcrossAttribute : public virtual IIRBase_AcrossAttribute, public virtual IIRScram_Attribute {

public:
  IIRScram_AcrossAttribute() {};
  virtual ~IIRScram_AcrossAttribute() {};

  /** @name Method for publishing VHDL code. */
  
  /** Returns the "across" type of the nature of the
      Nature.*/
  IIRScram_TypeDefinition* _get_subtype();
  
protected:

private:
};
#endif
