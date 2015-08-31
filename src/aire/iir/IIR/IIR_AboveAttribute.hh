
#ifndef IIR_ABOVE_ATTRIBUTE_HH
#define IIR_ABOVE_ATTRIBUTE_HH

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

// Authors: Harish Venkataramani venkath@ececs.uc.edu

#include "savant_config.hh"
#include "IIR_Attribute.hh"

class IIR_AboveAttribute : public virtual IIR_Attribute {

public:
  IIR_AboveAttribute() {};
  virtual ~IIR_AboveAttribute() {};
  
  /** Sets the value of the expression whose type 
      is the same as that of Q. */
  virtual void set_suffix(IIR* suffix) = 0;
  
  /** Returns the value of the expression. */
  virtual IIR* get_suffix() = 0;
protected:

private:

};
#endif
