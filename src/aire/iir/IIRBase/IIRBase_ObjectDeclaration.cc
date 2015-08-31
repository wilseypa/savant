
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
//          Malolan Chetlur     mal@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant.hh"
#include "error_func.hh"
#include "IIRBase_ObjectDeclaration.hh"
#include "IIRBase_AccessTypeDefinition.hh"
#include "IIR_AttributeSpecificationList.hh"
#include "IIR_Name.hh"

#include <iostream>
using std::cerr;
#include <sstream>
using std::ostringstream;

IIRBase_ObjectDeclaration::IIRBase_ObjectDeclaration()  :
  attributes(0)
{}

IIRBase_ObjectDeclaration::~IIRBase_ObjectDeclaration() {
}

// List Accessor(s)
IIR_AttributeSpecificationList *
IIRBase_ObjectDeclaration::get_attributes() {
  ASSERT(attributes != NULL);
  return attributes;
}

void
IIRBase_ObjectDeclaration::set_attributes(IIR_AttributeSpecificationList *new_attributes) {
  ASSERT(new_attributes != NULL);
  delete attributes;
  attributes = new_attributes;
}

void
IIRBase_ObjectDeclaration::set_subtype( IIR_TypeDefinition *subtype ){
  if( subtype && subtype->get_declaration() == 0 ){
    subtype->set_declaration( this );
  }
  IIRBase::set_subtype(subtype);
}

IIR *
IIRBase_ObjectDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ObjectDeclaration *new_node = dynamic_cast<IIRBase_ObjectDeclaration *>(IIRBase_Declaration::convert_tree(factory));

  // Process the variables
  new_node->attributes = dynamic_cast<IIR_AttributeSpecificationList *>(convert_node(attributes, factory));

  return new_node;
}

IIR_SignalKind
IIRBase_ObjectDeclaration::get_signal_kind(){
  _report_undefined_fn("get_signal_kind()");

  return IIR_NO_SIGNAL_KIND;
}

void
IIRBase_ObjectDeclaration::set_value(IIR *){
  _report_undefined_fn("set_value(IIR *)");
}

savant::set<IIR_Declaration> *
IIRBase_ObjectDeclaration::find_declarations( IIR_Name *to_find){
  savant::set<IIR_Declaration> *retval = NULL;

  ASSERT( get_subtype() != NULL );

  if( get_subtype()->is_record_type() == TRUE ){
    IIR_TypeDefinition *my_subtype = get_subtype();
    retval = my_subtype->find_declarations( to_find );
  }
  else if( get_subtype()->is_access_type() == TRUE ){
    IIR_AccessTypeDefinition *my_subtype = dynamic_cast<IIR_AccessTypeDefinition *>(get_subtype());
    if( my_subtype == NULL ){
      ostringstream err;
      err << "Cannot refer to element, as subtype has not yet been defined.";
//       err << "|" << *this << "| cannot refer to element |" << *dynamic_cast<IIR *>(to_find) << "|, as " 
// 	  << "subtype |" << *get_subtype() << "| has not yet been defined.";
      report_error( dynamic_cast<IIR *>(to_find), err.str());
      return NULL;
    }
    else{
      retval = my_subtype->find_declarations( to_find );
    }
  }

  return retval;
}

void
IIRBase_ObjectDeclaration::publish_vhdl_range( ostream &vhdl_out ){
  publish_vhdl( vhdl_out );
}

void
IIRBase_ObjectDeclaration::publish_vhdl_subtype_indication(ostream &vhdl_out){

  ASSERT( get_subtype() != NULL );	
  if (get_subtype()->is_anonymous() == TRUE) {
    dynamic_cast<IIRBase_TypeDefinition *>(get_subtype())->publish_vhdl_decl(vhdl_out);
  }
  else {
    get_subtype()->publish_vhdl(vhdl_out);
  }
}

void
IIRBase_ObjectDeclaration::publish_vhdl_expression(ostream &vhdl_out){
  IIRBase *val = dynamic_cast<IIRBase *>(get_value());
  if (val != NULL) {
    vhdl_out << " := ";
    val->publish_vhdl(vhdl_out);
  }
}

void
IIRBase_ObjectDeclaration::publish_vhdl_subtype_indication_with_expression(ostream &vhdl_out){
  publish_vhdl_subtype_indication(vhdl_out);
  publish_vhdl_expression(vhdl_out);
  vhdl_out << ";\n";
}

void
IIRBase_ObjectDeclaration::publish_vhdl_signal_kind(ostream &vhdl_out){
  switch(get_signal_kind()) {
  case IIR_REGISTER_KIND:
    vhdl_out << " register ";
    break;
  case IIR_BUS_KIND:
    vhdl_out << " bus ";
    break;
  case IIR_NO_SIGNAL_KIND:
    break;
  default:
    cerr << " ERROR!!! undefined Signal Kind in node " << get_kind_text();
    abort();
   }
}
