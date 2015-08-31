#ifndef IIRSCRAM_ENTITY_DECLARATION_HH
#define IIRSCRAM_ENTITY_DECLARATION_HH

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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_LibraryUnit.hh"
#include "IIRBase_EntityDeclaration.hh"

class IIRScram_EntityDeclaration : public virtual IIRScram_LibraryUnit, public virtual IIRBase_EntityDeclaration{

public:
  IIRScram_EntityDeclaration();
  virtual ~IIRScram_EntityDeclaration();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  void _make_interface_visible( symbol_table * );


  void _type_check();
  
  // Wrappers for IIRBase functions
  IIRScram_DeclarationList *                    _get_entity_declarative_part();
  IIRScram_EntityDeclaration*                   _get_entity();
  IIRScram_PortList *                           _get_port_clause();
  IIRScram_PortList *                           _get_port_list();
  IIRScram_GenericList *                        _get_generic_clause();
  IIRScram_GenericList *                        _get_generic_list();
  IIRScram_ArchitectureStatementList *          _get_entity_statement_part();
   
private:
};
#endif


