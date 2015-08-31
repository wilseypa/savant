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
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_DesignFile.hh"
#include "IIRScram_DesignatorByAll.hh"
#include "IIRScram_List.hh"
#include "IIRScram_Declaration.hh"
#include "IIRScram_AccessTypeDefinition.hh"
#include "set.hh"

savant::set<IIRScram_Declaration> *
IIRScram_DesignatorByAll::_symbol_lookup( savant::set<IIRScram_Declaration> *decl_set ){
  return new savant::set<IIRScram_Declaration>( *decl_set );
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_DesignatorByAll::_get_rval_set( savant::set<IIRScram_Declaration> *prefix_decls,
					 constraint_functor *functor){
  if( prefix_decls == NULL ){
    return NULL;
  }

  savant::set<IIRScram_TypeDefinition> *retval = new savant::set<IIRScram_TypeDefinition>;

  IIRScram_Declaration *current_decl = prefix_decls->getElement();
  while( current_decl != NULL ){
    if( current_decl->is_access_type() == TRUE ){
      IIRScram_TypeDefinition *access_to = current_decl->_get_subtype()->_get_designated_subtype();
      retval->add( access_to );
    }
    current_decl = prefix_decls->getNextElement();
  }

  retval->reduce_set( functor );

  if( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }
  
  return retval;
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_DesignatorByAll::_get_rval_set( savant::set<IIRScram_TypeDefinition> *prefix_types,
					 constraint_functor * ){
  if( prefix_types == NULL ){
    return NULL;
  }

  savant::set<IIRScram_TypeDefinition> *retval = new savant::set<IIRScram_TypeDefinition>;

  IIRScram_TypeDefinition *current_type = prefix_types->getElement();
  while( current_type != NULL ){
    if( current_type->is_access_type() == TRUE ){
      IIRScram_TypeDefinition *access_to = current_type->_get_designated_subtype();
      retval->add( access_to );
    }
    
    current_type = prefix_types->getNextElement();
  }

  if( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }
  
  return retval;
}

IIRScram_TypeDefinition *
IIRScram_DesignatorByAll::_determine_rval_in_set( savant::set<IIRScram_TypeDefinition> *prefix_types,
						  IIRScram_TypeDefinition *return_type ){
  IIRScram_TypeDefinition *retval = NULL;
  IIRScram_TypeDefinition *current_type = prefix_types->getElement();
  while( current_type != NULL ){
    if( current_type->is_access_type() == TRUE ){
      IIRScram_TypeDefinition *access_to = current_type->_get_subtype()->_get_designated_subtype();
      if( access_to->is_compatible( return_type ) != NULL ){
	retval = current_type;
	break;
      }
    }

    current_type = prefix_types->getNextElement();
  }

  return retval;
}

IIRScram_Declaration *
IIRScram_DesignatorByAll::_determine_decl_in_set( savant::set<IIRScram_Declaration> *prefix_decls,
						  IIRScram_TypeDefinition *return_type ){
  IIRScram_Declaration *retval = NULL;
  IIRScram_Declaration *current_decl = prefix_decls->getElement();
  while( current_decl != NULL ){
    if( current_decl->is_access_type() == TRUE ){
      IIRScram_TypeDefinition *access_to = current_decl->_get_subtype()->_get_designated_subtype();
      if( access_to->is_compatible( return_type ) != NULL ){
	retval = current_decl;
	break;
      }
    }

    current_decl = prefix_decls->getNextElement();
  }

  return retval;
}

IIRScram *
IIRScram_DesignatorByAll::_rval_to_decl( IIRScram_TypeDefinition *,
					 IIRScram_TypeDefinition * ){
  return this;
}

IIRScram *
IIRScram_DesignatorByAll::_rval_to_decl( IIRScram_Declaration *,
					 IIRScram_TypeDefinition * ){
  return this;
}

visitor_return_type *
IIRScram_DesignatorByAll::_accept_visitor( node_visitor *visitor,
					   visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_DesignatorByAll(this, arg);
}
