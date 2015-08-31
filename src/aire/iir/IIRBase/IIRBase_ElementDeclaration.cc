
// Copyright (c) 1996-1999 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
// DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.


// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com

//---------------------------------------------------------------------------

#include "IIRBase_ElementDeclaration.hh"
#include "IIR_ElementDeclarationList.hh"
#include "IIR_RecordTypeDefinition.hh"
#include "IIR_TypeDefinition.hh"
#include "savant.hh"

IIRBase_ElementDeclaration::IIRBase_ElementDeclaration(){}

IIRBase_ElementDeclaration::~IIRBase_ElementDeclaration(){}

savant::set<IIR_Declaration> *
IIRBase_ElementDeclaration::find_declarations( IIR_Name *to_find ){
  savant::set<IIR_Declaration> *retval = NULL;

  ASSERT( get_subtype() != NULL );

  if( get_subtype()->is_record_type() == TRUE ){
    IIR_RecordTypeDefinition *my_subtype = 
      dynamic_cast<IIR_RecordTypeDefinition *>(get_subtype());
    retval = my_subtype->get_element_declarations()->find_declarations( to_find );
  }
  else{
    retval = NULL;
  }

  return retval;
}

void 
IIRBase_ElementDeclaration::publish_vhdl_decl(ostream &vhdl_out) {
  ASSERT( get_declarative_region() != NULL );
  ASSERT(get_declarative_region()->get_kind() == IIR_RECORD_TYPE_DEFINITION);
  
 publish_vhdl_declarator_with_colon(vhdl_out);
 if (get_subtype()->get_kind() != IIR_ARRAY_SUBTYPE_DEFINITION) {
   get_subtype()->publish_vhdl(vhdl_out);
 } else {
   // HACK: Fix ArraySubtypeDefinitions as record elements.
   // ArraySubtypeDefinition does not correctly publish the type of the record element
   // in publish_vhdl
   dynamic_cast<IIRBase *>(get_subtype())->publish_vhdl_decl(vhdl_out);
 }
 vhdl_out << ";\n";
}
