
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



#include "IIRBase_AccessSubtypeDefinition.hh"
#include "savant.hh"
#include "IIR_FunctionDeclaration.hh"
#include <iostream>

using std::cerr;

IIRBase_AccessSubtypeDefinition::IIRBase_AccessSubtypeDefinition(){
  my_resolution_function = NULL;
}

IIRBase_AccessSubtypeDefinition::~IIRBase_AccessSubtypeDefinition(){
}

void 
IIRBase_AccessSubtypeDefinition::set_designated_subtype( IIR_TypeDefinition *designated_type){
  IIRBase_AccessTypeDefinition::set_designated_type( designated_type );
}


IIR_TypeDefinition *
IIRBase_AccessSubtypeDefinition::get_designated_subtype(){
  return IIRBase_AccessTypeDefinition::get_designated_type();
}


void 
IIRBase_AccessSubtypeDefinition::set_resolution_function( IIR_FunctionDeclaration *resolution_function ){
  my_resolution_function = resolution_function;
}

IIR_FunctionDeclaration *
IIRBase_AccessSubtypeDefinition::get_resolution_function(){
  return my_resolution_function;
}

IIR *
IIRBase_AccessSubtypeDefinition::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_AccessSubtypeDefinition *new_node = dynamic_cast<IIRBase_AccessSubtypeDefinition *>(IIRBase_AccessTypeDefinition::convert_tree(factory));

  // Process the variables
  new_node->my_resolution_function = dynamic_cast<IIR_FunctionDeclaration *>(convert_node(my_resolution_function, factory));

  return new_node;
}

IIR_Boolean
IIRBase_AccessSubtypeDefinition::is_subtype() {
  return TRUE;
}

void 
IIRBase_AccessSubtypeDefinition::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << "access ";
  get_designated_subtype()->publish_vhdl(vhdl_out);
}
