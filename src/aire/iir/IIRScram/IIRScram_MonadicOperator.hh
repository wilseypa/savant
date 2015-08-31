
#ifndef IIRSCRAM_MONADIC_OPERATOR_HH
#define IIRSCRAM_MONADIC_OPERATOR_HH

// Copyright (c) 1996-2003 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
// DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     
//          Umesh Kumar V. Rajasekaran
//          Krishnan Subramani  
//          Timothy J. McBrayer 
//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Operator.hh"
#include "IIRBase_MonadicOperator.hh"

class IIR_AboveAttribute;

class IIRScram_AssociationList;
class IIRScram_DesignatorList;
class IIRScram_TypeDefinition;
class IIRScram_SubprogramDeclaration;

class IIRScram_MonadicOperator : public virtual IIRScram_Operator,
				 public virtual IIRBase_MonadicOperator {
public:
  IIR_Boolean _is_readable();

  virtual IIRScram *_rval_to_decl( IIRScram_TypeDefinition *my_rval );

  void _build_generic_parameter_set( savant::set<IIRScram_Declaration> *);
  IIRScram *_clone();


  IIRScram_SubprogramDeclaration *_get_implementation();
  IIRScram *_get_operand();
  
protected:
  IIR_Int32 _get_num_args(){ return 1; }  
  IIRScram_AssociationList *_build_argument_list();

  const string _get_function_name() const;

  void _type_check_operands( );
    
private:
};
#endif
