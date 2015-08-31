
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

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer
//          Malolan Chetlur    
//          Narayanan Thondugulam
//          Umesh Kumar V. Rajasekaran
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_CaseStatementAlternativeByExpression.hh"
#include "IIRScram_Choice.hh"

savant::set<IIRScram_TypeDefinition> *
IIRScram_CaseStatementAlternativeByExpression::_get_rval_set( constraint_functor *functor ){
  ASSERT( _get_choice() != NULL );
  return _get_choice()->_get_rval_set(functor);
}


IIRScram *
IIRScram_CaseStatementAlternativeByExpression::_rval_to_decl( IIRScram_TypeDefinition *my_typedef){
  ASSERT( _get_choice() != NULL );
  set_choice( dynamic_cast<IIRScram_Choice *>(_get_choice()->_rval_to_decl( my_typedef )) );
  return this;
}


savant::set<IIRScram_Declaration> *
IIRScram_CaseStatementAlternativeByExpression::_symbol_lookup(){
  return _get_choice()->_symbol_lookup();
}

void 
IIRScram_CaseStatementAlternativeByExpression::_type_check( savant::set<IIRScram_TypeDefinition> *context_set ){
  _get_choice()->_type_check( context_set );
}

IIRScram*
IIRScram_CaseStatementAlternativeByExpression::_clone() {
  IIRScram_Choice *choiceclone;
  IIRScram_CaseStatementAlternativeByExpression *clone;
  clone = new IIRScram_CaseStatementAlternativeByExpression;
  IIRScram_CaseStatementAlternative::_clone(clone);

  choiceclone = dynamic_cast<IIRScram_Choice*>(_get_choice()->_clone());
  clone->set_choice(choiceclone);

  return clone;
}

visitor_return_type *
IIRScram_CaseStatementAlternativeByExpression::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_CaseStatementAlternativeByExpression(this, arg);
};

IIRScram_Choice*
IIRScram_CaseStatementAlternativeByExpression::_get_choice() {
  return dynamic_cast<IIRScram_Choice *>(get_choice());
}
