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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRBase_AliasDeclaration.hh"
#include "savant.hh"
#include "IIR_TypeDefinition.hh"
#include "IIR_TextLiteral.hh"

IIRBase_AliasDeclaration::IIRBase_AliasDeclaration() :
  name(0){}

IIRBase_AliasDeclaration::~IIRBase_AliasDeclaration(){
  delete name;
}

void 
IIRBase_AliasDeclaration::set_name( IIR *n) {
  name = n;
}

IIR*
IIRBase_AliasDeclaration::get_name() {
  return name;
}

IIR *
IIRBase_AliasDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_AliasDeclaration *new_node = dynamic_cast<IIRBase_AliasDeclaration *>(IIRBase_Declaration::convert_tree(factory));

  // Process the variables
  new_node->name = convert_node(name, factory);
  
  return new_node;
}

IIR_Boolean 
IIRBase_AliasDeclaration::is_signal(){
  ASSERT( get_name()->is_resolved() == TRUE );
  return get_name()->is_signal();
}

IIR_Boolean
IIRBase_AliasDeclaration::is_access_type(){
  ASSERT ( get_name()->is_resolved() == TRUE );
  return get_name()->is_access_type();
}

IIR_Boolean
IIRBase_AliasDeclaration::is_array_type(){
  ASSERT ( get_name()->is_resolved() == TRUE );
  return get_name()->is_array_type();
}

IIR_Boolean
IIRBase_AliasDeclaration::is_enumeration_type(){
  ASSERT ( get_name()->is_resolved() == TRUE );
  return get_name()->is_enumeration_type();
}

IIR_Boolean
IIRBase_AliasDeclaration::is_file_type(){
  ASSERT ( get_name()->is_resolved() == TRUE );
  return get_name()->is_file_type();
}

IIR_Boolean
IIRBase_AliasDeclaration::is_record_type(){
  ASSERT ( get_name()->is_resolved() == TRUE );
  return get_name()->is_record_type();
}

IIR_Boolean
IIRBase_AliasDeclaration::is_scalar_type(){
  ASSERT ( get_name()->is_resolved() == TRUE );
  return get_name()->is_scalar_type();
}

IIR_Boolean 
IIRBase_AliasDeclaration::is_locally_static(){
  ASSERT ( get_name()->is_resolved() == TRUE );
  return get_name()->is_locally_static();
}

IIR_Boolean 
IIRBase_AliasDeclaration::is_object(){
  ASSERT( get_name()->is_resolved() == TRUE );
  return get_name()->is_object();
}

IIR_Declaration::declaration_type 
IIRBase_AliasDeclaration::get_declaration_type(){
  return ALIAS;
}

IIR_Boolean
IIRBase_AliasDeclaration::is_type(){
  ASSERT ( get_name()->is_resolved() == TRUE );
  return get_name()->is_type();
}

IIR_Boolean 
IIRBase_AliasDeclaration::is_variable(){
  ASSERT( get_name()->is_resolved() == TRUE );
  return get_name()->is_variable();
}

void 
IIRBase_AliasDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << "alias ";
  get_declarator()->publish_vhdl(vhdl_out);
  if ( get_subtype() != NULL ){
    vhdl_out << " : ";
    get_subtype()->publish_vhdl(vhdl_out);
  }
  vhdl_out << " is ";
  get_name()->publish_vhdl(vhdl_out);
  vhdl_out << ";\n";
}
