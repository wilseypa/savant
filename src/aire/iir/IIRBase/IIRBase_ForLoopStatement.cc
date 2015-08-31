
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



#include "savant.hh"
#include "set.hh"
#include "IIRBase_ForLoopStatement.hh"
#include "IIRBase_TextLiteral.hh"
#include "IIR_SequentialStatementList.hh"
#include "IIR_ConstantDeclaration.hh"


IIRBase_ForLoopStatement::IIRBase_ForLoopStatement()  :
  sequence_of_statements(0) {
  set_iteration_scheme(NULL);
}


IIRBase_ForLoopStatement::~IIRBase_ForLoopStatement() {
  if(iterator != NULL)
    delete iterator;
}

void
IIRBase_ForLoopStatement::set_iteration_scheme( IIR_ConstantDeclaration *new_iterator ){
  iterator = new_iterator;
}

IIR_ConstantDeclaration*
IIRBase_ForLoopStatement::get_iteration_scheme() {
  return iterator;
}


// List Accessor(s)
IIR_SequentialStatementList *
IIRBase_ForLoopStatement::get_sequence_of_statements() {
  ASSERT(sequence_of_statements != NULL);
  return sequence_of_statements;
}


void
IIRBase_ForLoopStatement::set_sequence_of_statements(IIR_SequentialStatementList *new_sequence_of_statements) {
  ASSERT(new_sequence_of_statements != NULL);
  delete sequence_of_statements;
  sequence_of_statements = new_sequence_of_statements;
}

IIR *
IIRBase_ForLoopStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ForLoopStatement *new_node = dynamic_cast<IIRBase_ForLoopStatement *>(IIRBase_SequentialStatement::convert_tree(factory));

  // Process the variables
  new_node->sequence_of_statements = dynamic_cast<IIR_SequentialStatementList *>(convert_node(sequence_of_statements, factory));
  new_node->iterator = dynamic_cast<IIR_ConstantDeclaration *>(convert_node(iterator, factory));

  return new_node;
}

savant::set<IIR_Declaration> *
IIRBase_ForLoopStatement::find_declarations( IIR_Name *to_find ){
  ASSERT( get_iteration_scheme() != NULL );
  IIR_TextLiteral *loop_param = get_iteration_scheme()->get_declarator();
  if( IIRBase_TextLiteral::cmp( loop_param, to_find ) == 0 ){
    return new savant::set<IIR_Declaration>(get_iteration_scheme());
  }
  else{
    return NULL;
  }
}

IIR_Boolean
IIRBase_ForLoopStatement::is_above_attribute_found() {
  return get_sequence_of_statements()->is_above_attribute_found();
}

void 
IIRBase_ForLoopStatement::publish_vhdl(ostream &vhdl_out) {

  ASSERT(get_iteration_scheme() != NULL);
  ASSERT(get_iteration_scheme()->is_resolved() == TRUE);

  publish_vhdl_stmt_label(vhdl_out);
    
  vhdl_out << "for ";
  get_iteration_scheme()->get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << " in ";

  get_iteration_scheme()->get_subtype()->publish_vhdl(vhdl_out);
  
  vhdl_out << " loop\n";

  if (get_sequence_of_statements()->size() != 0) {
    get_sequence_of_statements()->publish_vhdl(vhdl_out);
  }

  vhdl_out << "end loop";
}
