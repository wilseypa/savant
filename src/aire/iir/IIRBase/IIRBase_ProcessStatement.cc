
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

#include "IIRBase_ProcessStatement.hh"
#include "IIRBase_DeclarationList.hh"
#include "IIR_SequentialStatementList.hh"
#include "IIR_DesignFile.hh"
#include "IIR_Label.hh"
#include "plugin_class_factory.hh"

IIRBase_ProcessStatement::IIRBase_ProcessStatement()  :
  process_declarative_part(0),
  process_statement_part(0),
  postponed( false ) { }

IIRBase_ProcessStatement::~IIRBase_ProcessStatement(){
  delete process_declarative_part;
  process_declarative_part = 0;
  delete process_statement_part;
  process_statement_part = 0;
}

void 
IIRBase_ProcessStatement::set_postponed( IIR_Boolean new_postponed ){
  postponed = new_postponed;
}

IIR_Boolean 
IIRBase_ProcessStatement::get_postponed() {
  return postponed;
}

// List Accessor(s)
IIR_DeclarationList *
IIRBase_ProcessStatement::get_process_declarative_part() {
  if( process_declarative_part == 0 ){
    process_declarative_part = 
      get_class_factory()->new_IIR_DeclarationList();
  }

  ASSERT(process_declarative_part != NULL);
  return process_declarative_part;
}

IIR_SequentialStatementList *
IIRBase_ProcessStatement::get_process_statement_part() {
  if( process_statement_part == 0 ){
    process_statement_part =
      get_class_factory()->new_IIR_SequentialStatementList();
  }
  ASSERT( process_statement_part != NULL);
  return process_statement_part;
}

void
IIRBase_ProcessStatement::set_process_declarative_part(IIR_DeclarationList *new_process_declarative_part) {
  ASSERT(new_process_declarative_part != NULL);
  process_declarative_part = new_process_declarative_part;
}

void
IIRBase_ProcessStatement::set_process_statement_part(IIR_SequentialStatementList *new_process_statement_part) {
  ASSERT(new_process_statement_part != NULL);
  delete process_statement_part;
  process_statement_part = new_process_statement_part;
}

IIR *
IIRBase_ProcessStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ProcessStatement *new_node = dynamic_cast<IIRBase_ProcessStatement *>(IIRBase_ConcurrentStatement::convert_tree(factory));

  // Process the variables
  new_node->process_declarative_part = dynamic_cast<IIR_DeclarationList *>(convert_node(process_declarative_part, factory));
  new_node->process_statement_part = dynamic_cast<IIR_SequentialStatementList *>(convert_node(process_statement_part, factory));
  new_node->postponed = postponed;

  return new_node;
}

savant::set<IIR_Declaration> *
IIRBase_ProcessStatement::find_declarations( IIR_Name *name){
  return get_process_declarative_part()->find_declarations( name);
}

void 
IIRBase_ProcessStatement::publish_vhdl(ostream &vhdl_out) {
  publish_vhdl_stmt_label(vhdl_out);
    
  if (get_postponed() == true) {
    vhdl_out << "postponed ";
  }
  vhdl_out << "process\n";
  dynamic_cast<IIRBase_DeclarationList *>(get_process_declarative_part())->publish_vhdl_decl(vhdl_out);
  vhdl_out << "\nbegin\n";
  get_process_statement_part()->publish_vhdl(vhdl_out);
  vhdl_out << "end ";
  if (get_postponed() == true) {
    vhdl_out << "postponed ";
  }
  vhdl_out << "process";
  if (get_label() != NULL) {
    vhdl_out << " ";
    get_label()->publish_vhdl(vhdl_out);
  }
  vhdl_out << ";\n\n";
}
