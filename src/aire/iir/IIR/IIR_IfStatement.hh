
#ifndef IIR_IF_STATEMENT_HH
#define IIR_IF_STATEMENT_HH

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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_SequentialStatement.hh"

class IIR_Elsif;
class IIR_SequentialStatementList;

class IIR_IfStatement : public virtual IIR_SequentialStatement{

public:
  virtual ~IIR_IfStatement() {}
    
  // List accessor(s)
  virtual IIR_SequentialStatementList   *get_then_sequence() = 0;
  virtual IIR_SequentialStatementList   *get_else_sequence() = 0;
  virtual void                          set_then_sequence(IIR_SequentialStatementList *) = 0;
  virtual void                          set_else_sequence(IIR_SequentialStatementList *) = 0;

  virtual void set_condition( IIR*) = 0;
  virtual IIR* get_condition() = 0;

  virtual void set_elsif(IIR_Elsif*) = 0;
  virtual IIR_Elsif* get_elsif() = 0;
};
#endif
