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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_AccessSubtypeDefinition.hh"
#include "savant.hh"
  
IIRScram_AccessSubtypeDefinition::~IIRScram_AccessSubtypeDefinition(){}

IIRScram *
IIRScram_AccessSubtypeDefinition::_clone(){
  IIRScram_AccessSubtypeDefinition *retval = new IIRScram_AccessSubtypeDefinition();
  _clone( retval );
  return retval;
}

void 
IIRScram_AccessSubtypeDefinition::_clone( IIRScram *copy_into ){
  ASSERT( copy_into->get_kind() == IIR_ACCESS_SUBTYPE_DEFINITION );
  IIRScram_AccessSubtypeDefinition *as_access_subtype = dynamic_cast<IIRScram_AccessSubtypeDefinition *>(copy_into);
  as_access_subtype->set_designated_subtype( get_designated_subtype() );

  IIRScram_AccessTypeDefinition::_clone( copy_into );
}

visitor_return_type *
IIRScram_AccessSubtypeDefinition::_accept_visitor( node_visitor *visitor,
						   visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_AccessSubtypeDefinition(this, arg);
}

IIRScram_AccessSubtypeDefinition *
IIRScram_AccessSubtypeDefinition::get( IIRScram_TypeDefinition * ){
  std::cerr << "IIRBase_AccessSubtypeDefinition::get has not been implemented yet.\n";
  abort();

  return NULL;
}

IIRScram_TypeDefinition *
IIRScram_AccessSubtypeDefinition::_get_designated_subtype(){ 
  return dynamic_cast<IIRScram_TypeDefinition *>(get_designated_subtype()); 
}
