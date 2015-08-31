#ifndef IIRSCRAM_ACCESS_TYPE_DEFINITION_HH
#define IIRSCRAM_ACCESS_TYPE_DEFINITION_HH
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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRBase_AccessTypeDefinition.hh"

class IIRScram_Name;
class IIRScram_FunctionDeclaration;
class IIRScram_AccessTypeDefinition;
class IIRScram_ScalarTypeDefinition;
class IIRScram_TypeDeclaration;
class IIRScram_AccessSubtypeDefinition;

class IIRScram_AccessTypeDefinition : public virtual IIRScram_TypeDefinition, public virtual IIRBase_AccessTypeDefinition{

public:
  IIRScram_AccessTypeDefinition();

  static IIRScram_AccessTypeDefinition *get( IIRScram_TypeDefinition *designated_type );

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  IIR_Boolean _is_iir_access_type_definition() { return TRUE; }
  IIR_Boolean _designates_incomplete_type();

  IIRScram_TypeDefinition *_get_element_subtype();

  IIR_Int32 get_num_indexes();
  
  virtual void _set_resolution_function( IIRScram_FunctionDeclaration * );

  IIRScram_TypeDefinition *_index_constrain_array( IIRScram_ScalarTypeDefinition *);
  
  void set_is_element( IIR_Boolean );  
  
  virtual IIRScram *_clone();
  virtual void _clone( IIRScram * );

  void _come_into_scope( symbol_table *sym_tab, IIRScram_TypeDeclaration *);
  void _come_out_of_scope( symbol_table *sym_tab );

  static IIRScram_AccessSubtypeDefinition *_construct_new_type( IIRScram_TypeDefinition         *designated_type,
                                                                IIRScram_TypeDeclaration        *type_decl,
                                                                IIRScram_DesignFile             *design_file);

  // Helper Functions
  IIRScram_TypeDefinition* _get_designated_type();
protected:
  virtual ~IIRScram_AccessTypeDefinition();
  
  IIRScram_TypeDefinition *_construct_new_subtype( IIRScram_Name                        *resolution_function, 
                                                   IIRScram_ScalarTypeDefinition        *new_constraint);
    
private:
};
#endif

