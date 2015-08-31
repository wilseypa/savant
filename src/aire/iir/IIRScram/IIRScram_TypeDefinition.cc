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

#include "savant.hh"
#include "IIRScram_AccessSubtypeDefinition.hh"
#include "IIRScram_ArrayTypeDefinition.hh"
#include "IIRScram_AttributeSpecificationList.hh"
#include "IIRScram_ConstantInterfaceDeclaration.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "IIRScram_FloatingSubtypeDefinition.hh"
#include "IIRScram_FunctionDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_IntegerSubtypeDefinition.hh"
#include "IIRScram_InterfaceList.hh"
#include "IIRScram_Name.hh"
#include "IIRScram_ProcessStatement.hh"
#include "IIRScram_RangeTypeDefinition.hh"
#include "IIRScram_StringLiteral.hh"
#include "constraint_functors.hh"
#include "error_func.hh"
#include "resolution_func.hh"
#include "set.hh"
#include "symbol_table.hh"
#include "StandardPackage.hh"
#include <sstream>
using std::ostringstream;

IIRScram_TypeDefinition::IIRScram_TypeDefinition() :
  my_attribute(0){}

IIRScram_TypeDefinition::~IIRScram_TypeDefinition(){}

IIR_Boolean
IIRScram_TypeDefinition::_is_line_type() {
  if(_get_declaration() != NULL) {
    return ( IIRBase_TextLiteral::cmp(_get_declaration()->_get_declarator(), "line") == 0 );
  }
  else {
    return FALSE;
  }
}

IIRScram_TypeDefinition *
IIRScram_TypeDefinition::_get_element_subtype(){
  _report_undefined_scram_fn("IIRScram_TypeDefinition::_get_element_subtype()");  
  return NULL;
}

IIRScram_TypeDefinition *
IIRScram_TypeDefinition::get_across(){
  _report_undefined_scram_fn("IIRScram_TypeDefinition::get_across()");
  return NULL;
}

IIRScram_TypeDefinition *
IIRScram_TypeDefinition::get_through(){
  _report_undefined_scram_fn("IIRScram_TypeDefinition::get_through()");
  return NULL;
}

IIR_Int32
IIRScram_TypeDefinition::get_num_indexes(){
  // This is over-ridden in IIRScram_ArrayTypeDefinition...
  return 0;
}

void 
IIRScram_TypeDefinition::set_is_element( IIR_Boolean ){
  _report_undefined_scram_fn("IIRScram_TypeDefinition::IIRScram_TypeDefinition::set_is_element");
  abort();
}

IIRScram_TypeDefinition *
IIRScram_TypeDefinition::_get_type_of_element( int index ){
  // Repeated almost verbatim in IIRScram_FunctionDeclaration
  if( index > get_num_indexes() ){
    return NULL;
  }
  
  IIRScram_TypeDefinition *current_subtype = dynamic_cast<IIRScram_TypeDefinition *>(this);
  if( index == 0 ){
    return current_subtype;
  }

  int i;
  for( i = 0; i < index - 1; i++ ){
    ASSERT( current_subtype->is_array_type() == TRUE );

    current_subtype = current_subtype->_get_element_subtype();
  }
  
  IIRScram_TypeDefinition *retval = current_subtype->_get_element_subtype();
  
  return retval;
}

IIRScram_TypeDefinition*
IIRScram_TypeDefinition::_is_explicit_type_conversion_needed(IIRScram_TypeDefinition *targetType) {
  // This method checks to see if an explicit type conversion needs to be
  // code-generated. If so it returns the common type else it return NULL.

  if (targetType == this) {
    return NULL;
  }

  if (targetType->is_anonymous() == TRUE) {
    targetType = dynamic_cast<IIRScram_TypeDefinition *>(targetType->get_bottom_base_type());
  }
  
  if (_is_base_type(targetType)) {
    // Target type is the base type of this type. No explicit type conversion
    // is needed.
    return NULL;
  }

  // return the most compaitable type.
  return dynamic_cast<IIRScram_TypeDefinition *>(is_compatible(targetType ));
}

IIR_Boolean
IIRScram_TypeDefinition::_is_base_type(IIRScram_TypeDefinition *_base) {
  IIRScram_TypeDefinition *base_type = _get_resolved_base_type();

  while (base_type != NULL) {
    if ((base_type == _base) ||
	(IIRBase_TextLiteral::cmp(base_type->_get_declarator(), _base->_get_declarator()) == 0)) {
      return TRUE;
    }

    base_type = base_type->_get_resolved_base_type();
  }
  return FALSE;
}

IIRScram_TypeDefinition *
IIRScram_TypeDefinition::_index_constrain_array( IIRScram_ScalarTypeDefinition * ){
  _report_undefined_scram_fn("IIRScram_TypeDefinition::_index_constrain_array( IIR_ScalarTypeDefinition *)");  
  return 0;
}

IIRScram_FunctionDeclaration * 
IIRScram_TypeDefinition::_resolve_resolution_function( IIRScram_Name *resolution_function ){
  IIRScram_FunctionDeclaration *resolution_function_decl = NULL;

  savant::set<IIRScram_Declaration> *func_decls;
  constraint_functor *functor = new is_function_declaration_functor;
  func_decls = resolution_function->_symbol_lookup( functor );
  delete functor;
  if( func_decls == NULL ){
    report_undefined_symbol( resolution_function );
  }

  resolution_function_decl = dynamic_cast<IIRScram_FunctionDeclaration *>(resolve_if_one( func_decls ));

  delete func_decls;
  return resolution_function_decl;
}

IIRScram_ScalarTypeDefinition *
IIRScram_TypeDefinition::_determine_type_of_bound( IIRScram *left_or_right ){
  IIRScram_ScalarTypeDefinition *retval = NULL;
  ASSERT( left_or_right != NULL );
  
  savant::set<IIRScram_TypeDefinition> *left_or_right_types = left_or_right->_get_rval_set();
  if( left_or_right_types == NULL ){
    report_undefined_symbol( left_or_right );
    return NULL;
  }

  constraint_functor *functor = new is_scalar_type_functor();
  left_or_right_types->reduce_set( functor );
  delete functor;
  
  IIRScram_ScalarTypeDefinition *left_or_right_type = NULL;  
  StandardPackage *package = left_or_right->_get_design_file()->get_standard_package();
  switch( left_or_right_types->size() ){
  case 0:{
    ostringstream err;
    err << "|" << *left_or_right << "| is not a scalar type and isn't valid in this context.";
    report_error( left_or_right, err.str() );
    break;
  }
  
  case 1:{
    retval = dynamic_cast<IIRScram_ScalarTypeDefinition *>(left_or_right_types->getElement());
    ASSERT( retval->is_scalar_type() == TRUE );
    break;
  }
    
  default:{
    if( left_or_right_types->contains( dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(package->get_savant_universal_integer()) ) == TRUE ){
      left_or_right_type = dynamic_cast<IIRScram_ScalarTypeDefinition *>(package->get_savant_universal_integer());
      retval = left_or_right_type;
    }
    else if( left_or_right_types->contains( dynamic_cast<IIRScram_FloatingSubtypeDefinition *>(package->get_savant_universal_real()) ) == TRUE ){
      left_or_right_type = dynamic_cast<IIRScram_ScalarTypeDefinition *>(package->get_savant_universal_real());
      retval = left_or_right_type;
    }
    else{
      report_ambiguous_error( left_or_right, left_or_right_types->convert_set<IIR_TypeDefinition>() );
      retval = dynamic_cast<IIRScram_ScalarTypeDefinition *>(left_or_right_types->getElement());
    }

    break;
  }
  }
  delete left_or_right_types;
  return retval;
}

IIRScram_ScalarTypeDefinition *
IIRScram_TypeDefinition::_construct_new_type( IIRScram_RangeTypeDefinition      *temp_range,
					      IIRScram_TypeDeclaration          *type_decl,
                                              IIRScram_DesignFile               *design_file){
  // We have a range like 1 to 10, or -2.0 to 7.1. The only other legal
  // possibility is for this to be type'range.  (This method should only be
  // used for creating a new type in a type declaration.

  IIRScram_ScalarTypeDefinition *retval = NULL;
  
  IIRScram *left = temp_range->_get_base_type_left();
  ASSERT( left != NULL );

  IIRScram_ScalarTypeDefinition *left_type = _determine_type_of_bound( left );

  IIRScram *right = temp_range->_get_base_type_right();
  if( right != NULL ){
    IIRScram_ScalarTypeDefinition *right_type = _determine_type_of_bound( right );
    if( right_type == NULL ){
      return NULL;
    }

    if( left_type->_is_iir_integer_type_definition() == TRUE ){
      if( right_type->_is_iir_integer_type_definition() == TRUE ){
	retval = IIRScram_IntegerTypeDefinition::_construct_new_type( temp_range, type_decl , design_file );
      }
      else{
	ostringstream err;
	err << "|" << left << " " << temp_range->_get_direction() << " " << right
	    << "| is not a valid range in this context. |" << right << "| is not an "
	    << "integer type, and |" << left << "| is.";
	report_error( temp_range, err.str() );
	retval = NULL;
      }
    }
    else if ( left_type->_is_iir_floating_type_definition() == TRUE ){
      if( right_type->_is_iir_floating_type_definition() == TRUE ){
	retval = IIRScram_FloatingTypeDefinition::_construct_new_type( temp_range, type_decl, design_file );	
      }
      else{
	ostringstream err;
	err << "|" << left << " " << temp_range->_get_direction() << " " << right
	    << "| is not a valid range in this context. |" << right << "| is not an "
	    << "floating type, and |" << left << "| is.";
	report_error( temp_range, err.str() );
	retval = NULL;
      }
    }
    else{
      ostringstream err;
      err << "Internal error in IIRScram_TypeDefinition::_construct_new_type - "
	  << "got a left that is a " << left_type->get_kind_text() << " and I don't know "
	  << "what to do!";
      report_error( temp_range, err.str() );
      abort();
    }
  } 
  else{
    // Then the left better have been a 'range.
    ostringstream err;
    err << "'range temporarily not supported in this context!";
    report_error( temp_range, err.str() );
    abort();
  }
  ASSERT( retval != NULL );
  ASSERT( retval->is_resolved() == TRUE );
  return retval;
}

IIRScram*
IIRScram_TypeDefinition::_get_direction(){
  _report_undefined_scram_fn("IIRScram_TypeDefinition::_get_direction()");  
  return  NULL;
}

IIRScram*
IIRScram_TypeDefinition::_get_base_type_left(){
  return dynamic_cast<IIRScram *>(get_base_type_left());
}

IIRScram*
IIRScram_TypeDefinition::_get_base_type_direction(){
  return dynamic_cast<IIRScram *>(get_base_type_direction());
}

IIRScram*
IIRScram_TypeDefinition::_get_base_type_right(){
  return dynamic_cast<IIRScram *>(get_base_type_right());
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_TypeDefinition::_get_rval_set( constraint_functor * ){
  return new savant::set<IIRScram_TypeDefinition>( dynamic_cast<IIRScram_TypeDefinition *>(this) );
}

void 
IIRScram_TypeDefinition::_type_check( savant::set<IIRScram_TypeDefinition> * ){
}

IIRScram_TypeDefinition *
IIRScram_TypeDefinition::_construct_new_subtype( IIRScram_Name *,
						 IIRScram_ScalarTypeDefinition * ){
  _report_undefined_scram_fn("IIRScram_TypeDefinition::_construct_new_subtype( IIRScram *resolution_function, IIRScram_ScalarTypeDefinition *new_constraint )");  
  return NULL;
}

IIRScram_TypeDefinition *
IIRScram_TypeDefinition::_get_new_subtype( ){
  _report_undefined_scram_fn("IIRScram_TypeDefinition::IIRScram_TypeDefinition::_get_new_subtype( )");  
  return NULL;
}

IIRScram_TypeDefinition *
IIRScram_TypeDefinition::_construct_new_subtype_resolution_function_only( IIRScram_Name *resolution_function ){
  IIRScram_TypeDefinition *retval;

  retval = _get_new_subtype();
  _clone( retval );

  if( resolution_function != NULL ){
    IIRScram_FunctionDeclaration *resolution_function_decl;
    resolution_function_decl = _resolve_resolution_function( resolution_function );

    retval->_set_resolution_function( resolution_function_decl );
  }
  if( is_subtype() == true ){
    retval->set_base_type( get_base_type() );
  }
  else{
    retval->set_base_type( dynamic_cast<IIRScram_TypeDefinition *>(this) );
  }
  return retval;
}

void 
IIRScram_TypeDefinition::_clone( IIRScram *copy_into ){
  ASSERT( copy_into->_is_iir_type_definition() == TRUE );

  IIRScram_TypeDefinition *as_type = dynamic_cast<IIRScram_TypeDefinition *>(copy_into);
  if( is_subtype() ){
    as_type->set_base_type( get_base_type() );
  }
  as_type->set_declaration( _get_declaration() );

  IIRScram::_clone( copy_into );
}

void 
IIRScram_TypeDefinition::_come_into_scope( symbol_table *sym_tab, 
					   IIRScram_TypeDeclaration *type_decl){
  StandardPackage *package = _get_design_file()->get_standard_package();
  // Type decl should _only_ be NULL for the universal operators.
  ASSERT( type_decl != NULL ||
          this == dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(package->get_savant_universal_integer()) ||
          this == dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(package->get_savant_universal_real()) );

  savant::set<IIR_Declaration> *implicit_declarations = NULL;
    
  if( type_decl != NULL ){
    implicit_declarations = type_decl->get_implicit_declarations();
  }
  
  if( implicit_declarations == NULL ){
    savant::set<IIRScram_Declaration> *scram_implicit_declarations = new savant::set<IIRScram_Declaration>();
    _build_implicit_operators( scram_implicit_declarations );
    ASSERT( scram_implicit_declarations != NULL );
    ASSERT( scram_implicit_declarations->size() > 0 );

    implicit_declarations = scram_implicit_declarations->convert_set<IIR_Declaration>();
    if( type_decl != NULL ){
      type_decl->set_implicit_declarations( implicit_declarations );
    }
    delete scram_implicit_declarations;
  } 
    
  sym_tab->add_declaration( implicit_declarations );
}

void 
IIRScram_TypeDefinition::_build_implicit_operators( savant::set<IIRScram_Declaration> *add_to ){
  StandardPackage *package = _get_design_file()->get_standard_package();
  // So, ALL types have these relational operators defined.
  const char *operators[] = { "\"=\"", "\"/=\"", NULL };
  _build_implicit_operators( operators,
                             add_to, 
                             dynamic_cast<IIRScram_EnumerationSubtypeDefinition *>(package->get_boolean_type()),
                             this,
                             this );
  if( _is_numeric_type() == TRUE ){
    const char *addition_operators[] = { "\"+\"", "\"-\"", NULL };
    _build_implicit_operators( addition_operators, add_to, this, this, this );
    // This is unary +/-
    _build_implicit_operators( addition_operators, add_to, this, this );
    _build_implicit_operator( "\"abs\"", add_to, this, this );
  }
  
  if( (this == dynamic_cast<IIRScram_EnumerationSubtypeDefinition *>(package->get_bit_type())) || 
      (this == dynamic_cast<IIRScram_EnumerationSubtypeDefinition *>(package->get_boolean_type())) ) {
    _build_logical_operators( add_to );
  }
}

void 
IIRScram_TypeDefinition::_build_implicit_operator( const char *op, 
						   savant::set<IIRScram_Declaration> *add_to,
						   IIRScram_TypeDefinition *return_type,
						   IIRScram_TypeDefinition *left_type,
						   IIRScram_TypeDefinition *right_type ){

  IIRScram_FunctionDeclaration *new_operator = new IIRScram_FunctionDeclaration();
  new_operator->set_declarator( IIRScram_StringLiteral::get(op, strlen(op), get_design_file()->get_class_factory() ) );
  
  IIRScram_ConstantInterfaceDeclaration *left = new IIRScram_ConstantInterfaceDeclaration();
  left->set_declarator( IIRScram_Identifier::get("left", strlen("left"), get_design_file()->get_class_factory()) );
  left->set_subtype( dynamic_cast<IIRScram_TypeDefinition *>(left_type ) );
  left->set_is_visible( FALSE );
  new_operator->set_is_implicit( TRUE );
  IIRScram::copy_location( this, left );
  new_operator->get_interface_declarations()->append( left );
  
  if( right_type != NULL ){
    IIRScram_ConstantInterfaceDeclaration *right = new IIRScram_ConstantInterfaceDeclaration();
    right->set_declarator( IIRScram_Identifier::get("right", strlen("right"), get_design_file()->get_class_factory() ) );
    right->set_subtype( dynamic_cast<IIRScram_TypeDefinition *>(right_type ) );
    right->set_is_visible( FALSE );
    new_operator->set_is_implicit( TRUE );
    IIRScram::copy_location( this, right );
    new_operator->get_interface_declarations()->append( right );
  }

  new_operator->set_return_type( dynamic_cast<IIRScram_TypeDefinition *>(return_type ) );
  new_operator->set_is_implicit( TRUE );
  IIRScram::copy_location( this, new_operator );
  
  add_to->add( new_operator );
}

void 
IIRScram_TypeDefinition::_build_implicit_operators( const char *ops[], 
						    savant::set<IIRScram_Declaration> *add_to,
						    IIRScram_TypeDefinition *return_type,
						    IIRScram_TypeDefinition *left_type,
						    IIRScram_TypeDefinition *right_type ){
  int i = 0;
  const char *current = ops[i];
  while( current != NULL ){
    _build_implicit_operator( current, add_to, return_type, left_type, right_type );
    current = ops[++i];
  }
}

void 
IIRScram_TypeDefinition::_build_logical_operators( savant::set<IIRScram_Declaration> *add_to ){
  const char *logical_operators[] = {
    "\"and\"", "\"or\"", "\"nand\"", "\"nor\"", "\"xor\"", "\"xnor\"", 0
  };

  _build_implicit_operators( logical_operators, add_to, this, this, this );
  _build_implicit_operator( "\"not\"", add_to, this, this );
}

void 
IIRScram_TypeDefinition::_build_ordering_operators( savant::set<IIRScram_Declaration> *add_to){
  // Scalar types have these relational operators defined.
  const char *operators[] = { "\"<\"", "\"<=\"", "\">\"", "\">=\"", NULL };
  StandardPackage *package = add_to->getElement()->_get_design_file()->get_standard_package();

  IIRScram_EnumerationSubtypeDefinition *temp =
    dynamic_cast<IIRScram_EnumerationSubtypeDefinition *>(package->get_boolean_type());
  _build_implicit_operators( operators,
                             add_to, 
                             temp,
                             this, 
                             this );
}

IIRScram_TypeDefinition *
IIRScram_TypeDefinition::_get_designated_subtype(){
  _report_undefined_scram_fn("IIRScram_TypeDefinition::_get_designated_subtype()");
  return NULL;
}

IIRScram_Declaration *
IIRScram_TypeDefinition::_get_declaration() {
  return dynamic_cast<IIRScram_Declaration *>(get_declaration());
}

IIRScram_TypeDefinition *
IIRScram_TypeDefinition::_get_this_element_subtype() {
  return (dynamic_cast<IIRScram_ArrayTypeDefinition*>(this))->_get_element_subtype();
}

void 
IIRScram_TypeDefinition::_set_resolution_function( IIRScram_FunctionDeclaration *) {
  _report_undefined_scram_fn("_set_resolution_function( IIRScram_FunctionDeclaration *)");
}

// Helper functions
IIRScram_TypeDefinition *
IIRScram_TypeDefinition::_get_type_mark() {
  return dynamic_cast<IIRScram_TypeDefinition *>(get_type_mark());
}

IIRScram_TypeDefinition*
IIRScram_TypeDefinition::_get_base_type(){
  return dynamic_cast<IIRScram_TypeDefinition *>(get_base_type());
}

IIRScram_TypeDefinition*
IIRScram_TypeDefinition::_get_resolved_base_type(){
  // This is the default case.  It's overloaded in several places as well.
  return dynamic_cast<IIRScram_TypeDefinition *>(get_base_type());
}

IIRScram_ScalarTypeDefinition *
IIRScram_TypeDefinition::_get_index_subtype() {
  _report_undefined_scram_fn("_set_resolution_function( IIRScram_FunctionDeclaration *)");
  return NULL;
}

IIRScram_ScalarTypeDefinition *
IIRScram_TypeDefinition::_get_resolved_index_subtype() {
  return dynamic_cast<IIRScram_ScalarTypeDefinition *>(get_resolved_index_subtype());
}

