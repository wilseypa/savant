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
//          Narayanan Thondugulam nthondug@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se
//---------------------------------------------------------------------------

#include "savant.hh"
#include "IIRScram_StringLiteral.hh"
#include "IIRScram_AccessSubtypeDefinition.hh"
#include "IIRScram_DesignFile.hh"
#include "StandardPackage.hh"
#include "set.hh"

using std::cerr;
using savant::set;

class IIRScram_AccessTypeDefinition;

void 
IIRScram_StringLiteral::_type_check( set<IIRScram_TypeDefinition> * ){}


set<IIRScram_TypeDefinition> *
IIRScram_StringLiteral::_get_rval_set(constraint_functor *functor){
  set<IIRScram_TypeDefinition> *retval = 0;

  if( cmp( this, "null" ) == 0 ){
    retval = new set<IIRScram_TypeDefinition>( dynamic_cast<IIRScram_TypeDefinition *>(_get_design_file()->get_standard_package()->get_savant_null_type_definition()) );
  }
  else{
    retval = _get_rval_set_for_string();
  }

  retval->reduce_set( functor );
  if( retval->size() == 0 ){
    delete retval;
    retval = 0;
  }

  return retval;
}

IIRScram*
IIRScram_StringLiteral::_clone() {
  return this;
}

visitor_return_type *
IIRScram_StringLiteral::_accept_visitor( node_visitor *visitor,
					 visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_StringLiteral(this, arg);
}

