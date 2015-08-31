
#ifndef IIRSCRAM_COMPONENT_INSTANTIATION_STATEMENT_HH
#define IIRSCRAM_COMPONENT_INSTANTIATION_STATEMENT_HH

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
//          Krishnan Subramani  
//          Narayanan Thondugulam
//          Timothy J. McBrayer
//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_ConcurrentStatement.hh"
#include "IIRBase_ComponentInstantiationStatement.hh"

class IIRScram_AssociationElement;
class IIRScram_AssociationList;
class IIRScram_ComponentDeclaration;
class IIRScram_ComponentInstantiationStatement;
class IIRScram_ConfigurationSpecification;
class IIRScram_EntityDeclaration;
class IIRScram_DeclarationList;
class IIRScram_Label;
class IIRScram_LibraryUnit;
class IIRScram_SimpleName;
class IIRScram_TypeDefinition;

class IIRScram_ComponentInstantiationStatement : public virtual IIRScram_ConcurrentStatement, public virtual IIRBase_ComponentInstantiationStatement{

public:
  IIRScram_ComponentInstantiationStatement();
  virtual ~IIRScram_ComponentInstantiationStatement();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  // This method _only_ resolves the instantiated unit, and it gets called
  // from the parser during the parse.  (Type check of configuration
  // specifications and component configurations requires this information
  // to be resolved.)
  void _type_check_instantiated_unit();

  // This does the _rest_ of the type checking, which can only happen
  // _after_ configuration specifications are resolved.
  void _type_check();

  // This method is overriding one defined in IIRScram_ConcurrentStatement
  // to actually do the type checking for this statement.
  void _type_check_instantiate_statements(){ _type_check(); }

  IIRScram_AssociationList *_get_generic_map_aspect();  
  IIRScram_TypeDefinition *_get_port_type( int );

  /** These methods provide a place for the parser to store what type
      of declaration the semantic routines should be looking for... */
  void _set_instantiation_type( IIR_Kind );
  IIR_Kind _get_instantiation_type();

#ifdef PROCESS_COMBINATION
  void _static_elaborate(IIRScram_ArchitectureDeclaration*, IIRScram_DeclarationList*,
			 char*);
#endif

  IIRScram_Label                *_find_instantiate_label( IIRScram_SimpleName * );

  IIRScram                      *_get_instantiated_unit();
  IIRScram_AssociationList      *_get_port_map_aspect();
  IIRScram                      *_get_configuration();
protected:

  // Methods used to _transmute()
  IIRScram_ComponentDeclaration *
  _build_implicit_component_declaration(IIRScram_EntityDeclaration *, const string &componentName );

  IIRScram_ConfigurationSpecification *
  _build_implicit_configuration_specification(IIRScram_LibraryUnit *, IIRScram_ComponentDeclaration *);


private:
  /** Returns the instantiated unit - the instantiation type is ENTITY. */
  void _resolve_instantiated_unit_for_entity();
  /** Returns the instantiated unit - the instantiation type is COMPONENT. */
  void _resolve_instantiated_unit_for_component();

  /** Returns the default entity/architecture if there is one, by the rules
      of 5.2.2 in the '93 LRM.  */
  IIRScram_ConfigurationSpecification *_get_default_binding_indication();
  /** Does the actual building for _get_default_binding_indication() */
  IIRScram_ConfigurationSpecification *_build_default_entity_aspect( IIRScram *component_name,
                                                                     IIRScram_ArchitectureDeclaration *arch);

  IIR_Kind my_instantiation_type;
};
#endif
