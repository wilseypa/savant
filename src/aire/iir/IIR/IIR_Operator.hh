#ifndef IIR_OPERATOR_HH
#define IIR_OPERATOR_HH
// Copyright (c) 1996-2000 The University of Cincinnati.  
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

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIR_Expression.hh"

class IIR_SubprogramDeclaration;

class IIR_Operator : public virtual IIR_Expression {
public:
  virtual ~IIR_Operator() {};

  virtual void set_implementation( IIR_SubprogramDeclaration * decl)  = 0;
  virtual IIR_SubprogramDeclaration *get_implementation() = 0;

  /**
     Returns the string representation of the name of this operator.  For
     example, IIR_AdditionOperator returns "+", IIR_XorOperator returns
     "xor", etc.
  */
  virtual const string &get_operator_string() const = 0;
};

#endif
