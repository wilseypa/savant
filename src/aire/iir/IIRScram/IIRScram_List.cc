
// Copyright (c) 1996-2000 The University of Cincinnati.  
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
//          Krishnan Subramani  skrish@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_ArchitectureStatementList.hh"
#include "IIRScram_DeclarationList.hh"
#include "IIRScram_List.hh"
#include "IIRScram_TypeDefinition.hh"
#include "savant.hh"


#include "plugin_class_factory.hh"

IIRScram_List::~IIRScram_List(){}

IIRScram_List *
IIRScram_List::_listcopy( IIRScram_List *source, plugin_class_factory *factory) {
  IIRScram_List *new_list = dynamic_cast<IIRScram_List *>(factory->get_new_class(source->get_kind()));
  for (IIR *ptr = source->first(); ptr != NULL; ptr = source->successor(ptr)) {
    new_list->append(ptr);
  }

  return new_list;
}

IIRScram *
IIRScram_List::_clone(){
  _report_undefined_scram_fn("_clone()");
  return NULL;
}


void 
IIRScram_List::_clone( IIRScram *clone_into ){
  ASSERT( clone_into->_is_iir_list() == TRUE );
  IIRScram_List *as_list = dynamic_cast<IIRScram_List *>(clone_into);

  IIRScram *current = dynamic_cast<IIRScram *>(first());
  while( current != NULL ){
    as_list->append( current->_clone() );
    current = dynamic_cast<IIRScram *>(successor( current ));
  }
}

IIRScram_Label *
IIRScram_List::_find_instantiate_label( IIRScram_SimpleName * ){
  _report_undefined_scram_fn("_find_instantiate_label( IIRScram_SimpleName * )");
  return NULL;
}

void 
IIRScram_List::_append( IIR_List *to_append ){
  ASSERT( to_append != NULL );

  // This is kind of inefficient - we could support it at a lower level and
  // hook the whole chain on at once.
  IIRScram *current = dynamic_cast<IIRScram *>(to_append->first());
  while( current != NULL ){
    append( current );
    current = dynamic_cast<IIRScram *>(to_append->successor( current ));
  }
}

void 
IIRScram_List::_make_interface_visible( symbol_table *add_to ){
  IIRScram *current = dynamic_cast<IIRScram *>(first());
  while( current != NULL ){
    current->_make_interface_visible( add_to );
    current = dynamic_cast<IIRScram *>(successor( current ));
  }
}

void 
IIRScram_List::_destroy_list(){
  IIRScram *current = dynamic_cast<IIRScram *>(first());
  IIRScram *last;
  while( current != NULL ){
    last = current;
    current = dynamic_cast<IIRScram *>(successor( current ));
    remove( last );
    delete last;
  }
}
