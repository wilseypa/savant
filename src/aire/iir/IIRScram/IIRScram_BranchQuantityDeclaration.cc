
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

#include "IIRScram_BranchQuantityDeclaration.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_Name.hh"
#include "IIRScram_TerminalDeclaration.hh"

IIRScram_BranchQuantityDeclaration::IIRScram_BranchQuantityDeclaration() {
  set_across_aspect_identifier_list(new IIRScram_DesignatorList());
  set_through_aspect_designator_list(new IIRScram_DesignatorList());
}

IIRScram_BranchQuantityDeclaration::~IIRScram_BranchQuantityDeclaration(){}

IIR_Int32
IIRScram_BranchQuantityDeclaration::get_plus_terminal_id() {
  ASSERT( get_plus_terminal_name() != NULL );
  return (dynamic_cast<IIRScram_TerminalDeclaration *>(get_plus_terminal_name()))->terminal_id;
}

IIR_Int32
IIRScram_BranchQuantityDeclaration::get_minus_terminal_id() {
  if ( get_minus_terminal_name() != NULL ) {
    return (dynamic_cast<IIRScram_TerminalDeclaration *>(get_minus_terminal_name()))->terminal_id;
  }
  else {
    return 0;
  }
}

IIR_Int32
IIRScram_BranchQuantityDeclaration::get_num_across_elements() {
  return get_across_aspect_identifier_list()->size();
}

IIR_Int32
IIRScram_BranchQuantityDeclaration::get_num_through_elements() {
  return get_through_aspect_designator_list()->size();
}

IIRScram_Name*
IIRScram_BranchQuantityDeclaration::_get_plus_terminal_name() {
  return dynamic_cast<IIRScram_Name *>(get_plus_terminal_name());
}

IIRScram_Name*
IIRScram_BranchQuantityDeclaration::_get_minus_terminal_name() {
  return dynamic_cast<IIRScram_Name *>(get_minus_terminal_name());
}

void
IIRScram_BranchQuantityDeclaration::_type_check() {
  IIRScram_ObjectDeclaration::_type_check();
}

IIR_Boolean
IIRScram_BranchQuantityDeclaration::_is_readable() {
  return TRUE;
}

IIRScram *
IIRScram_BranchQuantityDeclaration::_get_across_aspect_expression() {
  return dynamic_cast<IIRScram *>(get_across_aspect_expression());
}

IIRScram *
IIRScram_BranchQuantityDeclaration::_get_through_aspect_expression() {
  return dynamic_cast<IIRScram *>(get_through_aspect_expression());
}

IIRScram *
IIRScram_BranchQuantityDeclaration::_get_across_aspect_tolerance() {
  return dynamic_cast<IIRScram *>(get_across_aspect_tolerance());
}

IIRScram *
IIRScram_BranchQuantityDeclaration::_get_through_aspect_tolerance() {
  return dynamic_cast<IIRScram *>(get_through_aspect_tolerance());
}
