
#ifndef IIR_CONFIGURATION_SPECIFICATION_HH
#define IIR_CONFIGURATION_SPECIFICATION_HH

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
#include "IIR_Declaration.hh"

class IIR_LibraryUnit;
class IIR_DesignatorList;
class IIR_AssociationList;

class IIR_ConfigurationSpecification : public virtual IIR_Declaration{

public:
  virtual ~IIR_ConfigurationSpecification() {}    

  // List accessor(s)
  virtual IIR_DesignatorList    *get_instantiation_list() = 0;
  virtual IIR_AssociationList   *get_generic_map_aspect() = 0;
  virtual IIR_AssociationList   *get_port_map_aspect() = 0;
  virtual void                  set_instantiation_list(IIR_DesignatorList *new_instantiation_list) = 0;
  virtual void                  set_generic_map_aspect(IIR_AssociationList *new_generic_map_aspect) = 0;
  virtual void                  set_port_map_aspect(IIR_AssociationList *new_port_map_aspect) = 0;

  virtual void set_component_name(IIR *component_name) = 0;
  virtual IIR *get_component_name() = 0;

  /**
     Gets the entity aspect associated with the component specified.  This
     maps to the binding indication as specified by the LRM.  Will return
     NULL for "open" binding.
  */
  virtual IIR_LibraryUnit *get_entity_aspect() = 0;
  virtual void set_entity_aspect(IIR_LibraryUnit    *entity_aspect) = 0;
};
#endif
