#ifndef IIRSCRAM_PHYSICAL_TYPE_DEFINITION_HH
#define IIRSCRAM_PHYSICAL_TYPE_DEFINITION_HH

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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_ScalarTypeDefinition.hh"
#include "IIRBase_PhysicalTypeDefinition.hh"

class IIRScram_FunctionDeclaration;
class IIRScram_PhysicalTypeDefinition;
class IIRScram_PhysicalUnit;
class IIRScram_TypeDefinition;
class IIRScram_UnitList;

class IIRScram_PhysicalTypeDefinition : public virtual IIRScram_ScalarTypeDefinition,
					public virtual IIRBase_PhysicalTypeDefinition{

public:
  IIRScram_PhysicalTypeDefinition();
  ~IIRScram_PhysicalTypeDefinition();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  IIR_Boolean _is_numeric_type() { return TRUE; }
  IIR_Boolean _is_physical_type() { return TRUE; }
  IIR_Boolean _is_iir_physical_type_definition() { return TRUE; }

  
  virtual IIRScram_TypeDefinition *_get_new_subtype();
  virtual IIRScram *_clone();
  virtual void _clone( IIRScram * );
  virtual IIRScram_TypeDefinition *_construct_new_subtype( IIRScram_Name *resolution_function,
                                                           IIRScram_ScalarTypeDefinition *new_constraint);

  void _set_resolution_function( IIRScram_FunctionDeclaration * );

  // Wrappers for IIRBase functions
  IIRScram_UnitList *           _get_units();
  IIRScram_PhysicalUnit *       _get_primary_unit();
protected: 
  void _build_implicit_operators( savant::set<IIRScram_Declaration> * );
    
private:
};

#endif
