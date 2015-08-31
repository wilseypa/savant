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
//          Umesh Kumar V. Rajasekaran urajaske@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Timothy J. McBrayer tmcbraye@ececs.uc.edu
//          Swaminathan Subramanian ssubrama@ececs.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_ConcurrentStatement.hh"
#include "IIRScram_Declaration.hh"
#include "IIRScram_DesignatorExplicit.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_Name.hh"
#include "IIRScram_TypeDefinition.hh"

#include "set.hh"
using savant::set;
using std::cerr;
using std::endl;

//This function is used to publish the type of the
//name, i.e.
// Signal a: bitvector(1, to 3),
// then a(3) has the type bit.
//Currently this need is in the elaboration code
//presume needed in future
//#####This function needs a lot of work and thought

void 
IIRScram_Name::set_subtype( IIR_TypeDefinition * ){
  _report_undefined_scram_fn("set_subtype");
}

set<IIRScram_Declaration> *
IIRScram_Name::_symbol_lookup(){
  _report_undefined_scram_fn("_symbol_lookup()");
  return NULL;
}

set<IIRScram_Declaration> *
IIRScram_Name::_symbol_lookup( IIRScram_Declaration *decl ){
  set<IIR_Declaration> *decls = decl->find_declarations( dynamic_cast<IIRScram_Name *>(this) );
  
  if (decls == NULL)
    return NULL;
  else 
    return decls->convert_set<IIRScram_Declaration>();
}

set<IIRScram_Declaration> *
IIRScram_Name::_symbol_lookup( set<IIRScram_Declaration> * ){
  _report_undefined_scram_fn("_symbol_lookup( set<IIRScram_Declaration> *");
  
  return NULL;
}

set<IIRScram_Declaration> *
IIRScram_Name::_symbol_lookup( constraint_functor *functor ){
  return IIRScram::_symbol_lookup( functor );
}

IIRScram_TextLiteral *
IIRScram_Name::_get_string(){
  _report_undefined_scram_fn("IIRScram_TextLiteral *_get_string()");
  
  return NULL;
}

set<IIRScram_TypeDefinition> *
IIRScram_Name::_get_rval_set( set<IIRScram_TypeDefinition> *search_in,
			      constraint_functor * ){
  ASSERT( search_in != NULL );

  set<IIRScram_TypeDefinition> *retval = new set<IIRScram_TypeDefinition>;
  
  IIRScram_TypeDefinition *current = search_in->getElement();
  while( current != NULL ){
    set<IIRScram_Declaration> *found = NULL;

    if ( current->find_declarations( dynamic_cast<IIRScram_Name *>(this) ) != NULL ) {
      found = current->find_declarations( dynamic_cast<IIRScram_Name *>(this) )->convert_set<IIRScram_Declaration>();
    }

    if( found != NULL ){
      IIRScram_Declaration *symbol = found->getElement();
      while( symbol != NULL ){
	if( symbol != NULL ){
	  retval->add( symbol->_get_subtype() );
	}
	symbol = found->getNextElement();
      }
      delete found;
    }
    current = search_in->getNextElement();
  }

  if( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }

  return retval;
}

set<IIRScram_TypeDefinition> *
IIRScram_Name::_get_rval_set( set<IIRScram_Declaration> *search_in,
			      constraint_functor * ){
  ASSERT( search_in != NULL );

  set<IIRScram_TypeDefinition> *retval = new set<IIRScram_TypeDefinition>;
  
  IIRScram_Declaration *current = search_in->getElement();
  while( current != NULL ){
    set<IIR_Declaration> *found1 = current->find_declarations(this);
    set<IIRScram_Declaration> *found2 = 0;
    if( found1 ) {
      found2 = found1->convert_set<IIRScram_Declaration>();
      delete found1;
    }

    if( found2 != NULL ){
      IIRScram_Declaration *symbol = found2->getElement();
      while( symbol != NULL ){
	if( _get_suffix() != NULL ){
	  set<IIRScram_Declaration> temp_set( symbol );
	  retval->add( _get_suffix()->_get_rval_set( &temp_set ) );
	}
	else{
	  retval->add( symbol->_get_subtype() );
	}
	symbol = found2->getNextElement();
      }
      delete found2;
    }
    current = search_in->getNextElement();
  }

  if( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }

  return retval;
}

void 
IIRScram_Name::_set_suffix(IIRScram *){
  _report_undefined_scram_fn("_set_suffix");
}

void
IIRScram_Name::_clone( IIRScram *clone ){
  ASSERT( clone->_is_iir_name() == TRUE );
  IIRScram_Name *as_name = dynamic_cast<IIRScram_Name *>(clone);
  IIRScram::_clone(clone);

  as_name->set_prefix( _get_prefix()->_clone() );
}

void 
IIRScram_Name::_build_lib( IIRScram_LibraryUnit * ){
  _report_undefined_scram_fn("IIRScram_Name::_build_lib");
}

visitor_return_type *IIRScram_Name::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_Name(this, arg);
};

IIRScram **
IIRScram_Name::lookup( IIRScram_Name *,
		       IIR_Int32 &,
		       IIRScram *& ){
  IIRScram** return_array = NULL;
  cerr << "IIRBase_Name::lookup(IIRScram_Name    *name not implemented yet!"<< endl;
  abort();
  return return_array;
}

IIRScram *
IIRScram_Name::_get_prefix() {
  return dynamic_cast<IIRScram *>(get_prefix());
}
