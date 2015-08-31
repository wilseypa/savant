
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

#include "IIRBase_TypeConversion.hh"
#include "IIR_TypeDefinition.hh"
#include "savant.hh"
#include "IIR_TextLiteral.hh"

IIRBase_TypeConversion::IIRBase_TypeConversion() :
  type_mark(0),
  expression(0){}

IIRBase_TypeConversion::~IIRBase_TypeConversion() {
  delete expression;
  expression = 0;
  // Not type_mark
}

void
IIRBase_TypeConversion::set_type_mark( IIR_TypeDefinition *new_type_mark ) {
  type_mark = new_type_mark;
}

IIR_TypeDefinition*
IIRBase_TypeConversion::get_type_mark() {
  return type_mark;
}

void
IIRBase_TypeConversion::set_expression( IIR *new_expression ){
  expression = new_expression;
}

IIR*
IIRBase_TypeConversion:: get_expression() {
  return expression;
}

IIR *
IIRBase_TypeConversion::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_TypeConversion *new_node = dynamic_cast<IIRBase_TypeConversion *>(IIRBase_Expression::convert_tree(factory));

  // Process the variables
  new_node->type_mark = dynamic_cast<IIR_TypeDefinition *>(convert_node(type_mark, factory));
  new_node->expression = convert_node(expression, factory);

  return new_node;
}

IIR_Boolean
IIRBase_TypeConversion::is_resolved(){
  IIR_Boolean retval = TRUE;
  if( get_type_mark()->is_resolved() == FALSE || get_expression()->is_resolved() == FALSE ){
    retval = FALSE;
  }

  return retval;
}

IIR_TypeDefinition *
IIRBase_TypeConversion::get_subtype(){
  return get_type_mark();
}

IIR_Boolean 
IIRBase_TypeConversion::is_locally_static(){
  ASSERT( get_expression() != NULL );
  ASSERT( get_expression()->is_resolved() == TRUE );
  return get_expression()->is_locally_static();
}

ostream & 
IIRBase_TypeConversion::print( ostream &os ) {
  os << *get_type_mark();
  os << " ( ";
  os << *get_expression();
  os << " ) ";
  
  return os;
}

void 
IIRBase_TypeConversion::publish_vhdl(ostream &vhdl_out) {
  get_type_mark()->get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << "(";
  get_expression()->publish_vhdl(vhdl_out);
  vhdl_out << ")";
}
