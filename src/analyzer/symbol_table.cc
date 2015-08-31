
// Copyright (c) 1995-2001 The University of Cincinnati.
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

// Author: Dale E. Martin          dmartin@cliftonlabs.com

//---------------------------------------------------------------------------

#include "IIR_GenericList.hh"
#include "IIR_PortList.hh"
#include "IIR_EnumerationLiteralList.hh"
#include "IIR_SignalInterfaceDeclaration.hh"
#include "IIR_ConstantInterfaceDeclaration.hh"
#include "IIR_SubprogramDeclaration.hh"
#include "IIR_TypeDeclaration.hh"
#include "IIR_EnumerationTypeDefinition.hh"
#include "IIR_ArrayTypeDefinition.hh"
#include "IIR_IntegerTypeDefinition.hh"
#include "IIR_FloatingSubtypeDefinition.hh"
#include "IIR_EnumerationLiteral.hh"
#include "IIR_PhysicalUnit.hh"
#include "IIR_IncompleteTypeDefinition.hh"
#include "IIR_LibraryDeclaration.hh"
#include "IIR_LibraryUnit.hh"
#include "IIR_DeclarationList.hh"
#include "IIR_UnitList.hh"
#include "StandardPackage.hh"
#include "error_func.hh"
#include "symbol_table.hh"

#include "library_manager.hh"
#include "IIRScram_PackageDeclaration.hh"
#include "IIRScram_SubprogramDeclaration.hh"
#include "IIRScram_InterfaceList.hh"
#include "IIRScram_PhysicalTypeDefinition.hh"
#include "IIRScram_AccessTypeDefinition.hh"
#include "IIRScram_PhysicalUnit.hh"
#include "IIRScram_TypeDeclaration.hh"
#include "IIRScram_Identifier.hh"

#include <cstring>
#include <sstream>
using std::ostringstream;

symbol_table::symbol_table(StandardPackage *package, bool load_std_library){
  global_scope = new scope_entry( NULL, NULL );  
  current_scope = global_scope;
  std_package = package;

  if( load_std_library == true ){
    load_standard_library();
  }
}

symbol_table::symbol_table( int table_size, StandardPackage *package , bool load_std_library) : 
  visible_symbols(table_size), hidden_symbols(table_size){

  global_scope = new scope_entry( NULL, NULL ); 
  current_scope = global_scope;
  std_package = package;

  if( load_std_library == true ){
    load_standard_library();
  }
}

void 
symbol_table::load_standard_library(){
  //  ((IIR_TypeDefinition *)StandardPackage::savant_universal_integer)->_come_into_scope( this, 0 );
  //  ((IIR_TypeDefinition *)StandardPackage::savant_universal_real)->_come_into_scope( this, 0 );
//   bool old_val = debug_symbol_table;
//   debug_symbol_table = false;
  
  add_declaration( std_package->get_std_decl() );
  open_scope( std_package->get_std_decl() );
  add_declaration( std_package->get_std_standard_decl() );
  open_scope( std_package->get_std_standard_decl() );  
  add_declaration( std_package->get_std_standard_decl()->get_package_declarative_part() );
  close_scope( std_package->get_std_standard_decl() );  
  close_scope( std_package->get_std_decl() );  
  make_visible( std_package->get_std_standard_decl() );
  dynamic_cast<IIRScram_PackageDeclaration *>(std_package->get_std_standard_decl())->_make_interface_visible(this);
  
//   debug_symbol_table = old_val;
}

void 
symbol_table::add_subprogram_declaration( IIR_SubprogramDeclaration *decl_ptr,
					  bool leave_scope_open){
  add_declaration( decl_ptr );
  open_scope( decl_ptr );
  add_declaration( decl_ptr->get_interface_declarations());
  if( leave_scope_open == false ){
    close_scope( decl_ptr );
  }
}

void 
symbol_table::add_declaration( IIR_Declaration *decl_ptr ){
  IIRScram_Declaration *scram_decl = dynamic_cast<IIRScram_Declaration *>(decl_ptr);
  ASSERT( scram_decl != NULL );
  ASSERT( scram_decl->get_declaration_type() != IIR_Declaration::ERROR );
  //  ASSERT( decl_ptr->is_visible() == TRUE );
  
  if (debug_symbol_table) {
    cerr << this << " - adding declaration : |" << *scram_decl << "| - " << scram_decl;
  }

  IIR *current_declarative_region =  declarative_region_stack.get_top_of_stack();

  if( current_declarative_region != NULL && scram_decl->get_declarative_region() == NULL ){
    scram_decl->set_declarative_region( current_declarative_region );
  
    if( debug_symbol_table ){
      cerr << " - setting declarative region |";
      if( scram_decl->get_declarative_region() != NULL ){
	cerr << *scram_decl->get_declarative_region();
      }
      else{
	cerr << "NULL";
      }
      cerr << "|.";
    }
  }

  if( debug_symbol_table ){
    cerr << endl;
  }

  // Add the declaration to the list that are currently in scope...
  in_scope_list.append(decl_ptr);

  // Add the declaration to the list of its type that are in scope...
  in_scope_by_type[ scram_decl->get_declaration_type() ].append( decl_ptr );

  // Now, we need to add the declaration to the currently open scope.
  get_current_scope()->add_declaration( decl_ptr );

  visible_symbols.lookup_add( decl_ptr );
  scram_decl->_come_into_scope( this );
  
  if( dynamic_cast<IIR_LibraryUnit *>(scram_decl) != NULL ){
    library_manager::instance()->add_declaration( dynamic_cast<IIRScram_LibraryUnit *>(decl_ptr) );
  }
  if( scram_decl->is_incomplete_type_declaration() == TRUE ){
    get_incomplete_types()->add( dynamic_cast<IIR_TypeDeclaration *>(decl_ptr) );
  }
}

void 
symbol_table::add_declaration(IIR_DeclarationList *list_ptr) {
  ASSERT( list_ptr != NULL );
  IIR_Declaration *current_decl = dynamic_cast<IIR_Declaration *>(list_ptr->first());
  while( current_decl != NULL ){
    add_declaration( current_decl );
    current_decl = dynamic_cast<IIR_Declaration *>(list_ptr->successor( current_decl ));
  }
}

void 
symbol_table::add_declaration( savant::set<IIR_Declaration> *set_ptr ){
  ASSERT( set_ptr != NULL );

  IIR_Declaration *current_decl = set_ptr->getElement();
  while( current_decl != NULL ){
    add_declaration( current_decl );
    current_decl = set_ptr->getNextElement();
  }
}

void 
symbol_table::remove_from_visibility( IIR_Declaration *decl_ptr ){
  ASSERT( decl_ptr != NULL );
  ASSERT( decl_ptr->get_declaration_type() != IIR_Declaration::ERROR );
  
  if( debug_symbol_table == true ){
    cerr << this << " - Removing from visibility - |" << *decl_ptr << "| - " << decl_ptr << endl;
  }

  visible_symbols.lookup_remove( decl_ptr );
}

void 
symbol_table::remove_from_scope(IIR_Declaration *decl_ptr){
  IIRScram_Declaration *scram_decl = dynamic_cast<IIRScram_Declaration *>(decl_ptr);
  ASSERT( scram_decl != NULL );
  ASSERT( scram_decl->get_declaration_type() != IIR_Declaration::ERROR );

  if( debug_symbol_table == true ){
    cerr << this << " - Removing from scope - |" << *scram_decl << "| - " << scram_decl << endl;
  }
  
  remove_from_visibility( decl_ptr );
  scram_decl->_come_out_of_scope( this );
  
  in_scope_list.remove(decl_ptr);
  in_scope_by_type[ scram_decl->get_declaration_type() ].remove( decl_ptr );
  
  if( use_clause_entries.contains( decl_ptr ) ){
    use_clause_entries.remove( decl_ptr );
  }
}

 
void 
symbol_table::hide_declaration( IIR_Declaration *to_hide ){
  remove_from_visibility( to_hide );
}



bool
symbol_table::in_scope(IIR_Declaration *decl) {
  ASSERT( decl != NULL);
  ASSERT( decl->get_declarator() != NULL);

  return in_scope_by_type[ dynamic_cast<IIRScram_Declaration *>(decl)->get_declaration_type() ].in_list( decl );
}

bool
symbol_table::is_visible( IIR_Declaration *decl ){
  ASSERT( decl != NULL);
  ASSERT( decl->get_declarator() != NULL);

  // First look in the visibility list.
  savant::set<IIR_Declaration> *same_name_list = find_set( decl->get_declarator() );
  ASSERT( same_name_list != NULL );

  return same_name_list->contains( decl );
}

void 
symbol_table::open_scope( IIR *declarative_region ){
  scope_entry *new_scope =  current_scope->open_scope( declarative_region );
  current_scope = new_scope;

  if( declarative_region != NULL ){
    declarative_region_stack.push( declarative_region );
  }

  if (debug_symbol_table) {
    cerr << this << "- opening new scope ";
    if( declarative_region != NULL ){
      cerr << " - declarative region |" << *declarative_region << "|" << endl;
    }
    else{
      cerr << "NULL" << endl;
    }
  }  
}

void 
symbol_table::close_scope( IIR *declarative_region ){
  if( debug_symbol_table ) {
    cerr << this << " - closing scope";
  }
  
  IIR *decl_region = declarative_region_stack.pop();  
  ASSERT( decl_region == declarative_region );

  if( debug_symbol_table == TRUE ){
    if( decl_region != NULL ){
      cerr << " - popping declarative region |" << *decl_region << "|." << endl;
    }
    else{
      cerr << "NULL" << endl;
    }
  }

  // Because we're assured that _this_ is the deepest scope open, we know
  // we only need to pull out the declarations in this scope.  We can make some
  // assertions to be sure, however.
  ASSERT( current_scope != NULL );
  ASSERT( current_scope->get_owner() == decl_region );
  ASSERT( current_scope->get_scopes()->getElement() == NULL || 
	  current_scope->get_scopes()->getElement()->is_closed() == TRUE );
  
  IIR_Declaration *current = current_scope->get_declarations()->pop();
  while( current != NULL ){
    if( current->is_incomplete_type_declaration() == TRUE ){
      ASSERT( current->is_type_declaration() == TRUE );
      if( (dynamic_cast<IIRScram_TypeDeclaration *>(current))->_get_fully_defined_type() == NULL ){
	ostringstream err;
	err << "Type |" << *current << "| was defined as an incomplete type, but "
	    << "no full definition of it was found in this scope.";
	report_error( current, err.str() );
      }
    }
    remove_from_scope( current );
    current = current_scope->get_declarations()->pop();
  }
  
  current_scope->close_scope();
  current_scope = current_scope->get_previous_scope();
}

void 
symbol_table::reopen_scope( IIR *declarative_region ){
//   bool found_scope_marker = false;
//   IIR_Declaration *last = NULL;
  
//   // Walk the out of scope list backwards until we hit the first (in the
//   // list) declaration that came before this scope.  (I.e.  walk over all
//   // of the declarations in our scope.  When we've found _that_, then we
//   // need to walk forward again until we find the first declaration with
//   // that same scope as it's declarative region.  We have to do it this way
//   // since multiple scopes might have been opened/closed while the scope
//   // we're reopening was open.
//   IIR_Declaration *current = out_of_scope_list.last();
//   while( current != NULL ){
//     if( found_scope_marker == true ){
//       if( current->_get_declarative_region() != declarative_region ){
// 	// Move back up one.
// 	current = outsuccessor( current );
// 	break;
//       }
//     }
//     else{
//       if( current->_get_declarative_region() == declarative_region ){
// 	found_scope_marker = true;
//       }
//     }
//     current = out_of_scope_list.predecessor( current );
//   }

//   // So, we've walked backwards, and found the first declaration entered in
//   // this declarative region.  Now, we need to walk forwards until we found

  
//   // If current is NULL, something bad happened.  Either the symbol table
//   // mangled declarative regions, or someone asked to to reopen a
//   // non-existant scope.
//   ASSERT( current != NULL );

//   // So, "current" holds the _first_ declaration that we need to readd, and
//   // "last" holds the last.
//   while( current != last ){
//     out_of_scope_list.remove( current );
//     add_declaration( current );
//     current = out_of_scope_list.successor( current );
//     ASSERT( current != NULL );
//   }
//   // Add the last one.
//   out_of_scope_list.remove( current );
//   add_declaration( current );

}

IIR *
symbol_table::get_current_declarative_region(){
  return declarative_region_stack.get_top_of_stack();
}

void 
symbol_table::add_undefined( IIR_Char *name ){
  //	IIR_Declaration *undef_decl = new IIR_UndefinedDeclaration;
  //	undef_decl->name = new IIR_Identifier(); // : text_string(name);
  //	((IIR_Identifier *)undef_decl->name)->text_string = name;
  //	add_declaration( undef_decl );
}

void 
symbol_table::make_visible( IIR_Declaration *decl_ptr ){
  IIRScram_Declaration *scram_decl = dynamic_cast<IIRScram_Declaration *>(decl_ptr);
  ASSERT(scram_decl);
  if( scram_decl->_get_attribute_name() != NULL ){
    return;
  }

  if( debug_symbol_table ){
    cerr << this << " - making visible - |" << *scram_decl << "| - " << scram_decl << endl;
  }

  if( scram_decl->get_kind() == IIR_USE_CLAUSE ){
    scram_decl->_make_interface_visible( this );
  }
  
  // Since we're maintaining an out_of_scope list (temporarily), we 
  // need to take this declaration out of that list and put it back
  // in scope.
  if( scram_decl != NULL && scram_decl->_is_specification() == FALSE ){

    // First we'll make sure it's not already visible...
    if( is_visible( scram_decl ) == true ){
      if( debug_symbol_table == true ){
	cerr << this << "- it was already visible - returning!" << endl;
      }
      return;
    }

//     if( in_scope( decl_ptr ) == false ){
//       // Let's grab the out of scope symbol out of the list.
//       out_of_scope_list.remove( decl_ptr );
//       out_of_scope_by_type[ decl_ptr->_get_type() ].remove( decl_ptr );
//     }
    
    add_declaration( decl_ptr );


    if (scram_decl->get_kind() == IIR_TYPE_DECLARATION && scram_decl->is_enumeration_type() == TRUE ){
      IIR_EnumerationTypeDefinition *enum_type;
      IIR_EnumerationLiteral *lit;
      enum_type = dynamic_cast<IIR_EnumerationTypeDefinition *>((dynamic_cast<IIR_TypeDeclaration*>(decl_ptr))->get_type());
      for (lit = dynamic_cast<IIR_EnumerationLiteral *>(enum_type->get_enumeration_literals()->first());
	   lit != NULL;
	   lit = dynamic_cast<IIR_EnumerationLiteral *>(enum_type->get_enumeration_literals()->successor(lit))) {
	make_visible(lit);
      }
    }


    if( scram_decl->get_kind() == IIR_TYPE_DECLARATION && scram_decl->_is_physical_type() ){
      IIR_PhysicalTypeDefinition *physical_type =
	dynamic_cast<IIR_PhysicalTypeDefinition *>(scram_decl->_get_subtype());
      if( physical_type->get_primary_unit() != NULL ){
	make_visible( dynamic_cast<IIR_Declaration *>(dynamic_cast<IIRScram_PhysicalTypeDefinition *>(physical_type)->_get_primary_unit()) );
      }
      make_visible( dynamic_cast<IIR_DeclarationList *>(physical_type->get_units()) );
    }
  }
}

void 
symbol_table::make_visible( IIR_DeclarationList *decl_list ){
  if( decl_list != NULL ){
    IIR_Declaration *current = dynamic_cast<IIR_Declaration *>(decl_list->first());
    while( current != NULL ){
      make_visible( current );
      current = dynamic_cast<IIR_Declaration *>(decl_list->successor( current ));
    }
  }
}

void 
symbol_table::make_visible( savant::set<IIR_Declaration> *decl_set ){
  if( decl_set != NULL ){
    IIR_Declaration *current = decl_set->getElement();
    while( current != NULL ){
      make_visible( current );
      current = decl_set->getNextElement();
    }
  }
}


void 
symbol_table::add_to_use_list( IIR_Declaration *declaration ){
  ASSERT( use_clause_entries.contains( declaration ) == FALSE );
  use_clause_entries.add( declaration );
}

bool 
symbol_table::in_use_list( IIR_Declaration *to_find ){
  return use_clause_entries.contains( to_find );
}

void 
symbol_table::incomplete_type_fixup( IIR_TypeDeclaration *old_incomplete_type,
				     IIR_TypeDeclaration *new_complete_type ){
  ASSERT( new_complete_type != NULL );
  ASSERT( new_complete_type->get_type() != NULL );
  
  incomplete_types.remove( old_incomplete_type );

  // This new type declaration satisifies an incomplete type!  Now we
  // need to go through the list of access types that were designating
  // this incomplete type, and point them at this new one.  When we're
  // done, we can remove this incomplete type from our list.
  IIR_TypeDeclaration *current_access_type_declaration = designates_incomplete_type.getElement();
  while( current_access_type_declaration != NULL ){
    ASSERT(dynamic_cast<IIRScram_TypeDeclaration *>(current_access_type_declaration)->_designates_incomplete_type() == TRUE );
    //    ASSERT(dynamic_cast<IIRScram_TypeDeclaration *>(current_access_type_declaration)->_get_type()->_is_iir_access_type_definition() == TRUE);
    
    IIR_AccessTypeDefinition *access_type = 
      dynamic_cast<IIR_AccessTypeDefinition *>(current_access_type_declaration->get_type());
    ASSERT( dynamic_cast<IIRScram_AccessTypeDefinition *>(access_type)->_get_designated_type()->is_incomplete_type_definition() == TRUE );
    
    IIR_IncompleteTypeDefinition *current_type_definition =
      dynamic_cast<IIR_IncompleteTypeDefinition *>(access_type->get_designated_type());      
    if( IIRBase_TextLiteral::cmp( new_complete_type->get_declarator(),
                                  current_type_definition->get_designated_type_name() ) == 0 ) {
      access_type->set_designated_type( new_complete_type->get_type() );	
      designates_incomplete_type.remove( current_access_type_declaration ); 
    }
    current_access_type_declaration = designates_incomplete_type.getNextElement();
  }

  dynamic_cast<IIRScram_TypeDeclaration *>(old_incomplete_type)->_set_fully_defined_type( dynamic_cast<IIRScram_TypeDefinition *>(new_complete_type->get_type()) );
  
  // The following code handles this case:
  // type a;
  // type a is access a;
  //       delete old_incomplete_type->get_type();
  if( dynamic_cast<IIRScram_TypeDeclaration *>(new_complete_type)->is_access_type() ){
    IIR_AccessTypeDefinition *access_type = 
      dynamic_cast<IIR_AccessTypeDefinition *>( new_complete_type->get_type() );
    if( access_type->get_designated_type() == old_incomplete_type->get_type() ){
      access_type->set_designated_type( new_complete_type->get_type() );
    }
  }
}

