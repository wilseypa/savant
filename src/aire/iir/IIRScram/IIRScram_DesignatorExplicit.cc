
// Copyright (c) 1996-2003 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
// DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     
//          Narayanan Thondugulam 
//          Umesh Kumar V. Rajasekaran
//          Timothy J. McBrayer 
//          Krishnan Subramani  
//          Magnus Danielson    cfmd@swipnet.se
//---------------------------------------------------------------------------

#include "IIRScram_Declaration.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_DesignatorExplicit.hh"
#include "IIRScram_Signature.hh"
#include "set.hh"
#include "resolution_func.hh"

using std::cerr;

IIRScram_DesignatorExplicit::~IIRScram_DesignatorExplicit() {}

savant::set<IIRScram_TypeDefinition> *
IIRScram_DesignatorExplicit::_get_rval_set(constraint_functor *functor){
  savant::set<IIRScram_TypeDefinition> *retval = NULL;
  if( get_signature() == NULL ){
    retval = _get_name()->_get_rval_set(functor);
  }
  else{
    savant::set<IIRScram_Declaration> *possible_decls;
    possible_decls = _get_name()->_symbol_lookup();

    resolve_subprogram_decls( possible_decls,dynamic_cast<IIRScram_Signature*>(get_signature()));

    if( possible_decls->size() != 0 ){
      retval = new savant::set<IIRScram_TypeDefinition>;
      IIRScram_Declaration *current_decl = possible_decls->getElement();
      while( current_decl != NULL ){
	retval->add( current_decl->_get_subtype() );
	current_decl = possible_decls->getNextElement();
      }
    }
    
  }

  return retval;
}

savant::set<IIRScram_Declaration> *
IIRScram_DesignatorExplicit::_symbol_lookup(){
  savant::set<IIRScram_Declaration> *retval = NULL;

  if( get_signature() == NULL ){
    retval = _get_name()->_symbol_lookup();
  }
  else{
    savant::set<IIRScram_Declaration> *possible_decls;
    possible_decls = _get_name()->_symbol_lookup();

    resolve_subprogram_decls( possible_decls, dynamic_cast<IIRScram_Signature*>(get_signature()));

    if( possible_decls->size() != 0 ){
      retval = new savant::set<IIRScram_Declaration>;
      IIRScram_Declaration *current_decl = possible_decls->getElement();
      while( current_decl != NULL ){
	retval->add( current_decl );
	current_decl = possible_decls->getNextElement();
      }
    }
    
  }

  return retval;
}

IIRScram*
IIRScram_DesignatorExplicit::_clone() {
  IIRScram_Signature *sig = NULL;
  IIRScram *name = NULL;
  IIRScram_DesignatorExplicit *clone = new IIRScram_DesignatorExplicit;
  IIRScram::_clone(clone);

  name = _get_name()->_clone();
  clone->set_name(name);

  if (get_signature() != NULL) {

    sig = dynamic_cast<IIRScram_Signature*>((dynamic_cast<IIRScram *>(get_signature()))->_clone());
  }
  clone->set_signature(sig);

  return clone;
}

IIRScram *
IIRScram_DesignatorExplicit::_semantic_transform( savant::set<IIRScram_TypeDefinition> *transform_set ){
  set_name( _get_name()->_semantic_transform( transform_set ) );
  return this;
}

void 
IIRScram_DesignatorExplicit::_type_check( savant::set<IIRScram_TypeDefinition> *check_set ){
  _get_name()->_type_check( check_set );
}

IIRScram *
IIRScram_DesignatorExplicit::_rval_to_decl( IIRScram_TypeDefinition *my_type ){
  set_name( _get_name()->_rval_to_decl( my_type ) );
  
  return this;
}

visitor_return_type *
IIRScram_DesignatorExplicit::_accept_visitor( node_visitor *visitor,
					      visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_DesignatorExplicit(this, arg);
}

IIRScram *
IIRScram_DesignatorExplicit::_get_name() {
  return dynamic_cast<IIRScram *>(get_name());
}
