
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

// Authors: Prashanth Cherukuri cherukps@ececs.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram.hh"
#include "IIRScram_Attribute.hh"
#include "IIRScram_Declaration.hh"
#include "IIRScram_IndexedName.hh"
#include "IIRScram_SourceQuantityDeclaration.hh"
#include "IIRScram_TextLiteral.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_TerminalDeclaration.hh"
#include "set.hh"

IIRScram_SourceQuantityDeclaration::IIRScram_SourceQuantityDeclaration() {}

IIRScram_SourceQuantityDeclaration::~IIRScram_SourceQuantityDeclaration() {}

savant::set<IIRScram_TypeDefinition> *
IIRScram_SourceQuantityDeclaration::_get_rval_set() {
  savant::set<IIRScram_TypeDefinition> *retval = new savant::set<IIRScram_TypeDefinition>;
  retval->add( _get_subtype() );
  return retval;
}

IIRScram *
IIRScram_SourceQuantityDeclaration::_get_noise_expression() {
  return dynamic_cast<IIRScram *>(get_noise_expression());
}

IIRScram *
IIRScram_SourceQuantityDeclaration::_get_phase_expression() {
  return dynamic_cast<IIRScram *>(get_phase_expression());
}

IIRScram *
IIRScram_SourceQuantityDeclaration::_get_magnitude_expression() {
  return dynamic_cast<IIRScram *>(get_magnitude_expression());
}
