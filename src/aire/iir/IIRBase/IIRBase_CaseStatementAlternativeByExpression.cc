
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

#include "IIRBase_CaseStatementAlternativeByExpression.hh"
#include "IIR_Choice.hh"

IIRBase_CaseStatementAlternativeByExpression::IIRBase_CaseStatementAlternativeByExpression() {}
IIRBase_CaseStatementAlternativeByExpression::~IIRBase_CaseStatementAlternativeByExpression() {}


void 
IIRBase_CaseStatementAlternativeByExpression::set_choice(IIR_Choice* c) {
  choice = c;
}


IIR_Choice*
IIRBase_CaseStatementAlternativeByExpression::get_choice() {
  return choice;
}

IIR *
IIRBase_CaseStatementAlternativeByExpression::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_CaseStatementAlternativeByExpression *new_node = dynamic_cast<IIRBase_CaseStatementAlternativeByExpression *>(IIRBase_CaseStatementAlternative::convert_tree(factory));

  // Process the variables
  new_node->choice = dynamic_cast<IIR_Choice *>(convert_node(choice, factory));

  return new_node;
}

IIR_Boolean
IIRBase_CaseStatementAlternativeByExpression::is_resolved(){
  return get_choice()->is_resolved();
  // The statements should be checked if they're resolved somewhere
  // else.  If we do it here, then we'll end up with cascading calls
  // to "_is_resolved".  (What if one of our statements is also a case
  // statement, for instance, and one of it's)
}

ostream &
IIRBase_CaseStatementAlternativeByExpression::print( ostream &os ){
  os << *get_choice();
  return os;
}

void 
IIRBase_CaseStatementAlternativeByExpression::publish_vhdl(ostream &vhdl_out) {
  publish_vhdl_alternative(vhdl_out, get_choice());
}
