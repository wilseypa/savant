
#ifndef IIRBASE_GREATER_THAN_OR_EQUAL_OPERATOR_HH
#define IIRBASE_GREATER_THAN_OR_EQUAL_OPERATOR_HH

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
#include "IIR_GreaterThanOrEqualOperator.hh"
#include "IIRBase_DyadicOperator.hh"

class IIRBase_GreaterThanOrEqualOperator : public virtual IIRBase_DyadicOperator,
					   public virtual IIR_GreaterThanOrEqualOperator{

public:
  IIR_Kind get_kind() const {return IIR_GREATER_THAN_OR_EQUAL_OPERATOR;}
  const IIR_Char *get_kind_text() const {return "IIR_GreaterThanOrEqualOperator";}
  const string &get_operator_string() const;

  Precedence  get_precedence();
  IIR_Boolean is_relational_operator(){ return TRUE; }

protected:
  IIRBase_GreaterThanOrEqualOperator();
  virtual ~IIRBase_GreaterThanOrEqualOperator() = 0;
    
private:
};
#endif
