#ifndef IIRSCRAM_CONFIGURATION_DECLARATION_HH
#define IIRSCRAM_CONFIGURATION_DECLARATION_HH

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
#include "IIRScram_LibraryUnit.hh"
#include "IIRBase_ConfigurationDeclaration.hh"

class IIRScram_ArchitectureDeclaration;
class IIRScram_BlockConfiguration;

class IIRScram_ConfigurationDeclaration : public virtual IIRScram_LibraryUnit, public virtual IIRBase_ConfigurationDeclaration{
public:
  IIRScram_ConfigurationDeclaration();
  virtual ~IIRScram_ConfigurationDeclaration();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  void _make_interface_visible( symbol_table * );

  void _type_check();

  // Wrappers for IIRBase functions
  IIRScram_DeclarationList      *_get_configuration_declarative_part();
  IIRScram_BlockConfiguration   *_get_block_configuration();
  IIRScram_EntityDeclaration    *_get_entity();
protected:    
private:
};
#endif
