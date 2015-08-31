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
//          Malolan Chetlur     mal@ece.uc.edu
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_DesignFile.hh"
#include "IIRScram_FunctionCall.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_LibraryDeclaration.hh"
#include "IIRScram_SimpleName.hh"
#include "IIRScram_SubprogramDeclaration.hh"
#include "IIRScram_TypeDefinition.hh"

#include "error_func.hh"
#include "resolution_func.hh"
#include "set.hh"
#include "symbol_table.hh"
#include "savant.hh"

#include <sstream>
using std::ostringstream;
using savant::set;

IIRScram_SimpleName::~IIRScram_SimpleName() {}

set<IIRScram_Declaration> *
IIRScram_SimpleName::_symbol_lookup() {
  set<IIRScram_Declaration> *retval = NULL;

  IIRScram *prefix = _get_prefix();
  if( prefix->_is_iir_declaration() == true ){
    retval = new set<IIRScram_Declaration>( dynamic_cast<IIRScram_Declaration *>(prefix) );
  }
  else if( prefix->is_text_literal() == TRUE ){
    set<IIR_Declaration> *decls= new set<IIR_Declaration>(*_get_symbol_table()->find_set( get_prefix_string()));
    retval = decls->convert_set<IIRScram_Declaration>();
    delete decls;
    if( IIRBase_TextLiteral::cmp( get_prefix_string(), "work" ) == 0 ){
      retval->add( _get_work_library() );
    }
  }
  else{
    cerr << "Error in IIRScram_SimpleName::_symbol_lookup() - "
	 << " don't know how to resolve a " << prefix->get_kind_text()
	 << endl;

    abort();
  }
  return retval;
}


set<IIRScram_Declaration> *
IIRScram_SimpleName::_symbol_lookup( set<IIRScram_Declaration> *set_to_look_in ) {
  set<IIRScram_Declaration> *retval = new set<IIRScram_Declaration>;

  IIRScram_Declaration *current_decl = set_to_look_in->getElement();
  while( current_decl != NULL ){
    set<IIRScram_Declaration>   *found = NULL;
    set<IIR_Declaration>        *temp_set 
      = current_decl->find_declarations( this );

    if ( temp_set != NULL ) {
      found = temp_set->convert_set<IIRScram_Declaration>();
      delete temp_set;
    }

    if( found != NULL ){
      retval->add( found );
    }
    current_decl = set_to_look_in->getNextElement();
  }

  if ( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }
  
  return retval;
}

set<IIRScram_TypeDefinition> *
IIRScram_SimpleName::_get_rval_set(constraint_functor *functor) {
  set<IIRScram_TypeDefinition> *retval = NULL;

  // Get the set of declarations that correspond to our name, and then
  // get all of their RVALS.
  set<IIRScram_Declaration> *decl_set = _symbol_lookup();
  if( decl_set != NULL ){
    retval = decl_set_to_typedef_set( decl_set, functor );
  }
  return retval;
}


void 
IIRScram_SimpleName::_type_check( set<IIRScram_TypeDefinition> * ){}

IIRScram *
IIRScram_SimpleName::_rval_to_decl(IIRScram_TypeDefinition *my_rval) {
  IIRScram              *retval = NULL;
  
  set<IIRScram_Declaration> *my_decls = _symbol_lookup();
  if( my_decls == NULL ){
    ostringstream err;
    err << "Internal error in IIRScram_SimpleName::_rval_to_decl - no declaration for |"
	<< *this << "| found.";
    report_error( this, err.str() );
    return this;
  }

  set<IIRScram_Declaration> *possibilities = new set<IIRScram_Declaration>;
  IIRScram_Declaration *current_decl = my_decls->getElement();
  while( current_decl != NULL ){
    if ( (current_decl->_get_subtype() != NULL  
	  && current_decl->_get_subtype()->is_compatible( my_rval ) != NULL ) && 
	  (current_decl->is_subprogram() == FALSE || 
	   (dynamic_cast<IIRScram_SubprogramDeclaration *>(current_decl))->_num_required_args() == 0 )) {
      possibilities->add( current_decl );
    }
    current_decl = my_decls->getNextElement();
  }

  // In the case of:
  // constant V1: I1 := 1;
  //    constant V2: I2 := 20;
  //    type I5 is range V1 to V2;
  // We have a situation where V1 isn't compatible with I5.  The following snippet
  // basically says, "if you didn't find a compatible match, go with an incompatible
  // match.  There's got to be a better way to do this though.
  if( possibilities->size() == 0 ){
    current_decl = my_decls->getElement();
    while( current_decl != NULL ){
      if ( current_decl->is_subprogram() == FALSE || 
	   (dynamic_cast<IIRScram_SubprogramDeclaration *>(current_decl))->_num_required_args() == 0 ) {
	possibilities->add( current_decl );
      }
      current_decl = my_decls->getNextElement();
    }
  }

  delete my_decls;  

  switch( possibilities->size() ){
  case 0:{
    ostringstream err;
    err << "Internal error in IIRScram_SimpleName::_rval_to_decl - zero possibilities"
	<< " found for |" << *this << "|.";
    report_error( this, err.str() );
    abort();
    break;
  }
  case 1:{
    retval = possibilities->getElement();
    retval = _convert_to_function_call( dynamic_cast<IIRScram_Declaration *>(retval) );
    break;
  }
  default:{
    ostringstream err;
    err << "Internal error in IIRScram_SimpleName::_rval_to_decl - multiple possibilities"
	<< " found for |" << *this << "|.";
    report_error( this, err.str() );
    report_ambiguous_error( this, possibilities->convert_set<IIR_Declaration>() );
    abort();
  }
  }

  return retval;
}


IIRScram *
IIRScram_SimpleName::_decl_to_decl( IIRScram_Declaration *my_decl ){
  IIRScram *retval = _convert_to_function_call( my_decl );
  delete this;
  return retval;
}


IIRScram_TextLiteral *
IIRScram_SimpleName::_get_string(){
  return dynamic_cast<IIRScram_TextLiteral *>(get_prefix());
}


const string
IIRScram_SimpleName::convert_to_library_name() {
  ASSERT( _get_prefix() != NULL );
  return _get_prefix()->convert_to_library_name(); 
}


IIRScram *
IIRScram_SimpleName::_rval_to_decl( IIRScram_TypeDefinition *prefix, IIRScram_TypeDefinition *suffix ){
  IIRScram *retval = NULL;

  set<IIRScram_Declaration>     *decls = NULL;
  set<IIR_Declaration>          *temp_set 
    = prefix->find_declarations( this );

  if ( temp_set != NULL) {
    decls = temp_set->convert_set<IIRScram_Declaration>();
    delete temp_set;
  }

  ASSERT( decls != NULL );
  ASSERT( decls->size() == 1 );
  
  IIRScram_Declaration *decl = decls->getElement();
  delete decls;

  ASSERT( decl->_get_subtype()->is_compatible( suffix ) != NULL );
  retval = _convert_to_function_call( decl );

  return retval;
}


IIRScram *
IIRScram_SimpleName::_rval_to_decl( IIRScram_Declaration *prefix, IIRScram_TypeDefinition *suffix ){
  IIRScram *retval = NULL;

  set<IIRScram_Declaration>     *decls = NULL;
  set<IIR_Declaration>          *temp_set 
    = prefix->find_declarations( this );

  if ( temp_set != NULL ) {
    decls = temp_set->convert_set<IIRScram_Declaration>();
    delete temp_set;
  }

  ASSERT( decls != NULL );
  ASSERT( decls->size() == 1 );
  
  IIRScram_Declaration *decl = decls->getElement();
  delete decls;
  
  ASSERT( decl->_get_subtype()->is_compatible( suffix ) != NULL );
  retval = _convert_to_function_call( decl );

  return retval;
}


IIRScram_TypeDefinition *
IIRScram_SimpleName::_determine_rval_in_set( set<IIRScram_TypeDefinition> *search_in,
					     IIRScram_TypeDefinition *looking_for ){

  IIRScram_TypeDefinition *current_outer = search_in->getElement();
  while( current_outer != NULL ){
    set<IIRScram_Declaration>   *decls = NULL;
    set<IIR_Declaration>        *temp_set 
      = current_outer->find_declarations( this );
    
    if ( temp_set != NULL ) {
      decls = temp_set->convert_set<IIRScram_Declaration>();
      delete temp_set;
    }

    if( decls != NULL ){
      IIRScram_Declaration *current_inner = decls->getElement();
      while( current_inner != NULL ){
	if( current_inner->_get_subtype()->is_compatible( looking_for ) != NULL ){
	  delete decls;
	  return current_outer;
	}
	current_inner = decls->getNextElement();
      }
    }
    current_outer = search_in->getNextElement();
  }

  // If we made it here, something bad happened...
  ostringstream err;
  err << "Internal error in IIRScram_SimpleName::_determine_rval_in_set - no possiblilites found.";
  report_error( this, err.str() );
  return 0;
}


IIRScram_Declaration *
IIRScram_SimpleName::_determine_decl_in_set( set<IIRScram_Declaration> *search_in,
					     IIRScram_TypeDefinition *looking_for ){
  IIRScram_Declaration  *current_outer = search_in->getElement();

  while( current_outer != NULL ){
    set<IIRScram_Declaration>   *decls = NULL;
    set<IIR_Declaration>        *temp_set 
      = current_outer->find_declarations( this );

    if ( temp_set != NULL ) {
      decls = temp_set->convert_set<IIRScram_Declaration>();
      delete temp_set;
    }

    if( decls != NULL ){
      IIRScram_Declaration *current_inner = decls->getElement();
      while( current_inner != NULL ){
	if( current_inner->_get_subtype()->is_compatible( looking_for ) != NULL ){
	  delete decls;
	  return current_outer;
	}
	current_inner = decls->getNextElement();
      }
    }
    current_outer = search_in->getNextElement();
  }

  // If we made it here, something bad happened...
  ostringstream err;
  err << "Internal error in IIRScram_SimpleName::_determine_rval_in_set - no possiblilites found.";
  report_error( this, err.str() );
  return 0;
}


IIRScram *
IIRScram_SimpleName::_clone(){
  IIRScram_SimpleName *retval = new IIRScram_SimpleName();
  IIRScram_Name::_clone( retval );
  return retval;
}

IIRScram *
IIRScram_SimpleName::_convert_to_function_call( IIRScram_Declaration *my_decl ){
  ASSERT( my_decl != NULL );
  IIRScram *retval = my_decl;

  if( retval->get_kind() == IIR_FUNCTION_DECLARATION ){
    // This assertion isn't true in the case of an attribute of a function.
    // i.e. function foo( x : integer )
    // foo'bar
    //    ASSERT( (dynamic_cast<IIRScram_Declaration *>(retval)->_num_required_args() == 0 );
    // In this very special case, after the function declaration get's converted into
    // a function call, the caller will have to convert it _back_!
    IIRScram_FunctionCall *new_retval = new IIRScram_FunctionCall();
    copy_location( this, new_retval );
    new_retval->set_implementation( dynamic_cast<IIRScram_SubprogramDeclaration *>(retval) );
    IIRScram_TypeDefinition *my_rval = retval->_get_subtype();
    
    retval = new_retval->_semantic_transform( my_rval );
    retval->_type_check( my_rval );
    retval = retval->_rval_to_decl( my_rval );
  }

  return retval;
}

visitor_return_type *
IIRScram_SimpleName::_accept_visitor( node_visitor *visitor, 
				      visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_SimpleName(this, arg);
}
