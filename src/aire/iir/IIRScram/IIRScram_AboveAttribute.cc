
// Copyright (c) The University of Cincinnati.  All rights reserved.

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

#include "IIRScram_AboveAttribute.hh"
#include "error_func.hh"
#include "set.hh"
#include <iostream>
using std::cerr;
using std::endl;

void
IIRScram_AboveAttribute::_resolve_suffix_special() {
  ASSERT( _get_suffix() != NULL );
  savant::set<IIRScram_TypeDefinition> *suffix_rvals = _get_suffix()->_get_rval_set();
  if ( suffix_rvals == NULL ){
    report_undefined_symbol( _get_suffix() );
  }
  switch( suffix_rvals->size() ){
  case 0:{
    cerr << "|" << _get_suffix() << "| was not declared in this scope." << endl;
    abort();
  }
  case 1:{
    IIRScram_TypeDefinition *my_rval = suffix_rvals->getElement();
    set_suffix( _get_suffix()->_semantic_transform( my_rval ) );
    _get_suffix()->_type_check( my_rval );
    set_suffix( _get_suffix()->_rval_to_decl( my_rval ) );
    break;
  }
  default:{
    report_ambiguous_error( get_suffix(), suffix_rvals->convert_set<IIR_TypeDefinition>() );
  }
  }
}
