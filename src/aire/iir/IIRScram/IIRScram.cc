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
#include "IIRScram.hh"
#include "IIRScram_AccessTypeDefinition.hh"
#include "IIRScram_AliasDeclaration.hh"
#include "IIRScram_ArchitectureDeclaration.hh"
#include "IIRScram_ArchitectureStatement.hh"
#include "IIRScram_ArchitectureStatementList.hh"
#include "IIRScram_AssociationElementByExpression.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_AttributeSpecification.hh"
#include "IIRScram_AttributeSpecificationList.hh"
#include "IIRScram_BlockStatement.hh"
#include "IIRScram_ComponentDeclaration.hh"
#include "IIRScram_ConfigurationDeclaration.hh"
#include "IIRScram_ConfigurationSpecification.hh"
#include "IIRScram_ConstantDeclaration.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_DeclarationList.hh"
#include "IIRScram_EntityDeclaration.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "IIRScram_GenericList.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_LibraryDeclaration.hh"
#include "IIRScram_PortList.hh"
#include "IIRScram_PackageDeclaration.hh"
#include "IIRScram_ProcessStatement.hh"
#include "IIRScram_RangeTypeDefinition.hh"
#include "IIRScram_SignalDeclaration.hh"
#include "IIRScram_SignalInterfaceDeclaration.hh"
#include "error_func.hh"
#include "include_manager.hh"
#include "library_manager.hh"
#include "resolution_func.hh"
#include "set.hh"
#include "symbol_table.hh"
#include "StandardPackage.hh"
#include <clutils/StringUtilities.h>
#include <cstring>
#include <sstream>

class IIR_ContributionAttribute;
class IIR_ReferenceAttribute;

extern bool parse_error;
extern bool debug_symbol_table;

IIRScram::IIRScram(){}

IIRScram::~IIRScram() {}

IIRScram_TypeDefinition* 
IIRScram::_get_name_type() {
  _report_undefined_scram_fn("_get_name_type()");
  return NULL;
}

IIR_Boolean
IIRScram::_is_attribute(){ return FALSE; }

IIR_Boolean
IIRScram::_is_numeric_literal() {
  if( _is_integer_literal() == TRUE ||  _is_floating_literal() == TRUE ){
    return TRUE;
  }
  else {
    return FALSE;
  }
}

IIR_Boolean
IIRScram::_is_quantity() {
  return FALSE;
}

IIR_Boolean
IIRScram::_is_terminal() {
  return FALSE;
}

void 
IIRScram::_type_check( IIRScram_TypeDefinition *input_decl ){
  savant::set<IIRScram_TypeDefinition> temp_set;
  temp_set.add( input_decl );
  _type_check( &temp_set );
}

IIRScram *
IIRScram::_semantic_transform( savant::set<IIRScram_TypeDefinition> * ){
#ifdef SEMANTIC_DEBUG
  cout << "Semantic transform called for node " << get_kind_text() <<
    " - returning \"this\". " << endl;
#endif
  return (IIRScram *)this;
}

IIRScram *
IIRScram::_semantic_transform( IIRScram_TypeDefinition *input_decl ){
  savant::set<IIRScram_TypeDefinition> temp_set;
  temp_set.add( input_decl );
  return _semantic_transform( &temp_set );
}

IIRScram *
IIRScram::_rval_to_decl( IIRScram_TypeDefinition * ){
#ifdef SEMANTIC_DEBUG
  cout << "_rval_to_decl called for node " << get_kind_text() <<
    " - returning \"this\". " << endl;
#endif
 
  return (IIRScram *)this;
}

IIRScram_DesignFile *
IIRScram::_get_my_design_file() {
  IIRScram_DesignFile *file = dynamic_cast<IIRScram_DesignFile *>(_my_design_file);
  ASSERT( file != NULL);
  return file;
}

symbol_table *
IIRScram::_get_symbol_table( ){
  ASSERT( _my_design_file != NULL );
  ASSERT( _get_my_design_file()->_get_symbol_table() != NULL );

  return _get_my_design_file()->_get_symbol_table();
}

void 
IIRScram::_report_undefined_scram_fn(const char *fn_name) {
  ostringstream os;
  os << fn_name << " not defined for IIRScram node: " << get_kind_text();
  report_error( this, os.str() );
  abort();
}

IIR_Boolean
IIRScram::_is_readable() {
  _report_undefined_scram_fn("_is_readable()");
  return FALSE;
}

IIR_Boolean
IIRScram::_is_writable() {
  _report_undefined_scram_fn("_is_writable()");
  return FALSE;
}

IIRScram_GenericList *
IIRScram::_get_generic_list(){
  _report_undefined_scram_fn("_get_generic_list()");
  return NULL;
}

IIR_Mode
IIRScram::_get_mode() {
  _report_undefined_scram_fn("_get_mode()");
  return IIR_UNKNOWN_MODE;
}

savant::set<IIRScram_Declaration> *
IIRScram::_symbol_lookup(){
  _report_undefined_scram_fn("_symbol_lookup( )");
  return NULL;
}

savant::set<IIRScram_Declaration> *
IIRScram::_symbol_lookup( IIRScram_Declaration * ){
  _report_undefined_scram_fn("_symbol_lookup( IIRScram_Declaration * )");
  return NULL;
}

savant::set<IIRScram_Declaration> *
IIRScram::_symbol_lookup( savant::set<IIRScram_Declaration> * ){
  _report_undefined_scram_fn("_symbol_lookup( savant::set<IIRScram_Declaration> * )");
  return NULL;
}

savant::set<IIRScram_Declaration> *
IIRScram::_symbol_lookup( constraint_functor *functor ){
  savant::set<IIRScram_Declaration> *retval = _symbol_lookup();

  if( retval != NULL ){
    retval->reduce_set( functor );
  }

  return retval;
}

IIRScram_Label *
IIRScram::_lookup_label( IIR_Boolean complain_on_error ){
  IIRScram_Label *retval = NULL;
  
  ASSERT( complain_on_error == TRUE ||  complain_on_error == FALSE );
  
  constraint_functor *functor = new is_label_functor;
  savant::set<IIRScram_Declaration> *decls = _symbol_lookup( functor );
  delete functor;

  ASSERT( decls != NULL );
  if( decls->size() == 0 && complain_on_error == TRUE ){
    report_undefined_symbol( (IIRScram *)this );
  }

  switch( decls->size() ){
  case 0:{
    ostringstream err;
    err << "No label |" << *this << "| declared in this scope.";
    report_error( this, err.str() );
    break;
  }
  case 1:{
    IIRScram_Declaration *temp = decls->getElement();
    ASSERT( temp->is_label() == TRUE );
    retval = dynamic_cast<IIRScram_Label *>(temp);
    break;
  }
  default:{
    report_ambiguous_error( (IIRScram *)this, decls->convert_set<IIR_Declaration>() );
  }
  }

  return retval;
}

savant::set<IIRScram_TypeDefinition> *
IIRScram::_get_rval_set(constraint_functor * ){
  _report_undefined_scram_fn("_get_rval_set(),\nconstraint_functor *functor");
  return NULL;
}

savant::set<IIRScram_TypeDefinition> *
IIRScram::_get_rval_set( savant::set<IIRScram_TypeDefinition> *,
			 constraint_functor * ){
  _report_undefined_scram_fn("_get_rval_set( savant::set<IIRScram_TypeDefinition> * ),\nconstraint_functor *functor");
  return NULL;
}

savant::set<IIRScram_TypeDefinition> *
IIRScram::_get_rval_set( savant::set<IIRScram_Declaration> *, 
			 constraint_functor * ){
  _report_undefined_scram_fn("_get_rval_set( savant::set<IIRScram_Declaration> * ,\nconstraint_functor *functor )");
  return NULL;
}

IIRScram_Declaration *
IIRScram::_find_formal_declaration(){
  _report_undefined_scram_fn("_find_formal_declaration( )");
  return NULL;
}

IIRScram_TypeDefinition *
IIRScram::_determine_rval_in_set( savant::set<IIRScram_TypeDefinition> *,
				  IIRScram_TypeDefinition * ){
  _report_undefined_scram_fn("_determine_rval_in_set( savant::set<IIRScram_TypeDefinition> *, IIRScram_TypeDefinition * )");
  return NULL;  
}

IIRScram_Declaration *
IIRScram::_determine_decl_in_set( savant::set<IIRScram_Declaration> *, IIRScram_TypeDefinition * ){
  _report_undefined_scram_fn("_determine_decl_in_set( savant::set<IIRScram_Declaration> *, IIRScram_TypeDefinition *)");
  return NULL;  
}

IIRScram_TypeDefinition *
IIRScram::_get_subtype(){
  if( get_subtype() != 0 ){
    ASSERT( dynamic_cast<IIRScram_TypeDefinition *>(get_subtype()) != 0 );
  }
  return dynamic_cast<IIRScram_TypeDefinition *>(get_subtype());
}

IIRScram_TypeDefinition *
IIRScram::_get_rval_pointed_at(){
  IIRScram_TypeDefinition *retval = NULL;

  if( _get_subtype()->_is_iir_access_type_definition() == TRUE ){
    retval = dynamic_cast<IIRScram_TypeDefinition *>((dynamic_cast<IIRScram_AccessTypeDefinition *>(_get_subtype())->get_designated_type()));
  }

  return retval;
}

IIRScram_TypeDefinition *
IIRScram::_get_type_of_element( int ){
  _report_undefined_scram_fn("_get_type_of_element( int )");
  return NULL;
}

IIRScram_TypeDefinition *
IIRScram::_get_port_type( int ){
  _report_undefined_scram_fn("_get_port_type");
  return NULL;
}

void 
IIRScram::_type_check( savant::set<IIRScram_TypeDefinition> * ){
  _report_undefined_scram_fn("_type_check( savant::set<IIRScram_TypeDefinition> * )");
}

IIRScram *
IIRScram::_rval_to_decl( IIRScram_TypeDefinition *, IIRScram_TypeDefinition * ){
  _report_undefined_scram_fn("_rval_to_decl( IIRScram_TypeDefinition *prefix_rval, IIRScram_TypeDefinition *suffix_rval )");  
  return NULL;
}

IIRScram *
IIRScram::_rval_to_decl( IIRScram_Declaration *, IIRScram_TypeDefinition * ){
  _report_undefined_scram_fn("_rval_to_decl( IIRScram_Declaration *prefix_decl, IIRScram_TypeDefinition *suffix_rval )");  
  return NULL;
}

IIRScram *
IIRScram::_get_component_name( ){
  _report_undefined_scram_fn("_get_component_name()");
  return NULL;
}

void 
IIRScram::_set_component_name( IIRScram * ){
  _report_undefined_scram_fn("_set_component_name()");
}

IIRScram_LibraryUnit *
IIRScram::_get_entity_aspect(){
  _report_undefined_scram_fn("_get_entity_aspect()");
  return NULL;
}

IIRScram_LibraryUnit *
IIRScram::_find_default_binding( IIRScram *component_name ){
  ASSERT( component_name->get_kind() == IIR_SIMPLE_NAME ||
	  component_name->get_kind() == IIR_COMPONENT_DECLARATION );

  IIRScram_LibraryUnit *retval = NULL;

  IIRScram_EntityDeclaration *entity_decl = 
    dynamic_cast<IIRScram_EntityDeclaration *>(library_manager::instance()->lookup_entity( FALSE, component_name, _get_work_library(), _get_design_file()->get_standard_package(), _get_design_file()->get_class_factory() ));
  if( entity_decl != NULL ){
    // We need to go get the most recently analyzed architecure.
    retval = dynamic_cast<IIRScram_LibraryUnit *>(library_manager::instance()->lookup_default_architecture( entity_decl ));
  }

  return retval;
}

IIRScram_Declaration* 
IIRScram::_get_prefix_declaration() {
  return dynamic_cast<IIRScram_Declaration *>(get_prefix_declaration());
}

const string 
IIRScram::convert_to_library_name( ) {
  _report_undefined_scram_fn("convert_to_library_name()");
  return "";
}

void 
IIRScram::_make_interface_visible( symbol_table * ){
  _report_undefined_scram_fn("_make_interface_visible( symbol_table * )");
}

void 
IIRScram::_make_interface_visible( ){
  _make_interface_visible( _get_symbol_table() );
}

IIRScram*
IIRScram::_clone() {
  _report_undefined_scram_fn("IIRScram *_clone()");
  return NULL;
}

void
IIRScram::_clone(IIRScram* clone) {
  copy_location(this, clone);
}  

IIRScram_IntegerLiteral *
IIRScram::_get_integer_static_value(){
  _report_undefined_scram_fn("_get_integer_static_value()");
  return NULL;
}

IIRScram *
IIRScram::_decl_to_decl( IIRScram_Declaration * ){
  _report_undefined_scram_fn("_decl_to_decl( IIRScram_Declaration * )");
  return NULL;
}

IIRScram_FunctionDeclaration*
IIRScram::_get_resolution_function(){
  return NULL;
}

void 
IIRScram::_type_check_configuration( IIRScram_AssociationList &port_map_aspect,
				     IIRScram_AssociationList &generic_map_aspect,
				     int tmp_mode ){
  
  // Hack to work around #includeing this in the header.
  IIRScram_ConfigurationSpecification::type_check_mode mode = 
    (IIRScram_ConfigurationSpecification::type_check_mode)tmp_mode;

  _get_symbol_table()->open_scope( (IIRScram *)this );

  constraint_functor *functor = new is_component_declaration_functor();
  savant::set<IIRScram_Declaration> *component_decls = _get_component_name()->_symbol_lookup( functor );
  delete functor;

  if( component_decls == NULL ){
    report_undefined_symbol( _get_component_name() );
    return;
  }

  IIRScram_ComponentDeclaration *my_component = 0;
  switch( component_decls->size() ){
  case 0:{
    ostringstream err;
    err << "|" << *_get_component_name() 
	<< "| was not declared as a component in this scope.";
    report_error( this, err.str() );
    return;
  }
  case 1:{
    my_component = dynamic_cast<IIRScram_ComponentDeclaration *>(component_decls->getElement());
    _set_component_name( _get_component_name()->_decl_to_decl( my_component ) );
    if( debug_symbol_table == true ){
      cerr << "Type checking configuration - about to make |" << 
	_get_component_name() << "| visible." << endl;
    }
    my_component->_make_interface_visible( _get_symbol_table() );
    break;
  }
  default:{
    report_ambiguous_error( _get_component_name(), component_decls->convert_set<IIR_Declaration>() );
    break;
  }
  }

  // This currently gets resolved by the parser...
  IIRScram *aspect = _get_entity_aspect();
  if( aspect != NULL ){
    ASSERT( aspect->_is_iir_declaration() == TRUE );
    ASSERT( aspect->is_resolved() == TRUE );
    IIRScram_Declaration *aspect_decl = dynamic_cast<IIRScram_Declaration *>(aspect);
    
    // The formal generics and ports of the entity must be visible here.
    // See section 10.2 of the LRM.  So, now we're deciding what entity
    // we're looking at, and using this info to put those formals back
    // into scope.
    IIRScram_EntityDeclaration *entity_decl = NULL;
    switch( aspect_decl->get_kind() ){
      
    case IIR_ARCHITECTURE_DECLARATION:{
      IIRScram_ArchitectureDeclaration *as_arch = dynamic_cast<IIRScram_ArchitectureDeclaration *>(aspect_decl);
      entity_decl = as_arch->_get_entity();
      break;
    }
    case IIR_ENTITY_DECLARATION:{
      entity_decl =  dynamic_cast<IIRScram_EntityDeclaration *>(aspect_decl);
      break;
    }
    case IIR_CONFIGURATION_DECLARATION:{
      entity_decl = dynamic_cast<IIRScram_EntityDeclaration *>((dynamic_cast<IIRScram_ConfigurationDeclaration *>(aspect_decl))->get_entity());
      break;
    }
    default:{
      ostringstream err;
      err << "Internal error in IIRScram_ConfigurationSpecification::_type_check"
	  << " - got a " << aspect_decl->get_kind_text() 
	  << ", expecting architecture or entity.";
      report_error( this, err.str() );
      abort();
    }
    }
    
    _resolve_map( entity_decl->_get_port_list(),
		  my_component->_get_port_list(),
		  port_map_aspect,
		  mode );

    _resolve_map( entity_decl->_get_generic_list(),
		  my_component->_get_generic_list(),
		  generic_map_aspect,
		  mode );
  }
  _get_symbol_table()->close_scope( (IIR *)this );
  // else it's OPEN
  //  ASSERT( is_resolved() == TRUE );
  delete component_decls;
}

void
IIRScram::_resolve_map( IIRScram_InterfaceList *entity_interface_list,
			IIRScram_InterfaceList *component_interface_list,
			IIRScram_AssociationList &map,
			int tmp_mode ){
  // Hack to work around #includeing this in the header.
  IIRScram_ConfigurationSpecification::type_check_mode mode = 
    (IIRScram_ConfigurationSpecification::type_check_mode)tmp_mode;

  if( entity_interface_list && map.size() > 0 ){
    if( mode == IIRScram_ConfigurationSpecification::CONFIG_SPEC ){
      map._resolve_and_order( entity_interface_list,
			      component_interface_list,
			      dynamic_cast<IIRScram*>(this) );
    }
    else{
      ASSERT( mode == IIRScram_ConfigurationSpecification::COMPONENT_INSTANT );
      map._resolve_and_order( component_interface_list,
			      entity_interface_list,
			      dynamic_cast<IIRScram*>(this) );
    }
  }
  else{
    if( mode == IIRScram_ConfigurationSpecification::CONFIG_SPEC ){
      build_default_map( entity_interface_list,
                         component_interface_list,
			 map );
    }
    else{
      ASSERT( mode == IIRScram_ConfigurationSpecification::COMPONENT_INSTANT );
      build_default_map( component_interface_list,
			 entity_interface_list,
			 map );
    }
  }
}

IIRScram_TypeDefinition *
IIRScram::_type_check_iteration_scheme( IIRScram_ConstantDeclaration *iteration_scheme ){
  IIRScram_TypeDefinition *retval = NULL;

  ASSERT( iteration_scheme != NULL );
  IIRScram_TypeDefinition *range_type = iteration_scheme->_get_subtype();
  ASSERT( iteration_scheme->_get_subtype() != NULL );

  if( range_type->get_kind() == IIR_RANGE_TYPE_DEFINITION ){
    IIRScram_RangeTypeDefinition *temp = dynamic_cast<IIRScram_RangeTypeDefinition *>(range_type);
    IIRScram_TypeDefinition *constant_base_type = temp->_determine_discrete_type();
    if( constant_base_type != NULL ){
      retval = constant_base_type->_construct_new_subtype( NULL, temp);
    }
  }
  else{
    // else it should be resolved.
    ASSERT( iteration_scheme->_get_subtype()->is_resolved() == TRUE );
    retval = iteration_scheme->_get_subtype();
  }

  return retval;
}

IIR *
IIRScram::_type_check_file_open_information(){
  IIR *retval = this;

  savant::set<IIRScram_TypeDefinition> *rvals = _get_rval_set();
  if( rvals == NULL ){
    report_undefined_symbol( this );
  }
  else{
    savant::set<IIRScram_TypeDefinition> file_open_kind;
    ASSERT( get_design_file() != NULL );
    ASSERT( get_design_file()->get_standard_package() != NULL );
    file_open_kind.add( dynamic_cast<IIRScram_TypeDefinition *>(get_design_file()->get_standard_package()->get_file_open_kind_type() ));
    _type_check( &file_open_kind );
    reconcile_sets( &file_open_kind, rvals );
    switch( file_open_kind.size() ){
    case 0:{
      ostringstream err;
      err << "File open information |";
      this->publish_vhdl( err );
      err << "| is not compatible "
	  << "with std.standard.file_open_kind.";
      report_error( this, err.str() );
      break;
    }
    case 1:{
      retval = _rval_to_decl( file_open_kind.getElement() );
      break;
    }
    default:{
      // Should not be possible
      string err("Internal errror in IIRScram::_type_check_file_open_information()");
      report_error( this, err );
    }
    }
  }
  delete rvals;

  return retval;
}

IIRScram_LibraryDeclaration *
IIRScram::_get_work_library(){
  ASSERT( _my_design_file != 0 );
  return _get_my_design_file()->_get_work_library();
}

char *
IIRScram::_strdup( const char * const to_copy, unsigned int size ){
  if( size == 0 ){
    size = strlen( to_copy );
  }
  size++;

  char *retval = new char[size];
  memcpy( retval, to_copy, size - 1 );
  retval[ size ] = '0';

  return retval;
}

IIRScram_AttributeSpecificationList * 
IIRScram::_get_attribute_specification_list( ){
  return NULL;
}

IIR_Boolean 
IIRScram::_attach_attribute_specification( IIRScram_AttributeSpecification *to_attach ){
  IIRScram_AttributeSpecificationList *list = _get_attribute_specification_list();
  if( list == NULL ){
    return FALSE;
  }
  else{
    list->append( to_attach );
    return TRUE;
  }
}

IIR_Boolean 
IIRScram::_attach_disconnection_specification( IIRScram_AttributeSpecification * ){
  _report_undefined_scram_fn("_attach_disconnection_specification( IIRScram_AttributeSpecification *)");
  abort();
  return FALSE;
}

IIRScram_DeclarationList*
IIRScram::_get_declaration_list() {
  _report_undefined_scram_fn("_get_declaration_list()");
  return NULL;
}

include_manager *
IIRScram::get_include_manager(){
  // lazy initialization
  static include_manager *my_include_manager = new include_manager();

  return my_include_manager;
}

IIRScram_DesignFile *
IIRScram::_get_design_file() const{
  return dynamic_cast<IIRScram_DesignFile *>(_my_design_file);
}

void 
IIRScram::_set_design_file( IIRScram_DesignFile *new_design_file ){
  _my_design_file = dynamic_cast<IIR_DesignFile *>(new_design_file);
}

IIR_Boolean
IIRScram::_is_branchQ(){
  return FALSE;
}

void
IIRScram::_build_generic_parameter_set( savant::set<IIRScram_Declaration> * ){
  // do nothing
}

void
IIRScram::_build_reference_quantity_list( dl_list<IIRScram_ReferenceAttribute> * ){
  // do nothing
}

IIRScram_PortList *
IIRScram::_get_port_list(){
  _report_undefined_scram_fn("_get_port_list()");
  return NULL;
}

IIRScram_List *
IIRScram::_get_statement_list(){
  _report_undefined_scram_fn("_get_statement_list()");

  return NULL;
}

IIRScram_Declaration* 
IIRScram::_get_package_declaration() {
  return NULL;
}

IIRScram_Identifier *
IIRScram::_get_file_name(){
  return dynamic_cast<IIRScram_Identifier *>(get_file_name());
}

IIRScram_TextLiteral *
IIRScram::_get_declarator() {
  return dynamic_cast<IIRScram_TextLiteral *>(get_declarator());
}

