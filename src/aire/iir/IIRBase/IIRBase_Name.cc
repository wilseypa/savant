
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

#include "IIRBase_Name.hh"
#include "set.hh"
#include "symbol_table.hh"
#include <cstdlib>
#include <iostream>
#include "IIR_Identifier.hh"

#include "savant.hh"




IIRBase_Name::IIRBase_Name() :
  prefix(0){}

IIRBase_Name::~IIRBase_Name(){}

IIR *
IIRBase_Name::get_prefix(){
  return prefix;
}

void 
IIRBase_Name::set_prefix( IIR *new_prefix ){
  prefix = new_prefix;
}

void
IIRBase_Name::set_suffix( IIR * ){
  cerr << "IIRBase_Name::set_suffix called - node type is " << get_kind_text() 
       << " - aborting!" << endl;
  abort();
}

IIR *
IIRBase_Name::get_suffix(){
  return 0;
}


IIR *
IIRBase_Name::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_Name *new_node = dynamic_cast<IIRBase_Name *>(IIRBase::convert_tree(factory));

  // Process the variables
  new_node->prefix = convert_node(prefix, factory);

  return new_node;
}

IIR_Boolean
IIRBase_Name::is_signal(){
  return get_prefix()->is_signal();
}

void 
IIRBase_Name::set_subtype( IIR_TypeDefinition * ){
  ASSERT(0);
}

IIR_Boolean
IIRBase_Name::is_object(){
  return get_prefix()->is_object();
}

IIR_SignalKind 
IIRBase_Name::get_signal_kind(){
  return get_prefix()->get_signal_kind();
}

IIR_TextLiteral *
IIRBase_Name::get_prefix_string(){
  return get_prefix()->get_prefix_string();
}

IIR_Boolean
IIRBase_Name::is_locally_static(){
  ASSERT( get_prefix() && get_prefix()->is_resolved() );
  IIR_Boolean retval = get_prefix()->is_locally_static();
  if( get_suffix() ){
    retval = retval && get_suffix()->is_locally_static();
  }
  return retval;
}

IIR_Boolean
IIRBase_Name::is_variable(){
  return get_prefix()->is_variable();
}

ostream &
IIRBase_Name::print( ostream &os ){
  get_prefix()->print( os );
  
  return os;
}

IIR **
IIRBase_Name::lookup(IIR_Identifier *identifier,
		     IIR_Int32      &number_of_matches,
		     IIR            *&first_match){
  ASSERT(0);
  return NULL;
}

IIR **
IIRBase_Name::lookup(IIR_Name    *name,
		     IIR_Int32   &number_of_matches,
		     IIR         *&first_match){
  IIR** return_array = NULL;
  cerr << "IIRBase_Name::lookup(IIR_Name    *name not implemented yet!"<< endl;
  abort();
  return return_array;
}
