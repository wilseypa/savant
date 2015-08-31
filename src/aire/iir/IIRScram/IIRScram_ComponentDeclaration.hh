
#ifndef IIRSCRAM_COMPONENT_DECLARATION_HH
#define IIRSCRAM_COMPONENT_DECLARATION_HH

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
#include "IIRScram_Declaration.hh"
#include "IIRBase_ComponentDeclaration.hh"

class IIRScram_GenericList;
class IIRScram_List;
class IIRScram_Name;
class IIRScram_PortList;
class IIRScram_TypeDefinition;

class IIRScram_ComponentDeclaration : public virtual IIRScram_Declaration, public virtual IIRBase_ComponentDeclaration{

public:
  IIRScram_ComponentDeclaration();
  virtual ~IIRScram_ComponentDeclaration();
    
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);
  IIRScram_PortList *_get_port_list();
  IIRScram_GenericList *_get_generic_list();

  void _make_interface_visible( symbol_table * );

  IIRScram_TypeDefinition *_get_port_type( int );


#ifdef PROCESS_COMBINATION
  void _static_elaborate(IIRScram_ArchitectureDeclaration*, IIRScram_DeclarationList*,  char*);
#endif

  IIRScram_AttributeSpecificationList	*_get_attribute_specification_list();
  IIRScram_GenericList			*_get_local_generic_clause();
  IIRScram_PortList			*_get_local_port_clause();
  IIRScram_EntityDeclaration		*_get_entity();
  
protected:
private:
};
#endif
