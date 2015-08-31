
#ifndef IIRBASE_COMPONENT_DECLARATION_HH
#define IIRBASE_COMPONENT_DECLARATION_HH

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
#include "IIRBase_Declaration.hh"
#include "IIR_ComponentDeclaration.hh"

class IIR_AttributeSpecificationList;
class IIR_EntityDeclaration;
class IIR_GenericList;
class IIR_PortList;

class IIRBase_ComponentDeclaration : public virtual IIRBase_Declaration, public virtual IIR_ComponentDeclaration{

public:
  // List Accessor(s)
  IIR_GenericList                       *get_local_generic_clause();
  IIR_PortList                          *get_local_port_clause();
  IIR_AttributeSpecificationList        *get_attributes();
  void                                  set_local_generic_clause(IIR_GenericList *new_local_generic_clause);
  void                                  set_local_port_clause(IIR_PortList *new_local_port_clause);
  void                                  set_attributes(IIR_AttributeSpecificationList *new_attributes);

  IIR_Kind get_kind() const { return IIR_COMPONENT_DECLARATION; }
  const IIR_Char *get_kind_text() const { return "IIR_ComponentDeclaration"; }

  IIR *convert_tree(plugin_class_factory *factory);

  declaration_type get_declaration_type();

  savant::set<IIR_Declaration> *find_declarations( IIR_Name * );

  IIR_Boolean is_component_declaration(){ return TRUE; }
  void publish_vhdl_decl(ostream &);

  void set_entity( IIR_EntityDeclaration *entity );
  IIR_EntityDeclaration *get_entity();

protected:
  IIRBase_ComponentDeclaration();
  virtual ~IIRBase_ComponentDeclaration() = 0;
    
private:
  // List Variable(s)
  IIR_EntityDeclaration			*entity;
  IIR_GenericList                       *local_generic_clause;
  IIR_PortList                          *local_port_clause;
  IIR_AttributeSpecificationList        *attributes;

};
#endif
