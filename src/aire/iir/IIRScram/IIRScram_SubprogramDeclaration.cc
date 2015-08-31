
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
//          Malolan Chetlur     mal@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_AliasDeclaration.hh"
#include "IIRScram_AttributeSpecificationList.hh"
#include "IIRScram_AttributeSpecification.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_FunctionDeclaration.hh"
#include "IIRScram_InterfaceDeclaration.hh"
#include "IIRScram_InterfaceList.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_ProcedureDeclaration.hh"
#include "IIRScram_ProcessStatement.hh"
#include "IIRScram_ReturnStatement.hh"
#include "IIRScram_SequentialStatementList.hh"
#include "IIRScram_StringLiteral.hh"
#include "IIRScram_SubprogramDeclaration.hh"
#include "IIRScram_SubtypeDeclaration.hh"
#include "IIRScram_TypeDefinition.hh"

#include "set.hh"
#include "resolution_func.hh"
#include "symbol_table.hh"
#include "savant.hh"


IIRScram_SubprogramDeclaration::IIRScram_SubprogramDeclaration(){
  set_interface_declarations(new IIRScram_InterfaceList());
  set_subprogram_declarations(new IIRScram_DeclarationList());
  set_subprogram_body(new IIRScram_SequentialStatementList());
  set_attributes(new IIRScram_AttributeSpecificationList());
}

IIRScram_SubprogramDeclaration::~IIRScram_SubprogramDeclaration() {
  //Release the list memory
  delete get_interface_declarations();
  delete get_subprogram_declarations();
  delete get_subprogram_body();
  delete get_attributes();
}

// This method publishes file_close (which is implicit) for files declared
// in this subprogram


bool 
IIRScram_SubprogramDeclaration::_check_param( IIRScram_TypeDefinition *type_def,
					      int param_num ){

  ASSERT( param_num >= 0 );
  ASSERT( type_def != NULL );

  IIRScram_TypeDefinition *param_type = _get_type_of_param( param_num );
  if( param_type == NULL ){
    return false;
  }

  // Now current is on the right argument...
  if( param_type->is_compatible( type_def ) != NULL ){
    return true;
  }
  else{
    return false;
  }

}

void 
IIRScram_SubprogramDeclaration::_type_check(){
  _get_subprogram_declarations()->_type_check_attribute_specifications( _get_subprogram_body() );
}

IIR_Boolean 
IIRScram_SubprogramDeclaration::_type_check_return_statements( IIRScram_TypeDefinition *my_rval ){
  IIR_Boolean retval = FALSE;
  
  savant::set<IIRScram_TypeDefinition> *context_set = NULL;
  if( my_rval != NULL ){
    context_set = new savant::set<IIRScram_TypeDefinition>( my_rval );
  }

  IIRScram_SequentialStatement *stmt = NULL;

  IIR_Boolean found_one = FALSE;  
  stmt = dynamic_cast<IIRScram_SequentialStatement *>(get_subprogram_body()->first());
  while( stmt != NULL ){
    if( stmt->get_kind() == IIR_RETURN_STATEMENT ){
      IIRScram_ReturnStatement *return_stmt = dynamic_cast<IIRScram_ReturnStatement *>(stmt);
      return_stmt->set_enclosing_subprogram(dynamic_cast<IIRScram_SubprogramDeclaration *>(this));
      return_stmt->_type_check( context_set );

      ASSERT( return_stmt->is_resolved() == TRUE );

      retval = TRUE;
    }
    else if( stmt->has_statement_list() == TRUE ){
      found_one = 
	stmt->_type_check_return_statements( context_set, dynamic_cast<IIRScram_SubprogramDeclaration *>(this) );
      if( found_one == TRUE ){
	retval = TRUE;
      }      
    }

    stmt = dynamic_cast<IIRScram_SequentialStatement *>(get_subprogram_body()->successor( stmt ));
  }
  
  delete context_set;

  return retval;
}

IIRScram_TypeDefinition *
IIRScram_SubprogramDeclaration::_get_type_of_param( int param_number ){

  IIRScram_InterfaceDeclaration *current = 
    dynamic_cast<IIRScram_InterfaceDeclaration *>(get_interface_declarations()->first());
  if( current == NULL ){
    return NULL;
  }

  int i;
  for( i = 0; i < param_number; i++ ){
    current = 
      dynamic_cast<IIRScram_InterfaceDeclaration *>(get_interface_declarations()->successor( current ));

    if( current == NULL ){
      return NULL;
    }  
  }

  return current->_get_subtype();
}

IIR_Boolean 
IIRScram_SubprogramDeclaration::_compare_signatures( IIRScram_SubprogramDeclaration     *a,
						     IIRScram_SubprogramDeclaration     *b){
  ASSERT( a != NULL );
  ASSERT( b != NULL );
  
  if( a->_get_subtype()->is_compatible( b->_get_subtype()) == NULL ){
    return FALSE;
  }

  int a_num_params =  a->get_interface_declarations()->size();
  int b_num_params =  b->get_interface_declarations()->size();
  if( a_num_params != b_num_params ){
    return FALSE;
  }

  int i;
  for( i = 0 ; i < a_num_params; i++ ){
    if( a->_get_type_of_param( i )->is_compatible( b->_get_type_of_param( i ) ) == NULL ){
      return FALSE;
    }
  }

  // If we made it here, everything matched up...
  return TRUE;
}

void
IIRScram_SubprogramDeclaration::_make_interface_visible( symbol_table *sym_tab ){
  sym_tab->make_visible( dynamic_cast<IIRScram_DeclarationList *>(get_interface_declarations()) );
}

IIR_Boolean 
IIRScram_SubprogramDeclaration::_is_homograph_of( IIRScram_Declaration *compare_to ){
  ASSERT( compare_to != NULL );
  ASSERT( IIRBase_TextLiteral::cmp( compare_to->_get_declarator(), _get_declarator() ) == 0 );

  // If they're not the same kind of node, they're not.
  if( get_kind() != compare_to->get_kind() ){
    return FALSE;
  }

  ASSERT( compare_to->is_subprogram() == TRUE );
  IIRScram_SubprogramDeclaration *compare_as_subprog = dynamic_cast<IIRScram_SubprogramDeclaration *>(compare_to);
  
  if( _compare_signatures( this, compare_as_subprog ) == FALSE ){
    return FALSE;
  }
  
  return TRUE;
}

void 
IIRScram_SubprogramDeclaration::_add_declaration(){
  _get_symbol_table()->add_subprogram_declaration( dynamic_cast<IIRScram_SubprogramDeclaration *>(this) );
}

visitor_return_type *
IIRScram_SubprogramDeclaration::_accept_visitor( node_visitor *visitor, 
						 visitor_argument_type *arg){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_SubprogramDeclaration(this, arg);
}

IIRScram_AttributeSpecificationList* 
IIRScram_SubprogramDeclaration::_get_attribute_specification_list() {
  return dynamic_cast<IIRScram_AttributeSpecificationList *>(get_attributes());
}

IIR_Int32
IIRScram_SubprogramDeclaration::_num_required_args(){
  int retval = 0;

  IIRScram_InterfaceDeclaration *current_decl;
  current_decl =  dynamic_cast<IIRScram_InterfaceDeclaration *>(get_interface_declarations()->first());
  while ( current_decl != NULL ){
    if( current_decl->_get_value() == NULL ){
      retval++;
    }
    current_decl = dynamic_cast<IIRScram_InterfaceDeclaration *>(get_interface_declarations()->successor( current_decl ));
  }

  return retval;
}

IIR_Boolean 
IIRScram_SubprogramDeclaration::_can_be_in_same_region( IIRScram_Declaration *to_check ){
  if(( contains_body() == TRUE && to_check->contains_body() == FALSE ) ||
     ( contains_body() == FALSE && to_check->contains_body() == TRUE )){
    return TRUE;
  }
  else if(( _is_implicit_operator() == TRUE && to_check->_is_implicit_operator() == FALSE )||
	  ( _is_implicit_operator() == FALSE && to_check->_is_implicit_operator() == TRUE )){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

IIR_Boolean 
IIRScram_SubprogramDeclaration::_is_implicit_operator(){
  if( is_implicit_declaration() == TRUE && is_operator() == TRUE ){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

// IIRBase Function Wrapper(s)
IIRScram_InterfaceList *
IIRScram_SubprogramDeclaration::_get_interface_declarations() {
  return dynamic_cast<IIRScram_InterfaceList *>(get_interface_declarations());
}

IIRScram_SequentialStatementList *
IIRScram_SubprogramDeclaration::_get_subprogram_body() {
  return dynamic_cast<IIRScram_SequentialStatementList *>(get_subprogram_body());
}

IIRScram_DeclarationList *
IIRScram_SubprogramDeclaration::_get_subprogram_declarations() {
  return dynamic_cast<IIRScram_DeclarationList *>(get_subprogram_declarations());
}

IIRScram_List *
IIRScram_SubprogramDeclaration::_get_statement_list(){
  return dynamic_cast<IIRScram_List *>(get_subprogram_body());
}
