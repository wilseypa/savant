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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_DesignFile.hh"
#include "IIRScram_PhysicalLiteral.hh"
#include "IIRScram_PhysicalUnit.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_UnitList.hh"
#include "resolution_func.hh"
#include "error_func.hh"
#include "set.hh"
#include "IIRScram_PhysicalTypeDefinition.hh"
#include "savant.hh"

#include <sstream>
using std::ostringstream;
using std::cerr;

void 
IIRScram_PhysicalLiteral::_type_check( savant::set<IIRScram_TypeDefinition> *rval_set ){
  savant::set<IIRScram_Declaration> unit_decls( _get_unit_name() );
  reconcile_sets( &unit_decls, rval_set );
  switch( unit_decls.size() ){
  case 0:{
    ostringstream err;
    err << "Incompatible types in usage";
    report_error( this, err.str() );
    break;
  }

  case 1:{
    // Good they're actually compatible...
    ASSERT( unit_decls.getElement() != NULL );
    ASSERT( unit_decls.getElement()->get_kind() == IIR_PHYSICAL_UNIT );

    set_unit_name( dynamic_cast<IIRScram_PhysicalUnit*>((unit_decls.getElement())) );
    break;
  }

  default:{
    // We built a set of one - how could this be?
    cerr << "Internal error in IIRScram_PhysicalLiteral::_type_check";
    abort();
  }
  }
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_PhysicalLiteral::_get_rval_set( constraint_functor * ){
  savant::set<IIRScram_TypeDefinition> *retval;
  IIRScram_PhysicalUnit *my_unit = _get_unit_name();
  ASSERT( my_unit != NULL );
  ASSERT( my_unit->_is_iir_declaration() == TRUE );

  retval = new savant::set<IIRScram_TypeDefinition>( my_unit->_get_physical_type() );

  return retval;
}

IIRScram*
IIRScram_PhysicalLiteral::_clone() {
  return this;
}

visitor_return_type *
IIRScram_PhysicalLiteral::_accept_visitor( node_visitor *visitor, 
					   visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_PhysicalLiteral(this, arg);
}

IIRScram *
IIRScram_PhysicalLiteral::_get_abstract_literal() {
  return dynamic_cast<IIRScram *>(get_abstract_literal());
}

IIRScram_PhysicalUnit *
IIRScram_PhysicalLiteral::_get_unit_name() {
  return dynamic_cast<IIRScram_PhysicalUnit *>(get_unit_name());
}
