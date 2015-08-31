
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

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

#include "IIR_Choice.hh"
#include "IIR_ChoiceList.hh"
#include "IIRBase_CaseStatementAlternativeByChoices.hh"

IIRBase_CaseStatementAlternativeByChoices::IIRBase_CaseStatementAlternativeByChoices()  :
  choices(0) { }

IIRBase_CaseStatementAlternativeByChoices::~IIRBase_CaseStatementAlternativeByChoices() {
}

// List Accessor(s)
IIR_ChoiceList *
IIRBase_CaseStatementAlternativeByChoices::get_choices() {
  ASSERT(choices != NULL);
  return choices;
}


void
IIRBase_CaseStatementAlternativeByChoices::set_choices(IIR_ChoiceList *new_choices) {
  ASSERT(new_choices != NULL);
  delete choices;
  choices = new_choices;
}

IIR *
IIRBase_CaseStatementAlternativeByChoices::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_CaseStatementAlternativeByChoices *new_node = dynamic_cast<IIRBase_CaseStatementAlternativeByChoices *>(IIRBase_CaseStatementAlternative::convert_tree(factory));

  // Process the variables
  new_node->choices = dynamic_cast<IIR_ChoiceList *>(convert_node(choices, factory));

  return new_node;
}

IIR_Boolean 
IIRBase_CaseStatementAlternativeByChoices::is_resolved(){
  IIR_Boolean retval = TRUE;
  IIR_Choice *current_choice = dynamic_cast<IIR_Choice *>(get_choices()->first());
  while( current_choice != NULL ){
    if( current_choice->is_resolved() == FALSE ){
      retval = FALSE;
      break;
    }
    current_choice = dynamic_cast<IIR_Choice *>(get_choices()->successor( current_choice ));
  }
  return retval;
}

void
IIRBase_CaseStatementAlternativeByChoices::publish_vhdl(ostream &vhdl_out){
  publish_vhdl_alternative(vhdl_out, get_choices());  
}
