
#ifndef IIR_ATTRIBUTE_HH
#define IIR_ATTRIBUTE_HH

// Copyright (c) 1996-1999 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
// DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.


// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_Name.hh"

class IIR_Attribute : public virtual IIR_Name{
public:
  virtual ~IIR_Attribute() {}

  virtual IIR_Boolean is_function_attribute() = 0;
  virtual IIR_Boolean is_value_attribute() = 0;
  virtual IIR_Boolean has_suffix() = 0;

  /** Returns true if it is an above attribute. */ 
  virtual IIR_Boolean is_above_attribute() = 0;

  /** This returns an IIR_TextLiteral with the name of whatever attribute
      was instantiated. */
  virtual IIR_TextLiteral *build_attribute_name() = 0;
  virtual IIR_TextLiteral *get_attribute_name() = 0;
};
#endif
