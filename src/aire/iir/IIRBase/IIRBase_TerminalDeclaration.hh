
#ifndef IIRBASE_TERMINAL_DECLARATION_HH
#define IIRBASE_TERMINAL_DECLARATION_HH

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

#include "savant_config.hh"
#include "IIR_TerminalDeclaration.hh"
#include "IRBasicDataTypes.hh"
#include "IIR_NatureDefinition.hh"
#include "IIRBase_ObjectDeclaration.hh"

class IIR_NatureDefinition;
class IIRBase_TerminalDeclaration : public virtual IIRBase_ObjectDeclaration, public virtual IIR_TerminalDeclaration {
public: 
  IIR_Kind get_kind() const { return IIR_TERMINAL_DECLARATION; }
  const IIR_Char *get_kind_text() const { return "IIR_TerminalDeclaration"; }

  /** Set the nature of the terminal */
  void set_nature(IIR_NatureDefinition *nature);

  /** Returns the nature of the terminal */
  IIR_NatureDefinition* get_nature();

  IIR *convert_tree(plugin_class_factory *factory);

  declaration_type get_declaration_type();
  void publish_vhdl_decl(ostream &);
protected:

  IIRBase_TerminalDeclaration();
  virtual ~IIRBase_TerminalDeclaration() = 0;

private:

  IIR_NatureDefinition* nature;

};

#endif
