
#ifndef IIRSCRAM_TERMINAL_INTERFACE_DECLARATION_HH
#define IIRSCRAM_TERMINAL_INTERFACE_DECLARATION_HH

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
#include "IIRBase_TerminalInterfaceDeclaration.hh"
#include "IIRScram_InterfaceDeclaration.hh"

class IIRScram_TerminalInterfaceDeclaration : public virtual IIRScram_InterfaceDeclaration, public virtual IIRBase_TerminalInterfaceDeclaration {

public:
  IIRScram_TerminalInterfaceDeclaration() {}
  virtual ~IIRScram_TerminalInterfaceDeclaration();


  IIR_Boolean _is_terminal(){ return TRUE; }

  void _type_check( IIRScram_InterfaceDeclaration::_InterfaceListType );

protected:
private:
};
#endif
