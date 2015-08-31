#ifndef IIRSCRAM_ENUMERATION_SUBTYPE_DEFINITION_HH
#define IIRSCRAM_ENUMERATION_SUBTYPE_DEFINITION_HH
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
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_EnumerationTypeDefinition.hh"
#include "IIRBase_EnumerationSubtypeDefinition.hh"

class IIRScram_EnumerationSubtypeDefinition;
class IIRScram_FunctionDeclaration;
class IIRScram_EnumerationLiteral;

class IIRScram_EnumerationSubtypeDefinition : public virtual IIRBase_EnumerationSubtypeDefinition, public virtual IIRScram_EnumerationTypeDefinition{

public:
  IIRScram_EnumerationSubtypeDefinition();
  ~IIRScram_EnumerationSubtypeDefinition();

  static IIRScram_EnumerationSubtypeDefinition *  get( IIRScram_EnumerationTypeDefinition *base_type,
                                                       IIRScram_EnumerationLiteral *left_limit,
                                                       IIRScram_EnumerationLiteral *right_limit);

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  void set_resolution_function( IIRScram_FunctionDeclaration *);
  void _set_resolution_function( IIRScram_FunctionDeclaration *);
  IIRScram_FunctionDeclaration* _get_resolution_function();

  virtual void _type_check( );

  virtual IIRScram *_clone( );
  virtual void _clone( IIRScram * );

  // Wrappers for IIRBase functions
  IIRScram_EnumerationLiteralList *     _get_enumeration_literals();
protected:
private:
};
#endif

