
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
 
// Authors: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------

#include "IIR_DesignatorList.hh"
#include "IIR_TextLiteral.hh"
#include "IIRBase_BranchQuantityDeclaration.hh"
#include "savant.hh"


IIRBase_BranchQuantityDeclaration::IIRBase_BranchQuantityDeclaration() {

  set_across_aspect_expression(NULL);
  set_through_aspect_expression(NULL);
  set_plus_terminal_name(NULL);
  set_minus_terminal_name(NULL);
  across_aspect_identifier_list = NULL;
  through_aspect_designator_list = NULL;
}

IIRBase_BranchQuantityDeclaration::~IIRBase_BranchQuantityDeclaration() {
}

IIR_DesignatorList *
IIRBase_BranchQuantityDeclaration::get_across_aspect_identifier_list() {
  ASSERT(across_aspect_identifier_list != NULL);
  return across_aspect_identifier_list;
}

IIR_DesignatorList *
IIRBase_BranchQuantityDeclaration::get_through_aspect_designator_list() {  
  ASSERT(through_aspect_designator_list != NULL);
  return through_aspect_designator_list;
}

void
IIRBase_BranchQuantityDeclaration::set_across_aspect_identifier_list(IIR_DesignatorList *new_across_aspect_identifier_list) {
  ASSERT(new_across_aspect_identifier_list != NULL);
  delete across_aspect_identifier_list;
  across_aspect_identifier_list = new_across_aspect_identifier_list;
}

void
IIRBase_BranchQuantityDeclaration::set_through_aspect_designator_list(IIR_DesignatorList *new_through_aspect_designator_list) {  
  ASSERT(new_through_aspect_designator_list != NULL);  
  delete through_aspect_designator_list;
  through_aspect_designator_list = new_through_aspect_designator_list;
}

void
IIRBase_BranchQuantityDeclaration::set_across_aspect_expression(IIR* across_aspect){
  this->across_aspect_expression = across_aspect;
}

IIR*
IIRBase_BranchQuantityDeclaration::get_across_aspect_expression() {
  return across_aspect_expression;
}

void
IIRBase_BranchQuantityDeclaration::set_through_aspect_expression(IIR* through_aspect){
  this->through_aspect_expression = through_aspect;
}

IIR*
IIRBase_BranchQuantityDeclaration::get_through_aspect_expression() {
  return through_aspect_expression;
}

void
IIRBase_BranchQuantityDeclaration::set_plus_terminal_name(IIR* plus_terminal_name  ) {
  this->plus_terminal_name = plus_terminal_name;
}

IIR*
IIRBase_BranchQuantityDeclaration::get_plus_terminal_name() {
  return plus_terminal_name;
}

void
IIRBase_BranchQuantityDeclaration::set_minus_terminal_name(IIR* minus_terminal_name ) {
  this->minus_terminal_name = minus_terminal_name;
}

IIR*
IIRBase_BranchQuantityDeclaration::get_minus_terminal_name() {
  return minus_terminal_name;
}

void
IIRBase_BranchQuantityDeclaration::set_across_aspect_tolerance(IIR* tol_aspect) {
  this->across_aspect_tolerance = tol_aspect;
} 
 
IIR*
IIRBase_BranchQuantityDeclaration::get_across_aspect_tolerance() {
  return across_aspect_tolerance;
} 

void
IIRBase_BranchQuantityDeclaration::set_through_aspect_tolerance(IIR* tol_aspect) {
  this->through_aspect_tolerance = tol_aspect;
}
  
IIR*
IIRBase_BranchQuantityDeclaration::get_through_aspect_tolerance() {
  return through_aspect_tolerance;
}


IIR *
IIRBase_BranchQuantityDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_BranchQuantityDeclaration *new_node = dynamic_cast<IIRBase_BranchQuantityDeclaration *>(IIRBase_QuantityDeclaration::convert_tree(factory));

  // Process the variables
  new_node->across_aspect_identifier_list = dynamic_cast<IIR_DesignatorList *>(convert_node(across_aspect_identifier_list, factory));
  new_node->through_aspect_designator_list = dynamic_cast<IIR_DesignatorList *>(convert_node(through_aspect_designator_list, factory));
  new_node->across_aspect_expression = convert_node(across_aspect_expression, factory);
  new_node->through_aspect_expression = convert_node(through_aspect_expression, factory);
  new_node->plus_terminal_name = convert_node(plus_terminal_name, factory);
  new_node->minus_terminal_name = convert_node(minus_terminal_name, factory);
  new_node->across_aspect_tolerance = convert_node(across_aspect_tolerance, factory);
  new_node->through_aspect_tolerance = convert_node(through_aspect_tolerance, factory);

  return new_node;
}

IIR_Boolean
IIRBase_BranchQuantityDeclaration::_is_across_quantity() {
  if ( (get_across_aspect_identifier_list()->num_elements() != 0) && 
       (get_through_aspect_designator_list()->num_elements() == 0) ){
    return TRUE;
  }
  else {
    return FALSE;
  }
}

void
IIRBase_BranchQuantityDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << " quantity ";
  if(get_across_aspect_identifier_list()->size() != 0) {
    get_declarator()->publish_vhdl(vhdl_out);
    if ( get_across_aspect_expression() != NULL) {
      vhdl_out << " tolerance ";
      get_across_aspect_tolerance()->publish_vhdl(vhdl_out);
    }
    
    if ( get_across_aspect_expression() != NULL ){
      vhdl_out << " := ";
      get_across_aspect_expression()->publish_vhdl(vhdl_out);
    }
    vhdl_out << "  across ";
  }
   if(get_through_aspect_designator_list()->size() != 0) {
    get_declarator()->publish_vhdl(vhdl_out);
    if ( get_through_aspect_expression() != NULL) {
      vhdl_out << " tolerance ";
      get_through_aspect_tolerance()->publish_vhdl(vhdl_out);
    }
    if( get_through_aspect_expression() != NULL ){
      vhdl_out << " := ";
      get_through_aspect_expression()->publish_vhdl(vhdl_out);
    }
    vhdl_out << "  through  ";
  }
  ASSERT(get_plus_terminal_name() != NULL);
  get_plus_terminal_name()->publish_vhdl(vhdl_out);
  if ( get_minus_terminal_name() != NULL ) {
    vhdl_out << " to " ;
    get_minus_terminal_name()->publish_vhdl(vhdl_out);
  }
  vhdl_out << " ;\n" ;
}
