
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
#include "IIRBase_DisconnectSpecification.hh"
#include "IIR_DesignatorList.hh"
#include "IIR_TypeDefinition.hh"

IIRBase_DisconnectSpecification::IIRBase_DisconnectSpecification() :
  guarded_signal_list(0) {
  my_type_mark = NULL;
  my_time_expression = NULL;
}

IIRBase_DisconnectSpecification::~IIRBase_DisconnectSpecification(){
}

void 
IIRBase_DisconnectSpecification::set_type_mark( IIR_TypeDefinition *type_mark ){
  my_type_mark = type_mark;
}

IIR_TypeDefinition *
IIRBase_DisconnectSpecification::get_type_mark(){
  return my_type_mark;
}

void 
IIRBase_DisconnectSpecification::set_time_expression( IIR *time_expression ){
  my_time_expression = time_expression;
}

IIR *
IIRBase_DisconnectSpecification::get_time_expression(){
  return my_time_expression;
}

// List Accessor(s)
IIR_DesignatorList *
IIRBase_DisconnectSpecification::get_guarded_signal_list() {
  ASSERT(guarded_signal_list != NULL);
  return guarded_signal_list;
}


void
IIRBase_DisconnectSpecification::set_guarded_signal_list(IIR_DesignatorList *new_guarded_signal_list) {
  ASSERT(new_guarded_signal_list != NULL);
  delete guarded_signal_list;
  guarded_signal_list = new_guarded_signal_list;
}

IIR *
IIRBase_DisconnectSpecification::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_DisconnectSpecification *new_node = dynamic_cast<IIRBase_DisconnectSpecification *>(IIRBase_Declaration::convert_tree(factory));

  // Process the variables
  new_node->guarded_signal_list = dynamic_cast<IIR_DesignatorList *>(convert_node(guarded_signal_list, factory));
  new_node->my_type_mark = dynamic_cast<IIR_TypeDefinition *>(convert_node(my_type_mark, factory));
  new_node->my_time_expression = convert_node(my_time_expression, factory);

  return new_node;
}

void 
IIRBase_DisconnectSpecification::publish_vhdl_decl(ostream &vhdl_out) {
  publish_vhdl( vhdl_out );
}

void 
IIRBase_DisconnectSpecification::publish_vhdl(ostream &vhdl_out) {
  ASSERT( get_guarded_signal_list()->is_resolved() == TRUE );
  ASSERT( get_type_mark()->is_resolved() == TRUE );
  ASSERT( get_time_expression()->is_resolved() == TRUE );

  vhdl_out << " disconnect ";
  get_guarded_signal_list()->publish_vhdl(vhdl_out);
  vhdl_out << " : ";
  get_type_mark()->publish_vhdl(vhdl_out);
  vhdl_out << " after ";
  get_time_expression()->publish_vhdl(vhdl_out);
  vhdl_out << ";\n";
}
