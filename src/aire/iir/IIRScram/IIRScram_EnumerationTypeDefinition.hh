#ifndef IIRSCRAM_ENUMERATION_TYPE_DEFINITION_HH
#define IIRSCRAM_ENUMERATION_TYPE_DEFINITION_HH
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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_ScalarTypeDefinition.hh"
#include "IIRBase_EnumerationTypeDefinition.hh"

class IIRScram_EnumerationLiteralList;
class IIRScram_EnumerationSubtypeDefinition;
class IIRScram_EnumerationTypeDefinition;
class IIRScram_FunctionDeclaration;
class IIRScram_Name;
class IIRScram_TextLiteral;
class IIRScram_TypeDefinition;

class IIRScram_EnumerationTypeDefinition : public virtual IIRScram_ScalarTypeDefinition,
					   public virtual IIRBase_EnumerationTypeDefinition{

public:
  IIRScram_EnumerationTypeDefinition();
  virtual ~IIRScram_EnumerationTypeDefinition();
    
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  virtual IIRScram_TypeDefinition *_get_new_subtype();

  virtual IIRScram *_clone();
  virtual void _clone( IIRScram * );

  IIR_Boolean _is_iir_enumeration_type_definition(){ return TRUE; }

  void _come_into_scope( symbol_table *, IIRScram_TypeDeclaration * );
  void _come_out_of_scope( symbol_table * );

  void _set_resolution_function( IIRScram_FunctionDeclaration * );

  /**
     Using this definition of the literal list, construct a new type.
     
     @param literals The literal list.  The subtype will be set in the literals.

     @param locator_info The file and line info from this node will be copied into newly
     allocated IIRs - the base type, and the subtype.
  */
  static IIRScram_EnumerationSubtypeDefinition *
    _construct_new_type( IIRScram_EnumerationLiteralList *literals,
			 IIRScram_TypeDeclaration *type_decl,
			 IIRScram_DesignFile *design_file );

  // Wrappers for IIRBase functions
  IIRScram_EnumerationLiteralList *     _get_enumeration_literals();

protected:
private:
};
#endif


