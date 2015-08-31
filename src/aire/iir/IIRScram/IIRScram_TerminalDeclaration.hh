#ifndef IIRSCRAM_TERMINAL_DECLARATION_HH
#define IIRSCRAM_TERMINAL_DECLARATION_HH

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
 
// Authors: Sivakumar Gowrisankar             gowriss@ececs.uc.edu
//          Vinod Chamarty                    chamarv@ececs.uc.edu
//          Vasudevan Shanmugasundaram
//          Kathiresan Nellayappan
 
//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_ObjectDeclaration.hh"
#include "IIRBase_TerminalDeclaration.hh"

class IIRScram_TerminalDeclaration : public virtual IIRScram_ObjectDeclaration, public virtual IIRBase_TerminalDeclaration {

public:
  /** this function dumps the terminal declarations in the vhdl file. */ 

  IIR_Int32 terminal_id;
  IIR_Boolean _is_terminal(){ return TRUE; }
  void _type_check();

protected:
private:
};
#endif