
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
//          Malolan Chetlur     
//          Umesh Kumar V. Rajasekaran
//          Radharamanan Radhakrishnan

#include "savant.hh"
#include "IIRScram_TypeConversion.hh"
#include "IIRScram_AssociationElementByExpression.hh"
#include "IIRScram_ArrayTypeDefinition.hh"
#include "IIRScram_TextLiteral.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_PosAttribute.hh"
#include "IIRScram_FunctionCall.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_SubprogramDeclaration.hh"
#include "set.hh"

savant::set<IIRScram_TypeDefinition> *
IIRScram_TypeConversion::_get_rval_set(constraint_functor * ){
  return new savant::set<IIRScram_TypeDefinition>(_get_subtype());
}

IIRScram_Declaration *
IIRScram_TypeConversion::_find_formal_declaration(){
  ASSERT( is_resolved() == TRUE );
  ASSERT( _get_expression() != NULL );
  ASSERT( _get_expression()->get_kind() != IIR_ASSOCIATION_LIST || 
	  (dynamic_cast<IIRScram_AssociationList *>(_get_expression())->size() == 1 ));
  ASSERT( _get_type_mark() != NULL );
  return _get_type_mark()->_find_formal_declaration();
}

visitor_return_type *
IIRScram_TypeConversion::_accept_visitor( node_visitor *visitor, 
					  visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_TypeConversion(this, arg);
}

IIRScram_TypeDefinition *
IIRScram_TypeConversion::_get_type_mark() {
  return dynamic_cast<IIRScram_TypeDefinition *>(get_type_mark());
}

IIRScram *
IIRScram_TypeConversion::_get_expression() {
  return dynamic_cast<IIRScram *>(get_expression());
}
