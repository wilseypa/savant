
#ifndef SYMBOL_LOOKUP_HH
#define SYMBOL_LOOKUP_HH

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

#include "savant_config.hh"
#include "savant.hh"
#include <iostream>
#include "declaration_chain.hh"

class IIR_Declaration;
class IIR_TextLiteral;
class hidden_symbol_entry;
class declaration_chain;
class StandardPackage;

namespace savant {
  template <class type> class set;
}

extern bool debug_symbol_table;

class symbol_lookup {

  // This file contains the declaration of the class defining the symbol
  // table for the SAVANT VHDL analyzer.  The symbol_lookup type implements
  // a hash table functionality.
  
  friend ostream &operator<<(ostream &, symbol_lookup &);
  
public:
  // These methods take their given arguments and add them to the symbol
  // table.
  void lookup_add( IIR_Declaration * );
  void lookup_remove( IIR_Declaration * );
  
  // This method returns the list of declarations for a given symbol
  // name.  NOTE:  The list returned is a persistent list within
  // the symbol_lookup class.  Don't modify the list it points at! 
  // NOTE2:  Since the list is persistent, any calls to methods
  // _INCLUDING_ find_list can and will modify the list pointed too.
  savant::set<IIR_Declaration> *find_set( IIR_TextLiteral * );
  savant::set<IIR_Declaration> *find_set( char * );
  
  symbol_lookup(int table_size = 4093) : ht_size(table_size) {
    ht = new dl_list<declaration_chain>[ht_size];
  };
  
  virtual ~symbol_lookup() {   
    delete [] ht;
  };

  // this is for debug only
  void dump_usage_stats(char *filename = "usage_stats");

  // Return true if this declaration is currently visible.  False
  // otherwise.
  IIR_Boolean is_visible( IIR_Declaration * );
  
private:

  // This method either returns NULL, or returns a set of declarations that
  // should be hidden before adding the next declaration to the hash table.
  // It can be a set of declarations to hide, as opposed to only a single
  // declaration, because there can be a _set_ of functions hidden by a
  // single constant, for instance.
  savant::set<IIR_Declaration> *build_hidden_declaration_set( IIR_Declaration *about_to_add );

  // This method returns a hidden symbol entry for the declaration passed
  // in. If this declaration isn't currently hiding any other declarations,
  // then it will return NULL.
  hidden_symbol_entry *find_hidden_symbol_entry( IIR_Declaration *, 
						 declaration_chain * );
  
  // This method updates the hidden symbol information for the declaration
  // passed in.  The entry is modified to contain the set of hidden
  // declarations.  If the set that is passed in is NULL, then the hidden
  // symbol entry for this declaration will be removed, and its hidden set
  // deleted.
  void update_hidden_symbol_entry( IIR_Declaration *, 
				   savant::set<IIR_Declaration> *, 
				   declaration_chain * );

  // These methods find the declaration chain for the name passed in.
  declaration_chain *find_chain( IIR_TextLiteral * );
  declaration_chain *find_chain( char * );


  const int ht_size;
  dl_list<declaration_chain> *ht;
  
  // calculate a hash value for the string passed in
  int calculate_hash( IIR_TextLiteral * );
};   

#endif
