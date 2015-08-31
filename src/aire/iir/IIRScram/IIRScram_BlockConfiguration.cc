
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

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_ArchitectureDeclaration.hh"
#include "IIRScram_BlockConfiguration.hh"
#include "IIRScram_ConfigurationDeclaration.hh"
#include "IIRScram_ComponentConfiguration.hh"
#include "IIRScram_ConfigurationItemList.hh"
#include "IIRScram_DeclarationList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EntityDeclaration.hh"
#include "IIRScram_IndexedName.hh"
#include "IIRScram_IntegerSubtypeDefinition.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_SliceName.hh"
#include "IIRScram_Statement.hh"
#include "StandardPackage.hh"

#include "error_func.hh"
#include "library_manager.hh"
#include "resolution_func.hh"
#include "symbol_table.hh"

#include <sstream>
using std::ostringstream;

extern bool parse_error;
extern bool debug_symbol_table;

IIRScram_BlockConfiguration::IIRScram_BlockConfiguration() {
  set_use_clause_list(new IIRScram_DeclarationList());
  set_configuration_item_list(new IIRScram_ConfigurationItemList());  
}

IIRScram_BlockConfiguration::~IIRScram_BlockConfiguration(){}

void 
IIRScram_BlockConfiguration::_type_check_configuration_item( IIRScram_List *statement_list, 
							     IIRScram *enclosing_region ){
  _get_symbol_table()->open_scope( this );
  _type_check_block_specification( statement_list, enclosing_region );
  ASSERT( _get_block_specification()->is_resolved() == TRUE );

  if( debug_symbol_table == true ){
    cerr << "Type checking block configuration - making |"
	 << _get_block_specification() << "| visible" << endl;
  }
  _get_block_specification()->_make_interface_visible(_get_symbol_table() );

  _get_configuration_item_list()->_type_check_configuration_item( _get_block_specification()->_get_statement_list(),
							  this );
  _get_symbol_table()->close_scope( this );
}

void 
IIRScram_BlockConfiguration::_type_check_block_specification( IIRScram_List *statement_list,
							      IIRScram *enclosing_region ){
  // This method implements the type checking described in 1.3.1 of the '93 LRM.
  ASSERT( enclosing_region != NULL );

  // What type the specification is allowed to be depends largely on region 
  // it is contained in.
  switch( enclosing_region->get_kind() ){
  case IIR_CONFIGURATION_DECLARATION:{
    _resolve_specification_inside_configuration_declaration( dynamic_cast<IIRScram_ConfigurationDeclaration *>(enclosing_region) );
    
    break;
  }
  case IIR_COMPONENT_CONFIGURATION:{
    _resolve_specification_inside_component_configuration( dynamic_cast<IIRScram_ComponentConfiguration *>(enclosing_region) );
    break;
  }
  case IIR_BLOCK_CONFIGURATION:{
    _resolve_specification_inside_block_configuration( statement_list,
						       dynamic_cast<IIRScram_BlockConfiguration *>(enclosing_region));
    break;
  }
  default:{
    ostringstream err;
    err << "Internal error in IIRScram_BlockConfiguration::_type_check_block_specification -"
	<< " don't know what to do with enclosing region type " 
	<< enclosing_region->get_kind_text();
    report_error( this, err.str() );
    return;
  }
  }
  
  ASSERT( _get_block_specification()->is_resolved() == TRUE );

}

void 
IIRScram_BlockConfiguration::_resolve_specification_inside_configuration_declaration( IIRScram_ConfigurationDeclaration *enclosing_declaration ){
  // This method implements pg. 13 line 362 of the 93 LRM.

  ASSERT( enclosing_declaration != NULL );
  // The block specification must be an architecture name, and that
  // architecture name must denote a design entity body whose
  // interface is defined by the entity declaration denoted by the
  // entity name of the enclosing configuration declaration.
  IIRScram_EntityDeclaration *configuration_entity = enclosing_declaration->_get_entity();
  ASSERT( configuration_entity != NULL );

  IIRScram *original_specification = _get_block_specification();
  IIRScram_Declaration *specification_declaration = NULL;
  if( original_specification->get_kind() != IIR_SIMPLE_NAME &&
      original_specification->get_kind() != IIR_SELECTED_NAME ){
    ostringstream err;
    err << "Syntax error at |" << *original_specification << "| -"
	<< " expecting a simple or selected name.";
    report_error( original_specification, err.str() );
    return;
  }

  ASSERT( original_specification->_is_iir_name() == TRUE );
  specification_declaration = 
    dynamic_cast<IIRScram_Declaration *>(library_manager::instance()->lookup_architecture( TRUE, 
                                                                                           configuration_entity,
                                                                                           dynamic_cast<IIR_Name *>(original_specification)));

  if( specification_declaration == NULL ){
    ASSERT( parse_error == TRUE );
    return;
  }

  set_block_specification( original_specification->_decl_to_decl( specification_declaration ) );
}

void 
IIRScram_BlockConfiguration::_resolve_specification_inside_component_configuration( IIRScram_ComponentConfiguration *component_configuration ){
  // This method implements pg. 13 line 367 of the 93 LRM - If a block
  // configuration appears immediately within a component configuration,
  // then the corresponding components must be fully bound (see section
  // 5.2.1.1), the block specification of that block configuration denote
  // the same architecture body as that to which the corresponding
  // components are bound.

  ASSERT( component_configuration != NULL );
  ASSERT( _get_block_specification() != NULL );

  // So, we need to resolve the block specification to a component
  // instance within the component configuration passed in.

  // In the debugging case, we have get_block_specification == ALUBLOCK_D

  // This should give us the binding indication.  NULL means open
  IIRScram *binding_indication = component_configuration->_get_entity_aspect();
  if( binding_indication != NULL ){
    ASSERT( binding_indication->_is_iir_declaration() );

    IIRScram *resolved = _get_block_specification()->_decl_to_decl(dynamic_cast<IIRScram_Declaration *>(binding_indication) );
    set_block_specification( dynamic_cast<IIRScram_Declaration *>(resolved) );    
  }
  else{
    ostringstream err;
    err << "No binding indication, default or otherwise, for this block configuration";
    report_error( this, err.str() );
  }
}

void 
IIRScram_BlockConfiguration::_resolve_specification_inside_block_configuration( IIRScram_List *,
										IIRScram_BlockConfiguration * ){
  IIRScram_IndexedName *original_indexed_name = NULL;
  IIRScram_Name *to_lookup = NULL;
  StandardPackage *package = _get_design_file()->get_standard_package();

  if( get_block_specification()->get_kind() == IIR_INDEXED_NAME ){
    original_indexed_name = dynamic_cast<IIRScram_IndexedName *>(_get_block_specification());
    IIRScram *prefix = original_indexed_name->_get_prefix();
    ASSERT( prefix->_is_iir_name() == TRUE );
    to_lookup = dynamic_cast<IIRScram_Name *>(prefix);
  }
  else{
    ASSERT( _get_block_specification()->_is_iir_name() == TRUE );
    to_lookup = dynamic_cast<IIRScram_Name *>(_get_block_specification());
  }
  
  IIRScram_Label *my_label = to_lookup->_lookup_label( TRUE );
  IIRScram_Statement *current_statement = my_label->_get_statement();
  if( current_statement->get_kind() != IIR_BLOCK_STATEMENT &&
      current_statement->get_kind() != IIR_CONCURRENT_GENERATE_FOR_STATEMENT &&
      current_statement->get_kind() != IIR_CONCURRENT_GENERATE_IF_STATEMENT ){
    ostringstream err;
    err << "A block configuration that appears within another block configuration must "
	<< "have a block specification that specifies either a block statement label, "
	<< "or a generate statement label. |" << *my_label << "| specifies neither.";
    report_error( this, err.str() );
    return;
  }
      
  if( original_indexed_name != NULL ){
    if( my_label->get_statement()->get_kind() != IIR_CONCURRENT_GENERATE_FOR_STATEMENT ){
      ostringstream err;
      err << "Index specifications may only be applied to generate statements"
	  << " using the \"for\" syntax.";
      report_error( this, err.str() );
    }
    IIRScram_SliceName *new_spec = new IIRScram_SliceName();
    copy_location( this, new_spec );
    new_spec->set_prefix( my_label );
    IIRScram *suffix = original_indexed_name->_get_suffix(); 

    suffix = suffix->_semantic_transform( dynamic_cast<IIRScram_TypeDefinition *>(package->get_savant_universal_integer()) );
    suffix->_type_check( dynamic_cast<IIRScram_TypeDefinition *>(package->get_savant_universal_integer()) );
    suffix = suffix->_rval_to_decl( dynamic_cast<IIRScram_TypeDefinition *>(package->get_savant_universal_integer()));

    new_spec->set_suffix( suffix );

    set_block_specification( new_spec );
  }
  else{
    set_block_specification( my_label );
  }
}

visitor_return_type *
IIRScram_BlockConfiguration::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_BlockConfiguration(this, arg);
};

IIRScram*
IIRScram_BlockConfiguration::_get_block_specification() {
  return dynamic_cast<IIRScram *>(get_block_specification());
}

IIRScram_DeclarationList *
IIRScram_BlockConfiguration::_get_use_clause_list() {
  return dynamic_cast<IIRScram_DeclarationList *>(get_use_clause_list());
}

IIRScram_ConfigurationItemList *
IIRScram_BlockConfiguration::_get_configuration_item_list() {
  return dynamic_cast<IIRScram_ConfigurationItemList *>(get_configuration_item_list());
}
