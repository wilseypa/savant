
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
#include "IIRBase_FunctionCall.hh"

#include "IIRBase_AssociationList.hh"
#include "IIR_FunctionDeclaration.hh"
#include "IIR_SubprogramDeclaration.hh"
#include "IIR_TextLiteral.hh"
#include "IIR_TypeDefinition.hh"

IIRBase_FunctionCall::IIRBase_FunctionCall()  :
  parameter_association_list(0),
  implementation(0){}

IIRBase_FunctionCall::~IIRBase_FunctionCall(){
  delete parameter_association_list;
  parameter_association_list = 0;
  // Not implementation
}

void
IIRBase_FunctionCall::set_implementation( IIR_SubprogramDeclaration* implementation ) {
  this->implementation = implementation;
}

IIR_SubprogramDeclaration*
IIRBase_FunctionCall::get_implementation() {
  return implementation;
}

IIR_Boolean
IIRBase_FunctionCall::is_locally_static(){
  IIR_Boolean retval = false;
  if( get_implementation() ){
    retval = get_implementation()->is_implicit_declaration();
  }
  retval = retval && parameter_association_list->is_locally_static();
  return retval;
}

// List Accessor(s)
IIR_AssociationList *
IIRBase_FunctionCall::get_parameter_association_list() {
  ASSERT(parameter_association_list != NULL);
  return parameter_association_list;
}


void
IIRBase_FunctionCall::set_parameter_association_list(IIR_AssociationList *new_parameter_association_list) {
  ASSERT(new_parameter_association_list != NULL);
  delete parameter_association_list;
  parameter_association_list = new_parameter_association_list;
}

IIR *
IIRBase_FunctionCall::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_FunctionCall *new_node = dynamic_cast<IIRBase_FunctionCall *>(IIRBase_Expression::convert_tree(factory));

  // Process the variables
  new_node->parameter_association_list = dynamic_cast<IIR_AssociationList *>(convert_node(parameter_association_list, factory));
  new_node->implementation = dynamic_cast<IIR_SubprogramDeclaration *>(convert_node(implementation, factory));

  return new_node;
}

IIR_TypeDefinition *
IIRBase_FunctionCall::get_subtype(){
  ASSERT( get_implementation() != NULL );
  ASSERT( get_implementation()->get_kind() == IIR_FUNCTION_DECLARATION);
  IIR_FunctionDeclaration* func_decl = dynamic_cast<IIR_FunctionDeclaration*>(get_implementation());
  return func_decl->get_return_type();  
}

ostream &
IIRBase_FunctionCall::print( ostream &os ){
  ASSERT(get_implementation() != NULL);

  os << *(get_implementation()->get_declarator());
  if (get_parameter_association_list()->num_elements() != 0) {
    os << "(";
    os << get_parameter_association_list();
    os << ") ";
  }

  return os;
}


void 
IIRBase_FunctionCall::publish_vhdl(ostream &vhdl_out) {
  ASSERT(get_implementation() != NULL);

  get_implementation()->get_declarator()->publish_vhdl(vhdl_out);
  if(get_parameter_association_list()->size() != 0) {
    vhdl_out << "(";
    dynamic_cast<IIRBase_AssociationList *>(get_parameter_association_list())->publish_vhdl_without_formals(vhdl_out);
    vhdl_out << ") ";
  }
}
