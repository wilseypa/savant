
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
//          Timothy J. McBrayer 

//---------------------------------------------------------------------------
#include "IIRBase_PortList.hh"
#include "IIR_SignalInterfaceDeclaration.hh"
#include "IIRBase_InterfaceDeclaration.hh"

IIRBase_PortList::IIRBase_PortList() {}
IIRBase_PortList::~IIRBase_PortList() {}

void
IIRBase_PortList::prepend( IIR_InterfaceDeclaration *element ) {
  IIR_List::prepend( element );
}

void
IIRBase_PortList::append( IIR_InterfaceDeclaration *element ) {
  ASSERT( element->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION || 
          element->get_kind() == IIR_TERMINAL_INTERFACE_DECLARATION );
  IIR_List::append( element );
}

void  
IIRBase_PortList::insert_after( IIR_InterfaceDeclaration *existing_element,
				IIR_InterfaceDeclaration *new_element) {
  IIR_List::insert_after( existing_element, new_element );
}


IIR_Boolean
IIRBase_PortList::insert_before_element( IIR_InterfaceDeclaration *,
					 IIR_InterfaceDeclaration * ){
  return false;
}

IIR*
IIRBase_PortList::successor( IIR_InterfaceDeclaration *existing_element ){
  IIR *retval = IIR_List::successor( existing_element );
  ASSERT( retval == NULL || 
          retval->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION || 
          retval->get_kind() == IIR_TERMINAL_INTERFACE_DECLARATION );
  return retval;
}


IIR*
IIRBase_PortList::predecessor( IIR_InterfaceDeclaration *element ){
  IIR *retval = IIR_List::predecessor( element );

  ASSERT( retval == NULL || 
          retval->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION || 
          retval->get_kind() == IIR_TERMINAL_INTERFACE_DECLARATION );

  return retval;
}


IIR *
IIRBase_PortList::first( ) {
  IIR *retval = IIR_List::first( );
  ASSERT( retval == NULL || 
          retval->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION ||
          retval->get_kind() == IIR_TERMINAL_INTERFACE_DECLARATION );
  return retval;
}

IIR*
IIRBase_PortList::last() {
  IIR *retval = IIR_List::last( );
  ASSERT( retval == NULL || 
          retval->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION ||
          retval->get_kind() == IIR_TERMINAL_INTERFACE_DECLARATION );
  return retval;
}


IIR_Int32
IIRBase_PortList::get_position( IIR_InterfaceDeclaration *element ) {
  ASSERT( element->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION || 
          element->get_kind() == IIR_TERMINAL_INTERFACE_DECLARATION );
  return IIR_List::get_position( element );
}

void 
IIRBase_PortList::publish_vhdl(ostream &vhdl_out) {
  IIRBase_InterfaceDeclaration *i = NULL;
  for (i = dynamic_cast<IIRBase_InterfaceDeclaration *>(first()); i != NULL; ) {
    vhdl_out << "  ";
    i->publish_vhdl_decl(vhdl_out);
    i = dynamic_cast<IIRBase_InterfaceDeclaration *>(successor(i));
    if(i != NULL) {
      vhdl_out << ";\n";
    }
  }
}
