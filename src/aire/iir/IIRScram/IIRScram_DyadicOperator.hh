
#ifndef IIRSCRAM_DYADIC_OPERATOR_HH
#define IIRSCRAM_DYADIC_OPERATOR_HH

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
#include "IIRBase_DyadicOperator.hh"

class IIRScram_AssociationList;
class IIRScram_DesignatorList;
class IIRScram_TypeDefinition;
class IIR_ContributionAttribute;
class IIR_DotAttribute;
class IIRScram_SubprogramDeclaration;

class IIRScram_DyadicOperator : public virtual IIRScram_Operator,
				public virtual IIRBase_DyadicOperator{
public:
  IIRScram_DyadicOperator() {};

  //  virtual void _publish_cc_wait_data_short_circuit( published_file &_cc_out );

//   /** This function returns TRUE if the operation is a short circuit
//       operation.  As per section 7.2 of LRM: The logical operations
//       "and", "or", "nand" and "nor" defined for types BIT and BOOLEAN
//       are all short-circuit operations; furthermore, these are the only
//       short-circuit operations.  */
//   virtual IIR_Boolean _is_short_circuit();
  
  const string _get_function_name() const;

  IIR_Boolean _is_readable();

  void _resolve_operands( IIRScram_TypeDefinition *left_type, IIRScram_TypeDefinition *right_type );

  void _resolve_operand( IIRScram *(IIRScram_DyadicOperator::*get_method)(), 
			 void (IIRScram_DyadicOperator::*set_method)( IIRScram *),
			 IIRScram_TypeDefinition *operand_type );

  virtual void _clone( IIRScram * );

  IIRScram *_rval_to_decl( IIRScram_TypeDefinition *my_rval );

  // Wrappers
  IIRScram *_get_left_operand();
  IIRScram *_get_right_operand();
  IIRScram_SubprogramDeclaration *_get_implementation();
  void _build_reference_quantity_list(dl_list<IIRScram_ReferenceAttribute> *);

protected:
  IIR_Int32 _get_num_args(){ return 2; }
  IIRScram_AssociationList *_build_argument_list();

  virtual ~IIRScram_DyadicOperator() = 0;

  void _type_check_operands( );

private:
  
};
#endif
