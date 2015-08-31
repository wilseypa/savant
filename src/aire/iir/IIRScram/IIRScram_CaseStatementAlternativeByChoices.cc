
// Copyright (c) 1996-2002 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey    philip.wilsey@ieee.org
//          Timothy J. McBrayer
//          Umesh Kumar V. Rajasekaran
//          Malolan Chetlur    
//          Narayanan Thondugulam
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram.hh"
#include "IIRScram_CaseStatementAlternativeByChoices.hh"
#include "IIRScram_ChoiceList.hh"
#include "IIRScram_Choice.hh"
#include "IIRScram_SequentialStatementList.hh"
#include "error_func.hh"
#include "set.hh"

#include <clutils/Set.h>

IIRScram_CaseStatementAlternativeByChoices::IIRScram_CaseStatementAlternativeByChoices() {
  set_choices(new IIRScram_ChoiceList());
}

IIRScram_CaseStatementAlternativeByChoices::~IIRScram_CaseStatementAlternativeByChoices(){}

void 
IIRScram_CaseStatementAlternativeByChoices::
_type_check( savant::set<IIRScram_TypeDefinition> *context_set ){
  IIRScram_Choice *current_choice = NULL;

  current_choice = dynamic_cast<IIRScram_Choice *>(get_choices()->first());
  while( current_choice != NULL ){
    current_choice->_type_check( context_set );
    current_choice = dynamic_cast<IIRScram_Choice *>(get_choices()->successor( current_choice ));
  }
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_CaseStatementAlternativeByChoices::_get_rval_set( constraint_functor *functor ){
  savant::set<IIRScram_TypeDefinition> *retval = NULL;
  IIRScram_Choice *current_choice;

  current_choice = dynamic_cast<IIRScram_Choice *>(get_choices()->first());
  savant::set<IIRScram_TypeDefinition> *choice_rval_set;
  while( current_choice != NULL ){
    choice_rval_set = current_choice->_get_rval_set( functor );
    if( choice_rval_set == NULL ){
      report_undefined_symbol( current_choice );
      return NULL;
    }
    
    if( retval == NULL ){
      retval = choice_rval_set;
    }
    else{
      retval->intersect( choice_rval_set );
      delete choice_rval_set;
    }
    current_choice = dynamic_cast<IIRScram_Choice *>(get_choices()->successor( current_choice ));
  }
  return retval;
}

IIRScram*
IIRScram_CaseStatementAlternativeByChoices::_clone() {
  IIRScram_Choice *node, *choiceclone = NULL;
  IIRScram_CaseStatementAlternativeByChoices *clone = NULL; 

  clone = new IIRScram_CaseStatementAlternativeByChoices;
  IIRScram_CaseStatementAlternative::_clone(clone);

  node = dynamic_cast<IIRScram_Choice *>(get_choices()->first());
  while (NULL != node) {
    choiceclone = dynamic_cast<IIRScram_Choice*>(node->_clone());
    clone->get_choices()->append(choiceclone);
    node = dynamic_cast<IIRScram_Choice *>(get_choices()->successor(node));
  }
  return clone;
}

visitor_return_type *
IIRScram_CaseStatementAlternativeByChoices::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_CaseStatementAlternativeByChoices(this, arg);
};

IIRScram_ChoiceList *
IIRScram_CaseStatementAlternativeByChoices::_get_choices() {
  return dynamic_cast<IIRScram_ChoiceList *>(get_choices());
}


