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

#include "IIRScram_AccessSubtypeDefinition.hh"
#include "IIRScram_ArrayTypeDefinition.hh"
#include "IIRScram_ConstantInterfaceDeclaration.hh"
#include "IIRScram_Declaration.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_FunctionDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_InterfaceList.hh"
#include "IIRScram_ScalarTypeDefinition.hh"
#include "IIRScram_ProcedureDeclaration.hh"
#include "IIRScram_TypeDefinition.hh"
#include "error_func.hh"
#include "symbol_table.hh"
#include "set.hh"
#include <sstream>

IIRScram_AccessTypeDefinition::IIRScram_AccessTypeDefinition(){}
IIRScram_AccessTypeDefinition::~IIRScram_AccessTypeDefinition(){}

IIR_Boolean 
IIRScram_AccessTypeDefinition::_designates_incomplete_type() {
  IIRScram_TypeDefinition *type = _get_designated_type();
  if(  type != NULL && type->is_incomplete_type_definition() == TRUE ){
    return TRUE;
  } else {
    return FALSE;
  }
}

IIRScram_TypeDefinition *
IIRScram_AccessTypeDefinition::_get_element_subtype(){
  return _get_designated_type()->_get_element_subtype();
}

void 
IIRScram_AccessTypeDefinition::_come_into_scope( symbol_table *sym_tab, 
						 IIRScram_TypeDeclaration *type_declaration){
  
  sym_tab->get_in_scope_access_types()->add( this );

  if( type_declaration->get_implicit_declarations() == NULL ){
    IIRScram_TypeDefinition::_come_into_scope( sym_tab, type_declaration );
  
    const char *name = "deallocate";
    IIRScram_ProcedureDeclaration *new_procedure_declaration = new IIRScram_ProcedureDeclaration();
    copy_location( this, new_procedure_declaration );
    new_procedure_declaration->set_declarator( IIRScram_Identifier::get( name, strlen(name ), get_design_file()->get_class_factory() ) );
    new_procedure_declaration->set_is_implicit( TRUE );
    
    IIRScram_ConstantInterfaceDeclaration *new_interface_declaration = NULL;
    new_interface_declaration  = new IIRScram_ConstantInterfaceDeclaration();
    new_interface_declaration->set_is_implicit( TRUE );
    copy_location( this, new_interface_declaration );
    
    name = "p";
    new_procedure_declaration->get_interface_declarations()->append( new_interface_declaration );
    
    new_interface_declaration->set_declarator(  IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    new_interface_declaration->set_subtype( this );
    new_interface_declaration->set_mode( IIR_INOUT_MODE );
    
    new_procedure_declaration->_add_declaration();
    
    type_declaration->get_implicit_declarations()->add( new_procedure_declaration );    
  }
  else{
    sym_tab->add_declaration( type_declaration->get_implicit_declarations()->convert_set<IIR_Declaration>());   
  }
}

void 
IIRScram_AccessTypeDefinition::set_is_element( IIR_Boolean new_is_element ){
  IIRScram_TypeDefinition *type = _get_designated_type();
  type->set_is_element( new_is_element );
}


IIRScram *
IIRScram_AccessTypeDefinition::_clone(){
  IIRScram_AccessTypeDefinition *retval = new IIRScram_AccessTypeDefinition();
  _clone( retval );

  return retval;
}


void 
IIRScram_AccessTypeDefinition::_clone( IIRScram *copy_into ){
  ASSERT( copy_into->_is_iir_access_type_definition() == TRUE );
  IIRScram_AccessTypeDefinition *as_access_type = dynamic_cast<IIRScram_AccessTypeDefinition *>(copy_into);

  as_access_type->set_designated_type( get_designated_type() );

  IIRScram_TypeDefinition::_clone( copy_into );
}

void 
IIRScram_AccessTypeDefinition::_come_out_of_scope( symbol_table *sym_tab ){
  sym_tab->get_in_scope_access_types()->remove( (IIRScram_AccessTypeDefinition *)this );
}

IIRScram_TypeDefinition *
IIRScram_AccessTypeDefinition::_construct_new_subtype( IIRScram_Name                 *resolution_function,
						       IIRScram_ScalarTypeDefinition *new_constraint){

  IIRScram_AccessSubtypeDefinition *retval = new IIRScram_AccessSubtypeDefinition();
  IIRScram_TypeDefinition *new_designated_type = NULL;
  IIRScram_TypeDefinition *old_type = _get_designated_type();

  if( old_type != NULL && old_type->is_incomplete_type_definition() == FALSE ){
    new_designated_type = old_type->_construct_new_subtype( 0, new_constraint);
    retval->set_designated_subtype( new_designated_type );
  }
  else{
    ASSERT( new_constraint == NULL );
  }

  if( is_subtype() == TRUE ){
    retval->set_base_type( get_base_type() );
  }
  else{
    retval->set_base_type( this );
  }

  if( resolution_function != NULL ){
    retval->set_resolution_function(  _resolve_resolution_function( resolution_function ));
  }

  if( new_constraint != 0 ){
    retval->set_declaration( new_constraint->get_declaration() );
  }

  return retval;
}

IIRScram_AccessSubtypeDefinition *
IIRScram_AccessTypeDefinition::_construct_new_type( IIRScram_TypeDefinition     *designated_type,
						    IIRScram_TypeDeclaration    *type_decl,
                                                    IIRScram_DesignFile         *design_file){

  IIRScram_AccessTypeDefinition *base_type = new IIRScram_AccessTypeDefinition();
  base_type->set_designated_type( designated_type );
  base_type->set_declaration( type_decl );
  base_type->_set_design_file( design_file );

  IIRScram_TypeDefinition *temp =  base_type->_construct_new_subtype( 0, 0 );
  ASSERT( temp->get_kind() == IIR_ACCESS_SUBTYPE_DEFINITION );
  IIRScram_AccessSubtypeDefinition *retval = dynamic_cast<IIRScram_AccessSubtypeDefinition *>(temp);
  retval->set_declaration( type_decl );
  retval->set_designated_subtype( designated_type );

  return retval;
}


void 
IIRScram_AccessTypeDefinition::_set_resolution_function( IIRScram_FunctionDeclaration * ){
  ostringstream err;
  err << "Internal error - IIRScram_AccessTypeDefinition::_set_resolution_function was "
      << "called.  Resolution functions can't be associated with an access type and this "
      << "should have been caught earlier.";
  report_error( this, err.str() );
}

IIRScram_TypeDefinition *
IIRScram_AccessTypeDefinition::_index_constrain_array( IIRScram_ScalarTypeDefinition *constraint){
  IIRScram_TypeDefinition *retval = this;
  IIRScram_TypeDefinition *type = _get_designated_type();
  ASSERT( type != NULL && type->is_array_type() == true );
  type->_index_constrain_array( constraint);

  return retval;
}

visitor_return_type *
IIRScram_AccessTypeDefinition::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_AccessTypeDefinition(this, arg);
}

IIRScram_TypeDefinition *
IIRScram_AccessTypeDefinition::_get_designated_type() {
  return dynamic_cast<IIRScram_TypeDefinition *>(get_designated_type());
}

IIR_Int32
IIRScram_AccessTypeDefinition::get_num_indexes(){
  IIRScram_TypeDefinition *type = _get_designated_type();

  ASSERT(type != NULL);
  return type->get_num_indexes();
}
