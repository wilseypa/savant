
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
//          Kathiresan Nellayappan
 
#include "IIRScram_NatureDeclaration.hh"
#include "IIRScram_Identifier.hh"

#include "IIRScram_TerminalDeclaration.hh"
#include "IIRScram_NatureDeclaration.hh"
#include "IIRScram_ScalarNatureDefinition.hh"
#include "IIRScram_AttributeSpecificationList.hh"
#include "IIRScram_ArrayNatureDefinition.hh"
#include <iostream>
using std::cout;

IIRScram_NatureDeclaration::IIRScram_NatureDeclaration() {
  set_attributes(new IIRScram_AttributeSpecificationList());
}

IIRScram_NatureDeclaration::~IIRScram_NatureDeclaration() {
  delete get_attributes();
}

IIRScram_TypeDefinition *
IIRScram_NatureDeclaration::_get_rval(){
  return _get_nature();
}

void
IIRScram_NatureDeclaration::_type_check() {
  IIRScram_NatureDefinition *nature_definition = _get_nature();
  ASSERT(nature_definition != NULL);
  
  switch( nature_definition->get_kind() ){
  case IIR_SCALAR_NATURE_DEFINITION : {
    IIRScram_TerminalDeclaration *ref_terminal = nature_definition->get_reference_terminal();
    ref_terminal->set_subtype(nature_definition);
    ref_terminal->set_nature(nature_definition);
    set_reference_terminal( ref_terminal );
    copy_location(this,ref_terminal);
    ref_terminal->_add_declaration();
    break;
  }
  case IIR_ARRAY_SUBNATURE_DEFINITION : {
    IIRScram_NatureDefinition *nature_def;
    nature_definition = dynamic_cast<IIRScram_ArrayNatureDefinition *>(get_final_subtype());
    nature_def = nature_definition;
    ASSERT(nature_def != NULL) ;
    IIRScram_TerminalDeclaration *ref_terminal = nature_def->get_reference_terminal();
    ref_terminal->set_subtype(nature_def);
    ref_terminal->set_nature(nature_def);
    set_reference_terminal( ref_terminal );
    copy_location(this,ref_terminal);
    break;
  }
  default :
    cout << "ERROR: Unknown nature definition \n"; 
    abort();
  }
}


// IIRBase Function Wrapper(s)
IIRScram_AttributeSpecificationList *
IIRScram_NatureDeclaration::_get_attributes() {
  return dynamic_cast<IIRScram_AttributeSpecificationList *>(get_attributes());
}

IIRScram_NatureDefinition *
IIRScram_NatureDeclaration::_get_nature() {
  return dynamic_cast<IIRScram_NatureDefinition *>(get_nature());
}

