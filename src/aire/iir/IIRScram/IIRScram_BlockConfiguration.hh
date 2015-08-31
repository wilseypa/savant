#ifndef IIRSCRAM_BLOCK_CONFIGURATION_HH
#define IIRSCRAM_BLOCK_CONFIGURATION_HH

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
//          Umesh Kuamr V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_ConfigurationItem.hh"
#include "IIRBase_BlockConfiguration.hh"

class IIRScram_ConfigurationDeclaration;
class IIRScram_ConfigurationItemList;
class IIRScram_ComponentConfiguration;
class IIRScram_DeclarationList;
class IIRScram_List;

class IIRScram_BlockConfiguration : public virtual IIRScram_ConfigurationItem, public virtual IIRBase_BlockConfiguration {
public:
  IIRScram_BlockConfiguration();
  virtual ~IIRScram_BlockConfiguration();
    
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  void _type_check_configuration_item( IIRScram_List *, IIRScram * );

  IIRScram                              *_get_block_specification();
  IIRScram_DeclarationList              *_get_use_clause_list();
  IIRScram_ConfigurationItemList        *_get_configuration_item_list();

protected:
private:
  void _type_check_block_specification( IIRScram_List *, IIRScram * );
  void _resolve_specification_inside_configuration_declaration( IIRScram_ConfigurationDeclaration * );
  void _resolve_specification_inside_component_configuration( IIRScram_ComponentConfiguration * );
  void _resolve_specification_inside_block_configuration(  IIRScram_List *, IIRScram_BlockConfiguration * );
};

#endif
