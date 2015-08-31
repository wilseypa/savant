#ifndef IIRSCRAM_OPERATOR_HH
#define IIRSCRAM_OPERATOR_HH

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

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRBase_Operator.hh"
#include "IIRScram_Expression.hh"

class IIRScram_AssociationList;
class IIRScram_DesignatorList;
class IIRScram_SubprogramDeclaration;
class IIRScram_TypeDefinition;

class IIRScram_Operator : public virtual IIRScram_Expression,
			  public virtual IIRBase_Operator {
public:
  IIRScram_Operator(){ 
    my_rvals = NULL;
    has_been_type_checked = FALSE;
  }
  virtual ~IIRScram_Operator() {};
    
  virtual IIR_Int32 _get_num_args() = 0;
  virtual IIRScram_AssociationList *_build_argument_list() = 0;

  savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor = 0); 
  savant::set<IIRScram_TypeDefinition> *_get_user_overloaded_rvals();
  savant::set<IIRScram_Declaration> *_symbol_lookup();

  /** This is the entrance into the type checking routines for
      operators... */
  void _type_check( savant::set<IIRScram_TypeDefinition> * );

  /** If this operator is a call to one that's user overloaded, this method
      transforms it into an IIRScram_FunctionCall. */
  IIRScram *_semantic_transform( savant::set<IIRScram_TypeDefinition> * );

  /** This method looks for a user overloaded version of an operator and
      returns true if a valid user overloading of the operator is found.
      If not, the type_checking assumes a valid VHDL default definition of
      the operator is being used.  See next method. */
  IIR_Boolean _type_check_user_declared( savant::set<IIRScram_TypeDefinition> * );    
  
  IIRScram *_rval_to_decl( IIRScram_TypeDefinition * );

  // Helper Functions
  IIRScram_SubprogramDeclaration *_get_implementation();

protected:
  virtual const string _get_function_name() const = 0;  

  // We've found an implementation for this node - now we'll type check the
  // operands.
  virtual void _type_check_operands( ) = 0;

private:
  savant::set<IIRScram_TypeDefinition> *my_rvals;
  IIR_Boolean has_been_type_checked;
  IIRScram_SubprogramDeclaration *my_decl;
};
#endif
