
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

#include "IIRScram_ArchitectureStatement.hh"
#include "IIRScram_ArchitectureStatementList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_SimultaneousIfStatement.hh"
#include "IIRScram_SimultaneousElsif.hh"
#include "IIRScram_TypeDefinition.hh"

#include "resolution_func.hh"

#include "StandardPackage.hh"
#include "set.hh"

IIRScram_SimultaneousElsif::IIRScram_SimultaneousElsif() {
  set_then_sequence_of_statements(new IIRScram_ArchitectureStatementList());
}

IIRScram_SimultaneousElsif::~IIRScram_SimultaneousElsif(){}

void
IIRScram_SimultaneousElsif::_type_check( savant::set<IIRScram_TypeDefinition> * ){ 
  set_condition(IIRScram_Statement::_type_check_and_resolve_boolean_condition(_get_condition()));
  
  if (_get_else_clause() != NULL) {
    savant::set<IIRScram_TypeDefinition> *bool_rvals = 
      new savant::set<IIRScram_TypeDefinition>(dynamic_cast<IIRScram_TypeDefinition *>(_get_design_file()->get_standard_package()->get_boolean_type()));
    _get_else_clause()->_type_check( bool_rvals );
    delete bool_rvals;
  }
}

IIRScram *
IIRScram_SimultaneousElsif::_get_condition() {
  return dynamic_cast<IIRScram *>(get_condition());
}

IIRScram_ArchitectureStatementList *
IIRScram_SimultaneousElsif::_get_then_sequence_of_statements() {
  return dynamic_cast<IIRScram_ArchitectureStatementList *>(get_then_sequence_of_statements());
}

IIRScram_SimultaneousElsif *
IIRScram_SimultaneousElsif::_get_else_clause() {
  return dynamic_cast<IIRScram_SimultaneousElsif *>(get_else_clause());
}
