
#ifndef IIRSCRAM_DOT_ATTRIBUTE_HH
#define IIRSCRAM_DOT_ATTRIBUTE_HH

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
#include "IIRBase_DotAttribute.hh"
#include "IIRScram_Attribute.hh"

class IIR_Declaration;
template <class type> class dl_list;

/** The extension base for Dot attribute of quantities (Q'dot).  For a
    Quantity Q, the attribute Q'Dot yields a quantity of type as Q. */
class IIRScram_DotAttribute : public virtual IIRBase_DotAttribute, public virtual IIRScram_Attribute {

public:
  IIRScram_DotAttribute() {}
  virtual ~IIRScram_DotAttribute() {};

  /** @name Method for publishing VHDL code. */
    
  /** Returns the type of the quantity. The implicit quantity is of the
      same type as the quantity Q.*/
  IIRScram_TypeDefinition *_get_subtype();
  
protected:
  
private:
  
};
#endif
