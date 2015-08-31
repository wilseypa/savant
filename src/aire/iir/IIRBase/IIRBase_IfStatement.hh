
#ifndef IIRBASE_IF_STATEMENT_HH
#define IIRBASE_IF_STATEMENT_HH

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
#include "IIRBase_SequentialStatement.hh"
#include "IIR_IfStatement.hh"

class IIR_Elsif;
class IIR_SequentialStatementList;

class IIRBase_IfStatement : public virtual IIRBase_SequentialStatement, public virtual IIR_IfStatement{

public:
  // List Accessor(s)
  IIR_SequentialStatementList *get_then_sequence();
  IIR_SequentialStatementList *get_else_sequence();
  void                        set_then_sequence(IIR_SequentialStatementList *new_then_sequence);
  void                        set_else_sequence(IIR_SequentialStatementList *new_else_sequence);

  IIR_Kind get_kind() const {return IIR_IF_STATEMENT;}
  const IIR_Char *get_kind_text() const {return "IIR_IfStatement";}

  void set_condition( IIR*);
  IIR* get_condition();

  void set_elsif(IIR_Elsif*);
  IIR_Elsif* get_elsif();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean has_statement_list() { return TRUE; }
  IIR_Boolean is_above_attribute_found();

  void publish_vhdl(ostream &);
protected:
  IIRBase_IfStatement();
  virtual ~IIRBase_IfStatement() = 0;
    
private:
  // List Variable(s)
  IIR_SequentialStatementList   *then_sequence;
  IIR_SequentialStatementList   *else_sequence;

  IIR                           *condition;  
  IIR_Elsif                     *elsif_clause;

};
#endif
