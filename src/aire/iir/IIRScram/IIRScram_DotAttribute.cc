
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

#include "IIRScram_DotAttribute.hh"
#include "error_func.hh"
#include "set.hh"

#include <iostream>
using std::cerr;
using std::endl;

IIRScram_TypeDefinition *
IIRScram_DotAttribute::_get_subtype() {
  IIRScram *my_prefix = _get_prefix();
  savant::set<IIRScram_Declaration> *quantity_decl_set = NULL;
  quantity_decl_set = my_prefix->_symbol_lookup();
  IIRScram_Declaration *quan_decl = NULL;
  
  if (quantity_decl_set == NULL) {
    report_undefined_symbol(my_prefix);
    return NULL;
  }
  
  quan_decl = quantity_decl_set->getElement();
  while (quan_decl != NULL) {
    if (quan_decl->_is_quantity() == FALSE) {
      quantity_decl_set->remove(quan_decl);
    }
    quan_decl = quantity_decl_set->getNextElement();
  }
  switch(quantity_decl_set->size()) {
  case 0: {
    cerr << "|" << _get_attribute_name() 
	 << "| may only be applied to terminals." << endl;
    return NULL;
  }
    break;
  case 1: {
    set_prefix(quantity_decl_set->getElement());
  }
    break;
  default: {
    report_ambiguous_error(my_prefix, quantity_decl_set->convert_set<IIR_Declaration>());
    return NULL;
  }
  }
  return _get_prefix()->_get_subtype();
}
