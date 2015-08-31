
#ifndef IIRBASE_CONCURRENT_GENERATE_FOR_STATEMENT_HH
#define IIRBASE_CONCURRENT_GENERATE_FOR_STATEMENT_HH

// Copyright (c) 1996-2003 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
// DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_ConcurrentStatement.hh"
#include "IIR_ConcurrentGenerateForStatement.hh"

class IIR_ConstantDeclaration;
class IIR_DeclarationList;
class IIR_ArchitectureStatementList;

class IIRBase_ConcurrentGenerateForStatement : public virtual IIRBase_ConcurrentStatement, public virtual IIR_ConcurrentGenerateForStatement{

public:
  // List Accessor(s)
  IIR_DeclarationList           *get_block_declarative_part();
  IIR_ArchitectureStatementList *get_concurrent_statement_part();
  void                          set_block_declarative_part(IIR_DeclarationList *new_block_declarative_part);
  void                          set_concurrent_statement_part(IIR_ArchitectureStatementList *new_concurrent_statement_part);

  IIR_Kind get_kind() const {return IIR_CONCURRENT_GENERATE_FOR_STATEMENT;}
  const IIR_Char *get_kind_text() const {return "IIR_ConcurrentGenerateForStatement";}

  void set_generate_parameter_specification(IIR_ConstantDeclaration *parameter); 
  IIR_ConstantDeclaration *get_generate_parameter_specification();

  IIR *convert_tree(plugin_class_factory *factory);

  void publish_vhdl(ostream &);
protected:
  IIRBase_ConcurrentGenerateForStatement();
  virtual ~IIRBase_ConcurrentGenerateForStatement() = 0;
    
private:
  // List Variable(s)
  IIR_DeclarationList           *block_declarative_part;
  IIR_ArchitectureStatementList *concurrent_statement_part;

  IIR_ConstantDeclaration *parameter;
};
#endif
