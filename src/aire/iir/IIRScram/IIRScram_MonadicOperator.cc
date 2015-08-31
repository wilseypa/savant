
// Copyright (c) 1996-2003 The University of Cincinnati.  
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
//          Malolan Chetlur     
//          Umesh Kumar V. Rajasekaran
//          Krishnan Subramani  
//          Timothy J. McBrayer 
//---------------------------------------------------------------------------

#include "IIRScram_AbsoluteOperator.hh"
#include "IIRScram_AssociationElementByExpression.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_IdentityOperator.hh"
#include "IIRScram_InterfaceDeclaration.hh"
#include "IIRScram_InterfaceList.hh"
#include "IIRScram_FunctionCall.hh"
#include "IIRScram_MonadicOperator.hh"
#include "IIRScram_NegationOperator.hh"
#include "IIRScram_NotOperator.hh"
#include "IIRScram_SubprogramDeclaration.hh"

#include "error_func.hh"
#include "resolution_func.hh"
#include "set.hh"

#include <sstream>
using std::ostringstream;
using std::cerr;

const string
IIRScram_MonadicOperator::_get_function_name() const {
  string retval;
  switch ( get_kind() ){
  case IIR_IDENTITY_OPERATOR:{
    retval = "\"+\"";
    break;
  }
  case IIR_NEGATION_OPERATOR:{
    retval = "\"-\"";
    break;
  }
  case IIR_ABSOLUTE_OPERATOR:{
    retval = "\"abs\"";
    break;
  }
  case IIR_NOT_OPERATOR:{
    retval = "\"not\"";
    break;
  }
  default:{
    cerr << "Unknown operator type in IIRScram_MonadicOperator::_get_function_name()\n";
    abort();
  }
  }
  return retval;
}

IIRScram_AssociationList *
IIRScram_MonadicOperator::_build_argument_list(){
  IIRScram_AssociationList *retval = new IIRScram_AssociationList;
  //  copy_location( this, retval );
  
  if( _get_operand()->_is_association() == FALSE ){
    IIRScram_AssociationElementByExpression *new_assoc = new IIRScram_AssociationElementByExpression();
    copy_location( this, new_assoc );
    new_assoc->set_actual( get_operand() );
    retval->append( new_assoc );
  }
  else{
    retval->append( dynamic_cast<IIRScram_AssociationElement *>(get_operand() ));
  }

  return retval;
}

IIRScram *
IIRScram_MonadicOperator::_rval_to_decl( IIRScram_TypeDefinition *my_rval ){

  if( _get_operand() != NULL ){
    set_operand( _get_operand()->_rval_to_decl( my_rval ) );
  }

  return IIRScram_Expression::_rval_to_decl( my_rval );
}

IIR_Boolean 
IIRScram_MonadicOperator::_is_readable(){
  if( _get_operand() && _get_operand()->_is_readable() ){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

IIRScram *
IIRScram_MonadicOperator::_clone() {
  IIRScram *cloneop;
  IIRScram_MonadicOperator *clone = 0;

  switch (get_kind()) {
  case IIR_IDENTITY_OPERATOR:
    clone = new IIRScram_IdentityOperator;
    break;
  case IIR_NEGATION_OPERATOR:
    clone = new IIRScram_NegationOperator;
    break;
  case IIR_ABSOLUTE_OPERATOR:
    clone = new IIRScram_AbsoluteOperator;
    break;
  case IIR_NOT_OPERATOR:
    clone = new IIRScram_NotOperator;
    break;
  default:
    ostringstream err;
    err << "ERROR: unexpected node type \"" << get_kind_text() << "\" in "
	<< "IIRScram_MonadicOperator::_clone()";
    report_error( this, err.str() );
    break;
  }

  IIRScram_Expression::_clone(clone);
  clone->IIRBase_MonadicOperator::set_implementation(_get_implementation());
  cloneop = _get_operand()->_clone();
  clone->set_operand(cloneop);

  return clone;
}

void 
IIRScram_MonadicOperator::_type_check_operands(){
  ASSERT( _get_implementation() != NULL );
  ASSERT( _get_implementation()->get_interface_declarations()->size() == 1 );

  IIRScram_TypeDefinition *operand_subtype = 
    dynamic_cast<IIRScram *>(_get_implementation()->get_interface_declarations()->first())->_get_subtype();

  set_operand( _get_operand()->_semantic_transform( operand_subtype ) );
  _get_operand()->_type_check( operand_subtype );
  set_operand( _get_operand()->_rval_to_decl( operand_subtype ) );
}

IIRScram_SubprogramDeclaration *
IIRScram_MonadicOperator::_get_implementation() {
  return dynamic_cast<IIRScram_SubprogramDeclaration *>(IIRBase_MonadicOperator::get_implementation());
}

IIRScram *
IIRScram_MonadicOperator::_get_operand() {
  return dynamic_cast<IIRScram *>(get_operand());
}

void
IIRScram_MonadicOperator::_build_generic_parameter_set(savant::set<IIRScram_Declaration> *to_build) {
  _get_operand()->_build_generic_parameter_set(to_build);
}
