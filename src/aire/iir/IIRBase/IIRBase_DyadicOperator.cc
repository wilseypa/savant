
// Copyright (c) 1996-1999 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com

//---------------------------------------------------------------------------


#include "IIRBase_DyadicOperator.hh"
#include "IIR_SubprogramDeclaration.hh"
#include "savant.hh"

IIRBase_DyadicOperator::IIRBase_DyadicOperator(){
  set_implementation( NULL );
  set_left_operand( NULL );
  set_right_operand( NULL );
}

IIRBase_DyadicOperator::~IIRBase_DyadicOperator(){
}

void 
IIRBase_DyadicOperator::set_implementation( IIR_SubprogramDeclaration *implementation ){
  this->implementation = implementation;
}


IIR_SubprogramDeclaration *
IIRBase_DyadicOperator::get_implementation(){
  return implementation;
}

void 
IIRBase_DyadicOperator::set_left_operand( IIR *left_operand ){
  this->left_operand = left_operand;
}

IIR *
IIRBase_DyadicOperator::get_left_operand(){
  return left_operand;
}

void 
IIRBase_DyadicOperator::set_right_operand( IIR *right_operand ){
  this->right_operand = right_operand;
}

IIR *
IIRBase_DyadicOperator::get_right_operand(){
  return right_operand;
}

IIR *
IIRBase_DyadicOperator::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_DyadicOperator *new_node = dynamic_cast<IIRBase_DyadicOperator *>(IIRBase_Operator::convert_tree(factory));

  // Process the variables
  new_node->implementation = dynamic_cast<IIR_SubprogramDeclaration *>(convert_node(implementation, factory));
  new_node->left_operand = convert_node(left_operand, factory);
  new_node->right_operand = convert_node(right_operand, factory);

  return new_node;
}

IIR_Boolean 
IIRBase_DyadicOperator::is_resolved(){
  if( get_implementation() != NULL && get_implementation()->is_resolved() == FALSE ){
    return FALSE;
  }
  ASSERT( get_left_operand() != NULL );
  ASSERT( get_right_operand() != NULL );

  if( get_left_operand()->is_resolved() == TRUE 
      && get_right_operand()->is_resolved() == TRUE
      && get_subtype() != NULL ){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

IIR_Boolean
IIRBase_DyadicOperator::is_locally_static(){
  ASSERT( is_resolved() == TRUE );
  ASSERT( get_left_operand() );
  ASSERT( get_right_operand() );
  return get_left_operand()->is_locally_static() && get_right_operand()->is_locally_static();
}

IIR_Boolean
IIRBase_DyadicOperator::is_above_attribute_found() {
  IIR_Boolean retval = FALSE;
  ASSERT( get_left_operand() );
  ASSERT( get_right_operand() );
  retval = get_left_operand()->is_above_attribute_found() ||
    get_right_operand()->is_above_attribute_found();
  return retval;
}

bool
IIRBase_DyadicOperator::is_associative( IIR_Kind ){
  return TRUE;
}

ostream &
IIRBase_DyadicOperator::print( ostream &os ){
  if( get_left_operand() ){
    get_left_operand()->print( os );
  }
  os << get_operator_string();
  if( get_right_operand() ){
    get_right_operand()->print( os );
  }
  return os;
}

void
IIRBase_DyadicOperator::publish_vhdl(ostream &vhdl_out){
  bool left_bracket = FALSE;
  bool right_bracket = FALSE ;
  Precedence left_precedence = OTHERS;
  Precedence right_precedence = OTHERS;
  Precedence self_precedence = OTHERS;
  
  left_precedence  = dynamic_cast<IIRBase *>(get_left_operand())->get_precedence();
  right_precedence = dynamic_cast<IIRBase *>(get_right_operand())->get_precedence();
  self_precedence  = get_precedence();

  if (( left_precedence < self_precedence ) ||
      (dynamic_cast<IIRBase *>(get_left_operand())->is_relational_operator() )){
    left_bracket = TRUE ;
  }
  if (( get_left_operand()->get_kind() == get_kind()) &&
      !is_left_associative() ){
    left_bracket = TRUE ;
  }
  if (( left_precedence == self_precedence ) &&
      ( is_logical_operator() ) &&
      ( get_kind() != get_left_operand()->get_kind() )){
    left_bracket = TRUE ;
  }
  if (( right_precedence < self_precedence ) ||
      (get_right_operand()->is_relational_operator())){
    right_bracket = TRUE ;
  } 
  if ((right_precedence == self_precedence) &&
      (is_associative(get_right_operand()->get_kind()) == FALSE)) {
    right_bracket = TRUE;
  }
  if ( left_bracket ){
    vhdl_out << "(";
  }
  get_left_operand()->publish_vhdl(vhdl_out);
  if ( left_bracket ){
    vhdl_out << ")";
  }
  publish_vhdl_operator(vhdl_out);
  if ( right_bracket ){
    vhdl_out << "(";
  }
  get_right_operand()->publish_vhdl(vhdl_out);
  if ( right_bracket ){
    vhdl_out << ")";
  }
}
