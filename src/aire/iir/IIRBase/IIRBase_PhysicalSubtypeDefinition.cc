
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

#include "IIRBase_PhysicalSubtypeDefinition.hh"
#include "IIR_FunctionDeclaration.hh"
#include "IIR_PhysicalSubtypeDefinition.hh"
#include "savant.hh"
#include <cstdlib>//for abort
#include "error_func.hh"

IIRBase_PhysicalSubtypeDefinition::IIRBase_PhysicalSubtypeDefinition() :
  my_resolution_function(0){}

IIRBase_PhysicalSubtypeDefinition::~IIRBase_PhysicalSubtypeDefinition() {}

void 
IIRBase_PhysicalSubtypeDefinition::set_resolution_function( IIR_FunctionDeclaration *resolution_function ){
  my_resolution_function = resolution_function;
}


IIR_FunctionDeclaration *
IIRBase_PhysicalSubtypeDefinition::get_resolution_function(){
  return my_resolution_function;
}

IIR *
IIRBase_PhysicalSubtypeDefinition::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_PhysicalSubtypeDefinition *new_node = dynamic_cast<IIRBase_PhysicalSubtypeDefinition *>(IIRBase_PhysicalTypeDefinition::convert_tree(factory));

  // Process the variables
  new_node->my_resolution_function = dynamic_cast<IIR_FunctionDeclaration *>(convert_node(my_resolution_function, factory));

  return new_node;
}

IIR_Boolean
IIRBase_PhysicalSubtypeDefinition::is_subtype(){
  return TRUE;
}

void 
IIRBase_PhysicalSubtypeDefinition::publish_vhdl_decl(ostream &vhdl_out){
  // We have to do this because IIRBase_PhysicalTypeDefinition (our parent)
  // has overloaded this method, but we want one lower than that.
  IIRBase_ScalarTypeDefinition::publish_vhdl_decl( vhdl_out );
}
