
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

#include "IIR_Attribute.hh"
#include "IIR_TypeDefinition.hh"
#include "IIR_TextLiteral.hh"
#include "IIRBase_AttributeDeclaration.hh"
#include "savant.hh"

IIRBase_AttributeDeclaration::IIRBase_AttributeDeclaration(){
  set_attribute( NULL );
}

IIRBase_AttributeDeclaration::~IIRBase_AttributeDeclaration(){}

IIR *
IIRBase_AttributeDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_AttributeDeclaration *new_node = dynamic_cast<IIRBase_AttributeDeclaration *>(IIRBase_Declaration::convert_tree(factory));

  // Process the variables
  new_node->one_attribute = dynamic_cast<IIR_Attribute *>(convert_node(one_attribute, factory));

  return new_node;
}

IIR_Boolean 
IIRBase_AttributeDeclaration::is_signal(){
  if( get_attribute() != NULL ){
    return get_attribute()->is_signal();
  }
  else{
    // It must be user defined, and then it can't be signal valued..
    return FALSE;
  }
}

IIR_Attribute *
IIRBase_AttributeDeclaration::get_attribute(){
  return one_attribute;
}

void
IIRBase_AttributeDeclaration::set_attribute( IIR_Attribute *new_attr ){
  one_attribute = new_attr;
}


IIR_TypeDefinition *
IIRBase_AttributeDeclaration::get_subtype(){
  if( IIRBase::get_subtype() == NULL ){
    ASSERT( get_attribute() != NULL );
    return get_attribute()->get_subtype();
  }
  else{
    return IIRBase::get_subtype();
  }
}

IIR_Declaration::declaration_type 
IIRBase_AttributeDeclaration::get_declaration_type(){
  return ATTRIBUTE;
}

savant::set<IIR_Declaration> *
IIRBase_AttributeDeclaration::find_declarations( IIR_Name *to_find){
  return get_subtype()->find_declarations( to_find );
}

void 
IIRBase_AttributeDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << "attribute ";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << " : ";
  get_subtype()->get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << ";\n";
}

void 
IIRBase_AttributeDeclaration::publish_vhdl(ostream &vhdl_out) {
  get_declarator()->publish_vhdl(vhdl_out);
}
