
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

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer 
//          Malolan Chetlur     
//          Krishnan Subramani  
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam 
//          Radharamanan Radhakrishnan
//          Swaminathan Subramanian
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_AttributeSpecificationList.hh"
#include "IIRScram_CharacterLiteral.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EnumerationLiteral.hh"
#include "IIRScram_EnumerationLiteralList.hh"
#include "IIRScram_EnumerationTypeDefinition.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_StringLiteral.hh"
#include "set.hh"
#include "symbol_table.hh"


IIRScram_EnumerationLiteral::IIRScram_EnumerationLiteral() {
  set_attributes(new IIRScram_AttributeSpecificationList());
}

IIRScram_EnumerationLiteral::~IIRScram_EnumerationLiteral(){}

// Currently direction is implemented as an enumeration literal, where
// `to' is represented by IIRScram_EnumerationLiteral::declarator = "true", and
// `downto' is represented by IIRScram_EnumerationLiteral::declarator = "false"
// This method checks this condition and publishes the value of direction
// correspondingly. -- SK on Tue Mar 4.
savant::set<IIRScram_TypeDefinition> *
IIRScram_EnumerationLiteral::_get_rval_set(constraint_functor *functor){
  savant::set<IIRScram_TypeDefinition> *retval = NULL;

  if( is_resolved() == true ){
    ASSERT( _get_subtype() != NULL );
    retval = new savant::set<IIRScram_TypeDefinition>( _get_subtype() );
  }
  else{
    IIRScram_Declaration *current_decl = NULL;
    savant::set<IIRScram_Declaration> *my_decls = _symbol_lookup();
    if( my_decls == NULL ){
      return NULL;
    }

    current_decl = dynamic_cast<IIRScram_Declaration *>(my_decls->getElement());
    while( current_decl != NULL ){
      if( functor == 0 || (*functor)(current_decl) == TRUE ){
	if( retval == NULL ){
	  retval = new savant::set<IIRScram_TypeDefinition>;
	}
      
	retval->add( current_decl->_get_subtype() );
      } 
      current_decl = dynamic_cast<IIRScram_Declaration *>(my_decls->getNextElement());
    }

    delete my_decls;
  }
  
  return retval;
}

savant::set<IIRScram_Declaration> *
IIRScram_EnumerationLiteral::_symbol_lookup(){
  savant::set<IIRScram_Declaration>     *retval;
  retval = new savant::set<IIRScram_Declaration>(*(_get_symbol_table()->find_set( _get_declarator() )->convert_set<IIRScram_Declaration>()));
  
  return retval;
}

IIRScram *
IIRScram_EnumerationLiteral::_rval_to_decl( IIRScram_TypeDefinition *my_rval ){
  ASSERT( my_rval != NULL );

  IIRScram_Declaration *retval = NULL;

  if( _get_subtype() == NULL ){
    savant::set<IIRScram_Declaration> *my_decls = _symbol_lookup();
    ASSERT( my_decls != NULL );

    IIRScram_Declaration *current_decl = my_decls->getElement();
    while( current_decl != NULL ){
      if( current_decl->_get_subtype()->is_compatible( my_rval ) != NULL ){
	retval = current_decl;
	break;
      }
      current_decl = dynamic_cast<IIRScram_Declaration *>(my_decls->getNextElement());
    }

    ASSERT( retval != NULL );
  
    delete my_decls;
  }
  else{
    ASSERT( my_rval->is_compatible( _get_subtype() ) != NULL );
    retval = this;
  }

  return retval;
}

void 
IIRScram_EnumerationLiteral::_type_check( savant::set<IIRScram_TypeDefinition> * ){
}

IIRScram*
IIRScram_EnumerationLiteral::_clone() {
  return this;
}

IIR_Boolean 
IIRScram_EnumerationLiteral::_is_homograph_of( IIRScram_Declaration *compare_to ){
  if( get_kind() != compare_to->get_kind() ){
    return FALSE;
  }
  
  if( _get_subtype()->is_compatible( compare_to->_get_subtype() ) == NULL ){
    return FALSE;
  }

  return TRUE;
}

visitor_return_type *
IIRScram_EnumerationLiteral::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_EnumerationLiteral(this, arg);
}

IIRScram_AttributeSpecificationList* 
IIRScram_EnumerationLiteral::_get_attribute_specification_list() { 
  return dynamic_cast<IIRScram_AttributeSpecificationList *>(get_attributes()); 
}

// IIRBase Function Wrapper(s)
