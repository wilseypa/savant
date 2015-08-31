
// Copyright (c) 2002-2003 The University of Cincinnati.
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

// Authors: Prashanth Cherukuri cherukps@ececs.uc.edu

//---------------------------------------------------------------------------

#include "savant.hh"
#include "IIRBase_SourceQuantityDeclaration.hh"
#include "IIRBase_TextLiteral.hh"
#include "IIR_TypeDefinition.hh"

IIRBase_SourceQuantityDeclaration::IIRBase_SourceQuantityDeclaration() :
  magnitude_expression(0),
  phase_expression(0),
  noise_expression(0){}

IIRBase_SourceQuantityDeclaration::~IIRBase_SourceQuantityDeclaration(){
  delete magnitude_expression;
  magnitude_expression = 0;
  delete phase_expression;
  phase_expression = 0;
  delete noise_expression;
  noise_expression = 0;
}

void
IIRBase_SourceQuantityDeclaration::set_magnitude_expression(IIR* magnitude_exp){
  this->magnitude_expression = magnitude_exp;
}

IIR*
IIRBase_SourceQuantityDeclaration::get_magnitude_expression() {
  return magnitude_expression;
}

void
IIRBase_SourceQuantityDeclaration::set_phase_expression(IIR* phase) {
  this->phase_expression = phase;
}

IIR*
IIRBase_SourceQuantityDeclaration::get_phase_expression() {
  return phase_expression;
}

void
IIRBase_SourceQuantityDeclaration::set_noise_expression(IIR* noise_exp  ) {
  this->noise_expression = noise_exp;
}

IIR*
IIRBase_SourceQuantityDeclaration::get_noise_expression() {
  return noise_expression;
}

IIR *
IIRBase_SourceQuantityDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_SourceQuantityDeclaration *new_node = dynamic_cast<IIRBase_SourceQuantityDeclaration *>(IIRBase_QuantityDeclaration::convert_tree(factory));

  // Process the variables
  new_node->magnitude_expression = convert_node(magnitude_expression, factory);
  new_node->phase_expression = convert_node(phase_expression, factory);
  new_node->noise_expression = convert_node(noise_expression, factory);

  return new_node;
}

void
IIRBase_SourceQuantityDeclaration::publish_vhdl_decl(ostream& vhdl_out) {
  vhdl_out << " quantity ";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << ":" ;
  get_subtype()->publish_vhdl(vhdl_out);
  
  if( get_phase_expression() != NULL ){
    vhdl_out << " spectrum " ;
    get_magnitude_expression()->publish_vhdl(vhdl_out);
    vhdl_out << " , " ;
    get_phase_expression()->publish_vhdl(vhdl_out);
  }
  else {
    vhdl_out << " noise ";
    get_noise_expression()->publish_vhdl(vhdl_out);
  }
  vhdl_out << " ;\n" ;
}
