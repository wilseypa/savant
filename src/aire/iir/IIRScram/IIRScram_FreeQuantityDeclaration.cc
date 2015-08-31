
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
 
// Author: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_FreeQuantityDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_TypeDefinition.hh"

IIRScram_FreeQuantityDeclaration::~IIRScram_FreeQuantityDeclaration() {}

IIRScram_FreeQuantityDeclaration::IIRScram_FreeQuantityDeclaration() {
  default_rtol = 1e-3;
  default_atol = 1e-12;
}

IIR_Boolean
IIRScram_FreeQuantityDeclaration::_is_readable() {
  return TRUE;
}

void
IIRScram_FreeQuantityDeclaration::set_value(IIRScram *val) {
  IIRBase_FreeQuantityDeclaration::set_value(val);
}

void
IIRScram_FreeQuantityDeclaration::_type_check() {
  RTOL = default_rtol;
  ATOL = default_atol;
}

IIRScram *
IIRScram_FreeQuantityDeclaration::_get_value() {
  return dynamic_cast<IIRScram *>(IIRBase_FreeQuantityDeclaration::get_value());
}



