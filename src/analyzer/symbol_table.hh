
#ifndef SYMBOL_TABLE_HH
#define SYMBOL_TABLE_HH

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

// Authors: Dale E. Martin          dmartin@cliftonlabs.com
//          Timothy J. McBrayer     tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "dl_list.hh"
#include "symbol_lookup.hh"
#include "stack.hh"
#include "set.hh"
#include "stack.hh"
#include "IIRScram_TypeDeclaration.hh"
#include "IIRScram_Declaration.hh"
#include "IIR_Declaration.hh"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

class IIR_DeclarationList;
class IIR_PortList;
class IIR_GenericList;
class IIR_ArrayTypeDefinition;
class IIR_RecordTypeDefinition;
class IIR_AccessTypeDefinition;
class IIR_SubprogramDeclaration;
class StandardPackage;
extern bool debug_symbol_table;

// This class defines a scope in the symbol table
class scope_entry {
public:
  scope_entry( scope_entry *previous_scope, IIR *scope_owner ){
    belongs_to = scope_owner;
    declarations = new stack<IIR_Declaration>;
    scopes = new savant::set<scope_entry>;
    open = TRUE;
    previous = previous_scope;
  }
  
  void add_declaration( IIR_Declaration *to_add ){
    ASSERT( open == TRUE );
    declarations->push( to_add );
  }

  scope_entry *open_scope( IIR *to_add ){
    scope_entry *retval = new scope_entry( this, to_add );
    ASSERT( open == TRUE );
    scopes->add( retval );

    return retval;
  }

  IIR *get_owner(){
    return belongs_to;
  }

  savant::set<scope_entry> *get_scopes(){
    return scopes;
  }

  stack<IIR_Declaration> *get_declarations(){
    return declarations;
  }
  
  scope_entry *get_previous_scope(){
    return previous;
  }

  void close_scope(){
    open = FALSE;
  }

  IIR_Boolean is_closed(){
    switch( open ){
    case TRUE:{
      return FALSE;
    }
    case FALSE:{
      return TRUE;
    }
    default:{
      ASSERT( 0 );
    }
    }
    return FALSE;
  }

private:
  IIR *belongs_to;
  stack<IIR_Declaration> *declarations;
  savant::set<scope_entry> *scopes;
  IIR_Boolean open;
  scope_entry *previous;
};

class symbol_table {

public:
  /** Constructor */
  symbol_table(StandardPackage *package, bool load_std_library = true );

  /** Constructor */
  symbol_table( int table_size, StandardPackage *package, bool load_std_library = true );
  
  /** Destructor */
  ~symbol_table(){
    if( debug_symbol_table == true ){
      if (in_scope_list.num_elements() != 0){
	cout << "in_scope_list not empty at symbol table destruction:\n";
	cout << "(There are " << in_scope_list.num_elements()
	  << " left in it:)\n";
        // TODO: Remove Scram
	IIRScram_Declaration *current = dynamic_cast<IIRScram_Declaration *>(in_scope_list.first());
	while( current != NULL ){
	  cout << *current << endl;
	  current = dynamic_cast<IIRScram_Declaration *>(in_scope_list.successor( current ));
	}
      }
    }
  }

  //@{
  //** Methods to add new declarations... */
  void add_subprogram_declaration( IIR_SubprogramDeclaration *, bool leave_scope_open = false );
  void add_declaration(IIR_Declaration *);
  void add_declaration(IIR_DeclarationList *);
  void add_declaration( savant::set<IIR_Declaration> *set_ptr);
  //@}

  /** If this declaration is still in scope, but hidden, call this. */
  void remove_from_visibility(IIR_Declaration *);

  /** If this declaration is going out of scope, call this. */
  void remove_from_scope(IIR_Declaration *);

  void hide_declaration( IIR_Declaration * );

  /** Method which returns 'true' if the argument is in the symbol_table
      and is currently in scope. */
  bool in_scope( IIR_Declaration * );
  
  /** Method that returns 'true' if the argument is visible in the symbol
      table right now. */
  bool is_visible( IIR_Declaration * );

  /** This method takes a symbol that's already been declared and makes it
      visible again. */
  void make_visible( IIR_Declaration *);

  //@{
  /** These methods make the walking of several types of lists a little
      nice. */
  void make_visible( IIR_DeclarationList *);
  void make_visible( savant::set<IIR_Declaration> *);
  //@}

  /** Method to add entry for undefined symbols (to avoid flagging
      undefined things more than once.) */
  void add_undefined( IIR_Char *);

  //@{
  /** Methods to deal with scope */
  void open_scope( IIR *declarative_region );
  void close_scope( IIR *declarative_region );
  //@}

  /** This method takes an out of scope symbol, and reenters all symbols
      found in the "out of scope list" back into scope up until the next
      "live" scope marker. */
  void reopen_scope( IIR *declarative_region );

  IIR *get_current_declarative_region();

  //@{
  /** The following methods return the set of declarations with the name
      passed in.  If non exists, it returns NULL. */
  savant::set<IIR_Declaration> *find_set( char *to_find ){
    return visible_symbols.find_set( to_find );
  }
  savant::set<IIR_Declaration> *find_set( IIR_TextLiteral *to_find ){
    return visible_symbols.find_set( to_find );
  }  
  //@}

  /** We have an array of lists for each type of declaration defined in LRM
      as an entity class.  Conveniently enough, these types are define in
      sym_tab_declaration as the enumerated type "declaration_type". */
  dl_list<IIR_Declaration> 
  in_scope_by_type[IIR_Declaration::LAST_DECLARATION_TYPE];
  
  //@{
  /** Keep track of what files are being used in use clauses.  This way we
      know whether to rescan them or not if encountered multiple times in a
      file. */
  void add_to_use_list( IIR_Declaration * );
  bool in_use_list( IIR_Declaration * );
  //@}

  savant::set<IIR_ArrayTypeDefinition> *get_in_scope_array_types(){
    return &in_scope_array_types;
  }

  savant::set<IIR_ArrayTypeDefinition> *get_in_scope_one_d_array_types(){
    return &in_scope_one_d_array_types;
  }
  
  savant::set<IIR_AccessTypeDefinition> *get_in_scope_access_types(){
    return &in_scope_access_types;
  }

  savant::set<IIR_RecordTypeDefinition> *get_in_scope_record_types(){
    return &in_scope_record_types;
  }

  savant::set<IIR_TypeDeclaration> *get_incomplete_types(){
    return &incomplete_types;
  }

  savant::set<IIR_TypeDeclaration> *get_designates_incomplete_type(){
    return &designates_incomplete_type;
  }

  void incomplete_type_fixup( IIR_TypeDeclaration *old_incomplete_type,
			      IIR_TypeDeclaration *new_complete_type );
  
private:
  /** This is the table of visible symbols. */
  symbol_lookup visible_symbols;

  /** This is the table of hidden symbols. */
  symbol_lookup hidden_symbols;

  /** This is the list of declarations that are currently in scope. */
  dl_list<IIR_Declaration> in_scope_list;

  scope_entry *current_scope;
  scope_entry *get_current_scope(){
    return current_scope;
  }

  scope_entry           *global_scope;
  StandardPackage       *std_package;

  /** This is a list of filenames that we've been told we've scanned in use
      clauses. */
  savant::set<IIR_Declaration> use_clause_entries;

  savant::set<IIR_TypeDeclaration> incomplete_types;
  savant::set<IIR_TypeDeclaration> designates_incomplete_type;

  savant::set<IIR_AccessTypeDefinition> in_scope_access_types;
  savant::set<IIR_ArrayTypeDefinition> in_scope_array_types;
  savant::set<IIR_ArrayTypeDefinition> in_scope_one_d_array_types;
  savant::set<IIR_RecordTypeDefinition> in_scope_record_types;
  
  stack<IIR> declarative_region_stack;

  void load_standard_library();
};
#endif
