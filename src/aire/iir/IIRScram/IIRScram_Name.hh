#ifndef IIRSCRAM_NAME_HH
#define IIRSCRAM_NAME_HH

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
//          Timothy J. McBrayer tmcbraye@ececs.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram.hh"
#include "IIRBase_Name.hh"
#include "savant.hh"

class IIRScram_Declaration;
class IIRScram_DesignatorList;
class IIRScram_LibraryDeclaration;
class IIRScram_LibraryUnit;
class IIRScram_Name;
class IIRScram_TextLiteral;
class IIRScram_TypeDefinition;

class IIRScram_Name : public virtual IIRScram, public virtual IIRBase_Name{

public:
  static IIRScram **lookup( IIRScram_Identifier *identifier,
                            IIR_Int32      &number_of_matches,
                            IIRScram            *&first_match);

  static IIRScram **lookup( IIRScram_Name    *name,
                            IIR_Int32   &number_of_matches,
                            IIRScram         *&first_match);

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  IIR_Boolean _is_iir_name(){ return TRUE; }

  virtual IIR_Boolean _is_by_all(){ return FALSE; }

  virtual void set_subtype( IIR_TypeDefinition * );

  virtual savant::set<IIRScram_Declaration> *_symbol_lookup();
  virtual savant::set<IIRScram_Declaration> *_symbol_lookup( IIRScram_Declaration * );
  virtual savant::set<IIRScram_Declaration> *_symbol_lookup( savant::set<IIRScram_Declaration> * );
  virtual savant::set<IIRScram_Declaration> *_symbol_lookup( constraint_functor *functor );

  IIRScram_TextLiteral *_get_string();

  savant::set<IIRScram_TypeDefinition> *
  _get_rval_set(constraint_functor *functor = 0){ 
    return IIRScram::_get_rval_set( functor );
  }

  savant::set<IIRScram_TypeDefinition> *_get_rval_set( savant::set<IIRScram_TypeDefinition> *search_in,
                                                       constraint_functor *functor = 0 );
  savant::set<IIRScram_TypeDefinition> *_get_rval_set( savant::set<IIRScram_Declaration> *search_in,
                                                       constraint_functor *functor = 0 );

  IIRScram *_get_prefix();

  virtual IIRScram *_get_suffix() { return NULL; }

  virtual void _set_suffix(IIRScram *suffix);

  void _clone( IIRScram * );

  virtual void _build_lib( IIRScram_LibraryUnit * );

protected:    
private:
};
#endif
