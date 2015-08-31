#ifndef IIRSCRAM_CONFIGURATION_SPECIFICATION_HH
#define IIRSCRAM_CONFIGURATION_SPECIFICATION_HH
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
//          Timothy J. McBrayer tmcbraye@ececs.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Declaration.hh"
#include "IIRBase_ConfigurationSpecification.hh"

class IIRScram_ComponentInstantiationStatement;
class IIRScram_DeclarationList;
class IIRScram_DesignatorList;
class IIRScram_LibraryUnit;
class IIRScram_List;
class IIRScram_StatementList;

class IIRScram_ConfigurationSpecification : public virtual IIRScram_Declaration, public virtual IIRBase_ConfigurationSpecification{

public:
  IIRScram_ConfigurationSpecification();
  virtual ~IIRScram_ConfigurationSpecification();
  enum type_check_mode { CONFIG_SPEC, COMPONENT_INSTANT };

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  IIR_Boolean _is_specification() { return TRUE; }
  IIR_Boolean _is_iir_configuration_specification() { return TRUE; }

  IIRScram_DesignatorList *_get_instantiation_list();

  // The list passed into this type check method contains the statement region
  // of the declarative region this sepcification appears in.  It is used for
  // finding component instantiation statements, so it can resolve ALL and
  // OTHERS.
  void _type_check( IIRScram_List *statment_list, type_check_mode mode );

  IIRScram *_get_component_name( );
  void _set_component_name( IIRScram * );
  IIRScram_LibraryUnit *_get_entity_aspect();

  // Wrapper Functions
  IIRScram_AssociationList * _get_generic_map_aspect();
  IIRScram_AssociationList * _get_port_map_aspect();
};
#endif
