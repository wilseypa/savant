
#ifndef IIRBASE_CASE_STATEMENT_HH
#define IIRBASE_CASE_STATEMENT_HH

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
#include "IIRBase_SequentialStatement.hh"
#include "IIR_CaseStatement.hh"

class IIR_CaseStatementAlternativeList;
class IIRBase_CaseStatement : public virtual IIRBase_SequentialStatement, public virtual IIR_CaseStatement{

public:
  // List Accessor(s)
  IIR_CaseStatementAlternativeList  *get_case_statement_alternatives();
  void                              set_case_statement_alternatives(IIR_CaseStatementAlternativeList *new_case_statement_alternatives);

  IIR_Kind get_kind() const {return IIR_CASE_STATEMENT;}
  const IIR_Char *get_kind_text() const {return "IIR_CaseStatement";}

  void set_expression( IIR *expression);
  IIR* get_expression();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_resolved();
  IIR_Boolean has_statement_list() { return TRUE;  }
  IIR_Boolean is_above_attribute_found();  

  void publish_vhdl(ostream &);
protected:
  IIRBase_CaseStatement();
  virtual ~IIRBase_CaseStatement() = 0;
    
private:
  // List Variable(s)
  IIR_CaseStatementAlternativeList  *case_statement_alternatives;

  IIR *my_expression;
};
#endif
