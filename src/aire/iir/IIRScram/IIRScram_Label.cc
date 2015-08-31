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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Timothy J. McBrayer tmcbraye@ececs.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_AttributeSpecification.hh"
#include "IIRScram_AttributeSpecificationList.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_TextLiteral.hh"
#include "IIRScram_Statement.hh"



IIRScram_Label::IIRScram_Label() {
  set_attributes(new IIRScram_AttributeSpecificationList());
}

IIRScram_Label::~IIRScram_Label(){}

void 
IIRScram_Label::_make_interface_visible( symbol_table *sym_tab ){
  ASSERT( _get_statement() != NULL );
  ASSERT( sym_tab != NULL );

  _get_statement()->_make_interface_visible( sym_tab );
}


IIRScram*
IIRScram_Label::_clone() {
  IIRScram_Label *clone = new IIRScram_Label();

  IIRScram_Declaration::_clone(clone);

  clone->set_statement(get_statement());
  IIRScram_AttributeSpecification *attr = 
    dynamic_cast<IIRScram_AttributeSpecification *>(get_attributes()->first());
  while (attr != NULL) {
    clone->get_attributes()->append(dynamic_cast<IIR_AttributeSpecification *>(attr));
    attr = dynamic_cast<IIRScram_AttributeSpecification *>(get_attributes()->successor(attr));
  }

  return clone;
}

visitor_return_type *IIRScram_Label::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_Label(this, arg);
};

IIRScram_AttributeSpecificationList* 
IIRScram_Label::_get_attribute_specification_list() {
  return dynamic_cast<IIRScram_AttributeSpecificationList *>(get_attributes());
}

IIRScram_Statement* 
IIRScram_Label::_get_statement() {
  return dynamic_cast<IIRScram_Statement *>(get_statement());
}

// IIRBase Function Wrapper(s)
IIRScram_List *
IIRScram_Label::_get_statement_list(){
  ASSERT( _get_statement() != NULL );
  return _get_statement()->_get_statement_list();
}

IIRScram_AttributeSpecificationList *
IIRScram_Label::_get_attributes() {
  return dynamic_cast<IIRScram_AttributeSpecificationList *>(get_attributes());
}
