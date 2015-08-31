
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

#include "savant.hh"
#include "IIRBase_DeclarationList.hh"

#include "set.hh"

#include "IIR.hh"
#include "IIR_Declaration.hh"
#include "IIR_Name.hh"
#include "IIR_SelectedName.hh"
#include "IIRBase_TextLiteral.hh"
#include "IIR_TypeDeclaration.hh"

IIRBase_DeclarationList::IIRBase_DeclarationList(){}
IIRBase_DeclarationList::~IIRBase_DeclarationList(){}

void 
IIRBase_DeclarationList::append( IIR_Declaration *to_append ){
  IIRBase_List::append( to_append );
}

IIR *
IIRBase_DeclarationList::successor( IIR_Declaration *succeed_me ){
  IIR *retval = IIRBase_List::successor( succeed_me );
  return dynamic_cast<IIR_Declaration *>(retval);
}

IIR *
IIRBase_DeclarationList::first(){
  IIR *retval = IIRBase_List::first();

  return dynamic_cast<IIR_Declaration *>(retval);
}


void
IIRBase_DeclarationList::prepend( IIR_Declaration *element ) {
  IIRBase_List::prepend( element );
}

IIR*
IIRBase_DeclarationList::predecessor( IIR_Declaration *element ){
  IIR *retval = IIRBase_List::predecessor( element );

  ASSERT( retval != NULL );

  return dynamic_cast<IIR_Declaration*>(retval);
}


IIR *
IIRBase_DeclarationList::last() {
  IIR *retval = IIRBase_List::last( );

  ASSERT( retval != NULL );

  return dynamic_cast<IIR_Declaration*>(retval);
}

IIR *
IIRBase_DeclarationList::get_nth_element( IIR_Int32 to_get ){
  IIR *retval = IIRBase_List::get_nth_element( to_get );

  ASSERT( retval != NULL );

  return dynamic_cast<IIR_Declaration *>(retval);
}

savant::set<IIR_Declaration> *
IIRBase_DeclarationList::find_declarations( IIR_Name *to_find ){
  ASSERT( to_find != NULL );
  savant::set<IIR_Declaration> *retval = NULL;
  // The following assertion holds true because an indexed name doesn't generally
  // map into a declaration.  So, we can't expect to look at a list of declarations,
  // searching for an indexed name, and really find anything.
  ASSERT( to_find->get_kind() != IIR_INDEXED_NAME );
  
  switch( to_find->get_kind() ){
  case IIR_SIMPLE_NAME:{
    ASSERT( to_find->get_prefix() != NULL );
    IIR_TextLiteral *prefix = dynamic_cast<IIR_TextLiteral *>(to_find->get_prefix());
    ASSERT(prefix != NULL);
    retval = find_declarations( prefix );
    break;
  }
  case IIR_SELECTED_NAME:{
    IIR_SelectedName *as_selected_name = dynamic_cast<IIR_SelectedName *>(to_find);
    ASSERT( to_find->get_prefix() != NULL );
    ASSERT( dynamic_cast<IIR_Name *>(to_find->get_prefix()) );
    
    savant::set<IIR_Declaration> *found = find_declarations( dynamic_cast<IIR_Name *>(to_find->get_prefix()) );
    if( found == NULL ){
      retval = NULL;
    }
    else{
      ASSERT( as_selected_name->get_suffix() != NULL );
      ASSERT( dynamic_cast<IIR_Name *>(as_selected_name->get_suffix()) );
      savant::set<IIR_Declaration> *current_set;
      retval = new savant::set<IIR_Declaration>;

      IIR_Declaration *current_decl = found->getElement();
      while( current_decl != NULL ){
	current_set = 
	  current_decl->find_declarations(dynamic_cast<IIR_Name *>(as_selected_name->get_suffix()) );
	if( current_set != NULL ){
	  retval->add( current_set );
	  delete current_set;
	}
	current_decl = found->getNextElement();
      }
      if( retval->size() == 0 ){
	delete retval;
	retval = NULL;
      }
    }
    delete found;
    break;
  }
  default:{
    ASSERT(0);  // Internal error
  }
  }
  return retval;
}

savant::set<IIR_Declaration> *
IIRBase_DeclarationList::find_declarations( IIR_TextLiteral *to_find ){
  savant::set<IIR_Declaration> *retval = new savant::set<IIR_Declaration>;
  ASSERT( to_find != NULL );
  
  for (IIR_Declaration *current = dynamic_cast<IIR_Declaration *>(first());
       current != NULL;current = dynamic_cast<IIR_Declaration *>(successor(current))) {
    if( IIRBase_TextLiteral::cmp( current->get_declarator(), to_find ) == 0 ){
      retval->add( current );
    }
    else{
      if( current->get_kind() == IIR_TYPE_DECLARATION ){
	// We need to search the implicit declarations for whatever we're
	// looking for.
        IIR_TypeDeclaration *as_type_decl = dynamic_cast<IIR_TypeDeclaration *>(current);
 	ASSERT( as_type_decl->get_implicit_declarations() != NULL );
 	IIR_Declaration *current_implicit;
	current_implicit = as_type_decl->get_implicit_declarations()->getElement();
	while( current_implicit != NULL ){
	  if( IIRBase_TextLiteral::cmp( current_implicit->get_declarator(), to_find ) == 0 ){
	    retval->add( current_implicit );
	  }
	  current_implicit = as_type_decl->get_implicit_declarations()->getNextElement();
	}
	// If we have an enumeration type, we need to search for the our
	// culprit in the literal list.
	if( current->is_enumeration_type() == TRUE ){
	  savant::set<IIR_Declaration> *enumeration_literals = current->find_declarations( to_find );
	  if( enumeration_literals != NULL ){
	    ASSERT( enumeration_literals->size() == 1 );
	    retval->add( enumeration_literals );
	  }
	}
      }
    }
  }
  if( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }
  return retval;
}

void
IIRBase_DeclarationList::set_declarative_region( IIR *new_declarative_region ){
  IIR_Declaration *current = dynamic_cast<IIR_Declaration *>(first());
  while( current != 0 ){
    current->set_declarative_region( new_declarative_region );
    current = dynamic_cast<IIR_Declaration *>(successor( current ));
  }
}

void
IIRBase_DeclarationList::publish_vhdl(ostream &vhdl_out) {
  for (IIRBase_Declaration *decl = dynamic_cast<IIRBase_Declaration *>(first());
       decl != NULL;decl = dynamic_cast<IIRBase_Declaration *>(successor(decl))) {
    decl->publish_vhdl(vhdl_out);
  }
}

void 
IIRBase_DeclarationList::publish_vhdl_decl(ostream &vhdl_out) {
  for (IIRBase_Declaration *decl = dynamic_cast<IIRBase_Declaration *>(first());
       decl != NULL;decl = dynamic_cast<IIRBase_Declaration *>(successor(decl))) {
    decl->publish_vhdl_decl(vhdl_out);
  }
}
