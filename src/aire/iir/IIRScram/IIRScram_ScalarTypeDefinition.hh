#ifndef IIRSCRAM_SCALAR_TYPE_DEFINITION_HH
#define IIRSCRAM_SCALAR_TYPE_DEFINITION_HH
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
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRBase_ScalarTypeDefinition.hh"

class IIRScram_FunctionDeclaration;
class IIRScram_TypeDefinition;

class IIRScram_ScalarTypeDefinition : public virtual IIRScram_TypeDefinition,
				      public virtual IIRBase_ScalarTypeDefinition{

public:
  IIRScram_ScalarTypeDefinition();

  virtual IIRScram_TypeDefinition *
  _construct_new_subtype( IIRScram_Name                 *resolution_function,
			  IIRScram_ScalarTypeDefinition *new_constraint);
  
  /** This method takes all of the data passed in, and attempts to
     generate valid IIR for it.  */
  static void _init_scalar_type( IIRScram_RangeTypeDefinition *init_info,
				 IIRScram_ScalarTypeDefinition *base_type,
				 IIRScram_ScalarTypeDefinition *subtype,
				 IIRScram_TypeDeclaration *type_decl );

  virtual void set_resolution_function( IIRScram_FunctionDeclaration * );

  virtual void _clone( IIRScram * );

  /** This method takes the range passed in, and determines the discrete type that applies.
      The type must be determinable WITHOUT context.  This method is appropriate for 
      determining the type of the range given in:
      1) Index constraints of arrays.
      2) The discrete range of iteration schemes in for loops.
      3) The discrete range of iteration schemes in generate statements.
      See pg 42, line 354 of the 93 LRM. */
  static IIRScram_ScalarTypeDefinition *_determine_discrete_type( IIRScram_RangeTypeDefinition * );

  // Helper functions
  IIRScram                      *_get_left();
  IIRScram                      *_get_right();
  IIRScram                      *_get_direction();
protected:
  virtual ~IIRScram_ScalarTypeDefinition() = 0;
  void _build_implicit_operators( savant::set<IIRScram_Declaration> * );    
private:
};
#endif
