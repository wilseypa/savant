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

#include "IIRScram_ArraySubtypeDefinition.hh"
#include "IIRScram_Attribute.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "IIRScram_EnumerationLiteralList.hh"
#include "IIRScram_IntegerSubtypeDefinition.hh"
#include "IIRScram_RangeTypeDefinition.hh"
#include "IIRScram_TextLiteral.hh"
#include "error_func.hh"
#include "symbol_table.hh"
#include "resolution_func.hh"
#include "StandardPackage.hh"
#include <sstream> 

using std::ostringstream;

IIRScram_ArrayTypeDefinition::IIRScram_ArrayTypeDefinition(){}
IIRScram_ArrayTypeDefinition::~IIRScram_ArrayTypeDefinition(){}

IIRScram_TypeDefinition *
IIRScram_ArrayTypeDefinition::_get_element_subtype(){
  return dynamic_cast<IIRScram_TypeDefinition *>(get_element_subtype());
}

IIRScram_ScalarTypeDefinition *
IIRScram_ArrayTypeDefinition::_get_index_subtype(){
  return dynamic_cast<IIRScram_ScalarTypeDefinition *>(get_index_subtype());
}

IIR_Int32
IIRScram_ArrayTypeDefinition::get_num_indexes() {
  IIR_Int32 num_indexes = 1;

  IIRScram_TypeDefinition *current_subtype = _get_element_subtype();
  ASSERT(current_subtype != NULL);
  while( current_subtype->is_array_type() == TRUE
	 && current_subtype->is_element() == FALSE ){
    num_indexes++;
    current_subtype = current_subtype->_get_element_subtype();
    ASSERT(current_subtype != NULL);
  }

  return num_indexes;
}

IIRScram_ScalarTypeDefinition *
IIRScram_ArrayTypeDefinition::_build_proper_index( IIRScram_RangeTypeDefinition *range){
  IIRScram_ScalarTypeDefinition *range_type = 
    IIRScram_ScalarTypeDefinition::_determine_discrete_type( range );
  
  IIRScram_TypeDefinition *new_subtype =  range_type->_construct_new_subtype( NULL, range );

  ASSERT( new_subtype->is_scalar_type() == TRUE );

  return dynamic_cast<IIRScram_ScalarTypeDefinition *>(new_subtype);
}

IIRScram_TypeDefinition *
IIRScram_ArrayTypeDefinition::_index_constrain_array( IIRScram_ScalarTypeDefinition *constraint ){
#ifdef DEVELOPER_ASSERTIONS
  IIRScram_TypeDefinition *original_index_subtype = _get_resolved_index_subtype();
#endif

  IIRScram_ArraySubtypeDefinition *retval = NULL;

  IIRScram_TypeDefinition *current_index_type = _get_resolved_index_subtype(); 
  
  current_index_type = current_index_type->_construct_new_subtype( NULL, constraint );
  if( constraint->is_subtype() == FALSE && constraint->is_anonymous() == FALSE ){
    current_index_type->set_type_mark( constraint );
  }
  else{
    current_index_type->set_type_mark( constraint->_get_type_mark() );
  }

  retval = new IIRScram_ArraySubtypeDefinition();
  copy_location( constraint, retval );

  ASSERT( current_index_type->is_scalar_type() == TRUE );
  retval->set_index_subtype( dynamic_cast<IIRScram_ScalarTypeDefinition *>(current_index_type) );

  if( is_subtype() == TRUE ){
    retval->set_base_type( get_base_type() );    
  }
  else{
    retval->set_base_type( this );
  }

  ASSERT( original_index_subtype == _get_resolved_index_subtype() );

  return retval;
}

IIRScram_TypeDefinition *
IIRScram_ArrayTypeDefinition::_construct_new_subtype( IIRScram_Name                     *resolution_function,
						      IIRScram_ScalarTypeDefinition     *index_constraint){

  IIRScram_TypeDefinition *retval = NULL;

  if( resolution_function != NULL ){
    retval = _construct_new_subtype_resolution_function_only( resolution_function );
  }

  if( index_constraint != NULL ){
    retval = _index_constrain_array( index_constraint );
    retval->set_element_subtype( _get_element_subtype() );
    retval->set_declaration( index_constraint->get_declaration() );
  }
  
  if( retval == NULL ){
    // We'll just make a copy of ourseleves then.
    retval = _get_new_subtype();
    ASSERT( retval->_is_iir_array_type_definition() == TRUE );
    _clone( dynamic_cast<IIRScram_ArrayTypeDefinition *>(retval) );
    if( !is_subtype() ){
      retval->set_base_type( this );
    }
  }

  return retval;
}

IIRScram_ArrayTypeDefinition *
IIRScram_ArrayTypeDefinition::_construct_array_type( IIRScram_ScalarTypeDefinition      *index_subtype,
						     IIRScram_TypeDefinition            *element_subtype,
						     IIRScram_TypeDeclaration           *declaration){

  if( index_subtype->get_left() == NULL ){
    return _construct_unconstrained( index_subtype, element_subtype, declaration );
  }
  else{
    return _construct_constrained( index_subtype, element_subtype, declaration );
  }
}

IIRScram_ArraySubtypeDefinition *
IIRScram_ArrayTypeDefinition::_construct_unconstrained( IIRScram_ScalarTypeDefinition   *index_subtype,
						        IIRScram_TypeDefinition         *element_subtype,
							IIRScram_TypeDeclaration        *declaration){

  IIRScram_ArrayTypeDefinition *base_type = new IIRScram_ArrayTypeDefinition();
  index_subtype->copy_location( base_type );
  //  base_type->set_base_type(index_subtype->get_base_type());

  ASSERT( index_subtype->get_left() == NULL );
  ASSERT( index_subtype->get_direction() == NULL );
  ASSERT( index_subtype->get_right() == NULL );
  
  base_type->set_index_subtype( index_subtype );
  base_type->set_element_subtype( element_subtype );
  base_type->set_declaration( declaration );
  base_type->_set_design_file( index_subtype->_get_design_file() );

  IIRScram_ArraySubtypeDefinition *retval =
    dynamic_cast<IIRScram_ArraySubtypeDefinition *>(base_type->_construct_new_subtype( 0, 0 ));
  ASSERT( retval != 0 );

  retval->set_declaration( declaration );

  return retval;
}

IIRScram_ArraySubtypeDefinition *
IIRScram_ArrayTypeDefinition::_construct_constrained( IIRScram_ScalarTypeDefinition     *index_subtype,
						      IIRScram_TypeDefinition           *,
						      IIRScram_TypeDeclaration          *declaration){
  // This is the unconstrained base type mandated by the LRM.
  IIRScram_ArrayTypeDefinition *base_type = new IIRScram_ArrayTypeDefinition();
  index_subtype->copy_location( base_type );

  // This is implementing the rules of pg. 41, line 314 of the LRM.
  IIRScram_TypeDefinition *base_index_type;
  base_index_type = index_subtype->_get_new_subtype();
  base_index_type->set_base_type( index_subtype->get_base_type() );
  base_index_type->_set_resolution_function( index_subtype->_get_resolution_function() );
  base_index_type->set_type_mark( index_subtype );
  base_index_type->set_declaration( index_subtype->_get_declaration() );
  ASSERT( base_index_type->is_scalar_type_definition() == TRUE );
  base_type->set_index_subtype( dynamic_cast<IIRScram_ScalarTypeDefinition *>(base_index_type) );
  base_type->_get_resolved_index_subtype()->set_type_mark( index_subtype );
  base_type->_set_design_file( index_subtype->_get_design_file());

  IIRScram_TypeDefinition *temp =  base_type->_construct_new_subtype( 0, index_subtype );
  ASSERT( temp->get_kind() == IIR_ARRAY_SUBTYPE_DEFINITION );

  IIRScram_ArraySubtypeDefinition *retval = dynamic_cast<IIRScram_ArraySubtypeDefinition *>(temp);

  // This is a kludge for the code generator
  base_type->set_type_mark( retval );
  base_type->set_declaration( declaration );
  retval->set_declaration( declaration );
  return retval; 
}

IIRScram_TypeDefinition *
IIRScram_ArrayTypeDefinition::_get_new_subtype(){
  IIRScram_TypeDefinition * retval = new IIRScram_ArraySubtypeDefinition();
  copy_location( this, retval );
  return retval;
}

IIRScram *
IIRScram_ArrayTypeDefinition::_clone(){
  IIRScram_ArrayTypeDefinition *type_def = new IIRScram_ArrayTypeDefinition();
  _clone( type_def );

  return type_def;
}

void 
IIRScram_ArrayTypeDefinition::_clone( IIRScram *my_clone ){
  ASSERT( my_clone->_is_iir_array_type_definition() == TRUE );
  IIRScram_ArrayTypeDefinition *as_array_type = dynamic_cast<IIRScram_ArrayTypeDefinition *>(my_clone);
  
  as_array_type->set_index_subtype( get_index_subtype() );
  as_array_type->set_element_subtype( get_element_subtype() );

  IIRScram_TypeDefinition::_clone( my_clone );
}

void
IIRScram_ArrayTypeDefinition::_type_check(){
  // See lines 369-372 of 1076-1993 for this rule.  It seems to be OK to declare
  // an array of access types to unconstained arrays, hence the first part of the rule.
  if( _get_final_subtype()->_is_iir_array_type_definition() == TRUE &&
      _get_final_subtype()->is_unconstrained_array_type() == TRUE ){
    ostringstream err;
    err << "The element subtype indication for an array type definition must define "
	<< "a constrained array subtype.";
    report_error( this, err.str() );
  }
}

void 
IIRScram_ArrayTypeDefinition::_come_into_scope( symbol_table *sym_tab,
						IIRScram_TypeDeclaration *td ){
  IIRScram_TypeDefinition::_come_into_scope( sym_tab, td );

  if( get_num_indexes() == 1 ){
    sym_tab->get_in_scope_one_d_array_types()->add( dynamic_cast<IIRScram_ArrayTypeDefinition *>(this) );
  }

  sym_tab->get_in_scope_array_types()->add( dynamic_cast<IIRScram_ArrayTypeDefinition *>(this) );
}

void 
IIRScram_ArrayTypeDefinition::_come_out_of_scope( symbol_table *sym_tab ){
  if( get_num_indexes() == 1 ){
    sym_tab->get_in_scope_one_d_array_types()->remove( dynamic_cast<IIRScram_ArrayTypeDefinition *>(this) );
  }

  sym_tab->get_in_scope_array_types()->remove( dynamic_cast<IIRScram_ArrayTypeDefinition *>(this) );
}

void 
IIRScram_ArrayTypeDefinition::_build_implicit_operators( savant::set<IIRScram_Declaration> *add_to ){
  const char *shift_operators[] = { "\"sll\"", "\"srl\"", "\"sla\"", "\"sra\"",
				    "\"rol\"", "\"ror\"", NULL };

  IIRScram_TypeDefinition::_build_implicit_operators( add_to );

  StandardPackage *package = _get_design_file()->get_standard_package();
  if( get_num_indexes() == 1 ){
    IIRScram_TypeDefinition *boolean_type = dynamic_cast<IIRScram_TypeDefinition *>(package->get_boolean_type());
    IIRScram_TypeDefinition *bit_type =  dynamic_cast<IIRScram_TypeDefinition *>(package->get_bit_type());
    IIRScram_TypeDefinition *integer_type = dynamic_cast<IIRScram_TypeDefinition *>(package->get_integer_type());
    
    // The order of the operands is result type, left type, right type.

    if( _get_element_subtype()->is_discrete_type() == TRUE ){
      _build_ordering_operators( add_to );
    }
    
    if( _get_element_subtype()->is_compatible( boolean_type ) != NULL ||
	_get_element_subtype()->is_compatible( bit_type ) != NULL ){
      // return this type, left is this type, right is integer
      IIRScram_TypeDefinition::_build_implicit_operators( shift_operators, add_to, this, this, integer_type );      
      IIRScram_TypeDefinition::_build_logical_operators( add_to );
    }

    IIRScram_TypeDefinition::_build_implicit_operator( "\"&\"", add_to, this, this, this );    
    IIRScram_TypeDefinition::_build_implicit_operator( "\"&\"", add_to, this, _get_element_subtype(),this);    
    IIRScram_TypeDefinition::_build_implicit_operator( "\"&\"", add_to, this, this, _get_element_subtype());    
    IIRScram_TypeDefinition::_build_implicit_operator( "\"&\"", add_to, this, _get_element_subtype(), _get_element_subtype());
  }
}

IIRScram_TypeDefinition*
IIRScram_ArrayTypeDefinition::_get_final_subtype() {
  return dynamic_cast<IIRScram_TypeDefinition *>(get_final_subtype());
}

void 
IIRScram_ArrayTypeDefinition::_set_resolution_function( IIRScram_FunctionDeclaration * ){
  ostringstream err;
  err << "Internal error - IIRScram_ArrayTypeDefinition::_set_resolution_function was "
      << "called.  Resolution functions can't be associated with an array type and this "
      << "should have been caught earlier.";
  report_error( this, err.str() );
}

visitor_return_type *
IIRScram_ArrayTypeDefinition::_accept_visitor( node_visitor *visitor,
					       visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ArrayTypeDefinition(this, arg);
}
