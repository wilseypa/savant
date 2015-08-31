// Copyright (c) 1996-2000 The University of Cincinnati.  
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

// Authors: Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_Choice.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EnumerationLiteral.hh"
#include "IIRScram_Literal.hh"
#include "IIRScram_ScalarTypeDefinition.hh"

#include "set.hh"
#include "resolution_func.hh"
#include "error_func.hh"

#include <sstream>
using std::ostringstream;

savant::set<IIRScram_TypeDefinition> *
IIRScram_Choice::_get_rval_set(constraint_functor *functor){
  ASSERT( _get_value() != NULL );
  return _get_value()->_get_rval_set(functor);
}


IIRScram *
IIRScram_Choice::_rval_to_decl( IIRScram_TypeDefinition *my_typedef ){
  set_value( _get_value()->_rval_to_decl( my_typedef ) );
  return (IIRScram *)this;
}

savant::set<IIRScram_Declaration> *
IIRScram_Choice::_symbol_lookup(){
  return _get_value()->_symbol_lookup();
}

void 
IIRScram_Choice::_type_check( savant::set<IIRScram_TypeDefinition> *context_set ){
  set_value( _get_value()->_semantic_transform( context_set ) );
  _get_value()->_type_check( context_set );
  
  savant::set<IIRScram_TypeDefinition> *choice_rvals = _get_value()->_get_rval_set();
  
  if( choice_rvals == NULL ){
    report_undefined_symbol( _get_value() );
  }

  reconcile_sets( context_set, choice_rvals );
  switch( context_set->size() ){
  case 0:{
    ostringstream err;
    err << "Choice |" << _get_value() << " is not of expected type.";
    break;
  }
  case 1:{
    IIRScram_TypeDefinition *my_type = context_set->getElement();
    set_value( _get_value()->_rval_to_decl( my_type ) );
    break;
  }
  default:
    report_ambiguous_error( _get_value(), choice_rvals->convert_set<IIR_TypeDefinition>() );
  }
  delete choice_rvals;
}


IIRScram*
IIRScram_Choice::_clone() {
  return this;
}

visitor_return_type *
IIRScram_Choice::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_Choice(this, arg);
};

IIRScram *
IIRScram_Choice::_get_value() {
  return dynamic_cast<IIRScram *>(IIRBase_Choice::get_value());
}
