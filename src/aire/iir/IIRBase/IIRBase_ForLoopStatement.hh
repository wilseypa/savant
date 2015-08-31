
#ifndef IIRBASE_FOR_LOOP_STATEMENT_HH
#define IIRBASE_FOR_LOOP_STATEMENT_HH

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
#include "IIRBase_SequentialStatement.hh"
#include "IIR_ForLoopStatement.hh"

class IIR_ConstantDeclaration;
class IIR_SequentialStatementList;

class IIRBase_ForLoopStatement : public virtual IIRBase_SequentialStatement, public virtual IIR_ForLoopStatement{

public:
  // List Accessor(s)
  IIR_SequentialStatementList   *get_sequence_of_statements();
  void                          set_sequence_of_statements(IIR_SequentialStatementList *new_sequence_of_statements);

  IIR_Kind get_kind() const {return IIR_FOR_LOOP_STATEMENT;}
  const IIR_Char *get_kind_text() const {return "IIR_ForLoopStatement";}

  void set_iteration_scheme( IIR_ConstantDeclaration* iterator);
  IIR_ConstantDeclaration* get_iteration_scheme();

  IIR *convert_tree(plugin_class_factory *factory);
 
  IIR_Boolean has_statement_list() { return TRUE; }
  IIR_Boolean is_above_attribute_found();

  savant::set<IIR_Declaration> *find_declarations( IIR_Name * );

  void publish_vhdl(ostream &);
protected:
  IIRBase_ForLoopStatement();
  virtual ~IIRBase_ForLoopStatement() = 0;
    
private:
  // List Variable(s)
  IIR_SequentialStatementList *sequence_of_statements;

  IIR_ConstantDeclaration* iterator;

};
#endif
