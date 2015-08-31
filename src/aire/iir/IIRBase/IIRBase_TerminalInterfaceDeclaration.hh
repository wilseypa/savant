
#ifndef IIRBASE_TERMINAL_INTERFACE_DECLARATION_HH
#define IIRBASE_TERMINAL_INTERFACE_DECLARATION_HH

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

#include "savant_config.hh"
#include "IIR_TerminalInterfaceDeclaration.hh"
#include "IIRBase_InterfaceDeclaration.hh"

class IIRBase_TerminalInterfaceDeclaration : public virtual IIRBase_InterfaceDeclaration, public virtual IIR_TerminalInterfaceDeclaration {
public:
  /** Returns the IIR_Kind of this node. */
  IIR_Kind get_kind() const {  return IIR_TERMINAL_INTERFACE_DECLARATION;  }
  
  /** Returns the text name of this node. */
  const IIR_Char *get_kind_text() const {  return "IIR_TerminalInterfaceDeclaration";  }

  declaration_type get_declaration_type();
  void publish_vhdl_decl(ostream &);
protected:
  IIRBase_TerminalInterfaceDeclaration();
  virtual ~IIRBase_TerminalInterfaceDeclaration() = 0;

private:
};
#endif
