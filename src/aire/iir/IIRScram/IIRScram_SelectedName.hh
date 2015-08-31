#ifndef IIRSCRAM_SELECTED_NAME_HH
#define IIRSCRAM_SELECTED_NAME_HH

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

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_Name.hh"
#include "IIRBase_SelectedName.hh"

class IIRScram_Declaration;
class IIRScram_GenericList;
class IIRScram_LibraryDeclaration;
class IIRScram_LibraryUnit;
class IIRScram_PortList;
class IIRScram_TypeDefinition;

class IIRScram_SelectedName : public virtual IIRScram_Name, public virtual IIRBase_SelectedName{

public:
  IIRScram_SelectedName(){  }

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  /** Find the first prefix.  It should be a library.  Return it. */
  IIRScram_LibraryDeclaration *_get_library_declaration();

  savant::set<IIRScram_Declaration> *_symbol_lookup();
  
  IIRScram *_get_suffix();

  const string convert_to_library_name();
  void _type_check( savant::set<IIRScram_TypeDefinition> * );
  savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor = 0);
  IIRScram *_rval_to_decl( IIRScram_TypeDefinition * );
  IIRScram *_decl_to_decl( IIRScram_Declaration * );

  IIR_Boolean is_object();
  IIR_Boolean is_configuration_declaration();
  IIR_Boolean _is_readable();
  IIR_Boolean _is_writable();

  IIR_Boolean _is_by_all();

  IIR_Boolean is_locally_static();
  
  void _set_suffix(IIRScram *suffix);

  void _build_lib( IIRScram_LibraryUnit * );
  
  void _make_interface_visible( symbol_table * );
  void _come_into_scope( symbol_table * );
  void _come_out_of_scope( symbol_table * );
  
  IIRScram_GenericList *_get_generic_list();
  IIRScram_PortList *_get_port_list();

  IIRScram *_clone();

  IIRScram_TypeDefinition *_get_rval_pointed_at();

protected:
private:
};

#endif
