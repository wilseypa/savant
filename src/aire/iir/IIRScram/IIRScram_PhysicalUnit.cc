
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
//          Krishnan Subramani  skrish@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_AttributeSpecificationList.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_PhysicalTypeDefinition.hh"
#include "IIRScram_PhysicalUnit.hh"
#include "IIRScram_UnitList.hh"
#include "set.hh"
#include "savant.hh"

IIRScram_PhysicalUnit::IIRScram_PhysicalUnit(){
  set_attributes(new IIRScram_AttributeSpecificationList());
}

IIRScram_PhysicalUnit::~IIRScram_PhysicalUnit(){
  //Release the list memory
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_PhysicalUnit::_get_rval_set( constraint_functor *functor ){
  return new savant::set<IIRScram_TypeDefinition>( _get_subtype() );
}

visitor_return_type *
IIRScram_PhysicalUnit::_accept_visitor( node_visitor *visitor, 
					visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_PhysicalUnit(this, arg);
}

// IIRBase Function Wrapper(s)
IIRScram_AttributeSpecificationList *
IIRScram_PhysicalUnit::_get_attribute_specification_list(){ 
  return dynamic_cast<IIRScram_AttributeSpecificationList *>(get_attributes()); 
}

IIRScram *
IIRScram_PhysicalUnit::_get_multiplier() {
  return dynamic_cast<IIRScram *>(get_multiplier());
}

IIRScram_PhysicalTypeDefinition *
IIRScram_PhysicalUnit::_get_physical_type() {
  return dynamic_cast<IIRScram_PhysicalTypeDefinition *>(get_subtype());
}
