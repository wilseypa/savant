
#ifndef IIRBASE_SEQUENTIAL_STATEMENT_LIST_HH
#define IIRBASE_SEQUENTIAL_STATEMENT_LIST_HH

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
//          Timothy J. McBrayer tmcrbaye@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_List.hh"
#include "IIR_SequentialStatementList.hh"

class IIR_SequentialStatement;

class IIRBase_SequentialStatementList : public virtual IIRBase_List, public virtual IIR_SequentialStatementList{
public:
  IIR_Kind get_kind() const {return IIR_SEQUENTIAL_STATEMENT_LIST;}
  const IIR_Char *get_kind_text() const {return "IIR_SequentialStatementList";}

  IIR_SequentialStatement* first();
  IIR_SequentialStatement* successor(IIR_SequentialStatement*);

  IIR_Boolean is_above_attribute_found();

  void publish_vhdl(ostream &);
protected:
  
  IIRBase_SequentialStatementList();
  virtual ~IIRBase_SequentialStatementList() = 0;
    
private:

};
#endif
