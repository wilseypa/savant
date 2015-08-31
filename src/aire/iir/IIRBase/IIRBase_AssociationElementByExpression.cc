
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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//---------------------------------------------------------------------------


#include "IIRBase_AssociationElementByExpression.hh"

IIRBase_AssociationElementByExpression::IIRBase_AssociationElementByExpression() {
  set_actual(NULL);
}


IIRBase_AssociationElementByExpression::~IIRBase_AssociationElementByExpression() {}


void
IIRBase_AssociationElementByExpression::set_actual(IIR *a) {
  actual = a;
}


// This method publishes the element as an argument to a subprogram
// (function/procudure).  This is different from _publish_cc because this
// publishes just the declarators.
// For example, 
//   "var" will be published by _publish_cc_lvalue( _cc_out ) as 
//     "state.current->var" and as
//     "var" by _publish_cc_subprogram_arguments( _cc_out ).
// Assumption: get_actual() returns one of IIR_Declaration (any), IIR_Literal
// or IIR_IndexedName 
IIR*
IIRBase_AssociationElementByExpression::get_actual() {
  return actual;
}

IIR *
IIRBase_AssociationElementByExpression::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_AssociationElementByExpression *new_node = dynamic_cast<IIRBase_AssociationElementByExpression *>(IIRBase_AssociationElement::convert_tree(factory));

  // Process the variables
  new_node->actual = convert_node(actual, factory);

  return new_node;
}

IIR_Boolean 
IIRBase_AssociationElementByExpression::is_resolved(){
  IIR_Boolean retval = TRUE;

  if( get_formal() != NULL && get_formal()->is_resolved() == FALSE ){
    retval = FALSE;
    goto finish;
  }
  
  if( get_actual() != NULL && get_actual()->is_resolved() == FALSE ){
    retval = FALSE;
  }

 finish:
  return retval;
}

IIR_Boolean 
IIRBase_AssociationElementByExpression::is_signal(){
  IIR_Boolean retval = TRUE;

  if( get_actual()->is_signal() == FALSE ){
    retval = FALSE;
  }

  return retval;
}

IIR_Boolean 
IIRBase_AssociationElementByExpression::is_variable(){
  IIR_Boolean retval = TRUE;

  if( get_actual()->is_variable() == FALSE ){
    retval = FALSE;
  }

  return retval;
}

IIR_Boolean
IIRBase_AssociationElementByExpression::is_above_attribute_found(){
  IIR_Boolean retval = FALSE;
  if(get_actual() != NULL) {
    retval = retval || get_actual()->is_above_attribute_found();
  }
  return retval;
}

IIR_Boolean
IIRBase_AssociationElementByExpression::is_locally_static(){
  bool retval = true;
  if( get_actual() ){
    retval = get_actual()->is_locally_static();
  }
  return retval;
}

ostream &
IIRBase_AssociationElementByExpression::print( ostream &os ){
  if( get_formal() != NULL ){
    os << *(get_formal());
    os << " => ";
  }

  if( get_actual() != NULL ){
    os << *(get_actual());
  }

  return os;
}

void 
IIRBase_AssociationElementByExpression::publish_vhdl(ostream &vhdl_out) {
  if (get_formal() != NULL) {
    if( get_formal()->get_kind() == IIR_INTEGER_SUBTYPE_DEFINITION ){
      dynamic_cast<IIRBase *>(get_formal())->publish_vhdl_range(vhdl_out);
    }
    else {
      get_formal()->publish_vhdl(vhdl_out);
    }
    vhdl_out << " => ";
  }

  if( get_actual() != NULL ){
    get_actual()->publish_vhdl(vhdl_out);
  }
  else{
    vhdl_out << "open";
  }
}

void 
IIRBase_AssociationElementByExpression::publish_vhdl_without_formals(ostream &vhdl_out) {
  
  if ( get_formal() != NULL ){
    if ( get_formal()->get_kind() == IIR_FUNCTION_CALL ){
      get_formal()->publish_vhdl(vhdl_out);
      vhdl_out << " => ";
    }
  }

  if( get_actual() != NULL ){
    get_actual()->publish_vhdl(vhdl_out);
  }
  else{
    vhdl_out << "open";
  }
}
