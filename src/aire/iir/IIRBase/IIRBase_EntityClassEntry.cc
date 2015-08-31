
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

#include "IIRBase_EntityClassEntry.hh"
#include "savant.hh"

IIRBase_EntityClassEntry::IIRBase_EntityClassEntry(){
  my_entity_kind = _IIR_ERROR;
  my_is_boxed = FALSE;
}

IIRBase_EntityClassEntry::~IIRBase_EntityClassEntry() {}

void  
IIRBase_EntityClassEntry::set_entity_kind( IIR_Kind entity_kind ){
  my_entity_kind = entity_kind;
}

IIR_Kind
IIRBase_EntityClassEntry::get_entity_kind(){
  return my_entity_kind;
}

void  
IIRBase_EntityClassEntry::set_boxed( IIR_Boolean is_boxed ){
  my_is_boxed = is_boxed;
}

IIR_Boolean
IIRBase_EntityClassEntry::get_boxed(){
  return my_is_boxed;
}

IIR *
IIRBase_EntityClassEntry::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_EntityClassEntry *new_node = dynamic_cast<IIRBase_EntityClassEntry *>(IIRBase_Tuple::convert_tree(factory));

  // Process the variables
  new_node->my_entity_kind = my_entity_kind;
  new_node->my_is_boxed = my_is_boxed;

  return new_node;
}

void 
IIRBase_EntityClassEntry::publish_vhdl(ostream &vhdl_out) {

  vhdl_out << get_entity_kind();
  
  if (get_boxed() == TRUE) {
    vhdl_out << " <> ";
  }
}
