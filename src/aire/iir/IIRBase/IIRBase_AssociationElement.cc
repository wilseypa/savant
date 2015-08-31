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
//          Timothy J. McBrayer tmcrbaye@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant.hh"
#include "IIRBase_AssociationElement.hh"

IIRBase_AssociationElement::IIRBase_AssociationElement() {
  set_formal(NULL);
}


IIRBase_AssociationElement::~IIRBase_AssociationElement() {
}


void
IIRBase_AssociationElement::set_formal(IIR *f) {
  formal = f;
}


IIR*
IIRBase_AssociationElement::get_formal() {
  return formal;
}

IIR *
IIRBase_AssociationElement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_AssociationElement *new_node = dynamic_cast<IIRBase_AssociationElement *>(IIRBase_Tuple::convert_tree(factory));

  // Process the variables
  new_node->formal = convert_node(formal, factory);

  return new_node;
}

IIR_Boolean 
IIRBase_AssociationElement::is_named(){
  // If the formal isn't NULL we're named, unless we're by others.
  return get_formal() != NULL && is_by_others() == FALSE ;
}

IIR_Boolean
IIRBase_AssociationElement::is_by_others(){
  if( get_actual() != NULL && get_actual()->get_kind() == IIR_OTHERS_INITIALIZATION ){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

void
IIRBase_AssociationElement::publish_vhdl_without_formals(ostream &){
  _report_undefined_fn("publish_vhdl_without_formals(ostream &)");
}
