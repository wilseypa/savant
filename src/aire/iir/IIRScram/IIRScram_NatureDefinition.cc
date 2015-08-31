
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
 
// Authors: Sivakumar Gowrisankar             gowriss@ececs.uc.edu
//          Vinod Chamarty                    chamarv@ececs.uc.edu
//          Vasudevan Shanmugasundaram

#include "savant.hh"
#include "IIRScram_Declaration.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_NatureDefinition.hh"

IIRScram_TerminalDeclaration *
IIRScram_NatureDefinition::get_reference_terminal() {
  _report_undefined_scram_fn("get_reference_terminal()");
  return  NULL;
}

// got this here temporarily to avoid compilation errors.
void
IIRScram_NatureDefinition::_set_resolution_function( IIRScram_FunctionDeclaration *new_function) {
  _report_undefined_scram_fn("_set_resolution_function()");
}

IIRScram_Declaration *
IIRScram_NatureDefinition::_get_declaration() {
  return dynamic_cast<IIRScram_Declaration *>(get_declaration());
}

IIRScram_TypeDefinition *
IIRScram_NatureDefinition::_get_element_subtype(){
  _report_undefined_scram_fn("_get_element_subtype()");
  return NULL;
}

IIRScram_TypeDefinition *
IIRScram_NatureDefinition::_get_final_subtype() {
  return dynamic_cast<IIRScram_TypeDefinition *>(get_final_subtype());
}
