// Copyright (c) The University of Cincinnati.  
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

#include "IIRScram_DesignFile.hh"
#include "IIRScram_FloatingPointLiteral.hh"
#include "IIRScram_FloatingSubtypeDefinition.hh"
#include "IIRScram_IntegerSubtypeDefinition.hh"
#include "StandardPackage.hh"
#include "error_func.hh"
#include <sstream>

using std::ostringstream;

IIRScram_FloatingTypeDefinition::~IIRScram_FloatingTypeDefinition() {}

IIRScram_TypeDefinition *
IIRScram_FloatingTypeDefinition::_get_new_subtype(){
  IIRScram_TypeDefinition *retval = new IIRScram_FloatingSubtypeDefinition();
  copy_location( this, retval );
  return retval;
}

IIRScram *
IIRScram_FloatingTypeDefinition::_clone(){
  IIRScram_FloatingTypeDefinition *retval = NULL;
  IIRScram_TypeDefinition *temp = _get_new_subtype();

  ASSERT( temp->_is_iir_floating_type_definition() == TRUE );
  retval = dynamic_cast<IIRScram_FloatingTypeDefinition *>(temp);
  IIRScram_ScalarTypeDefinition::_clone( retval );

  return retval;
}

void 
IIRScram_FloatingTypeDefinition::_build_implicit_operators( savant::set<IIRScram_Declaration> *add_to ){
  const char *multiplying_operators[] = {"\"*\"", "\"/\"", NULL };
  IIRScram_ScalarTypeDefinition::_build_implicit_operators( add_to );
  IIRScram_TypeDefinition::_build_implicit_operators( multiplying_operators,
                                                      add_to,
                                                      this,
                                                      this,
                                                      this );

  IIRScram_TypeDefinition *integer_type = dynamic_cast<IIRScram_TypeDefinition *>(_get_design_file()->get_standard_package()->get_integer_type());
  IIRScram_TypeDefinition::_build_implicit_operator( "\"**\"", add_to, this, this, integer_type );  
}

void 
IIRScram_FloatingTypeDefinition::_set_resolution_function( IIRScram_FunctionDeclaration * ){
  ostringstream err;
  err << "Internal error - IIRScram_FloatingTypeDefinition::_set_resolution_function was "
      << "called.  Resolution functions can't be associated with a floating type and this "
      << "should have been caught earlier.";
  report_error( this, err.str() );
}

IIRScram_FloatingSubtypeDefinition *
IIRScram_FloatingTypeDefinition::_construct_new_type( IIRScram_RangeTypeDefinition *init_info,
						      IIRScram_TypeDeclaration     *type_decl,
                                                      IIRScram_DesignFile          *design_file){

  IIRScram_FloatingSubtypeDefinition *retval = new IIRScram_FloatingSubtypeDefinition();
  IIRScram_FloatingTypeDefinition *base_type = new IIRScram_FloatingTypeDefinition();
  retval->_set_design_file(design_file);
  base_type->_set_design_file(design_file);

  _init_scalar_type( init_info, base_type, retval, type_decl );

  return retval;
}


visitor_return_type *
IIRScram_FloatingTypeDefinition::_accept_visitor( node_visitor *visitor,
						  visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_FloatingTypeDefinition(this, arg);
}

