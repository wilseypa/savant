
// Copyright (c) 1996-2008 The University of Cincinnati.  
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

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

#include "IIRBase_CaseStatementAlternative.hh"
#include "IIR_SequentialStatementList.hh"

IIRBase_CaseStatementAlternative::IIRBase_CaseStatementAlternative() :
  sequence_of_statements(0) { }

IIRBase_CaseStatementAlternative::~IIRBase_CaseStatementAlternative(){
}

// List Accessor(s)
IIR_SequentialStatementList *
IIRBase_CaseStatementAlternative::get_sequence_of_statements() {
  ASSERT(sequence_of_statements != NULL);
  return sequence_of_statements;
}


void
IIRBase_CaseStatementAlternative::set_sequence_of_statements(IIR_SequentialStatementList *new_sequence_of_statements) {
  ASSERT(new_sequence_of_statements != NULL);
  delete sequence_of_statements;
  sequence_of_statements = new_sequence_of_statements;
}

IIR *
IIRBase_CaseStatementAlternative::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_CaseStatementAlternative *new_node = dynamic_cast<IIRBase_CaseStatementAlternative *>(IIRBase_Tuple::convert_tree(factory));

  // Process the variables
  new_node->sequence_of_statements = dynamic_cast<IIR_SequentialStatementList *>(convert_node(sequence_of_statements, factory));

  return new_node;
}

void
IIRBase_CaseStatementAlternative::publish_vhdl_alternative(ostream &vhdl_out, IIR *choice) {

  vhdl_out << "when ";
  choice->publish_vhdl(vhdl_out);

  // In selected signal assignment statements, the sequence_of_statements
  // list is empty.  In case statements the sequence_of_statements must be
  // published.  If the sequence of statements is empty, the analyzer must
  // insert a null statement into the statement list or else republishing
  // the vhdl will come out incorrectly (without the "=>").
  if (get_sequence_of_statements()->first() != NULL) {
    vhdl_out << " =>\n";
    get_sequence_of_statements()->publish_vhdl(vhdl_out);
  }
  
}
