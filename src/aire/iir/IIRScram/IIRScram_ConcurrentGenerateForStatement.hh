#ifndef IIRSCRAM_CONCURRENT_GENERATE_FOR_STATEMENT_HH
#define IIRSCRAM_CONCURRENT_GENERATE_FOR_STATEMENT_HH

// Copyright (c) 1996-2003 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_ConcurrentStatement.hh"
#include "IIRBase_ConcurrentGenerateForStatement.hh"

class IIRScram_AssociationList;
class IIRScram_DeclarationList;
class IIRScram_Label;
class IIRScram_SimpleName;

class IIRScram_ConcurrentGenerateForStatement : public virtual IIRScram_ConcurrentStatement, public virtual IIRBase_ConcurrentGenerateForStatement{

public:
  IIRScram_ConcurrentGenerateForStatement();  
  virtual ~IIRScram_ConcurrentGenerateForStatement();
 
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  void _type_check();

  void _type_check_instantiate_statements();

  IIRScram_List *_get_statement_list();
  virtual IIRScram_AssociationList *_get_generic_map_aspect(){ return NULL; }

  IIRScram_DeclarationList* _get_declaration_list();
  
  IIRScram_Label *_find_instantiate_label( IIRScram_SimpleName * );

  IIRScram_ConstantDeclaration *                _get_generate_parameter_specification();
  IIRScram_DeclarationList *                    _get_block_declarative_part();
  IIRScram_ArchitectureStatementList *          _get_concurrent_statement_part();

protected:
    
private:
};
#endif
