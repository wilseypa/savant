#ifndef IIRSCRAM_INTEGER_SUBTYPE_DEFINITION_HH
#define IIRSCRAM_INTEGER_SUBTYPE_DEFINITION_HH

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
//          Krishnan Subramani  skrish@ece.uc.ed
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_IntegerTypeDefinition.hh"
#include "IIRBase_IntegerSubtypeDefinition.hh"

class IIRScram_FunctionDeclaration;
class IIRScram_IntegerSubtypeDefinition;

class IIRScram_IntegerSubtypeDefinition : public virtual IIRScram_IntegerTypeDefinition,
					  public virtual IIRBase_IntegerSubtypeDefinition{
public:
  IIRScram_IntegerSubtypeDefinition();
  ~IIRScram_IntegerSubtypeDefinition();

  static IIRScram_IntegerSubtypeDefinition* 
  get( IIRScram_IntegerTypeDefinition* base_type,
       IIRScram* left_limit, IIRScram* direction, IIRScram* right_limit);

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);
  //  void _publish_cc_parent_type_name( published_file &_cc_out );

  IIRScram *_clone();

  IIRScram_FunctionDeclaration* _get_resolution_function();
  void _set_resolution_function(IIRScram_FunctionDeclaration *new_function );
  void set_resolution_function(IIRScram_FunctionDeclaration *new_function );

  virtual void _type_check();

protected:
private:
};
#endif
