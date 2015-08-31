
#ifndef IIRSCRAM_BREAK_ELEMENT_HH
#define IIRSCRAM_BREAK_ELEMENT_HH

// Copyright (c) 2003 The University of Cincinnati.
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

// Author: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_Tuple.hh"
#include "IIRBase_BreakElement.hh"

class IIRScram_Name;

/** The extension base for Break Element. In each Break Element, the
    quantity denoted by the quantity name is the break quantity of the
    break element. */
class IIRScram_BreakElement : public virtual IIRBase_BreakElement, public virtual IIRScram_Tuple {

public: 
  IIRScram_BreakElement() {};
  virtual ~IIRScram_BreakElement() {}
  
  /** @name Method for publishing VHDL code. */
    
  void _type_check();
  
  // Helper functions
  IIRScram_Name *_get_quantity_name();
  IIRScram_Name *_get_selector_quantity_name();
  IIRScram      *_get_expression();
protected:
private:
  
};
#endif
