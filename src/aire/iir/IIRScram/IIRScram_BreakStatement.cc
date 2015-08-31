
// Copyright (c) 2003 The University of Cincinnati.
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

// Author: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_BreakList.hh"
#include "IIRScram_BreakStatement.hh"
#include "IIRScram_BreakElement.hh"

void
IIRScram_BreakStatement::_type_check() {
  IIRScram *new_condition = NULL;
  IIRScram_BreakElement *break_element =
    dynamic_cast<IIRScram_BreakElement *>(get_break_list()->first());
  while ( break_element != NULL) {
    break_element->_type_check();
    break_element = dynamic_cast<IIRScram_BreakElement *>(get_break_list()->successor(break_element));
  }
  
  if ( get_condition() != NULL ){
    new_condition = _type_check_and_resolve_boolean_condition( _get_condition() );
    ASSERT( new_condition != NULL);
    ASSERT( new_condition->is_resolved() == TRUE );
    set_condition( new_condition );
  }
}

IIRScram_BreakList *
IIRScram_BreakStatement::_get_break_list() {
  return dynamic_cast<IIRScram_BreakList *>(get_break_list());
}

IIRScram *
IIRScram_BreakStatement::_get_condition() {
  return dynamic_cast<IIRScram *>(get_condition());
}
