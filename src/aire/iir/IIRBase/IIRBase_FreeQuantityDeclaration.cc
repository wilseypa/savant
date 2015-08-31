
// Copyright (c) 2002 The University of Cincinnati.
// All rights reserved.
 
// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
// DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.
 
// Author: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------

#include "IIRBase_FreeQuantityDeclaration.hh"
#include "IIR_TextLiteral.hh"
#include "IIRBase_TypeDefinition.hh"
#include "savant.hh"

IIRBase_FreeQuantityDeclaration::IIRBase_FreeQuantityDeclaration() :
  value(0){}

IIRBase_FreeQuantityDeclaration::~IIRBase_FreeQuantityDeclaration() {}

void
IIRBase_FreeQuantityDeclaration::set_value(IIR* value) {
  this->value = value;
}

IIR*
IIRBase_FreeQuantityDeclaration::get_value() {
  return value;
}

IIR *
IIRBase_FreeQuantityDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_FreeQuantityDeclaration *new_node = dynamic_cast<IIRBase_FreeQuantityDeclaration *>(IIRBase_QuantityDeclaration::convert_tree(factory));

  // Process the variables
  new_node->value = convert_node(value, factory);

  return new_node;
}

void
IIRBase_FreeQuantityDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << " quantity " ;
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << " : " ;
  dynamic_cast<IIRBase_TypeDefinition *>(IIRBase_ObjectDeclaration::get_subtype())->publish_vhdl(vhdl_out);
  if(IIRBase_FreeQuantityDeclaration::get_value() != NULL) {
    vhdl_out << " := ";
    dynamic_cast<IIRBase *>(IIRBase_FreeQuantityDeclaration::get_value())->publish_vhdl(vhdl_out);
  }
  vhdl_out << " ;\n";

}
