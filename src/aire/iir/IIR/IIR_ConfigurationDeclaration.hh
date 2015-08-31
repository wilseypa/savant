
#ifndef IIR_CONFIGURATION_DECLARATION_HH
#define IIR_CONFIGURATION_DECLARATION_HH

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
#include "IIR_LibraryUnit.hh"

class IIR_BlockConfiguration;
class IIR_EntityDeclaration;
class IIR_DeclarationList;

class IIR_ConfigurationDeclaration : public virtual IIR_LibraryUnit{

public:
  virtual ~IIR_ConfigurationDeclaration() {}
    
  // List accessor(s)
  virtual IIR_DeclarationList   *get_configuration_declarative_part() = 0;
  virtual void                  set_configuration_declarative_part(IIR_DeclarationList *) = 0;

  virtual void set_block_configuration(IIR_BlockConfiguration *block_configuration) = 0;
  virtual IIR_BlockConfiguration *get_block_configuration() = 0;

  virtual void set_entity( IIR_EntityDeclaration *entity ) = 0;
  virtual IIR_EntityDeclaration *get_entity() = 0;
};
#endif
