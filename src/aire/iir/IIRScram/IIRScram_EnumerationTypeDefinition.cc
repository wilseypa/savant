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
//          Malolan Chetlur     mal@ece.uc.edu
//          Krishnan Sunbramani skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EnumerationLiteral.hh"
#include "IIRScram_EnumerationLiteralList.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "IIRScram_IntegerLiteral32.hh"
#include "IIRScram_StringLiteral.hh"
#include "StandardPackage.hh"
#include "symbol_table.hh"
#include "error_func.hh"
#include "resolution_func.hh"

#include <sstream>
using std::ostringstream;

IIRScram_EnumerationTypeDefinition::IIRScram_EnumerationTypeDefinition(){}

IIRScram_EnumerationTypeDefinition::~IIRScram_EnumerationTypeDefinition(){}

IIRScram_TypeDefinition *
IIRScram_EnumerationTypeDefinition::_get_new_subtype(){
  IIRScram_TypeDefinition *retval = new IIRScram_EnumerationSubtypeDefinition();
  copy_location(this, retval);
  return retval;
}

IIRScram *
IIRScram_EnumerationTypeDefinition::_clone(){
  IIRScram_EnumerationTypeDefinition *retval = new IIRScram_EnumerationTypeDefinition();
  _clone( retval );

  return retval;
}

void 
IIRScram_EnumerationTypeDefinition::_clone( IIRScram *copy_into ){
  ASSERT( copy_into->_is_iir_enumeration_type_definition() == TRUE );
  IIRScram_EnumerationTypeDefinition *as_enumeration_type = 
    dynamic_cast<IIRScram_EnumerationTypeDefinition *>(copy_into);

  as_enumeration_type->set_enumeration_literals(IIRBase_EnumerationTypeDefinition::get_enumeration_literals());
  IIRScram_ScalarTypeDefinition::_clone( copy_into );
}

void 
IIRScram_EnumerationTypeDefinition::_come_into_scope( symbol_table *sym_tab,
						      IIRScram_TypeDeclaration *type_decl){
  IIRScram_ScalarTypeDefinition::_come_into_scope( sym_tab, type_decl );
  IIR_EnumerationLiteralList *list = get_enumeration_literals();

  IIRScram_EnumerationLiteral *literal =
    dynamic_cast<IIRScram_EnumerationLiteral *>(list->first());
  while( literal != NULL ){
    sym_tab->add_declaration( literal );
    literal = dynamic_cast<IIRScram_EnumerationLiteral *>(list->successor( literal ));
  }
}

void 
IIRScram_EnumerationTypeDefinition::_come_out_of_scope( symbol_table *sym_tab ){
  IIRScram_ScalarTypeDefinition::_come_out_of_scope( sym_tab );
  IIR_EnumerationLiteralList *list = get_enumeration_literals();

  IIRScram_EnumerationLiteral *literal =
    dynamic_cast<IIRScram_EnumerationLiteral *>(list->first());
  while( literal != NULL ){
    sym_tab->remove_from_scope( literal );
    literal = dynamic_cast<IIRScram_EnumerationLiteral *>(list->successor( literal ));
  }
}

void 
IIRScram_EnumerationTypeDefinition::_set_resolution_function( IIRScram_FunctionDeclaration * ){
  ostringstream err;
  err << "Internal error - IIRScram_EnumerationTypeDefinition::_set_resolution_function was "
      << "called.  Resolution functions can't be associated with an enumeration type and this "
      << "should have been caught earlier.";
  report_error( this, err.str() );
}

IIRScram_EnumerationSubtypeDefinition *
IIRScram_EnumerationTypeDefinition::_construct_new_type(IIRScram_EnumerationLiteralList *literals,
							IIRScram_TypeDeclaration *type_decl,
							IIRScram_DesignFile *design_file ) {
  ASSERT( literals != NULL );

  IIRScram_EnumerationSubtypeDefinition *retval = NULL;
  IIRScram_EnumerationTypeDefinition *base_type = new IIRScram_EnumerationTypeDefinition();
  type_decl->copy_location( base_type );

  base_type->set_left( literals->first() );
  base_type->set_direction( design_file->get_standard_package()->get_true_literal( ) );  
  base_type->set_right( literals->last() );
  base_type->set_enumeration_literals(literals);
  base_type->set_declaration( type_decl );
  base_type->_set_design_file( design_file );

  IIRScram_TypeDefinition *temp = base_type->_construct_new_subtype( 0, 0 );
  type_decl->copy_location( temp );
  ASSERT( temp->get_kind() == IIR_ENUMERATION_SUBTYPE_DEFINITION );
  retval = dynamic_cast<IIRScram_EnumerationSubtypeDefinition *>(temp);

  retval->set_declaration( type_decl );

  IIRScram_EnumerationLiteral *current =
    dynamic_cast<IIRScram_EnumerationLiteral *>(literals->first());
  while( current != NULL ){
    current->set_subtype( retval );
    current = dynamic_cast<IIRScram_EnumerationLiteral *>(literals->successor( current ));
  }

  return retval; 
}

visitor_return_type *
IIRScram_EnumerationTypeDefinition::_accept_visitor( node_visitor *visitor,
						     visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_EnumerationTypeDefinition(this, arg);
}

// IIRBase Function Wrapper(s)
IIRScram_EnumerationLiteralList *
IIRScram_EnumerationTypeDefinition::_get_enumeration_literals() {
  return dynamic_cast<IIRScram_EnumerationLiteralList *>(IIRBase_EnumerationTypeDefinition::get_enumeration_literals());
}
