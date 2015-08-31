
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

#include "IIRBase_ReturnStatement.hh"
#include "IIR_SubprogramDeclaration.hh"
#include "savant.hh"

IIRBase_ReturnStatement::IIRBase_ReturnStatement() {
  set_enclosing_subprogram(NULL);
  set_return_expression(NULL); 
}

IIRBase_ReturnStatement::~IIRBase_ReturnStatement() {
  delete get_return_expression();
}

void
IIRBase_ReturnStatement::set_enclosing_subprogram( IIR_SubprogramDeclaration*
						   enclosing_subprogram) {
  this->enclosing_subprogram = enclosing_subprogram;
}

IIR_SubprogramDeclaration*
IIRBase_ReturnStatement::get_enclosing_subprogram() {
  return enclosing_subprogram;
}

void IIRBase_ReturnStatement::set_return_expression( IIR* return_expression) {
  this->return_expression =  return_expression;
}

IIR*
IIRBase_ReturnStatement::get_return_expression() {
  return  return_expression;
}

IIR *
IIRBase_ReturnStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ReturnStatement *new_node = dynamic_cast<IIRBase_ReturnStatement *>(IIRBase_SequentialStatement::convert_tree(factory));

  // Process the variables
  new_node->enclosing_subprogram = dynamic_cast<IIR_SubprogramDeclaration *>(convert_node(enclosing_subprogram, factory));
  new_node->return_expression = convert_node(return_expression, factory);
    
  return new_node;
}

IIR_Boolean 
IIRBase_ReturnStatement::is_resolved(){
  ASSERT( get_enclosing_subprogram() != NULL );

  if( get_return_expression() != NULL ){
    return get_return_expression()->is_resolved();
  }
  else {
    return TRUE;
  }
}

void 
IIRBase_ReturnStatement::publish_vhdl(ostream &vhdl_out) {

  publish_vhdl_stmt_label(vhdl_out);

  vhdl_out << "return ";
    
  if (get_return_expression() != NULL) {
    ASSERT(get_return_expression()->is_resolved());
    get_return_expression()->publish_vhdl(vhdl_out);
  }
}
