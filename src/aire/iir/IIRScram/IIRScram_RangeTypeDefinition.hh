#ifndef IIRSCRAM_RANGE_TYPE_DEFINITION_HH
#define IIRSCRAM_RANGE_TYPE_DEFINITION_HH

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
#include "IIRBase_RangeTypeDefinition.hh"

class IIRScram_FunctionDeclaration;
class IIRScram_TypeDefinition;

/**
   The extension base for range types.
 */
class IIRScram_RangeTypeDefinition : public virtual IIRScram_ScalarTypeDefinition, public virtual IIRBase_RangeTypeDefinition{

public:
  IIRScram_RangeTypeDefinition() {}
  virtual ~IIRScram_RangeTypeDefinition();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  IIR_Boolean _is_numeric_type(){ return TRUE; };


  void _set_resolution_function( IIRScram_FunctionDeclaration * );

  virtual IIRScram_TypeDefinition *_get_new_subtype();

  // This method takes the range passed in, and determines the discrete type that applies.
  // The type must be determinable WITHOUT context.  This method is appropriate for 
  // determining the type of the range given in:
  // 1) Index constraints of arrays.
  // 2) The discrete range of iteration schemes in for loops.
  // 3) The discrete range of iteration schemes in generate statements.
  // See pg 42, line 354 of the 93 LRM.
  IIRScram_ScalarTypeDefinition *_determine_discrete_type();

protected:    
private:
  IIRScram_ScalarTypeDefinition *_determine_universal_subtype(IIRScram_TypeDefinition *left_type,
							      IIRScram_TypeDefinition *right_type);
  
};
#endif
