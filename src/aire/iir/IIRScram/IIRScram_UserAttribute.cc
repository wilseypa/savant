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
//          Umesh Kumar V. Rajasekaran urajaske@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_AssociationList.hh"
#include "IIRScram_Aggregate.hh"
#include "IIRScram_AssociationElementByExpression.hh"
#include "IIRScram_AttributeSpecification.hh"
#include "IIRScram_ConstantDeclaration.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_QualifiedExpression.hh"
#include "IIRScram_TextLiteral.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_UserAttribute.hh"

#include "error_func.hh"
#include "resolution_func.hh"
#include "set.hh"
#include "savant.hh"

#include <sstream>
using std::ostringstream;

// I'm not quite sure what to do with these yet...
IIRScram_TypeDefinition *
IIRScram_UserAttribute::_get_subtype(){
  IIRScram_TypeDefinition       *retval = NULL;
  savant::set<IIRScram_TypeDefinition>  *suffix_rvals;

  ASSERT( _get_suffix() != NULL );

  if( _is_qualified_expression() == FALSE ){

    suffix_rvals = _get_suffix()->_get_rval_set();
    if( suffix_rvals == NULL ){
      report_undefined_symbol( _get_suffix() );
      return NULL;
    }

    switch( suffix_rvals->size() ){
    case 0:{
      ostringstream err;
      err << "|" << *_get_suffix() << "| was not declared as an attribute in this scope.";
      report_error( this, err.str() );
      break;
    }
    case 1 :{
      retval = suffix_rvals->getElement();
      break;
    }

    default:{
      report_ambiguous_error( _get_suffix(), suffix_rvals->convert_set<IIR_TypeDefinition>() );
    }
    }
  }
  else{
    if( _get_suffix()->get_kind() == IIR_AGGREGATE ){
      IIRScram_Aggregate *suffix_as_aggregate = dynamic_cast<IIRScram_Aggregate *>(_get_suffix());
      if( suffix_as_aggregate->get_element_association_list()->size() == 1 ){
	IIRScram_AssociationElement *first_element;
	first_element = dynamic_cast<IIRScram_AssociationElement *>(suffix_as_aggregate->get_element_association_list()->first());
	if( first_element->get_kind() == IIR_ASSOCIATION_ELEMENT_BY_EXPRESSION ){
	  IIRScram_AssociationElementByExpression *by_expression;
	  by_expression = dynamic_cast<IIRScram_AssociationElementByExpression *>(first_element);
	  if( by_expression->get_formal() == NULL ){
	    _set_suffix( by_expression->_get_actual() );
	  }
	}
      }
    }
    
    suffix_rvals = _get_suffix()->_get_rval_set();
    if( suffix_rvals == NULL ){
      report_undefined_symbol( _get_suffix() );
      return NULL;
    }
    savant::set<IIRScram_TypeDefinition> *prefix_rvals = _get_prefix()->_get_rval_set();
    if( prefix_rvals != NULL ){
      reconcile_sets( prefix_rvals, suffix_rvals );
      switch( prefix_rvals->size() ){
      case 0:{
	ostringstream err;
	
	err << "|" << *_get_prefix() << "| and |" << *_get_suffix() << "| aren't compatible, "
	    << "and therefore make an invalid qualified expression.";
	
	report_error( this, err.str() );
	break;
      }
      case 1:{
	retval = prefix_rvals->getElement();
	break;
      }
      default:{
	report_ambiguous_error( this, prefix_rvals->convert_set<IIR_TypeDefinition>() );
	break;
      }
      }
    }
    else{
      ostringstream err;
      err << "Internal error in IIRScram_UserAttribute::get_subtype() - no prefix rvals found.";
      report_error( this, err.str() );
      return NULL;
    }
  }

  return retval;
}

IIRScram *
IIRScram_UserAttribute::_semantic_transform( savant::set<IIRScram_TypeDefinition> * ){
  IIRScram              *retval = this;
  if( _is_qualified_expression() == TRUE ){
    // We have to type check the qualified expression right here to build it
    // correctly...
    savant::set<IIRScram_TypeDefinition> *suffix_rvals = _get_suffix()->_get_rval_set();
    if( suffix_rvals == NULL ){
      report_undefined_symbol( _get_suffix() );
    }

    savant::set<IIRScram_TypeDefinition> *prefix_rvals = _get_prefix()->_get_rval_set();
    if( prefix_rvals == NULL ){
      report_undefined_symbol( _get_suffix() );
    }
    

    reconcile_sets( prefix_rvals, suffix_rvals );
    switch( prefix_rvals->size() ){
    case 0:{
      ostringstream err;
      err << "|" << *_get_prefix() << "| and |" << *_get_suffix() << "| aren't compatible, "
	  << "and therefore make an invalid qualified expression.";

      report_error( this, err.str() );
      break;
    }
    case 1:{
      IIRScram_TypeDefinition *my_rval = prefix_rvals->getElement();
      IIRScram_QualifiedExpression *new_expr = new IIRScram_QualifiedExpression();
      copy_location( this, new_expr );
      new_expr->set_type_mark( my_rval );
      new_expr->set_expression( _get_suffix() );
      retval = new_expr;
      delete this;
      break;
    }
    default:{
      report_ambiguous_error( _get_prefix(), prefix_rvals->convert_set<IIR_TypeDefinition>() );
      break;
    }
    }
    delete suffix_rvals;
  }
  else{
    _survived_transformation = TRUE;
  }
  
  return retval;
}


IIR_Boolean 
IIRScram_UserAttribute::_is_qualified_expression(){
  IIR_Boolean retval = FALSE;
  // An attribute name can have a suffix that is a simple name, or
  // a suffix that is an indexed name, with a simple name prefix.
  // In either case, the simple name MUST refer to an attribute.
  if( _survived_transformation == TRUE ){
    // Then retval remains false;
    return FALSE;
  }
  if(_get_prefix()->get_kind() == IIR_SIMPLE_NAME || _get_prefix()->get_kind() == IIR_SELECTED_NAME){
    constraint_functor *functor = new is_type_functor;
    savant::set<IIRScram_Declaration> *prefix_decls = _get_prefix()->_symbol_lookup( functor );
    delete functor;
    if( prefix_decls != NULL ){
      if( prefix_decls->size() == 1 ){
	// Then it's unabiguously a type declaration.
	retval = TRUE;
      }
      delete prefix_decls;
    }
  }

  return retval;
}

void
IIRScram_UserAttribute::_resolve_suffix_special(){  
  if( _get_suffix() != NULL ){
    constraint_functor *functor = new is_attribute_declaration_functor;
    savant::set<IIRScram_TypeDefinition> *suffix_rvals = _get_suffix()->_get_rval_set(functor);
    delete functor;
    
    if( suffix_rvals == NULL ){
      report_undefined_symbol( _get_suffix() );
    }
    
    //    reconcile_sets( suffix_rvals, context_set );
    switch( suffix_rvals->size() ){
    case 0:{
      ostringstream err;
      err << "|" << *_get_suffix() << "| was not declared as an attribute in this scope.";
      report_error( this, err.str() );
      break;
    }
    case 1:{
      IIRScram_TypeDefinition *my_rval = suffix_rvals->getElement();
      
      _set_suffix( _get_suffix()->_semantic_transform( my_rval ) );
      _get_suffix()->_type_check( my_rval );
      _set_suffix( _get_suffix()->_rval_to_decl( my_rval ) );
      
      break;
    }
    default:{
      report_ambiguous_error( _get_suffix(), suffix_rvals->convert_set<IIR_TypeDefinition>() );
    }
    }
    delete suffix_rvals;
  }
}

visitor_return_type *
IIRScram_UserAttribute::_accept_visitor( node_visitor *visitor, 
					 visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_UserAttribute(this, arg);
}

IIRScram *
IIRScram_UserAttribute::_get_suffix() {
  return dynamic_cast<IIRScram *>(get_suffix());
}
