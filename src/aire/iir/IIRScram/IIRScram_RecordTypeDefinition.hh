#ifndef IIRSCRAM_RECORD_TYPE_DEFINITION_HH
#define IIRSCRAM_RECORD_TYPE_DEFINITION_HH
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
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRBase_RecordTypeDefinition.hh"

class IIRScram_ElementDeclarationList;
class IIRScram_FunctionDeclaration;
class IIRScram_Name;
class IIRScram_ScalarTypeDefinition;
class IIRScram_TypeDeclaration;
class IIRScram_TypeDefinition;

class IIRScram_RecordTypeDefinition : public virtual IIRScram_TypeDefinition, public virtual IIRBase_RecordTypeDefinition{

public:
  IIRScram_RecordTypeDefinition();
  ~IIRScram_RecordTypeDefinition();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  virtual IIR_Boolean _is_iir_record_type_definition() { return TRUE; }

  IIRScram_ElementDeclarationList *_get_element_declarations();

  int _get_field_number(IIRScram *);
  
  IIRScram_FunctionDeclaration* _get_resolution_function();
  void _set_resolution_function(IIRScram_FunctionDeclaration *new_function );
  
  IIRScram_TypeDefinition *_get_new_subtype();

  IIRScram_TypeDefinition *
  _construct_new_subtype( IIRScram_Name                 *resolution_function,
			  IIRScram_ScalarTypeDefinition *new_constraint);

  void _make_interface_visible( symbol_table * );

  virtual void _type_check();

  virtual IIRScram *_clone();
  virtual void _clone( IIRScram * );

  void _come_into_scope( symbol_table *, IIRScram_TypeDeclaration * );
  void _come_out_of_scope( symbol_table * );

  IIRScram_TypeDefinition *_get_element_subtype(int);
protected:
private:
};
#endif


