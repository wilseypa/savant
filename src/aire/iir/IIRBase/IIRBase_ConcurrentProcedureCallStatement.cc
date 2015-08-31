
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


#include "IIRBase_ConcurrentProcedureCallStatement.hh"
#include "IIR_ArchitectureStatementList.hh"
#include "IIRBase_AssociationList.hh"

IIRBase_ConcurrentProcedureCallStatement::IIRBase_ConcurrentProcedureCallStatement() :
  actual_parameter_part(0),
  process_statement_part(0),
  postponed(false),
  procedure_name(0){}


IIRBase_ConcurrentProcedureCallStatement::~IIRBase_ConcurrentProcedureCallStatement(){
  delete actual_parameter_part;
  actual_parameter_part = 0;
  delete process_statement_part;
  process_statement_part = 0;
}

void 
IIRBase_ConcurrentProcedureCallStatement::set_postponed( IIR_Boolean postponed ){
  this->postponed = postponed;
}

IIR_Boolean 
IIRBase_ConcurrentProcedureCallStatement::get_postponed(){
  return postponed;
}

void 
IIRBase_ConcurrentProcedureCallStatement::set_procedure_name( IIR *procedure_name ){
  this->procedure_name = procedure_name;
}

IIR *
IIRBase_ConcurrentProcedureCallStatement::get_procedure_name(){
  return procedure_name;
}

// List Accessor(s)
IIR_AssociationList *
IIRBase_ConcurrentProcedureCallStatement::get_actual_parameter_part() {
  ASSERT(actual_parameter_part != NULL);
  return actual_parameter_part;
}

IIR_ArchitectureStatementList *
IIRBase_ConcurrentProcedureCallStatement::get_process_statement_part() {
  ASSERT(process_statement_part != NULL);
  return process_statement_part;
}


void
IIRBase_ConcurrentProcedureCallStatement::set_actual_parameter_part(IIR_AssociationList *new_actual_parameter_part) {
  ASSERT(new_actual_parameter_part != NULL);
  actual_parameter_part = new_actual_parameter_part;
}

void
IIRBase_ConcurrentProcedureCallStatement::set_process_statement_part(IIR_ArchitectureStatementList *new_process_statement_part) {
  ASSERT(new_process_statement_part != NULL);
  delete process_statement_part;
  process_statement_part = new_process_statement_part;
}

IIR *
IIRBase_ConcurrentProcedureCallStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ConcurrentProcedureCallStatement *new_node = dynamic_cast<IIRBase_ConcurrentProcedureCallStatement *>(IIRBase_ConcurrentStatement::convert_tree(factory));

  // Process the variables
  new_node->actual_parameter_part = dynamic_cast<IIR_AssociationList *>(convert_node(actual_parameter_part, factory));
  new_node->process_statement_part = dynamic_cast<IIR_ArchitectureStatementList *>(convert_node(process_statement_part, factory));
  new_node->postponed = postponed;
  new_node->procedure_name = convert_node(procedure_name, factory);

  return new_node;
}

void 
IIRBase_ConcurrentProcedureCallStatement::publish_vhdl(ostream &vhdl_out) {

  publish_vhdl_stmt_label(vhdl_out);

  if (get_postponed() == true) {
    vhdl_out << "postponed ";
  }
  
  get_procedure_name()->publish_vhdl(vhdl_out);
  
  if (get_actual_parameter_part()->size() != 0) {
    vhdl_out << "(";
    
    if(get_actual_parameter_part()->size() != 0) {
      dynamic_cast<IIRBase_AssociationList *>(get_actual_parameter_part())->publish_vhdl_without_formals(vhdl_out);
    }
    
    vhdl_out << ")";
  }
  
  vhdl_out << ";\n";
}
