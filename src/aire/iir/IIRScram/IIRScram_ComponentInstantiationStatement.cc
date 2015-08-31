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
//          Timothy J. McBrayer
//          Krishnan Subramani 
//          Narayanan Thondugulam
//	    Magnus Danielson	cfmd@swipnet.se

#include "IIRScram.hh"
#include "IIRScram_ArchitectureDeclaration.hh"
#include "IIRScram_AssociationElementByExpression.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_ComponentConfiguration.hh"
#include "IIRScram_ComponentDeclaration.hh"
#include "IIRScram_ComponentInstantiationStatement.hh"
#include "IIRScram_ConfigurationSpecification.hh"
#include "IIRScram_DesignatorExplicit.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EntityDeclaration.hh"
#include "IIRScram_FunctionCall.hh"
#include "IIRScram_GenericList.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_IndexedName.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_LibraryDeclaration.hh"
#include "IIRScram_PortList.hh"
#include "IIRScram_SelectedName.hh"
#include "IIRScram_SignalDeclaration.hh"
#include "IIRScram_SignalInterfaceDeclaration.hh"
#include "IIRScram_SimpleName.hh"
#include "IIRScram_SubprogramDeclaration.hh"

#include "error_func.hh"
#include "set.hh"
#include "library_manager.hh"

#include <sstream>

using std::ostringstream;
using std::cerr;
using std::endl;

extern bool parse_error;

IIRScram_ComponentInstantiationStatement::IIRScram_ComponentInstantiationStatement() : 
  my_instantiation_type( IIR_COMPONENT_DECLARATION ) {
  set_generic_map_aspect(new IIRScram_AssociationList());
  set_port_map_aspect(new IIRScram_AssociationList());
}

IIRScram_ComponentInstantiationStatement::~IIRScram_ComponentInstantiationStatement(){}

void 
IIRScram_ComponentInstantiationStatement::_set_instantiation_type( IIR_Kind instantiation_type ){
  my_instantiation_type = instantiation_type;
}

IIRScram_TypeDefinition * 
IIRScram_ComponentInstantiationStatement::_get_port_type( int port_num ){
  return _get_instantiated_unit()->_get_port_type( port_num );
}

IIR_Kind 
IIRScram_ComponentInstantiationStatement::_get_instantiation_type(){
  return my_instantiation_type;
}

void 
IIRScram_ComponentInstantiationStatement::_resolve_instantiated_unit_for_entity(){
  IIRScram *entity_name = 0;
  IIRScram *arch_name = 0;
  IIRScram_EntityDeclaration *entity_decl = 0;

  if( _get_instantiated_unit()->get_kind() == IIR_INDEXED_NAME ){
    // The prefix of the indexed name is the entity.  The suffix is the
    // architecture.
    IIRScram_IndexedName *as_indexed_name = dynamic_cast<IIRScram_IndexedName *>(_get_instantiated_unit());
    entity_name = as_indexed_name->_get_prefix();
    arch_name = as_indexed_name->_get_suffix();
      
    ASSERT( entity_name->_is_iir_name() == TRUE );
    entity_decl = dynamic_cast<IIRScram_EntityDeclaration *>(library_manager::instance()->lookup_entity( TRUE, 
                                                                                                         dynamic_cast<IIRScram_Name *>(entity_name),
                                                                                                         _get_work_library(),
                                                                                                         get_design_file()->get_standard_package(),
                                                                                                         get_design_file()->get_class_factory()));
    if( entity_decl != NULL ){
      ASSERT( arch_name->_is_iir_name() == TRUE );
      IIRScram_ArchitectureDeclaration *arch_decl = 
	dynamic_cast<IIRScram_ArchitectureDeclaration *>(library_manager::instance()->lookup_architecture( TRUE,
                                                                                                           entity_decl,
                                                                                                           dynamic_cast<IIRScram_Name *>(arch_name)));
      
      if( arch_decl == 0 ){
	report_undefined_symbol( arch_name );
      }
      else{
	as_indexed_name->set_prefix( entity_name->_decl_to_decl( entity_decl ) );
	as_indexed_name->set_suffix( arch_name->_decl_to_decl( arch_decl ) );
	
	ASSERT( as_indexed_name->is_resolved() == TRUE );
	set_instantiated_unit( as_indexed_name );
      }
    }
    else{
      report_undefined_symbol( entity_name );
    }
  }
  else{
    entity_name = _get_instantiated_unit();
    ASSERT( entity_name->_is_iir_name() == TRUE );
    entity_decl = dynamic_cast<IIRScram_EntityDeclaration *>(library_manager::instance()->lookup_entity( TRUE, 
                                                                                                         dynamic_cast<IIRScram_Name *>(entity_name),
                                                                                                         _get_work_library(),
                                                                                                         get_design_file()->get_standard_package(),
                                                                                                         get_design_file()->get_class_factory()));
      
    set_instantiated_unit( _get_instantiated_unit()->_decl_to_decl( entity_decl ) );
  }
}

void
IIRScram_ComponentInstantiationStatement::_resolve_instantiated_unit_for_component(){
  constraint_functor *functor = new is_component_declaration_functor();
  savant::set<IIRScram_Declaration> *instantiated_unit_decls =
    _get_instantiated_unit()->_symbol_lookup(functor);
  delete functor;

  if( instantiated_unit_decls == NULL ){
    report_undefined_symbol( _get_instantiated_unit() );
  }
  else{
    // This needs to get pushed into a separate method.
    switch( instantiated_unit_decls->size() ){
    case 0:{
      ostringstream err;
      err << "|" << *_get_instantiated_unit() << "| was not declared as a";
	
      switch( _get_instantiation_type() ){
      case IIR_ENTITY_DECLARATION:
	err << "n entity";
	break;
      case IIR_COMPONENT_DECLARATION:
	err << " component";
	break;
      case IIR_CONFIGURATION_DECLARATION:
	err << " configuration";
	break;
      default:
	err << " (unknown type)";
      }
      err << " in this scope.";
	
      report_error( this, err.str() );
      break;
    }
    case 1:{
      IIRScram_Declaration *instantiated_decl = instantiated_unit_decls->getElement();
      set_instantiated_unit( _get_instantiated_unit()->_decl_to_decl( instantiated_decl ) );
      break;
    }
    default:{
      report_ambiguous_error( _get_instantiated_unit(), instantiated_unit_decls->convert_set<IIR_Declaration>() );
      break;
    }
    }
  }
  delete instantiated_unit_decls;
}

void 
IIRScram_ComponentInstantiationStatement::_type_check_instantiated_unit(){
  ASSERT( _get_instantiated_unit() != NULL );
    
  switch( _get_instantiation_type() ){
  case IIR_ENTITY_DECLARATION:{
    _resolve_instantiated_unit_for_entity();
    break;
  }
  case IIR_COMPONENT_DECLARATION:{
    _resolve_instantiated_unit_for_component();
    // We're also going to set up a default configuration here.  If there
    // is a configuration specification, it will come back in and set the
    // proper configuration.
    set_configuration( _get_default_binding_indication() );
    break;
  }
  case IIR_CONFIGURATION_DECLARATION:{
    ostringstream err;
    err << "IIRScram_ComponentInstantiationStatement::_type_check() :ERROR " 
	<< "\n - configurations in instantiation stmt not handled yet\n";
    report_error( this, err.str() );
    break;
  }
  default:{
    ostringstream err;
    err << "IIRScram_ComponentInstantiationStatement::_type_check() :ERROR " 
	<< "\n - Illegal declaration type\n";
    report_error( this, err.str() );
    break;
  }
  }
}

void 
IIRScram_ComponentInstantiationStatement::_type_check(){
  // So, the instantiated unit should be resolved, unless there was an error.

  if( _get_instantiated_unit() != NULL && _get_instantiated_unit()->is_resolved() == TRUE ){
    // The locals are in "get_instantiated_unit()->_get_generic_list()"
    _get_generic_map_aspect()->_resolve_and_order( _get_instantiated_unit()->_get_generic_list(),
						   0, this );
    // The locals are in "get_instantiated_unit()->_get_port_list()"
    _get_port_map_aspect()->_resolve_and_order( _get_instantiated_unit()->_get_port_list(),
						0, this );
  }
}

IIRScram_Label *
IIRScram_ComponentInstantiationStatement::_find_instantiate_label( IIRScram_SimpleName *to_find ){
  IIRScram_Label *retval = NULL;
  if( _get_label() != NULL ){
    if( IIRBase_TextLiteral::cmp( _get_label()->_get_declarator(), to_find ) == 0 ){
      retval = _get_label();
    }
  }

  return retval;
}

IIRScram_ComponentDeclaration*
IIRScram_ComponentInstantiationStatement::_build_implicit_component_declaration(IIRScram_EntityDeclaration *entity,
										const string &compName) {
  IIRScram_ComponentDeclaration *componentDecl = new IIRScram_ComponentDeclaration;
  
  copy_location(this, componentDecl);
  componentDecl->set_local_generic_clause(entity->get_generic_clause());
  componentDecl->set_local_port_clause(entity->get_port_clause());
  componentDecl->set_declarator(IIRScram_Identifier::get( compName, get_design_file()->get_class_factory() ));

  return componentDecl;
}

IIRScram_ConfigurationSpecification*
IIRScram_ComponentInstantiationStatement::_build_implicit_configuration_specification( IIRScram_LibraryUnit *instantiatedUnit, 
										       IIRScram_ComponentDeclaration *compDecl) {
  IIRScram_ConfigurationSpecification *config_spec = new IIRScram_ConfigurationSpecification;
  copy_location(this, config_spec);
  config_spec->set_component_name(compDecl);
  config_spec->set_entity_aspect(instantiatedUnit);

  IIRScram_DesignatorExplicit *designator = new IIRScram_DesignatorExplicit();
  designator->set_name( get_label() );
  config_spec->get_instantiation_list()->append( designator );


  return config_spec;
}

IIRScram_ConfigurationSpecification *
IIRScram_ComponentInstantiationStatement::_get_default_binding_indication(){
  // This method attempts to implement the rules found on page 79 of the
  // '93 LRM.
  IIRScram_ConfigurationSpecification *retval = 0;
  ASSERT( _get_instantiated_unit() != 0 );
  ASSERT( _get_instantiation_type() == IIR_COMPONENT_DECLARATION );
  
  IIRScram *component_name = _get_instantiated_unit();

  IIRScram_ArchitectureDeclaration *arch = 0;
  IIRScram_EntityDeclaration *entity = dynamic_cast<IIRScram_EntityDeclaration *>(library_manager::instance()->lookup_entity( FALSE,
                                                                                                                              component_name,
                                                                                                                              _get_work_library(),
                                                                                                                              get_design_file()->get_standard_package(),
                                                                                                                              get_design_file()->get_class_factory()));
  
  if( entity != 0 ){
    arch = dynamic_cast<IIRScram_ArchitectureDeclaration *>(library_manager::instance()->lookup_default_architecture( entity ));
    // So, we found an entity/arch that matched.  Now we'll build an
    // IIR_ConfigurationSpec to return
    if( arch != 0 ){
      retval = _build_default_entity_aspect( component_name, arch );
    }
    else{
      ostringstream err;
      err << "Component |" << *component_name << "| has no explicit binding indication,"
	  << " and the default binding is broken.  While entity |" << *entity << "| "
	  << "is a match by name, there is no cooresponding architecture";
      report_error( this, err.str() );
    }
  }

  return retval;
}

IIRScram *
IIRScram_ComponentInstantiationStatement::_get_instantiated_unit() {
  return dynamic_cast<IIRScram*>(IIRBase_ComponentInstantiationStatement::get_instantiated_unit());
}

IIRScram_ConfigurationSpecification *
IIRScram_ComponentInstantiationStatement::_build_default_entity_aspect(IIRScram *component_name,
								       IIRScram_ArchitectureDeclaration *arch){
  ASSERT( arch->_get_entity() != 0 );

  IIRScram_ConfigurationSpecification *retval = new IIRScram_ConfigurationSpecification();
  copy_location( this, retval );
  copy_location( this, retval->get_port_map_aspect() );
  copy_location( this, retval->get_generic_map_aspect() );
  retval->_set_design_file( _get_design_file() );
  retval->set_component_name( IIRBase_ComponentInstantiationStatement::get_instantiated_unit() );
  retval->set_entity_aspect( arch );
  retval->set_is_implicit( true );
  retval->_get_port_map_aspect()->_build_default_map( this,
                                                      arch->_get_entity()->_get_port_clause(),
                                                      component_name->_get_port_list() );

  retval->_get_generic_map_aspect()->_build_default_map( this,
                                                         arch->_get_entity()->_get_generic_clause(),
                                                         component_name->_get_generic_list() );  
  
  return retval;
}

visitor_return_type *
IIRScram_ComponentInstantiationStatement::_accept_visitor( node_visitor *visitor, 
							   visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ComponentInstantiationStatement(this, arg);
}

IIRScram_AssociationList *
IIRScram_ComponentInstantiationStatement::_get_generic_map_aspect() {
  return dynamic_cast<IIRScram_AssociationList *>(get_generic_map_aspect());
}

IIRScram_AssociationList *
IIRScram_ComponentInstantiationStatement::_get_port_map_aspect() {
  return dynamic_cast<IIRScram_AssociationList *>(get_port_map_aspect());
}

IIRScram *
IIRScram_ComponentInstantiationStatement::_get_configuration() {
  return dynamic_cast<IIRScram *>(get_configuration());
}
