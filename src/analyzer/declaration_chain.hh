
#ifndef DECLARATION_CHAIN_HH
#define DECLARATION_CHAIN_HH

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
#include "IIR_Declaration.hh"
#include "set.hh"
#include "IIR_TextLiteral.hh"
#include "IIRScram_Declaration.hh"

using namespace savant;

// This class encapsulates an entry of a single declaration in the symbol
// table.  If one symbol hides another when it's added, this information
// necessarily needs to live in the symbol table and it's here that it's
// kept.
class hidden_symbol_entry{
public:
  hidden_symbol_entry( IIR_Declaration *init_declaration, 
		       savant::set<IIR_Declaration> *init_hidden ){
    my_declaration = init_declaration;
    hidden_declarations = init_hidden;
  }

  ~hidden_symbol_entry(){ delete hidden_declarations; }

  IIR_Declaration *get_declaration(){ return my_declaration; }
  savant::set<IIR_Declaration> *get_hidden_declarations(){ return hidden_declarations; }

private:
  IIR_Declaration *my_declaration;
  savant::set<IIR_Declaration> *hidden_declarations;
};

class declaration_chain {

  // This file holds the declaration of a class used in the symbol table
  // management for the savant project.  This class encapsulates a string
  // with a list of pointers to declarations of "declarable things" of
  // VHDL.  For instance, there might be a signal "x" and a variable "x" in
  // the same entity.  In this case, the declaration_chain would have a
  // string "x" and a two elements.
  
  // In addition, each declartion chain keeps a set of hidden declaration
  // information.  The data in this set is somewhat redundant in that when
  // one declaration is hiding another there will be two pointers to a
  // single declaration in one chain.  However, the most frequent operation
  // on the symbol lookup is to retrieve the set of declarations in a
  // chain, so we're going to live with a replicated pointer in order to
  // keep lookups speedy.

public:

  IIR_TextLiteral *name;
  savant::set<IIR_Declaration> declarations;
  savant::set<hidden_symbol_entry> hidden_declaration_info;
  
  declaration_chain() {
    // this is for safety's sake
    name = NULL;
  };
  
  ~declaration_chain() {};

};

inline ostream &operator<< (ostream &os, declaration_chain &dc) {

//  os << "name: " << dc.name << " list_size: " 
//    << dc.declaration_list.num_elements();

    os << "name: \"" << dc.name << "\"";

    IIR_Declaration *current_declaration = dc.declarations.getElement();

    while( current_declaration != NULL ) {
      os << " " << *dynamic_cast<IIRScram_Declaration *>(current_declaration);
      current_declaration = dc.declarations.getNextElement();
    }

    return os;
}
#endif

