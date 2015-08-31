
#ifndef IIR_COMPONENT_CONFIGURATION_HH
#define IIR_COMPONENT_CONFIGURATION_HH

// Copyright (c) 1996-1999 The University of Cincinnati.  
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

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_ConfigurationItem.hh"

class IIR_LibraryUnit;
class IIR_BlockConfiguration;
class IIR_DesignatorList;
class IIR_AssociationList;

class IIR_ComponentConfiguration : public virtual IIR_ConfigurationItem{

public:
  virtual ~IIR_ComponentConfiguration() {}
    
  // List accessor(s)
  virtual IIR_DesignatorList    *get_instantiation_list() = 0;
  virtual IIR_AssociationList   *get_generic_map_aspect() = 0;
  virtual IIR_AssociationList   *get_port_map_aspect() = 0;
  virtual void                  set_instantiation_list(IIR_DesignatorList *new_instantiation_list) = 0;
  virtual void                  set_generic_map_aspect(IIR_AssociationList *new_generic_map_aspect) = 0;
  virtual void                  set_port_map_aspect(IIR_AssociationList *new_port_map_aspect) = 0;

  /**
     Gets the component name that was specified for this configuration.
     Prior to type check, this node will contain a descendant of IIR_Name.
     After type checking, it will contain an IIR_ComponentDeclaration.
  */
  virtual IIR *get_component_name() = 0;
  virtual void set_component_name( IIR *component_name ) = 0;
  
  /**
     Gets the entity aspect associated with the component specified.  This
     maps to the binding indication as specified by the LRM.  Will return
     NULL for "open" binding.

     If there was no binding indication specified explicitly, then the
     default rules specified in section 5.2.2 of the '93 LRM.
  */
  virtual IIR_LibraryUnit *get_entity_aspect() = 0;
  virtual void set_entity_aspect( IIR_LibraryUnit *entity_aspect ) = 0;

  virtual void set_block_configuration( IIR_BlockConfiguration *block_configuration ) = 0;
  virtual IIR_BlockConfiguration *get_block_configuration() = 0;
};
#endif
