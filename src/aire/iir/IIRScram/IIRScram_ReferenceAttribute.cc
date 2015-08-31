
// Copyright (c) 2002-2003 The University of Cincinnati.
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

// Authors: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_ReferenceAttribute.hh"
#include "IIRScram_Declaration.hh"
#include "error_func.hh"
#include "set.hh"

#include <iostream>
using std::cerr;
using std::endl;

#include <sstream>
using std::ostringstream;

IIRScram_ReferenceAttribute::~IIRScram_ReferenceAttribute() {}
     
IIRScram_TypeDefinition *
IIRScram_ReferenceAttribute::_get_subtype(){
  IIRScram *my_prefix = _get_prefix();
  savant::set<IIRScram_Declaration> *terminal_decl_set = my_prefix->_symbol_lookup();
  IIRScram_Declaration *term_decl = NULL;
  if (terminal_decl_set == NULL) {
    report_undefined_symbol(my_prefix);
    return NULL;
  }
  term_decl = terminal_decl_set->getElement();
  while (term_decl != NULL) {
    if (term_decl->_is_terminal() == FALSE) {
      terminal_decl_set->remove(term_decl);
    }
    term_decl = terminal_decl_set->getNextElement();
  }
  switch (terminal_decl_set->size()) {
  case 0: {
    ostringstream cerr;
    cerr << "|" << _get_attribute_name() 
	 << "| may only be applied to terminals." << endl;
    return NULL;
  }
    break;
  case 1: {
    set_prefix(terminal_decl_set->getElement());
  }
    break;
  default: {
    report_ambiguous_error(my_prefix, terminal_decl_set->convert_set<IIR_Declaration>());
    return NULL;
  }
  }
  ASSERT(_get_prefix()->_get_subtype() != NULL);
  return dynamic_cast<IIRScram_TypeDefinition *>((_get_prefix()->_get_subtype())->get_across());
}
