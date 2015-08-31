
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
#include "IIRBase_ConstantInterfaceDeclaration.hh"
#include "IIRBase_GenericList.hh"
#include "IIR_InterfaceList.hh"

IIRBase_GenericList::IIRBase_GenericList() {}
IIRBase_GenericList::~IIRBase_GenericList() {}

void
IIRBase_GenericList::prepend( IIR_ConstantInterfaceDeclaration* element ){
  ASSERT( element->get_kind() == IIR_CONSTANT_INTERFACE_DECLARATION );  
  IIRBase_InterfaceList::prepend( element );
}

void
IIRBase_GenericList::append( IIR_ConstantInterfaceDeclaration* element ){
  ASSERT( element->get_kind() == IIR_CONSTANT_INTERFACE_DECLARATION );  
  IIRBase_InterfaceList::append( element );
}

IIR_Boolean 
IIRBase_GenericList::insert_after( IIR_ConstantInterfaceDeclaration* existing_element,
				   IIR_ConstantInterfaceDeclaration* new_element) {

  ASSERT( existing_element->get_kind() == IIR_CONSTANT_INTERFACE_DECLARATION );
  ASSERT( new_element->get_kind() == IIR_CONSTANT_INTERFACE_DECLARATION );

  IIRBase_InterfaceList::insert_after( existing_element, new_element );

  return true;
}

IIR_Boolean
IIRBase_GenericList::insert_before_element(  IIR_ConstantInterfaceDeclaration *,
					     IIR_ConstantInterfaceDeclaration * ){

  ASSERT(0);  // This function not defined

  return true;
}

IIR*
IIRBase_GenericList::successor( IIR_ConstantInterfaceDeclaration* element ) {

  IIR_InterfaceDeclaration *retval = dynamic_cast<IIR_InterfaceDeclaration *>(IIRBase_InterfaceList::successor( element ));

  return retval;
}

IIR*
IIRBase_GenericList::predecessor( IIR_ConstantInterfaceDeclaration *element ){
  ASSERT( element->get_kind() == IIR_CONSTANT_INTERFACE_DECLARATION );

  IIR_InterfaceDeclaration *retval = dynamic_cast<IIR_InterfaceDeclaration *>(IIRBase_InterfaceList::predecessor( element ));
  
  ASSERT( retval == NULL || retval->get_kind() == IIR_CONSTANT_INTERFACE_DECLARATION );

  return retval;
}

IIR *
IIRBase_GenericList::first( ) {
  IIR_InterfaceDeclaration *retval = dynamic_cast<IIR_InterfaceDeclaration *>(IIRBase_InterfaceList::first());
  
  ASSERT( retval == NULL || retval->get_kind() == IIR_CONSTANT_INTERFACE_DECLARATION );

  return retval;
}

IIR*
IIRBase_GenericList::get_nth_element( IIR_Int32 position ){
  
  IIR_InterfaceDeclaration *retval = dynamic_cast<IIR_InterfaceDeclaration *>(IIRBase_InterfaceList::get_nth_element( position ));
  
  ASSERT( retval == NULL || retval->get_kind() == IIR_CONSTANT_INTERFACE_DECLARATION );

  return retval;  
}

IIR*
IIRBase_GenericList::last() {
  IIR_InterfaceDeclaration *retval = dynamic_cast<IIR_InterfaceDeclaration *>(IIRBase_InterfaceList::last());
  
  ASSERT( retval == NULL || retval->get_kind() == IIR_CONSTANT_INTERFACE_DECLARATION );

  return retval;
}

IIR_Int32
IIRBase_GenericList::get_position( IIR_ConstantInterfaceDeclaration* element ) {

  return IIRBase_InterfaceList::get_position(element);
}



void 
IIRBase_GenericList::publish_vhdl(ostream &vhdl_out) {
  IIRBase_ConstantInterfaceDeclaration* i = NULL;
  for(i = dynamic_cast<IIRBase_ConstantInterfaceDeclaration *>(first()); 
      i != NULL;) {
    vhdl_out << "  ";
    i->publish_vhdl_decl(vhdl_out);
    i = dynamic_cast<IIRBase_ConstantInterfaceDeclaration *>(successor(i));
    if (i != NULL) {
      vhdl_out << ";\n";
    }
  }
}
