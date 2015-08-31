#ifndef IIRSCRAM_SLICE_NAME_HH
#define IIRSCRAM_SLICE_NAME_HH

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
//          Krishnan Subramani  skrish@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_Name.hh"
#include "IIRBase_SliceName.hh"

class IIRScram_Declaration;
class IIRScram_List;
class IIRScram_TypeDefinition;

class IIRScram_SliceName : public virtual IIRScram_Name, public virtual IIRBase_SliceName{

public:
  IIRScram_SliceName(){ }
  virtual ~IIRScram_SliceName();    

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor = 0 );
  void _type_check( savant::set<IIRScram_TypeDefinition> * );


  IIR_Mode _get_mode();

  IIR_Boolean _is_readable();
  IIR_Boolean _is_writable();  
  savant::set<IIRScram_Declaration> *_symbol_lookup(){ return NULL; }
  IIRScram_TypeDefinition* _get_name_type();
  
  // These methods can be called when a block configuration has a
  // block specification in the form of <GENERATE LABEL>( <RANGE> ) -
  // the parser builds a slice to represent this.
  void _make_interface_visible( symbol_table * );

  IIRScram_List *_get_statement_list();

  IIRScram *_clone();

  IIRScram *_get_suffix();

  // (See IIRScram.hh for description)
  IIRScram_Declaration *_find_formal_declaration();

  // Override the undefined definition in IIRScram_Name
  void set_subtype(IIR_TypeDefinition *type) { IIRBase::set_subtype(type); }
protected:  
private:

};

#endif

