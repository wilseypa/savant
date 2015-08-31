
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


#include "IIRBase_UserAttribute.hh"
#include "IIR_Declaration.hh"
#include "IIR_ConstantDeclaration.hh"
#include "IIR_TextLiteral.hh"

#include "savant.hh"

IIRBase_UserAttribute::IIRBase_UserAttribute() {
  set_suffix( NULL );
}

IIRBase_UserAttribute::~IIRBase_UserAttribute() {}

void
IIRBase_UserAttribute::set_suffix( IIR *new_suffix ){
  suffix = new_suffix;
}

IIR*
IIRBase_UserAttribute::get_suffix() {

  return suffix;
}

IIR *
IIRBase_UserAttribute::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_UserAttribute *new_node = dynamic_cast<IIRBase_UserAttribute *>(IIRBase_Attribute::convert_tree(factory));

  // Process the variables
  new_node->suffix = convert_node(suffix, factory);

  return new_node;
}

IIR_Boolean 
IIRBase_UserAttribute::is_locally_static(){
  // Need to fix this 
  IIR_Declaration *implicit_decl = NULL;
  //  IIR_Declaration *implicit_decl = IIR_Attribute::get_implicit_declaration();

  ASSERT( implicit_decl != NULL );
  ASSERT( implicit_decl->get_kind() == IIR_CONSTANT_DECLARATION );
  IIR_ConstantDeclaration *as_constant = dynamic_cast<IIR_ConstantDeclaration *>(implicit_decl);
  ASSERT( as_constant->get_value() != NULL );

  return as_constant->get_value()->is_locally_static();
}

IIR_TextLiteral *
IIRBase_UserAttribute::build_attribute_name(){
  IIR_TextLiteral *retval = 0;

  if( get_suffix() && get_suffix()->is_name() == TRUE ){
    retval = dynamic_cast<IIR_TextLiteral *>(dynamic_cast<IIR_Name *>(get_suffix())->get_prefix_string());
  }
  else if ( get_suffix() && dynamic_cast<IIR_Declaration *>(get_suffix()) != NULL ){
    retval = get_suffix()->get_declarator();
  }
  
  return retval;
}

void 
IIRBase_UserAttribute::publish_vhdl(ostream &vhdl_out) {
  ASSERT(get_prefix() != NULL);
  ASSERT(get_prefix()->is_resolved() == TRUE);
  ASSERT(get_suffix() != NULL);
  ASSERT(get_suffix()->is_resolved() == TRUE);

  get_prefix()->publish_vhdl(vhdl_out);
  vhdl_out << "'";
  get_suffix()->publish_vhdl(vhdl_out);
}
