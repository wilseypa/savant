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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------
#include "IIRScram_TextLiteral.hh"
#include "IIRScram_AccessSubtypeDefinition.hh"
#include "IIRScram_ArrayTypeDefinition.hh"
#include "IIRScram_Name.hh"

#include "resolution_func.hh"

#include "symbol_table.hh"
#include <cctype>
#include "constraint_functors.hh"

IIRScram_TextLiteral::IIRScram_TextLiteral(){}

IIRScram_TextLiteral::~IIRScram_TextLiteral(){}

void 
IIRScram_TextLiteral::_to_lower(){
  const string &my_string = get_text();
  int my_len = get_text_length();
  
  string tmp_buf = my_string;
  int i;
  for( i = 0; i < my_len; i++ ){
    tmp_buf[i] = (char)tolower( my_string[i] );
  }

  set_text( tmp_buf.c_str(), my_len );
}

savant::set<IIRScram_Declaration> *
IIRScram_TextLiteral::_symbol_lookup(){
  savant::set<IIRScram_Declaration> *retval;

  retval = new savant::set<IIRScram_Declaration>(*(( _get_symbol_table()->find_set( dynamic_cast<IIRScram_TextLiteral *>(this) ))->convert_set<IIRScram_Declaration>()));

  return retval;
}


savant::set<IIRScram_Declaration> *
IIRScram_TextLiteral::_symbol_lookup(constraint_functor *functor){
  return IIRScram::_symbol_lookup( functor );
}


savant::set<IIRScram_TypeDefinition> *
IIRScram_TextLiteral::_get_rval_set(constraint_functor *functor) {
  savant::set<IIRScram_TypeDefinition> *retval = NULL;

  // Get the set of declarations that correspond to our name, and then
  // get all of their RVALS.
  savant::set<IIRScram_Declaration> *decl_set = _symbol_lookup();

  retval = decl_set_to_typedef_set( decl_set, functor );
  delete decl_set;

  return retval;
}


savant::set<IIRScram_TypeDefinition> *
IIRScram_TextLiteral::_get_rval_set_for_string(){
  savant::set<IIRScram_TypeDefinition> *retval = NULL;

  int my_length = get_text_length();
  // A string literal can be a constant initializer for an array of
  // enumeration literals.  We'll look up each of the elements, and if
  // they are enumeration literals, we'll get the enumeration type they
  // belong to, and it it to the return set.  Also, we store the quotes in
  // the string..  So we need to start at 1, and end at length - 1.
  char delimiter;

  int start = 0;
  int i;
  for( i = 0 ; i < my_length; i++ ){
    if ( operator[](i) == '"' ){
      delimiter = '"';
      break;
    }
    else if (  operator[](i) == '%' ){
      delimiter = '%';
      break;
    }
  }
  
  start = i + 1;
  ASSERT( start < my_length );  
  retval = _get_symbol_table()->get_in_scope_array_types()->convert_set<IIRScram_TypeDefinition>();

  constraint_functor *functor = new is_character_type_functor();
  retval->reduce_set( functor );
  delete functor;
  
  if ( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }

  return retval;
}
