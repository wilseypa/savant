
#ifndef IIRSCRAM_CONSTANT_INTERFACE_DECLARATION_HH
#define IIRSCRAM_CONSTANT_INTERFACE_DECLARATION_HH

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
//          Timothy J. McBrayer 
//          Krishnan Subramani  
//          Umesh Kumar V. Rajasekaran 
//          Narayanan Thondugulam 

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_InterfaceDeclaration.hh"
#include "IIRBase_ConstantInterfaceDeclaration.hh"

class IIRScram_List;

class IIRScram_ConstantInterfaceDeclaration : public virtual IIRScram_InterfaceDeclaration, public virtual IIRBase_ConstantInterfaceDeclaration{

public:
  IIRScram_ConstantInterfaceDeclaration() {}
  virtual ~IIRScram_ConstantInterfaceDeclaration();

  IIR_Boolean is_locally_static_primary();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  void _build_generic_parameter_set(savant::set<IIRScram_Declaration> *);

  IIRScram *_clone();

  void _type_check( IIRScram_InterfaceDeclaration::_InterfaceListType );

  IIRScram * _get_value();

protected:    

private:
  IIR_Int32 _stmt_node_index;
};
#endif

