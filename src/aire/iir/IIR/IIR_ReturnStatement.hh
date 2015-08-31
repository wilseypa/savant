
#ifndef IIR_RETURN_STATEMENT_HH
#define IIR_RETURN_STATEMENT_HH

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
//          Malolan Chetlur     mal@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIR_SequentialStatement.hh"

class IIR_SubprogramDeclaration;

class IIR_ReturnStatement : public virtual IIR_SequentialStatement{
public:
  virtual ~IIR_ReturnStatement() {}
    
  virtual void set_enclosing_subprogram( IIR_SubprogramDeclaration *enclosing_subprogram) = 0;
  virtual IIR_SubprogramDeclaration* get_enclosing_subprogram() = 0;

  virtual void set_return_expression( IIR *return_expression ) = 0;
  virtual IIR* get_return_expression() = 0;
};
#endif
