
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

#include "IIRBase_DesignatorExplicit.hh"
#include "IIR_Signature.hh"
#include "savant.hh"

IIRBase_DesignatorExplicit::IIRBase_DesignatorExplicit() {
  set_name( NULL );
  set_signature( NULL );
}

IIRBase_DesignatorExplicit::~IIRBase_DesignatorExplicit(){
}

void 
IIRBase_DesignatorExplicit::set_name( IIR *name ){
  this->name = name;
}

IIR *
IIRBase_DesignatorExplicit::get_name(){
  return name;
}

void 
IIRBase_DesignatorExplicit::set_signature( IIR_Signature *signature ){
  this->signature = signature;
}

IIR_Signature *
IIRBase_DesignatorExplicit::get_signature(){
  return signature;
}

IIR *
IIRBase_DesignatorExplicit::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_DesignatorExplicit *new_node = dynamic_cast<IIRBase_DesignatorExplicit *>(IIRBase_Designator::convert_tree(factory));

  // Process the variables
  new_node->name = convert_node(name, factory);
  new_node->signature = dynamic_cast<IIR_Signature *>(convert_node(signature, factory));

  return new_node;
}

IIR_Boolean 
IIRBase_DesignatorExplicit::is_resolved(){
  ASSERT( get_name() != NULL );
  return get_name()->is_resolved();
}

IIR_Boolean 
IIRBase_DesignatorExplicit::is_signal(){
  ASSERT( get_name() != NULL );
  return get_name()->is_signal();
}

IIR_Boolean 
IIRBase_DesignatorExplicit::is_locally_static(){
  ASSERT( get_name() != NULL );
  return get_name()->is_locally_static();
}

IIR_Boolean
IIRBase_DesignatorExplicit::is_above_attribute_found() {
  return get_name()->is_above_attribute_found();
}

IIR_SignalKind 
IIRBase_DesignatorExplicit::get_signal_kind(){
  ASSERT( get_name() != NULL );
  return get_name()->get_signal_kind();
}

ostream &
IIRBase_DesignatorExplicit::print( ostream &os ){
  ASSERT( get_name() != NULL );
  return get_name()->print( os );
}

void 
IIRBase_DesignatorExplicit::publish_vhdl(ostream &vhdl_out) {
  ASSERT(get_name()->is_resolved() == TRUE);
  get_name()->publish_vhdl(vhdl_out);
}
