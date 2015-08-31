
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
#include "IIRBase_OthersInitialization.hh"
#include "IIR_TypeDefinition.hh"

IIRBase_OthersInitialization::IIRBase_OthersInitialization() :
  expression(0){}

IIRBase_OthersInitialization::~IIRBase_OthersInitialization() {
  delete expression;
  expression = 0;
}

void
IIRBase_OthersInitialization::set_expression( IIR* expression) {
  this->expression = expression;
}

IIR*
IIRBase_OthersInitialization::get_expression() {
  return expression;
}



IIR *
IIRBase_OthersInitialization::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_OthersInitialization *new_node = dynamic_cast<IIRBase_OthersInitialization *>(IIRBase_Expression::convert_tree(factory));

  // Process the variables
  new_node->expression = convert_node(expression, factory);

  return new_node;
}

IIR_Boolean
IIRBase_OthersInitialization::is_resolved(){
  ASSERT( get_expression() != NULL );

  return get_expression()->is_resolved();
}

ostream & 
IIRBase_OthersInitialization::print( ostream &os ) {
  os << " others => ";
  ASSERT(get_expression() != NULL);
  os << *get_expression();
  
  return os;
}

void 
IIRBase_OthersInitialization::publish_vhdl(ostream &vhdl_out) {
  ASSERT(get_subtype() != NULL);
  if (get_subtype()->is_record_type() == TRUE) {
    vhdl_out << " (";
  }
  vhdl_out << "others => ";

  ASSERT(get_expression() != NULL);
  ASSERT(get_expression()->is_resolved() == TRUE);
  get_expression()->publish_vhdl(vhdl_out);
  if (get_subtype()->is_record_type() == TRUE) {
    vhdl_out << ")";
  }
}
