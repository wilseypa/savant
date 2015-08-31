
#ifndef IIR_FLOATING_POINT_LITERAL_HH
#define IIR_FLOATING_POINT_LITERAL_HH

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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_Literal.hh"


class IIR_FloatingPointLiteral : public virtual IIR_Literal{
  friend class VHDLParser;

public:
  virtual ~IIR_FloatingPointLiteral() {}
    
  virtual void release() = 0;

  virtual const string print_value(IIR_Int32) = 0;

  virtual void set_base(IIR_Int32) = 0;
  virtual IIR_Int32 get_base() = 0;
  virtual void set_mantissa(IIR_Char*, IIR_Int32) = 0;
  virtual IIR_Char* get_mantissa() = 0;
  virtual IIR_Int32 get_mantissa_length() = 0;
  virtual void set_exponent(IIR_Char*, IIR_Int32) = 0;
  virtual IIR_Char* get_exponent() = 0;
  virtual IIR_Int32 get_exponent_length() = 0;
};
#endif
