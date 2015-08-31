#ifndef IIRSCRAM_NATURE_DEFINITION_HH
#define IIRSCRAM_NATURE_DEFINITION_HH

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
 
//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRBase_NatureDefinition.hh"

class IIRScram_FunctionDeclaration;
class IIRScram_TerminalDeclaration;
class IIRScram_TextLiteral;

class IIRScram_NatureDefinition : public virtual IIRScram_TypeDefinition, public virtual IIRBase_NatureDefinition {
public:
  IIR_Boolean _is_nature_definition() { return TRUE; }

  virtual IIRScram_TerminalDeclaration *get_reference_terminal();
  virtual IIRScram_TypeDefinition *_get_element_subtype();
  void _set_resolution_function(IIRScram_FunctionDeclaration *);

  IIRScram_Declaration * _get_declaration();
  IIRScram_TypeDefinition *_get_final_subtype();
protected:
};
#endif
