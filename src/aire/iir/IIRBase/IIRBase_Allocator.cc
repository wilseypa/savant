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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------



#include "IIRBase_Allocator.hh"
#include "savant.hh"
#include "IIR_TypeDefinition.hh"


IIRBase_Allocator::IIRBase_Allocator(){
  set_type_mark( NULL );
  set_value(NULL);
}

IIRBase_Allocator::~IIRBase_Allocator(){
  delete get_type_mark();
  delete get_value();
}

void 
IIRBase_Allocator::set_type_mark( IIR_TypeDefinition *new_type_mark ){
  type_mark = new_type_mark;
}


IIR_TypeDefinition *
IIRBase_Allocator::get_type_mark(){
  return type_mark;
}

void 
IIRBase_Allocator::set_value( IIR *new_value ) {
  value = new_value;
}


IIR*
IIRBase_Allocator::get_value() {
  return value;
}

IIR *
IIRBase_Allocator::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_Allocator *new_node = dynamic_cast<IIRBase_Allocator *>(IIRBase_Expression::convert_tree(factory));

  // Process the variables
  new_node->type_mark = dynamic_cast<IIR_TypeDefinition *>(convert_node(type_mark, factory));
  new_node->value = convert_node(value, factory);

  return new_node;
}

IIR_Boolean 
IIRBase_Allocator::is_resolved(){
  ASSERT( get_type_mark() != NULL );
  return get_type_mark()->is_resolved();
}

ostream &
IIRBase_Allocator::print( ostream &os ){
  os << "new ";
  os << *get_type_mark();

  return os;
}

void
IIRBase_Allocator::publish_vhdl(ostream &vhdl_out) {
  vhdl_out << "new ";
  get_type_mark()->publish_vhdl(vhdl_out);
  
  if( IIRBase_Allocator::get_value() != NULL ){
    ASSERT( get_value()->is_resolved() == TRUE );

    vhdl_out << "'( ";
    get_value()->publish_vhdl( vhdl_out );
    vhdl_out << " )";    
  }
}
