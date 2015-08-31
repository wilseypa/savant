
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
//          Malolan Chetlur     mal@ece.cu.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram.hh"
#include "IIRScram_ConfigurationItemList.hh"
#include "IIRScram_ConfigurationItem.hh"
#include "savant.hh"  

IIRScram_ConfigurationItemList::~IIRScram_ConfigurationItemList(){}

void
IIRScram_ConfigurationItemList::_type_check_configuration_item( IIRScram_List *statement_list,
								IIRScram *enclosing_region ){
  ASSERT( enclosing_region != NULL );
  IIRScram_ConfigurationItem *configuration_item = first();
  while( configuration_item != NULL ){
    configuration_item->_type_check_configuration_item( statement_list, enclosing_region );
    configuration_item = successor( configuration_item );
  }
}

IIRScram_ConfigurationItem *
IIRScram_ConfigurationItemList::first(){
  return dynamic_cast<IIRScram_ConfigurationItem *>(IIRScram_List::first());
}

IIRScram_ConfigurationItem *
IIRScram_ConfigurationItemList::successor( IIRScram_ConfigurationItem *to_succeed ){
  ASSERT( to_succeed != NULL );
  ASSERT( to_succeed->_is_iir_configuration_item() == TRUE );
  IIRScram *temp = dynamic_cast<IIRScram *>(IIRScram_List::successor( to_succeed ));
  if( temp != NULL ){
    ASSERT( temp->_is_iir_configuration_item() == TRUE );
    return dynamic_cast<IIRScram_ConfigurationItem *>(temp);
  }
  else{
    return NULL;
  }
}

void 
IIRScram_ConfigurationItemList::append( IIRScram_ConfigurationItem *to_append ){
  ASSERT( to_append != NULL );
  ASSERT( to_append->_is_iir_configuration_item() == TRUE );
  IIRScram_List::append( to_append );
}

visitor_return_type *IIRScram_ConfigurationItemList::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ConfigurationItemList(this, arg);
};
