
// Copyright (c) The University of Cincinnati.  
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

#include "savant.hh"
#include "IIRBase_FunctionDeclaration.hh"
#include "IIR_SequentialStatementList.hh"
#include "IIRBase_TextLiteral.hh"
#include "IIR_TypeDefinition.hh"
#include "IIRBase_InterfaceList.hh"

IIRBase_FunctionDeclaration::IIRBase_FunctionDeclaration() :
  purity(IIR_PURE_FUNCTION){}

IIRBase_FunctionDeclaration::~IIRBase_FunctionDeclaration() {}

void
IIRBase_FunctionDeclaration::set_pure( IIR_Pure new_purity ){
  purity = new_purity;
}

IIR_Pure
IIRBase_FunctionDeclaration::get_pure() {
  return purity;
}

IIR_Boolean
IIRBase_FunctionDeclaration::is_locally_static(){
    return (get_pure() == IIR_PURE_FUNCTION);
}

void
IIRBase_FunctionDeclaration::set_return_type( IIR_TypeDefinition *new_return_type ){
  IIRBase::set_subtype( new_return_type );
}

IIR_TypeDefinition*
IIRBase_FunctionDeclaration::get_return_type() {
  return IIRBase::get_subtype();
}

IIR *
IIRBase_FunctionDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_FunctionDeclaration *new_node = dynamic_cast<IIRBase_FunctionDeclaration *>(IIRBase_SubprogramDeclaration::convert_tree(factory));

  // Process the variables
  new_node->purity = purity;

  return new_node;
}

IIR_Declaration::declaration_type 
IIRBase_FunctionDeclaration::get_declaration_type(){
   return IIR_Declaration::FUNCTION;
}

IIR_Boolean
IIRBase_FunctionDeclaration::is_operator() {
  // This is needed as operators are seen as function calls but are handled
  // differently.
  static const char *operators[] = {"\"=\"", "\"=\"", "\">\"", "\"<\"",
				    "\"<=\"", "\">=\"", "\"/=\"", "\"&\"",
				    "\"+\"", "\"-\"", "\"*\"", "\"/\"",
				    "\"**\"", "\"mod\"", "\"rem\"", "\"abs\"",
				    "\"and\"", "\"or\"", "\"not\"", "\"xor\"",
				    "\"xnor\"", "\"sll\"", "\"srl\"",
				    "\"sla\"", "\"sra\"", "\"rol\"",
				    "\"ror\"", "\"nor\"", "\"nand\"", 0};
  
  IIR_TextLiteral *decl = get_declarator();
  
  for(int i = 0; operators[i] != 0; i++) {
    if (IIRBase_TextLiteral::cmp(decl, operators[i]) == 0) {
      return TRUE;
    }
  }

  return FALSE;
}

void 
IIRBase_FunctionDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  if (get_pure() == IIR_IMPURE_FUNCTION) {
    vhdl_out << "impure ";
  }
  
  vhdl_out << "function ";
  get_declarator()->publish_vhdl(vhdl_out);
  
  if (get_interface_declarations()->size() != 0) {
    vhdl_out << " (";
    dynamic_cast<IIRBase_InterfaceList *>(get_interface_declarations())->publish_vhdl_decl(vhdl_out);
    vhdl_out << ")";
  }
	
  vhdl_out << " return ";
  get_return_type()->publish_vhdl(vhdl_out);
  
  if (contains_body() == TRUE) {
    vhdl_out << " is " << endl;
    dynamic_cast<IIRBase_DeclarationList *>
      (get_subprogram_declarations())->publish_vhdl_decl(vhdl_out);
    vhdl_out << "begin" << endl;
    get_subprogram_body()->publish_vhdl(vhdl_out);
    vhdl_out << "end function " << *get_declarator()
              << ";" << endl;
  }
  else {
    vhdl_out << ";\n";
  }
}
