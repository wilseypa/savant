
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

#include "IIRBase_ProcedureDeclaration.hh"
#include "IIRBase_ProcedureReturnTypeDefinition.hh"
#include "IIRBase_InterfaceList.hh"
#include "IIR_SequentialStatementList.hh"
#include "IIR_TypeDefinition.hh"
#include "IIR_TextLiteral.hh"

IIRBase_ProcedureDeclaration::IIRBase_ProcedureDeclaration() {}
IIRBase_ProcedureDeclaration::~IIRBase_ProcedureDeclaration() {}

IIR_Declaration::declaration_type 
IIRBase_ProcedureDeclaration::get_declaration_type(){
   return PROCEDURE;
}

void
IIRBase_ProcedureDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << "procedure ";
  get_declarator()->publish_vhdl(vhdl_out);
  
  if (get_interface_declarations()->size() != 0) {
    vhdl_out << "(";
    dynamic_cast<IIRBase_InterfaceList *>
      (get_interface_declarations())->publish_vhdl_decl(vhdl_out);
    vhdl_out << ")";
  }

  if (contains_body() == TRUE) {
    vhdl_out << " is\n";
    if( get_subprogram_declarations()->size() != 0) {
      dynamic_cast<IIRBase_DeclarationList *>
	(get_subprogram_declarations())->publish_vhdl_decl(vhdl_out);
    }
    vhdl_out << "begin\n";
    get_subprogram_body()->publish_vhdl(vhdl_out);
    vhdl_out << "end procedure " << *get_declarator();
  }
  vhdl_out << ";\n";
}
