
#ifndef IIR_COMPONENT_DECLARATION_HH
#define IIR_COMPONENT_DECLARATION_HH

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
#include "IIR_Declaration.hh"

class IIR_AttributeSpecificationList;
class IIR_EntityDeclaration;
class IIR_GenericList;
class IIR_PortList;

class IIR_ComponentDeclaration : public virtual IIR_Declaration{

public:
  virtual ~IIR_ComponentDeclaration() {}
    
  virtual IIR_EntityDeclaration			*get_entity() = 0;
  virtual void					set_entity( IIR_EntityDeclaration *entity ) = 0;
  // List accessor(s)
  virtual IIR_GenericList                       *get_local_generic_clause() = 0;
  virtual IIR_PortList                          *get_local_port_clause() = 0;
  virtual IIR_AttributeSpecificationList        *get_attributes() = 0;
  virtual void                                  set_local_generic_clause(IIR_GenericList *) = 0;
  virtual void                                  set_local_port_clause(IIR_PortList *) = 0;
  virtual void                                  set_attributes(IIR_AttributeSpecificationList *) = 0;
};
#endif
