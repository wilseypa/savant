
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
//          Malolan Chetlur     mal@ece.uc.edu

//---------------------------------------------------------------------------





#include "savant.hh"
#include "IIRBase_QualifiedExpression.hh"
#include "IIR_TypeDefinition.hh"

IIRBase_QualifiedExpression::IIRBase_QualifiedExpression() {
  set_type_mark(NULL);
  set_expression(NULL);
}

IIRBase_QualifiedExpression::~IIRBase_QualifiedExpression() {
  delete dynamic_cast <IIR *>(get_expression());
}

void 
IIRBase_QualifiedExpression::set_type_mark( IIR_TypeDefinition* type_mark) {
  this->type_mark = type_mark;
  set_subtype(type_mark);
}

IIR_TypeDefinition*
 IIRBase_QualifiedExpression::get_type_mark() {
   return type_mark;
}

void 
IIRBase_QualifiedExpression::set_expression(IIR* expression) {
  this->expression = expression;
}

IIR* 
IIRBase_QualifiedExpression::get_expression() {
  return expression;
}


IIR *
IIRBase_QualifiedExpression::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_QualifiedExpression *new_node = dynamic_cast<IIRBase_QualifiedExpression *>(IIRBase_Expression::convert_tree(factory));

  // Process the variables
  new_node->expression = convert_node(expression, factory);
  new_node->type_mark = dynamic_cast<IIR_TypeDefinition *>(convert_node(type_mark, factory));

  return new_node;
}

IIR_Boolean 
IIRBase_QualifiedExpression::is_resolved(){
  if( get_type_mark()->is_resolved() == FALSE ||  get_expression()->is_resolved() == FALSE ){
    return FALSE;
  }
  else{
    return TRUE;
  }
}

IIR_TypeDefinition*
IIRBase_QualifiedExpression::get_subtype(){
  return get_type_mark();
}

IIR_Boolean 
IIRBase_QualifiedExpression::is_locally_static(){
  ASSERT( get_expression() != NULL );
  ASSERT( get_expression()->is_resolved() == TRUE );
  return get_expression()->is_locally_static();
}

ostream &
IIRBase_QualifiedExpression::print( ostream &os ){
  os << *get_type_mark() << "'";
  if( get_expression()->get_kind() == IIR_AGGREGATE ){
    os << *get_expression();
  }
  else{
    os << "( ";
    os << *get_expression();
    os << " )";
  }

  return os;
}

void 
IIRBase_QualifiedExpression::publish_vhdl(ostream &vhdl_out) {
  ASSERT(get_subtype() != NULL);
  get_type_mark()->publish_vhdl(vhdl_out);
  vhdl_out << "'" ;
  if ( get_expression()->is_aggregate_expression() == FALSE ){ 
  vhdl_out << " ( ";
  }
  get_expression()->publish_vhdl(vhdl_out);
  if ( get_expression()->is_aggregate_expression() == FALSE ){
  vhdl_out << " ) ";
  }
}
