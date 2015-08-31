
// Copyright (c) 1996-2003 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     
//          Narayanan Thondugulam
//          Timothy J. McBrayer

//---------------------------------------------------------------------------
#include "IIRScram_AttributeSpecification.hh"
#include "IIRScram_AttributeSpecificationList.hh"
#include "IIRScram_DeclarationList.hh"
#include "IIRScram_LibraryDeclaration.hh"
#include "IIRScram_LibraryUnit.hh"
#include "IIRScram_TextLiteral.hh"



#include "language_processing_control.hh"

IIRScram_LibraryUnit::IIRScram_LibraryUnit(){}

IIRScram_LibraryUnit::~IIRScram_LibraryUnit(){}

IIRScram_AttributeSpecificationList* 
IIRScram_LibraryUnit::_get_attribute_specification_list() { 
  return dynamic_cast<IIRScram_AttributeSpecificationList *>(get_attributes()); 
}

void
IIRScram_LibraryUnit::_clone(IIRScram *cl) {
  IIRScram_LibraryUnit *clone = dynamic_cast<IIRScram_LibraryUnit*>(cl);
  IIRScram_Declaration::_clone(clone);
  IIRScram_Declaration *decl = dynamic_cast<IIRScram_Declaration *>(get_context_items()->first());
  
  while (decl != NULL) {
    clone->get_context_items()->append(decl);
    decl = dynamic_cast<IIRScram_Declaration *>(get_context_items()->successor(decl));
  }
  clone->set_context_items(get_context_items());
  IIRScram_AttributeSpecification *attrib =
    dynamic_cast<IIRScram_AttributeSpecification *>(get_attributes()->first());
  while (attrib != NULL) {
    clone->get_attributes()->append(dynamic_cast<IIRScram_AttributeSpecification*>(attrib->_clone()));
    attrib = dynamic_cast<IIRScram_AttributeSpecification *>(get_attributes()->successor(attrib));
  }
}

IIR_Boolean 
IIRScram_LibraryUnit::_is_homograph_of( IIRScram_Declaration *to_check ){
  ASSERT( to_check != NULL );
  if( to_check->_is_iir_library_unit() == TRUE ){

    // Two library units with the same name aren't homographs.
    return FALSE;    
  }
  else{
    return TRUE;
  }
}

// IIRBase Function Wrapper(s)
IIRScram_EntityDeclaration*
IIRScram_LibraryUnit::_get_entity() {
  _report_undefined_scram_fn("_get_entity()");
  return NULL;
}

IIRScram_DeclarationList *
IIRScram_LibraryUnit::_get_context_items() {
  return dynamic_cast<IIRScram_DeclarationList *>(get_context_items());
}
