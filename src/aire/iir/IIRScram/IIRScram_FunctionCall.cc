
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
//          Krishnan Subramani  
//          Umesh Kumar V. Rajasekaran 
//          Timothy J. McBrayer 
//	    Magnus Danielson	
//---------------------------------------------------------------------------

#include "IIRScram_FunctionCall.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_AssociationElement.hh"
#include "IIRScram_FunctionDeclaration.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_Identifier.hh"

IIRScram_FunctionCall::IIRScram_FunctionCall() :
  has_been_type_checked( FALSE )
{
  set_parameter_association_list(new IIRScram_AssociationList());
}

IIRScram_FunctionCall::~IIRScram_FunctionCall(){}

savant::set<IIRScram_Declaration> *
IIRScram_FunctionCall::_symbol_lookup(){
  ASSERT( _get_implementation() != NULL );
  return new savant::set<IIRScram_Declaration>( _get_implementation() );
}

IIRScram_FunctionCall *
IIRScram_FunctionCall::_build_function_call( IIRScram_SubprogramDeclaration *func_decl,
					     IIRScram_IndexedName * ){
  IIRScram_FunctionCall *retval = new IIRScram_FunctionCall;
  func_decl->copy_location( retval );
  retval->set_implementation( func_decl );
  return retval;
}

// This method is called from
// IIRScram_ComponentInstantiationStatement::_publish_cc_elaborate_Add.
// This happens ONLY when this is used as a type conversion function.
// Then, this function call MUST have ONLY one argument.
void 
IIRScram_FunctionCall::_type_check( savant::set<IIRScram_TypeDefinition> * ){
  if (has_been_type_checked  == FALSE) {
    has_been_type_checked = TRUE;
    ASSERT(_get_implementation() != NULL);
    IIRScram_SubprogramDeclaration *my_decl = _get_implementation();
  
    if (_get_parameter_association_list()->is_resolved() == FALSE) {
      _get_parameter_association_list()->_resolve_and_order(my_decl->_get_interface_declarations(),
							    NULL,
							    this);
    }
    _get_parameter_association_list()->_fill_in_defaults( this,
							  my_decl->_get_interface_declarations());
    

    ASSERT( _get_parameter_association_list()->is_resolved() == TRUE );
  }
}

IIRScram *
IIRScram_FunctionCall::_rval_to_decl( IIRScram_TypeDefinition *my_type ){
  // These are some simple sanity checks...
  ASSERT( _get_implementation() != NULL );
  ASSERT( _get_implementation()->_get_subtype() != NULL );
  ASSERT( my_type != NULL );
  ASSERT( _get_implementation()->_get_subtype()->is_compatible( my_type ) != NULL );

  return dynamic_cast<IIRScram *>(this);
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_FunctionCall::_get_rval_set( constraint_functor *functor ){
  ASSERT( _get_implementation() != NULL );

  return _get_implementation()->_get_rval_set(functor);
}

IIRScram*
IIRScram_FunctionCall::_clone() {
  IIRScram_FunctionCall *funccall = new IIRScram_FunctionCall();

  IIRScram_Expression::_clone(funccall);
  funccall->set_implementation(_get_implementation());
  
  IIRScram_AssociationElement *newassoc, *assoc = 
    dynamic_cast<IIRScram_AssociationElement *>(get_parameter_association_list()->first());

  while (assoc != NULL) {
    newassoc = dynamic_cast<IIRScram_AssociationElement*>(assoc->_clone());
    funccall->get_parameter_association_list()->append(newassoc);
    assoc = 
      dynamic_cast<IIRScram_AssociationElement *>(get_parameter_association_list()->successor(assoc));
  }

  return funccall;
}

IIR_Mode
IIRScram_FunctionCall::_get_mode() {
  ASSERT(get_parameter_association_list()->size() == 1);
  ASSERT(dynamic_cast<IIRScram_AssociationElement *>(get_parameter_association_list()->first())->is_signal() == TRUE);

  return dynamic_cast<IIRScram_AssociationElement *>(get_parameter_association_list()->first())->_get_actual()->_get_mode();
}

IIRScram_Declaration *
IIRScram_FunctionCall::_find_formal_declaration(){
  ASSERT( is_resolved() == TRUE );
  ASSERT( get_parameter_association_list()->size() == 1 );
  ASSERT( get_parameter_association_list()->first() != NULL );
  return dynamic_cast<IIRScram_AssociationElement *>(get_parameter_association_list()->first())->_find_formal_declaration();
}

visitor_return_type *
IIRScram_FunctionCall::_accept_visitor( node_visitor *visitor,
					visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_FunctionCall(this, arg);
}

// IIRBase Function Wrapper(s)
IIRScram_SubprogramDeclaration*
IIRScram_FunctionCall::_get_implementation() {
  return dynamic_cast<IIRScram_SubprogramDeclaration *>(get_implementation());
}

IIRScram_AssociationList *
IIRScram_FunctionCall::_get_parameter_association_list() {
  return dynamic_cast<IIRScram_AssociationList *>(get_parameter_association_list());
}
