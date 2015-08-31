
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
//          Krishnan Subramani 
//          Timothy J. McBrayer
//	    Magnus Danielson	cfmd@swipnet.se	

//---------------------------------------------------------------------------

#include "IIRScram_AssociationElementByExpression.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_ContributionAttribute.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_DyadicOperator.hh"
#include "IIRScram_FunctionCall.hh"
#include "IIRScram_InterfaceDeclaration.hh"
#include "IIRScram_InterfaceList.hh"
#include "IIRScram_ReferenceAttribute.hh"
#include "IIRScram_SubprogramDeclaration.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_TerminalDeclaration.hh"


using std::cerr;

IIRScram_DyadicOperator::~IIRScram_DyadicOperator() {}

const string
IIRScram_DyadicOperator::_get_function_name() const {
  string retval;

  switch( get_kind() ){
  case IIR_AND_OPERATOR:{
    retval = "\"and\"";
    break;
  }
  case IIR_OR_OPERATOR:{
    retval = "\"or\"";
    break;
  }
  case IIR_NAND_OPERATOR:{
    retval = "\"nand\"";
    break;
  }
  case IIR_NOR_OPERATOR:{
    retval = "\"nor\"";
    break;
  }
  case IIR_XOR_OPERATOR:{
    retval = "\"xor\"";
    break;
  }
  case IIR_XNOR_OPERATOR:{
    retval = "\"xnor\"";
    break;
  }
  case IIR_EQUALITY_OPERATOR:{
    retval = "\"=\"";
    break;
  }
  case IIR_INEQUALITY_OPERATOR:{
    retval = "\"/=\"";
    break;
  }
  case IIR_LESS_THAN_OPERATOR:{
    retval = "\"<\"";
    break;
  }
  case IIR_LESS_THAN_OR_EQUAL_OPERATOR:{
    retval = "\"<=\"";
    break;
  }
  case IIR_GREATER_THAN_OPERATOR:{
    retval = "\">\"";
    break;
  }
  case IIR_GREATER_THAN_OR_EQUAL_OPERATOR:{
    retval = "\">=\"";
    break;
  }
  case IIR_SLL_OPERATOR:{
    retval = "\"sll\"";
    break;
  }
  case IIR_SLA_OPERATOR:{
    retval = "\"sla\"";
    break;
  }
  case IIR_SRL_OPERATOR:{
    retval = "\"srl\"";
    break;
  }
  case IIR_SRA_OPERATOR:{
    retval = "\"sra\"";
    break;
  }
  case IIR_ROL_OPERATOR:{
    retval = "\"rol\"";
    break;
  }
  case IIR_ROR_OPERATOR:{
    retval = "\"ror\"";
    break;
  }
  case IIR_ADDITION_OPERATOR:{
    retval = "\"+\"";
    break;
  }
  case IIR_SUBTRACTION_OPERATOR:{
    retval = "\"-\"";
    break;
  }
  case IIR_CONCATENATION_OPERATOR:{
    retval = "\"&\"";
    break;
  }
  case IIR_MULTIPLICATION_OPERATOR:{
    retval = "\"*\"";
    break;
  }
  case IIR_DIVISION_OPERATOR:{
    retval = "\"/\"";
    break;
  }
  case IIR_MODULUS_OPERATOR:{
    retval = "\"mod\"";
    break;
  }  
  case IIR_REMAINDER_OPERATOR:{
    retval = "\"rem\"";
    break;
  }  
  case IIR_EXPONENTIATION_OPERATOR:{
    retval = "\"**\"";
    break;
  }  
  default:{
    cerr << "Unknown operator type in IIRScram_DyadicOperator::_get_function_name()";
    abort();
  }
  }
  return retval;
}

IIRScram_AssociationList *
IIRScram_DyadicOperator::_build_argument_list(){
  IIRScram_AssociationList *retval = new IIRScram_AssociationList;
  //  copy_location( this, retval );
  
  IIRScram_AssociationElementByExpression *new_assoc = new IIRScram_AssociationElementByExpression();
  copy_location( _get_left_operand(), new_assoc );
  new_assoc->set_actual( _get_left_operand() );
  retval->append( new_assoc );

  new_assoc = new IIRScram_AssociationElementByExpression();
  copy_location( _get_right_operand(), new_assoc );
  new_assoc->set_actual( _get_right_operand() );
  retval->append( new_assoc );

  return retval;
}

IIR_Boolean
IIRScram_DyadicOperator::_is_readable(){
  if( _get_left_operand() && _get_left_operand()->_is_readable() == TRUE &&
      _get_right_operand() && _get_right_operand()->_is_readable() == TRUE ){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

void
IIRScram_DyadicOperator::_clone( IIRScram *copy_into ){
  ASSERT( dynamic_cast<IIRScram_DyadicOperator *>(copy_into) );
  
  IIRScram_DyadicOperator *as_dyadic = dynamic_cast<IIRScram_DyadicOperator *>(copy_into);

  IIRScram *cloneop;

  // Copy the base info
  IIRScram_Expression::_clone( copy_into );

  // Implementation
  as_dyadic->IIRBase_DyadicOperator::set_implementation( _get_implementation() );
  
  // Left
  cloneop = _get_left_operand()->_clone();
  as_dyadic->set_left_operand( cloneop );

  // Right
  cloneop = _get_right_operand()->_clone();
  as_dyadic->set_right_operand( cloneop );
}

void 
IIRScram_DyadicOperator::_type_check_operands(){
  ASSERT( _get_implementation() != NULL );
  ASSERT( _get_implementation()->_get_interface_declarations()->size() == 2 );

  IIRScram_InterfaceDeclaration *first_argument_decl = 
    dynamic_cast<IIRScram_InterfaceDeclaration *>(_get_implementation()->get_interface_declarations()->first());
  IIRScram_InterfaceDeclaration *second_argument_decl = 
    dynamic_cast<IIRScram_InterfaceDeclaration *>(_get_implementation()->get_interface_declarations()->successor( first_argument_decl ));
  
  IIRScram_TypeDefinition *left_type = first_argument_decl->_get_subtype();
  IIRScram_TypeDefinition *right_type = second_argument_decl->_get_subtype();

  set_left_operand( _get_left_operand()->_semantic_transform( left_type ) );
  _get_left_operand()->_type_check( left_type );
  set_left_operand( _get_left_operand()->_rval_to_decl( left_type ) );

  set_right_operand( _get_right_operand()->_semantic_transform( right_type ) );
  _get_right_operand()->_type_check( right_type );
  set_right_operand( _get_right_operand()->_rval_to_decl( right_type ) );

}

IIRScram *
IIRScram_DyadicOperator::_rval_to_decl( IIRScram_TypeDefinition *my_rval ){
  if( _get_implementation() == NULL ){
    set_left_operand( _get_left_operand()->_semantic_transform( my_rval ) );
    _get_left_operand()->_type_check( my_rval );
    set_left_operand( _get_left_operand()->_rval_to_decl( my_rval ) );
    
    set_right_operand( _get_right_operand()->_semantic_transform( my_rval ) );
    _get_right_operand()->_type_check( my_rval );
    set_right_operand( _get_right_operand()->_rval_to_decl( my_rval ) );
  }
  set_subtype( my_rval );
  ASSERT( is_resolved() == TRUE );
  return this;
}

void
IIRScram_DyadicOperator::_build_reference_quantity_list(dl_list<IIRScram_ReferenceAttribute>
                                                           *reference_quantity_list) {
  _get_left_operand()->_build_reference_quantity_list(reference_quantity_list);
  _get_right_operand()->_build_reference_quantity_list(reference_quantity_list);
}

IIRScram *
IIRScram_DyadicOperator::_get_left_operand() {
  return dynamic_cast<IIRScram *>(get_left_operand());
}

IIRScram *
IIRScram_DyadicOperator::_get_right_operand() {
  return dynamic_cast<IIRScram *>(get_right_operand());
}

IIRScram_SubprogramDeclaration *
IIRScram_DyadicOperator::_get_implementation() {
  return dynamic_cast<IIRScram_SubprogramDeclaration *>(IIRBase_DyadicOperator::get_implementation());
}
