
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
//---------------------------------------------------------------------------

#include "IIRScram_DivisionOperator.hh"
#include "IIRScram_IntegerSubtypeDefinition.hh"
#include "StandardPackage.hh"
#include "set.hh"
#include "error_func.hh"
#include "resolution_func.hh"

IIRScram_DivisionOperator::~IIRScram_DivisionOperator() {}

IIRScram*
IIRScram_DivisionOperator::_clone() {
  IIRScram_DivisionOperator *clone = new IIRScram_DivisionOperator();
  IIRScram_DyadicOperator::_clone(clone);
  return clone;
}


visitor_return_type *
IIRScram_DivisionOperator::_accept_visitor( node_visitor *visitor,
					    visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_DivisionOperator(this, arg);
}
