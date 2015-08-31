
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





#include "IIR_AssociationElement.hh"
#include "IIRBase_AssociationList.hh"
#include "IIRBase_Aggregate.hh"

IIRBase_Aggregate::IIRBase_Aggregate() :
  element_association_list(0)
 { }

IIRBase_Aggregate::~IIRBase_Aggregate(){
}

// List Accessor(s)
IIR_AssociationList *IIRBase_Aggregate::get_element_association_list() {
  ASSERT(element_association_list != NULL);
  return element_association_list;
}


void
IIRBase_Aggregate::set_element_association_list(IIR_AssociationList *new_element_association_list) {
  ASSERT(new_element_association_list != NULL);
  delete element_association_list;
  element_association_list = new_element_association_list;
}

IIR *
IIRBase_Aggregate::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_Aggregate *new_node = dynamic_cast<IIRBase_Aggregate *>(IIRBase_Expression::convert_tree(factory));

  // Process the variables
  new_node->element_association_list = dynamic_cast<IIR_AssociationList *>(convert_node(element_association_list, factory));

  return new_node;
}

IIR_Boolean 
IIRBase_Aggregate::is_resolved( ){
  IIR_Boolean retval = TRUE;

  if( get_element_association_list()->is_resolved() == FALSE ){
    retval = FALSE;
  }

  if( get_subtype() == NULL ){
    retval = FALSE;
  }

  return retval;
}

IIR_Boolean 
IIRBase_Aggregate::is_signal( ){
  IIR_Boolean retval = TRUE;
  IIR_AssociationElement *current_assoc;
  IIR_AssociationList *list = get_element_association_list();

  ASSERT( is_resolved() == TRUE );
  current_assoc = dynamic_cast<IIR_AssociationElement *>(list->first());
  while( current_assoc != NULL ){
    if( current_assoc->is_signal() == FALSE ){
      retval = FALSE;
    }
    current_assoc = dynamic_cast<IIR_AssociationElement *>(list->successor( current_assoc ));
  }

  return retval;
}

IIR_Boolean 
IIRBase_Aggregate::is_variable( ){
  IIR_Boolean retval = TRUE;
  IIR_AssociationElement *current_assoc;
  IIR_AssociationList *list = get_element_association_list();

  ASSERT( is_resolved() == TRUE );
  current_assoc = dynamic_cast<IIR_AssociationElement *>(list->first());
  while( current_assoc != NULL ){
    if( current_assoc->is_variable() == FALSE ){
      retval = FALSE;
    }
    current_assoc = dynamic_cast<IIR_AssociationElement *>(list->successor( current_assoc ));
  }

  return retval;
}

IIR_Boolean
IIRBase_Aggregate::is_locally_static(){
  return get_element_association_list()->is_locally_static();
}

ostream &
IIRBase_Aggregate::print( ostream &os ){
  os << "(";
  os << dynamic_cast<IIRBase_AssociationList *>(get_element_association_list());
  os << ")";

  return os;
}

void 
IIRBase_Aggregate::publish_vhdl(ostream &vhdl_out) {
  ASSERT( is_resolved() == TRUE );
  vhdl_out << " ( ";
  dynamic_cast<IIRBase_AssociationList *>(get_element_association_list())->publish_vhdl(vhdl_out);
  vhdl_out << " ) ";
}
