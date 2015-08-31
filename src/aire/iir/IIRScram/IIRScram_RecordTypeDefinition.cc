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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------
#include "IIRScram_DesignFile.hh"
#include "IIRScram_ElementDeclaration.hh"
#include "IIRScram_ElementDeclarationList.hh"
#include "IIRScram_FunctionDeclaration.hh"
#include "IIRScram_RecordTypeDefinition.hh"
#include "IIRScram_ScalarTypeDefinition.hh"
#include "IIRScram_TextLiteral.hh"

#include "symbol_table.hh"
#include "resolution_func.hh"
#include "error_func.hh"
#include "savant.hh"

#include <sstream>
using std::ostringstream;

IIRScram_RecordTypeDefinition::IIRScram_RecordTypeDefinition() {
  set_element_declarations(new IIRScram_ElementDeclarationList());
}

IIRScram_RecordTypeDefinition::~IIRScram_RecordTypeDefinition(){}

IIRScram_TypeDefinition *
IIRScram_RecordTypeDefinition::_construct_new_subtype( IIRScram_Name  *resolution_function,
						       IIRScram_ScalarTypeDefinition *new_constraint){
  IIRScram_TypeDefinition *retval = NULL;

  retval = _construct_new_subtype_resolution_function_only( resolution_function );
  if( new_constraint != 0 ){
    ostringstream err;
    err << "Constraints may not be applied to record types.";
    report_error( this, err.str() );
  }

  return retval;
}

IIRScram_TypeDefinition *
IIRScram_RecordTypeDefinition::_get_new_subtype(){
  IIRScram_TypeDefinition *retval = new IIRScram_RecordTypeDefinition();
  copy_location( this, retval );
  return retval;
}

void
IIRScram_RecordTypeDefinition::_type_check(){
  if( _get_resolution_function() != NULL ){
    _get_resolution_function()->_type_check_resolution_function( this );
  }
  IIRScram_TypeDefinition::_type_check();
}

void
IIRScram_RecordTypeDefinition::_clone( IIRScram *copy_into ){
  ASSERT( copy_into->_is_iir_record_type_definition() == TRUE );
  IIRScram_RecordTypeDefinition *as_record_type = dynamic_cast<IIRScram_RecordTypeDefinition *>(copy_into);

  as_record_type->set_declaration( _get_declaration() );
  as_record_type->set_type_mark( _get_type_mark() );
  as_record_type->set_resolution_function( get_resolution_function() );
  // This copies the elements over.
  as_record_type->set_element_declarations(get_element_declarations());
  // This should take care of anything else:
  IIRScram_TypeDefinition::_clone( copy_into );
}

IIRScram *
IIRScram_RecordTypeDefinition::_clone(){
  IIRScram_RecordTypeDefinition *retval;
  IIRScram_TypeDefinition *temp = _get_new_subtype();

  ASSERT( temp->_is_iir_record_type_definition() == TRUE );
  retval = dynamic_cast<IIRScram_RecordTypeDefinition *>(temp);

  _clone( retval );

  ASSERT( retval->get_element_declarations()->size() == get_element_declarations()->size() );
  ASSERT( retval->get_kind() == get_kind() );

  return retval;
}

void
IIRScram_RecordTypeDefinition::_make_interface_visible( symbol_table *sym_tab ){
  sym_tab->make_visible( _get_element_declarations() );
}


void
IIRScram_RecordTypeDefinition::_come_into_scope( symbol_table *sym_tab,
                                               IIRScram_TypeDeclaration *td){
  sym_tab->get_in_scope_record_types()->add( dynamic_cast<IIRScram_RecordTypeDefinition *>(this ) );
  IIRScram_TypeDefinition::_come_into_scope( sym_tab, td );
}

void
IIRScram_RecordTypeDefinition::_come_out_of_scope( symbol_table *sym_tab ){
  sym_tab->get_in_scope_record_types()->remove( dynamic_cast<IIRScram_RecordTypeDefinition *>(this ) );
}

visitor_return_type *
IIRScram_RecordTypeDefinition::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_RecordTypeDefinition(this, arg);
}

IIRScram_FunctionDeclaration*
IIRScram_RecordTypeDefinition::_get_resolution_function(){
  return dynamic_cast<IIRScram_FunctionDeclaration*>(get_resolution_function());
}
void
IIRScram_RecordTypeDefinition::_set_resolution_function(IIRScram_FunctionDeclaration *new_function ){
  set_resolution_function( new_function );
}

IIRScram_TypeDefinition *
IIRScram_RecordTypeDefinition::_get_element_subtype(int i) {
  return dynamic_cast<IIRScram_TypeDefinition *>(get_element_subtype(i));
}

IIRScram_ElementDeclarationList *
IIRScram_RecordTypeDefinition::_get_element_declarations() {
  return dynamic_cast<IIRScram_ElementDeclarationList *>(get_element_declarations()); 
}
