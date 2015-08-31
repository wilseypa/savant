
#ifndef IIRBASE_CONFIGURATION_SPECIFICATION_HH
#define IIRBASE_CONFIGURATION_SPECIFICATION_HH

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
#include "IIRBase_Declaration.hh"
#include "IIR_ConfigurationSpecification.hh"
#include "IIR_AssociationList.hh"

class IIR_LibraryUnit;
class IIR_DesignatorList;
class IIR_AssociationList;

class IIRBase_ConfigurationSpecification : public virtual IIRBase_Declaration, public virtual IIR_ConfigurationSpecification{

public:
  // List Accessor(s)
  IIR_DesignatorList    *get_instantiation_list();
  IIR_AssociationList   *get_generic_map_aspect();
  IIR_AssociationList   *get_port_map_aspect();
  void                  set_instantiation_list(IIR_DesignatorList *new_instantiation_list);
  void                  set_generic_map_aspect(IIR_AssociationList *new_generic_map_aspect);
  void                  set_port_map_aspect(IIR_AssociationList *new_port_map_aspect);

  IIR_Kind get_kind() const {return IIR_CONFIGURATION_SPECIFICATION;}
  const IIR_Char *get_kind_text() const {return "IIR_ConfigurationSpecification";}
  
  void set_component_name(IIR *component_name);
  IIR *get_component_name();

  /**
     Gets the entity aspect associated with the component specified.  This
     maps to the binding indication as specified by the LRM.  Will return
     NULL for "open" binding.
  */
  IIR_LibraryUnit *get_entity_aspect();
  void set_entity_aspect(IIR_LibraryUnit    *entity_aspect);

  IIR *convert_tree(plugin_class_factory *factory);

  void publish_vhdl(ostream &);
  void publish_vhdl_decl(ostream &);
protected:
  IIRBase_ConfigurationSpecification();
  virtual ~IIRBase_ConfigurationSpecification() = 0;
    
private:
  // List Variable(s)
  /**
     Holds the list of component designators specified in the component configuration.
  */
  IIR_DesignatorList  *instantiation_list;

  /**
     Holds the generic map specified for the component configuration.
  */
  IIR_AssociationList    *generic_map_aspect;

  /**
     Holds the port map specified for the component configuration.
  */
  IIR_AssociationList    *port_map_aspect;

  IIR              *my_component_name;
  IIR_LibraryUnit  *my_entity_aspect;
};
#endif
