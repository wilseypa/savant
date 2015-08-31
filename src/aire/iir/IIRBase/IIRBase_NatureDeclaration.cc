
// Copyright (c) 2002 The University of Cincinnati.
// All rights reserved.
 
// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
// NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
 
// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S., and
// the terms of this license.
  
// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2, June
// 1991. A copy of this license agreement can be found in the file "LGPL",
// distributed with this archive.
 
// Authors: Sivakumar Gowrisankar             gowriss@ececs.uc.edu
//          Vinod Chamarty                    chamarv@ececs.uc.edu
//          Vasudevan Shanmugasundaram
//          Kathiresan Nellayappan
 
//---------------------------------------------------------------------------

#include "IIRBase_NatureDeclaration.hh"
#include "IIRBase_NatureDefinition.hh"
#include "IIR_AttributeSpecificationList.hh"
#include "IIR_TerminalDeclaration.hh"
#include "IIR_TextLiteral.hh"
#include "savant.hh"

IIRBase_NatureDeclaration::IIRBase_NatureDeclaration() {}

IIRBase_NatureDeclaration::~IIRBase_NatureDeclaration() {}

void
IIRBase_NatureDeclaration::set_nature(IIR_NatureDefinition *nature){
  this-> nature = nature;
}

IIR_NatureDefinition*
IIRBase_NatureDeclaration::get_nature(){
  ASSERT(nature !=NULL);
  return nature;
}

// List Accessor(s)
IIR_AttributeSpecificationList *
IIRBase_NatureDeclaration::get_attributes() {
  ASSERT(attributes != NULL);
  return attributes;
}


void
IIRBase_NatureDeclaration::set_attributes(IIR_AttributeSpecificationList *new_attributes) {
  ASSERT(new_attributes != NULL);
  delete attributes;
  attributes = new_attributes;
}

IIR *
IIRBase_NatureDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_NatureDeclaration *new_node = dynamic_cast<IIRBase_NatureDeclaration *>(IIRBase_Declaration::convert_tree(factory));

  // Process the variables
  new_node->attributes = dynamic_cast<IIR_AttributeSpecificationList *>(convert_node(attributes, factory));
  new_node->nature = dynamic_cast<IIR_NatureDefinition *>(convert_node(nature, factory));
  new_node->reference_terminal = dynamic_cast<IIR_TerminalDeclaration *>(convert_node(reference_terminal, factory));

  return new_node;
}

IIR_Boolean
IIRBase_NatureDeclaration::is_array_type() {
  if( get_nature() != NULL ){
    return get_nature()->is_array_type();
  }
  else {
    return FALSE;
  }
}

IIR_TypeDefinition *
IIRBase_NatureDeclaration::get_subtype(){
  return dynamic_cast<IIR_TypeDefinition *>(get_nature());
}

IIR_Declaration::declaration_type 
IIRBase_NatureDeclaration::get_declaration_type(){
  return NATURE;
}

IIR_TerminalDeclaration*
IIRBase_NatureDeclaration::get_reference_terminal() {
  return reference_terminal;
}
 
void 
IIRBase_NatureDeclaration::set_reference_terminal(IIR_TerminalDeclaration* ref_term) {
  reference_terminal = ref_term;
}

IIR_TypeDefinition*
IIRBase_NatureDeclaration::get_final_subtype(){
  ASSERT( get_nature() != NULL );

  return get_nature()->get_final_subtype();
}

void
IIRBase_NatureDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  IIR_Kind nature_kind = get_nature()->get_kind();
  
  ASSERT( nature_kind == IIR_SCALAR_NATURE_DEFINITION ||
	  nature_kind == IIR_ARRAY_SUBNATURE_DEFINITION );

  vhdl_out << " nature " ;
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << " is " ;
  if( nature_kind == IIR_ARRAY_SUBNATURE_DEFINITION ){
    dynamic_cast<IIRBase_NatureDefinition *>(get_nature())->publish_vhdl_type_decl(vhdl_out);
  }
  else {
    dynamic_cast<IIRBase_NatureDefinition *>(get_nature())->publish_vhdl_decl(vhdl_out);
  }
  vhdl_out << " ;\n";
}

