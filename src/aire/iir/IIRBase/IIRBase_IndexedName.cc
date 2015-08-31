
// Copyright (c) 1996-1999 The University of Cincinnati.  
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

//---------------------------------------------------------------------------

#include "savant.hh"
#include "IIRBase_IndexedName.hh"
#include "IIR_AssociationList.hh"
#include "IIR_DesignFile.hh"
#include "IIR_Declaration.hh"
#include "IIR_AssociationElement.hh"
#include "IIR_AssociationElementByExpression.hh"
#include "plugin_class_factory.hh"

IIRBase_IndexedName::IIRBase_IndexedName() {
  set_suffix(NULL);
}

IIRBase_IndexedName::~IIRBase_IndexedName() {}

void
IIRBase_IndexedName::set_suffix( IIR* suffix) {
  this->suffix = suffix;
}

IIR*
IIRBase_IndexedName::get_suffix() {
  return suffix;
}

IIR *
IIRBase_IndexedName::get_declarative_region(){
  ASSERT( get_prefix_declaration() != 0 );
  return get_prefix_declaration()->get_declarative_region();
}

IIR *
IIRBase_IndexedName::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_IndexedName *new_node = dynamic_cast<IIRBase_IndexedName *>(IIRBase_Name::convert_tree(factory));

  // Process the variables
  new_node->suffix = convert_node(suffix, factory);

  return new_node;
}

IIR_Boolean 
IIRBase_IndexedName::is_resolved(){
  if( get_prefix()->is_resolved() == TRUE && 
      get_suffix()->is_resolved() == TRUE ){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

IIR_Boolean 
IIRBase_IndexedName::is_signal(){
  ASSERT( is_resolved() == TRUE );
  return get_prefix()->is_signal();
}


IIR_Boolean
IIRBase_IndexedName::is_interface() {
  return get_prefix()->is_interface();
}

IIR *
IIRBase_IndexedName::get_index( int index_num ){
  if( get_suffix()->get_kind() == IIR_ASSOCIATION_LIST ){
    IIR_AssociationList *as_list = dynamic_cast<IIR_AssociationList *>(get_suffix());
    return dynamic_cast<IIR *>(as_list->get_nth_element( index_num - 1 ));
  }
  else{
    ASSERT( index_num == 1 );
    return get_suffix();
  }
}

void 
IIRBase_IndexedName::set_index( int index_num, IIR *new_index ){
  ASSERT( get_suffix()->get_kind() == IIR_ASSOCIATION_LIST );
  
  IIR_AssociationList *as_list = dynamic_cast<IIR_AssociationList *>(get_suffix());
  IIR_AssociationElement *current_index = dynamic_cast<IIR_AssociationElement *>(as_list->get_nth_element( index_num - 1 ));
  
  IIR_AssociationElement *new_association = dynamic_cast<IIR_AssociationElement *>(new_index);
  if( new_index == NULL ){
    IIR_AssociationElementByExpression *by_expr = get_design_file()->get_class_factory()->new_IIR_AssociationElementByExpression();
    copy_location( this, by_expr );
    by_expr->set_actual( new_index );
    new_association = by_expr;
  }
  
  as_list->_replace( current_index, new_association );
}

IIR_Int32 
IIRBase_IndexedName::get_num_indexes(){
  if( get_suffix()->get_kind() == IIR_ASSOCIATION_LIST ){
    IIR_AssociationList *as_list = dynamic_cast<IIR_AssociationList *>(get_suffix());
    return as_list->num_elements();
  }
  else{
    return 1;
  }
}

IIR_Boolean 
IIRBase_IndexedName::is_variable(){
  ASSERT( is_resolved() == TRUE );
  return get_prefix()->is_variable();
}

ostream &
IIRBase_IndexedName::print( ostream &os ){
  os << *get_prefix();
  os << "(";
  os << *get_suffix();
  os << ")";

  return os;
}

IIR_Declaration*
IIRBase_IndexedName::get_prefix_declaration() {
  return get_prefix()->get_prefix_declaration();
}

void 
IIRBase_IndexedName::publish_vhdl(ostream &vhdl_out) {
  get_prefix()->publish_vhdl(vhdl_out);
  vhdl_out << "(";
  get_suffix()->publish_vhdl(vhdl_out);
  vhdl_out << ")";
}
