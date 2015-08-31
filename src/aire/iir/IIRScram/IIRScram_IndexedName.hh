#ifndef IIRSCRAM_INDEXED_NAME_HH
#define IIRSCRAM_INDEXED_NAME_HH
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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Name.hh"
#include "IIRBase_IndexedName.hh"

class IIRScram_Declaration;
class IIRScram_GenericList;
class IIRScram_PortList;
class IIRScram_SliceName;
class IIRScram_TypeDefinition;

class IIRScram_IndexedName : public virtual IIRScram_Name, public virtual IIRBase_IndexedName{

public:
  virtual ~IIRScram_IndexedName() {}
  IIRScram_IndexedName(){
    _been_transformed = FALSE;
    _my_rval_set = NULL;
    _have_rval_set = FALSE;
  }

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  IIRScram_Declaration* _get_package_declaration();
  
  /** This has to return a set because we can't always precisely determine
      the type without context... */
  savant::set<IIRScram_TypeDefinition> *_return_type_given_prefix_declaration( IIRScram_Declaration *prefix_decl );

  savant::set<IIRScram_Declaration> *_symbol_lookup();
  savant::set<IIRScram_Declaration> *_symbol_lookup( savant::set<IIRScram_Declaration> *);
  savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor = 0);
  savant::set<IIRScram_TypeDefinition> *_get_rval_set( savant::set<IIRScram_Declaration> *, 
                                                       constraint_functor *functor = 0);

  IIRScram_TypeDefinition *_get_name_type();

  IIR_Boolean _is_readable();
  IIR_Boolean _is_writable();

  /** Assuming we have an array type (which gets asserted), is this an
      array access (returns TRUE) or a slice? */
  IIR_Boolean _is_array_access();

  IIRScram *_semantic_transform( savant::set<IIRScram_TypeDefinition> *context_set );
  IIRScram *_rval_to_decl( IIRScram_TypeDefinition * );
  IIRScram *_rval_to_decl( IIRScram_Declaration *, IIRScram_TypeDefinition * );
  IIRScram_Declaration *_determine_decl_in_set( savant::set<IIRScram_Declaration> *, IIRScram_TypeDefinition * );

  void _type_check( savant::set<IIRScram_TypeDefinition> * );

  // Override the IIR_Name default
  void set_subtype(IIR_TypeDefinition *type) { IIRBase::set_subtype(type); }

  IIRScram *_get_suffix();
  IIRScram *_get_prefix();
  IIRScram *_clone();

  // This is for type checking.  Assume this indexed name is a
  // function call, and create an IIRScram_FunctionCall if it really is.
  // Return NULL if it's not.
  IIRScram *_process_as_function_call( savant::set<IIRScram_TypeDefinition> *context_set );

  // Same as above, but for a type conversion...
  IIRScram *_process_as_type_conversion( savant::set<IIRScram_TypeDefinition> * );

  // (See IIRScram.hh for description)
  IIRScram_Declaration *_find_formal_declaration();

  IIRScram_GenericList *_get_generic_list();
  IIRScram_PortList *_get_port_list();

  IIR_Mode _get_mode();

  void _set_my_rval( IIRScram_TypeDefinition *new_rval );

  IIRScram *_get_index(int index_num);

protected:    
private:
  // Same as above, but for an array...
  IIRScram *_process_as_array( savant::set<IIRScram_TypeDefinition> * );
  // Same as above, but for a slice...
  IIRScram *_process_as_slice( savant::set<IIRScram_TypeDefinition> * );

  savant::set<IIRScram_TypeDefinition> *_my_type_given_array_prefix_type( IIRScram_TypeDefinition * );

  IIRScram_SliceName *_build_slice( IIRScram_TypeDefinition * );

  savant::set<IIRScram_TypeDefinition> *_get_array_prefixes();

  // This flag tells us when calculating rvals whether we need to consider
  // that this node might represent a function call.
  IIR_Boolean _been_transformed;
  savant::set<IIRScram_TypeDefinition> *_my_rval_set;
  IIR_Boolean _have_rval_set;
};
#endif
