#ifndef IIRSCRAM_DESIGNATORBYALL_HH
#define IIRSCRAM_DESIGNATORBYALL_HH
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
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Designator.hh"
#include "IIRBase_DesignatorByAll.hh"
#include "savant.hh"
#include <cstring>

class IIRScram_Declaration;
class IIRScram_TypeDefinition;

class IIRScram_DesignatorByAll : public virtual IIRScram_Designator, public virtual IIRBase_DesignatorByAll{
public:
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  const string convert_to_library_name(){ return ""; }
  
  savant::set<IIRScram_Declaration> *_symbol_lookup( savant::set<IIRScram_Declaration> * );

  savant::set<IIRScram_TypeDefinition> *_get_rval_set( savant::set<IIRScram_Declaration> *, 
                                                       constraint_functor *functor = 0 );

  savant::set<IIRScram_TypeDefinition> *_get_rval_set( savant::set<IIRScram_TypeDefinition> *, 
                                                       constraint_functor *functor = 0 );


  IIRScram_Declaration *_determine_decl_in_set( savant::set<IIRScram_Declaration> *, IIRScram_TypeDefinition * );
  IIRScram_TypeDefinition *_determine_rval_in_set( savant::set<IIRScram_TypeDefinition> *prefix_types,
                                                   IIRScram_TypeDefinition *return_type );

  IIRScram *_rval_to_decl( IIRScram_TypeDefinition *prefix_type, IIRScram_TypeDefinition *suffix_rval );
  IIRScram *_rval_to_decl( IIRScram_Declaration *prefix_decl, IIRScram_TypeDefinition *suffix_rval );
  IIR_Boolean _is_writable(){ return TRUE; };
  IIR_Boolean _is_readable(){ return TRUE; };
  IIR_Boolean _is_by_all(){ return TRUE; }

protected:
private:
};
#endif
