
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

#include "IIRScram_ScalarNatureDefinition.hh"
#include "IIRScram_TerminalDeclaration.hh"
#include "IIRScram_TextLiteral.hh"
#include "IIRScram_TypeDefinition.hh"

#include <iostream>
using std::cerr;
using std::endl;

IIRScram_TypeDefinition *
IIRScram_ScalarNatureDefinition::_get_through() {
  return dynamic_cast<IIRScram_TypeDefinition *>(IIRBase_ScalarNatureDefinition::get_through());
}

IIRScram_TypeDefinition *
IIRScram_ScalarNatureDefinition::_get_across() {
  return dynamic_cast<IIRScram_TypeDefinition *>(IIRBase_ScalarNatureDefinition::get_across());
}

IIRScram_TerminalDeclaration *
IIRScram_ScalarNatureDefinition::_get_reference_terminal() {
  return dynamic_cast<IIRScram_TerminalDeclaration *>(IIRBase_ScalarNatureDefinition::get_reference_terminal());
}
