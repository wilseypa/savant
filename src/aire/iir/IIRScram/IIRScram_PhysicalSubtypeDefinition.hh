#ifndef IIRSCRAM_PHYSICAL_SUBTYPE_DEFINITION_HH
#define IIRSCRAM_PHYSICAL_SUBTYPE_DEFINITION_HH

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
//          Umesh Kumar V. Rajasekaran urajsek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_PhysicalTypeDefinition.hh"
#include "IIRBase_PhysicalSubtypeDefinition.hh"

class IIRScram_FunctionDeclaration;
class IIRScram_PhysicalSubtypeDefinition;

class IIRScram_PhysicalSubtypeDefinition : public virtual IIRScram_PhysicalTypeDefinition,
					   public virtual IIRBase_PhysicalSubtypeDefinition{

public:
  static IIRScram_PhysicalSubtypeDefinition* get(IIRScram_PhysicalTypeDefinition* base_type,
                                                 IIRScram* left_limit,
                                                 IIRScram* right_limit);

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);



  void _set_resolution_function(IIRScram_FunctionDeclaration *function);
  IIRScram_FunctionDeclaration* _get_resolution_function();

  virtual void _type_check();

  virtual IIRScram *_clone();
  virtual void _clone( IIRScram * );
  virtual IIR_Boolean _is_iir_physical_subtype_definition(){ return TRUE; }

protected:
private:
};

#endif
