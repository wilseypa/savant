
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

#include "IIRBase_TerminalInterfaceDeclaration.hh"

IIRBase_TerminalInterfaceDeclaration::IIRBase_TerminalInterfaceDeclaration() {}
IIRBase_TerminalInterfaceDeclaration::~IIRBase_TerminalInterfaceDeclaration() {}

IIR_Declaration::declaration_type
IIRBase_TerminalInterfaceDeclaration::get_declaration_type(){
   return INTERFACE_TERMINAL;
}

void
IIRBase_TerminalInterfaceDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << " terminal ";
  publish_vhdl_declarator_with_colon(vhdl_out);
  publish_vhdl_subtype_indication(vhdl_out);
}
