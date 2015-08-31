
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
//          Malolan Chetlur     mal@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRBase_SliceName.hh"
#include "savant.hh"

IIRBase_SliceName::IIRBase_SliceName() {
  set_suffix(NULL);
}

IIRBase_SliceName::~IIRBase_SliceName() {}

void
IIRBase_SliceName::set_suffix( IIR *new_suffix ){
  suffix = new_suffix;
}

IIR*
IIRBase_SliceName::get_suffix() {
  return suffix;
}


IIR *
IIRBase_SliceName::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_SliceName *new_node = dynamic_cast<IIRBase_SliceName *>(IIRBase_Name::convert_tree(factory));

  // Process the variables
  new_node->suffix = convert_node(suffix, factory);

  return new_node;
}

IIR_Boolean 
IIRBase_SliceName::is_resolved(){
  IIR_Boolean retval = TRUE;
  if( get_prefix()->is_resolved() == FALSE || get_suffix()->is_resolved() == FALSE ){
    retval = FALSE;
  }

  return retval;
}

IIR_Boolean 
IIRBase_SliceName::is_variable(){
  return get_prefix()->is_variable();
}

ostream &
IIRBase_SliceName::print( ostream &os ){
  os << *get_prefix();
  os << "(";
  os << *get_suffix();
  os << ")";

  return os;
}

// We handle slice names as aliases.  An implicit alias of the prefix with
// the corresponding range is created and used as the slice.
IIR_Declaration*
IIRBase_SliceName::get_prefix_declaration() {
  return get_prefix()->get_prefix_declaration();
}

void 
IIRBase_SliceName::publish_vhdl(ostream &vhdl_out) {
  ASSERT(get_prefix() != NULL);
  ASSERT(get_prefix()->is_resolved() == TRUE);
  ASSERT(get_suffix() != NULL);
  ASSERT(get_suffix()->is_resolved() == TRUE);

  get_prefix()->publish_vhdl(vhdl_out);
  vhdl_out << " ( ";
  dynamic_cast<IIRBase *>(get_suffix())->publish_vhdl_range(vhdl_out);
  vhdl_out << " ) ";
}
