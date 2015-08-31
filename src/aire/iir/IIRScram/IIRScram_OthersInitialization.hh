#ifndef IIRSCRAM_OTHERS_INITIALIZATION_HH
#define IIRSCRAM_OTHERS_INITIALIZATION_HH

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
//          Krishnan Subramani  skrish@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_Expression.hh"
#include "IIRBase_OthersInitialization.hh"

class IIRScram_DesignatorList;
class IIRScram_TypeDefinition;

class IIRScram_OthersInitialization : public virtual IIRScram_Expression, public virtual IIRBase_OthersInitialization{

public:
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor = 0);
  IIRScram *_semantic_transform( savant::set<IIRScram_TypeDefinition> * );
  void _type_check( savant::set<IIRScram_TypeDefinition> * );

  IIRScram *_rval_to_decl( IIRScram_TypeDefinition * );

  IIRScram *_get_expression();
protected:
private:
  // This method will build a set of the possible element types of this
  // "others" based off of the context passed in.
  savant::set<IIRScram_TypeDefinition> *_build_element_subtype_set( savant::set<IIRScram_TypeDefinition> *context_set );
};

#endif
