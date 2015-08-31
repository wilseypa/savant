
#ifndef IIRSCRAM_FUNCTION_CALL_HH
#define IIRSCRAM_FUNCTION_CALL_HH

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
//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_Expression.hh"
#include "IIRBase_FunctionCall.hh"

class IIRScram_Declaration;
class IIRScram_DesignatorList;
class IIRScram_FunctionCall;
class IIRScram_IndexedName;
class IIRScram_SubprogramDeclaration;
class IIRScram_TypeDefinition;

class IIRScram_FunctionCall : public virtual IIRScram_Expression, public virtual IIRBase_FunctionCall {
public:
  IIRScram_FunctionCall();
  virtual ~IIRScram_FunctionCall();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  //void _publish_cc_kernel_type( ostream &os );

  void _type_check( savant::set<IIRScram_TypeDefinition> * );
  IIRScram * _rval_to_decl( IIRScram_TypeDefinition * );
  IIRScram_SubprogramDeclaration* _get_implementation();

  savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor = 0);
  IIR_Boolean _is_readable(){ return TRUE; }
  IIR_Boolean _is_writable(){ return FALSE; }

  static IIRScram_FunctionCall *_build_function_call( IIRScram_SubprogramDeclaration *, IIRScram_IndexedName * );

  savant::set<IIRScram_Declaration> *_symbol_lookup();

  IIRScram *_clone();
  IIR_Mode _get_mode();

  // (See IIRScram.hh for description)
  IIRScram_Declaration *_find_formal_declaration();

  /** Resets the index values and the list of quantity and signal
      indexes. */

  // Helper functions
  IIRScram_AssociationList *_get_parameter_association_list();
protected:    

private:
  IIR_Boolean has_been_type_checked;
};
#endif
