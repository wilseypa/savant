
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
//          Timothy J. McBrayer 
//          Malolan Chetlur     
//          Krishnan Subramani  
//          Radharamanan Radhakrishnan

#include "IIRScram_DesignFile.hh"
#include "IIRScram_IntegerLiteral.hh"
#include "IIRScram_IntegerSubtypeDefinition.hh"
#include "IIRScram_Declaration.hh"
#include "StandardPackage.hh"
#include "symbol_table.hh"
#include "resolution_func.hh"
#include "set.hh"


void
IIRScram_IntegerLiteral::set_subtype( IIR_TypeDefinition *subtype ){
  IIRScram_TypeDefinition *my_subtype = dynamic_cast<IIRScram_TypeDefinition *>(subtype);
  ASSERT( my_subtype->_is_iir_integer_type_definition() == TRUE ||
	  my_subtype->_is_iir_physical_type_definition() == TRUE );
  IIRScram_Literal::set_subtype( my_subtype );
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_IntegerLiteral::_get_rval_set( constraint_functor * ){
  savant::set<IIRScram_TypeDefinition> *retval = 
    new savant::set<IIRScram_TypeDefinition>( dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(_get_design_file()->get_standard_package()->get_savant_universal_integer()) );
  return retval;
}

IIR_Boolean
IIRScram_IntegerLiteral::_is_integer_literal() {
  return true;
}

IIRScram_IntegerLiteral *
IIRScram_IntegerLiteral::_get_integer_static_value(){
  return dynamic_cast<IIRScram_IntegerLiteral *>(get( get_base(), get_mantissa(), get_mantissa_length(), get_exponent(), get_exponent_length() ));
}

visitor_return_type *
IIRScram_IntegerLiteral::_accept_visitor( node_visitor *visitor,
					  visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_IntegerLiteral(this, arg);
}

IIRScram_IntegerLiteral *
IIRScram_IntegerLiteral::get( IIR_Int32 base, 
                              IIR_Char *mantissa, 
                              IIR_Int32 mantissa_length,
                              IIR_Char *exponent, 
                              IIR_Int32 exponent_length) {
  ASSERT((mantissa != NULL && mantissa_length > 0));
  ASSERT((exponent != NULL && exponent_length > 0) || 
	 (exponent == NULL && exponent_length == 0));

  IIRScram_IntegerLiteral *retval = new IIRScram_IntegerLiteral();
  retval->set_base(base);
  retval->set_mantissa(strdup(mantissa), mantissa_length);
  if( exponent != NULL ){
    retval->set_exponent(strdup(exponent), exponent_length);
  }
  else{
    retval->set_exponent(exponent, exponent_length);
  }

  return retval;
}
