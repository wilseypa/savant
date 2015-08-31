
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

#include "savant.hh"
#include "IIRBase_TerminalDeclaration.hh"
#include "IIR_TextLiteral.hh"

IIRBase_TerminalDeclaration::IIRBase_TerminalDeclaration(){
  set_nature(NULL);
}

IIRBase_TerminalDeclaration::~IIRBase_TerminalDeclaration() {}

void
IIRBase_TerminalDeclaration::set_nature( IIR_NatureDefinition *new_nature ){
  nature = new_nature;
}

IIR_NatureDefinition*
IIRBase_TerminalDeclaration::get_nature(){
  return nature;
}

IIR *
IIRBase_TerminalDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_TerminalDeclaration *new_node = dynamic_cast<IIRBase_TerminalDeclaration *>(IIRBase_ObjectDeclaration::convert_tree(factory));

  // Process the variables
  new_node->nature = dynamic_cast<IIR_NatureDefinition *>(convert_node(nature, factory));

  return new_node;
}

IIR_Declaration::declaration_type
IIRBase_TerminalDeclaration::get_declaration_type(){
   return TERMINAL;
}

void
IIRBase_TerminalDeclaration::publish_vhdl_decl(ostream &vhdl_out){
  vhdl_out << " terminal ";
  get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << " : ";
  get_subtype()->publish_vhdl(vhdl_out);
  vhdl_out << " ;\n";
}
