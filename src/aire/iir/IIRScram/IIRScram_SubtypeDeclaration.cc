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
//          Umesh Kumar V.Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Swaminathan Subramanian ssubrama@ececs.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_SubtypeDeclaration.hh"
#include "IIRScram_AttributeSpecificationList.hh"
#include "IIRScram_AttributeSpecification.hh"
#include "IIRScram_TextLiteral.hh"
#include "IIRScram_TypeDefinition.hh"
#include "set.hh"

IIRScram_SubtypeDeclaration::IIRScram_SubtypeDeclaration() {
  set_attributes(new IIRScram_AttributeSpecificationList());
}

IIRScram_SubtypeDeclaration::~IIRScram_SubtypeDeclaration() {
  delete get_attributes();
}

IIR_Int32 
IIRScram_SubtypeDeclaration::get_num_indexes(){
  ASSERT( _get_subtype() != NULL );
  return _get_subtype()->get_num_indexes();
}

IIRScram_AttributeSpecificationList*
IIRScram_SubtypeDeclaration::_get_attribute_specification_list(){
  return dynamic_cast<IIRScram_AttributeSpecificationList *>(get_attributes());
}

void
IIRScram_SubtypeDeclaration::_type_check(){
  ASSERT( _get_subtype() != NULL );
  _get_subtype()->_type_check();
}


IIRScram*
IIRScram_SubtypeDeclaration::_clone() {
  return this;
}

visitor_return_type *
IIRScram_SubtypeDeclaration::_accept_visitor( node_visitor *visitor, 
					      visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_SubtypeDeclaration(this, arg);
}
