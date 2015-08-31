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
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_DesignFile.hh"
#include "IIRScram_FunctionDeclaration.hh"
#include "IIRScram_IntegerSubtypeDefinition.hh"
#include "IIRScram_InterfaceList.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_ValAttribute.hh"
#include "IIRScram_VariableInterfaceDeclaration.hh"

#include "error_func.hh"
#include "set.hh"
#include "StandardPackage.hh"

#include <sstream>
using std::ostringstream;

IIRScram_TypeDefinition *
IIRScram_ValAttribute::_get_subtype(){
  return _get_prefix_subtype();
}


void 
IIRScram_ValAttribute::_resolve_suffix_special(){
  if( _get_suffix() != NULL && _get_suffix()->is_resolved() == FALSE ){

    ASSERT( _get_prefix()->is_resolved() == TRUE );

    savant::set<IIRScram_TypeDefinition> *suffix_types = _get_suffix()->_get_rval_set();
    if( suffix_types == NULL ){
      report_undefined_symbol( _get_suffix() );
    }

    constraint_functor *functor = new is_integer_type_functor;
    suffix_types->reduce_set( functor );
    delete functor;
    
    switch( suffix_types->size() ){
    case 0:{
      ostringstream err;
      err << "|" << *_get_suffix() << "| is not a valid suffix for |" << this << "|.";
      err << " The suffix must be a locally static expression of an integer type.";
    
      report_error( this, err.str() );
      break;
    }
    case 1:{
      IIRScram_TypeDefinition *suffix_type = suffix_types->getElement();

      _set_suffix( _get_suffix()->_semantic_transform( suffix_type ) );
      _get_suffix()->_type_check( suffix_type );
      
      _set_suffix( _get_suffix()->_rval_to_decl( suffix_type ));
      break;
    }
    default:{
      report_ambiguous_error( _get_suffix(), suffix_types->convert_set<IIR_TypeDefinition>() );
      break;
    }
    }
  }  
}

visitor_return_type *IIRScram_ValAttribute::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ValAttribute(this, arg);
};
