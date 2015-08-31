#ifndef IIRSCRAM_ARRAY_SUBTYPE_DEFINITION_HH
#define IIRSCRAM_ARRAY_SUBTYPE_DEFINITION_HH
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
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_ArrayTypeDefinition.hh"
#include "IIRBase_ArraySubtypeDefinition.hh"
#include "IIRScram_FunctionDeclaration.hh"

class visitor_argument_type;
class published_file;
class node_visitor;
class visitor_return_type;
class IIRScram_ScalarTypeDefinition;

class IIRScram_ArraySubtypeDefinition : public virtual IIRScram_ArrayTypeDefinition,
					public virtual IIRBase_ArraySubtypeDefinition{

public:
  IIRScram_ArraySubtypeDefinition(){}
  virtual ~IIRScram_ArraySubtypeDefinition();
    
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  static IIRScram_ArraySubtypeDefinition *get( IIRScram_ArrayTypeDefinition *bt,
                                               IIRScram_ScalarTypeDefinition *is,
                                               IIRScram_FunctionDeclaration *res_func );


  virtual void _type_check();
  virtual IIRScram *_clone();

  IIRScram_FunctionDeclaration* _get_resolution_function(){ return dynamic_cast<IIRScram_FunctionDeclaration *>(get_resolution_function()); }

  IIR_Boolean is_locally_static();

  virtual void _set_resolution_function( IIRScram_FunctionDeclaration *new_decl ){
    set_resolution_function( dynamic_cast<IIR_FunctionDeclaration *>(new_decl) ); 
  }
};
#endif
