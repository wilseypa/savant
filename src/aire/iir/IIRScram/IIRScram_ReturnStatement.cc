
// Copyright (c) 1996-2001 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING
// OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found
// in the file "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer
//          Krishnan Subramani 
//          Umesh Kumar V. Rajasekaran
//          Malolan Chetlur    
//          Narayanan Thondugulam

//---------------------------------------------------------------------------

#include "IIRScram_DesignFile.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_ReturnStatement.hh"
#include "IIRScram_SubprogramDeclaration.hh"
#include "IIRScram_TypeDefinition.hh"
#include "error_func.hh"
#include "set.hh"
#include "resolution_func.hh"
#include "savant.hh"

#include <sstream>
using std::ostringstream;


void 
IIRScram_ReturnStatement::_type_check(){
  // This needs to actually be type-checked within the context of the
  // return type.
  // See next method...
}

void 
IIRScram_ReturnStatement::_type_check( savant::set<IIRScram_TypeDefinition> *context_set ){
  ASSERT( get_enclosing_subprogram() != NULL );

  if( get_enclosing_subprogram()->get_kind() == IIR_FUNCTION_DECLARATION  ){
    // Then this return statement appeared in a function declaration.
    // 1) The expression must not be NULL.
    // 2) If the context_set is NULL, something is broken.
    ASSERT( context_set != NULL );

    if( get_return_expression() != NULL ){
      // Then we need to type_check based on the context_set passed in...
      set_return_expression( _get_return_expression()->_semantic_transform( context_set ));
      _get_return_expression()->_type_check( context_set );

      savant::set<IIRScram_TypeDefinition> *expression_types = _get_return_expression()->_get_rval_set();
      if( expression_types == NULL ){
	report_undefined_symbol( _get_return_expression() );
	return;
      }

      reconcile_sets( context_set, expression_types );
      
      switch( expression_types->size() ){
      case 0:{
	ostringstream err;
	err << "Expression |" << *_get_return_expression() << "| must have a return type "
	    << "compatible with that of its function, |" 
	    << *_get_enclosing_subprogram()->_get_declarator() << "|.";
	report_error( this, err.str() );
	break;
      }
      case 1:{
	IIRScram_TypeDefinition *my_type = expression_types->getElement() ;
	set_return_expression( _get_return_expression()->_rval_to_decl( my_type ));
	break;
      }
      default:{
	report_ambiguous_error( _get_return_expression(), expression_types->convert_set<IIR_TypeDefinition>() );
	break;
      }
      }

      delete expression_types;
    }
    else{
      ostringstream err;
      err << "|" << *_get_enclosing_subprogram()->_get_declarator() << "| " 
	  << "was declared as a function, and should return a value.";
      report_error( this, err.str(), WARNING );
    }
  }
  else{
    // Then this return statement appeared in a procedure declaration.
    // 1) The expression must be NULL.
    ASSERT( get_enclosing_subprogram()->get_kind() == IIR_PROCEDURE_DECLARATION );

    if( get_return_expression() != NULL ){
      ostringstream err;
      err << "|" << *get_enclosing_subprogram()->get_declarator() << "| " 
	  << "was declared as a procedure, and may not return a value.";
      report_error( this, err.str() );
    }
  }
}

visitor_return_type *
IIRScram_ReturnStatement::_accept_visitor( node_visitor *visitor, 
					   visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ReturnStatement(this, arg);
}

IIRScram *
IIRScram_ReturnStatement::_get_return_expression() {
  return dynamic_cast<IIRScram *>(get_return_expression());
}

IIRScram_SubprogramDeclaration*
IIRScram_ReturnStatement::_get_enclosing_subprogram() {
  return dynamic_cast<IIRScram_SubprogramDeclaration *>(get_enclosing_subprogram());
}
