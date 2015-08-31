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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_AssociationList.hh"
#include "IIRScram_ConcurrentGenerateForStatement.hh"
#include "IIRScram_ConstantDeclaration.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_RangeAttribute.hh"
#include "IIRScram_ScalarTypeDefinition.hh"
#include "IIRScram_SliceName.hh"
#include "set.hh"
#include "savant.hh"


IIRScram_SliceName::~IIRScram_SliceName() {}

IIR_Mode
IIRScram_SliceName::_get_mode() {
  return _get_prefix()->_get_mode();
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_SliceName::_get_rval_set(constraint_functor *functor){
  if( _get_subtype() == NULL ){
    return _get_prefix()->_get_rval_set( functor );
  }
  else{
    return new savant::set<IIRScram_TypeDefinition>( _get_subtype() );
  }
}

void 
IIRScram_SliceName::_type_check( savant::set<IIRScram_TypeDefinition> * ){
  ASSERT( is_resolved() == TRUE );
}

IIR_Boolean 
IIRScram_SliceName::_is_readable(){
  return _get_prefix()->_is_readable();
}

IIR_Boolean 
IIRScram_SliceName::_is_writable(){
  return _get_prefix()->_is_writable();
}

IIRScram_TypeDefinition*
IIRScram_SliceName::_get_name_type() {
  return _get_prefix()->_get_subtype();
}

void 
IIRScram_SliceName::_make_interface_visible( symbol_table *sym_tab ){
  ASSERT( _get_prefix()->is_label() == TRUE );
  _get_prefix()->_make_interface_visible( sym_tab );
}

IIRScram *
IIRScram_SliceName::_clone(){
  IIRScram_SliceName *retval = new IIRScram_SliceName();
  IIRScram_Name::_clone( retval );
  retval->set_prefix( _get_prefix()->_clone() );
  retval->set_suffix( _get_suffix()->_clone() );

  retval->set_subtype(get_subtype());
  
  return retval;
}

IIRScram *
IIRScram_SliceName::_get_suffix(){
  ASSERT(get_suffix() != NULL);
  return dynamic_cast<IIRScram *>(get_suffix());
}


IIRScram_Declaration *
IIRScram_SliceName::_find_formal_declaration(){
  ASSERT( is_resolved() == TRUE );
  ASSERT( _get_suffix() != NULL );
  ASSERT( get_suffix()->get_kind() != IIR_ASSOCIATION_LIST || 
	  (dynamic_cast<IIRScram_AssociationList *>(get_suffix()))->size() == 1 );
  return _get_prefix()->_find_formal_declaration();
}

visitor_return_type *
IIRScram_SliceName::_accept_visitor( node_visitor *visitor, 
				     visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_SliceName(this, arg);
}

IIRScram_List *
IIRScram_SliceName::_get_statement_list(){
  ASSERT( _get_prefix()->is_label() == TRUE );
  return _get_prefix()->_get_statement_list();
}
