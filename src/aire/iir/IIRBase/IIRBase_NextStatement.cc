
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
#include "IIRBase_NextStatement.hh"
#include "IIR_Label.hh"

IIRBase_NextStatement::IIRBase_NextStatement() :
  condition(0),
  loop(0){}

IIRBase_NextStatement::~IIRBase_NextStatement() {
  delete condition;
  condition = 0;
  // Not loop
}


void
IIRBase_NextStatement::set_enclosing_loop( IIR_SequentialStatement* loop) {
  this->loop = loop;
}

IIR_SequentialStatement*
IIRBase_NextStatement::get_enclosing_loop() {
  return loop;
}

void
IIRBase_NextStatement::set_condition( IIR* condition) {
  this->condition = condition;
}

IIR*
IIRBase_NextStatement::get_condition() {
  return condition;
}

IIR_Boolean
IIRBase_NextStatement::is_above_attribute_found() {
  IIR_Boolean retval = FALSE;
  if(get_condition() != NULL ) {
    retval = retval || get_condition()->is_above_attribute_found();
  }
  return retval;
}

IIR *
IIRBase_NextStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_NextStatement *new_node = dynamic_cast<IIRBase_NextStatement *>(IIRBase_SequentialStatement::convert_tree(factory));

  // Process the variables
  new_node->condition = convert_node(condition, factory);
  new_node->loop = dynamic_cast<IIR_SequentialStatement *>(convert_node(loop, factory));

  return new_node;
}

void
IIRBase_NextStatement::publish_vhdl(ostream &vhdl_out) {
  publish_vhdl_stmt_label(vhdl_out);
    
  vhdl_out << "next ";
    
  if (get_enclosing_loop() != NULL) {
    if ( get_enclosing_loop()->get_label() != NULL ){
      get_enclosing_loop()->get_label()->publish_vhdl(vhdl_out);
    }
  }
    
  if (get_condition() != NULL) {
    vhdl_out << "\nwhen ";
    get_condition()->publish_vhdl(vhdl_out);
  }
}
