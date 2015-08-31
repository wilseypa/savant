
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
//          Timothy J. McBrayer 
//          Narayanan Thondugulam
//	    Magnus Danielson	cfmd@swipnet.se

#include "IIRScram_ArchitectureStatement.hh"
#include "IIRScram_ArchitectureStatementList.hh"

using std::cerr;

IIRScram_Label *
IIRScram_ArchitectureStatementList::_find_instantiate_label( IIRScram_SimpleName *to_find ){
  IIRScram_Label *retval = NULL;
  IIRScram_ArchitectureStatement *node;

  for (node = dynamic_cast<IIRScram_ArchitectureStatement *>(first()); 
       node != NULL; 
       node = dynamic_cast<IIRScram_ArchitectureStatement *>(successor(node))) {
    retval = node->_find_instantiate_label( to_find );
    if( retval != NULL ){
      break;
    }
  }

  return retval;
}

void 
IIRScram_ArchitectureStatementList::_type_check_instantiate_statements(){
  IIRScram_ArchitectureStatement *node;

  for (node = dynamic_cast<IIRScram_ArchitectureStatement *>(first()); 
       node != NULL; 
       node = dynamic_cast<IIRScram_ArchitectureStatement *>(successor(node))) {
    node->_type_check_instantiate_statements();
  }
}

visitor_return_type *
IIRScram_ArchitectureStatementList::_accept_visitor( node_visitor *visitor,
						     visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ArchitectureStatementList(this, arg);
}
