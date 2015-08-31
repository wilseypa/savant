
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

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer
//          Umesh Kumar V. Rajasekaran
//          Krishnan Subramani 
//          Malolan Chetlur    

//---------------------------------------------------------------------------

#include "IIRScram_DesignFile.hh"
#include "IIRScram_FloatingPointLiteral.hh"
#include "IIRScram_FloatingSubtypeDefinition.hh"
#include "StandardPackage.hh"
#include "set.hh"


#include <iomanip>

using std::setprecision;

IIRScram_FloatingPointLiteral::~IIRScram_FloatingPointLiteral() {}


void 
IIRScram_FloatingPointLiteral::_type_check( savant::set<IIRScram_TypeDefinition> * ){
  // We could make sure that the set contains a floating point type...
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_FloatingPointLiteral::_get_rval_set(constraint_functor *functor){
  savant::set<IIRScram_TypeDefinition> *retval = new savant::set<IIRScram_TypeDefinition>( dynamic_cast<IIRScram_FloatingSubtypeDefinition *>(_get_design_file()->get_standard_package()->get_savant_universal_real()) );

  retval->reduce_set( functor );

  return retval;
}

visitor_return_type *
IIRScram_FloatingPointLiteral::_accept_visitor( node_visitor *visitor,
						visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_FloatingPointLiteral(this, arg);
}

IIRScram_FloatingPointLiteral*
IIRScram_FloatingPointLiteral::get(IIR_Int32 base, 
                                   IIR_Char* mantissa, IIR_Int32 mantissa_length,
                                   IIR_Char* exponent, IIR_Int32 exponent_length) {
  ASSERT((mantissa != NULL && mantissa_length > 0));

  IIRScram_FloatingPointLiteral *retval = new IIRScram_FloatingPointLiteral();
  retval->set_base(base);
  retval->set_mantissa( strdup(mantissa), mantissa_length );
  if (exponent != NULL) {
    retval->set_exponent( strdup(exponent), exponent_length );
  }
  else {
    retval->set_exponent(exponent, exponent_length);
  }
  return retval;
}
