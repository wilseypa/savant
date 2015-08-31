
#ifndef IIRBASE_CONFIGURATION_DECLARATION_HH
#define IIRBASE_CONFIGURATION_DECLARATION_HH

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

#include "savant_config.hh"
#include "IIRBase_LibraryUnit.hh"
#include "IIR_ConfigurationDeclaration.hh"

class IIR_BlockConfiguration;
class IIR_DeclarationList;
class IIR_EntityDeclaration;

class IIRBase_ConfigurationDeclaration : public virtual IIRBase_LibraryUnit, public virtual IIR_ConfigurationDeclaration{

public:
  // List Accessor(s)
  IIR_DeclarationList   *get_configuration_declarative_part();
  void                  set_configuration_declarative_part(IIR_DeclarationList *new_configuration_declarative_part);

  IIR_Kind get_kind() const {return IIR_CONFIGURATION_DECLARATION;}
  const IIR_Char *get_kind_text() const {return "IIR_ConfigurationDeclaration";}

  void set_block_configuration(IIR_BlockConfiguration *block_configuration);
  IIR_BlockConfiguration *get_block_configuration();

  void set_entity( IIR_EntityDeclaration *entity );
  IIR_EntityDeclaration *get_entity();

  IIR *convert_tree(plugin_class_factory *factory);

  declaration_type get_declaration_type();

  IIR_Boolean is_configuration_declaration(){ return TRUE; }
  IIR_Boolean is_primary_unit(){ return TRUE; }

  void publish_vhdl_decl(ostream &);
  void publish_vhdl_binding_name(ostream &);
  void publish_vhdl_with_library_name(ostream &);
protected:
  IIRBase_ConfigurationDeclaration();
  virtual ~IIRBase_ConfigurationDeclaration() = 0;
    
private:
  // List Variable(s)
  IIR_DeclarationList   *configuration_declarative_part;

  IIR_BlockConfiguration *block_configuration;
  IIR_EntityDeclaration *entity;
};
#endif
