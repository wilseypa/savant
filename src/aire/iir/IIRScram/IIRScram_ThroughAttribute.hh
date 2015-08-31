
#ifndef IIRSCRAM_THROUGH_ATTRIBUTE_HH
#define IIRSCRAM_THROUGH_ATTRIBUTE_HH

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
#include "IIRBase_ThroughAttribute.hh"
#include "IIRScram_Attribute.hh"

/** The extension base for Through attribute of Nature (N'through).  This
    class describes N'Through. For a nature N, the attribute N'through
    returns the through type of the nature N. */
class IIRScram_ThroughAttribute : public virtual IIRBase_ThroughAttribute, public virtual IIRScram_Attribute {

public:
  IIRScram_ThroughAttribute(){}
  virtual ~IIRScram_ThroughAttribute() {};

  /** @name Method for publishing VHDL code. */

  /** Returns the "through" type of the nature of the 
      Nature.*/
  IIRScram_TypeDefinition* _get_subtype();

protected:

private:
};
#endif

