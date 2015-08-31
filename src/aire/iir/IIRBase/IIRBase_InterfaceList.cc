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

#include "IIRBase_InterfaceList.hh"
#include "IIRBase_InterfaceDeclaration.hh"

IIRBase_InterfaceList::IIRBase_InterfaceList() {}
IIRBase_InterfaceList::~IIRBase_InterfaceList() {}


IIR* 
IIRBase_InterfaceList::first() {
  IIR *element = IIRBase_DeclarationList::first();

  return element;
}


IIR*
IIRBase_InterfaceList::successor(IIR_InterfaceDeclaration* node) {
  IIR *element = IIRBase_DeclarationList::successor( node );
  return element;
}


IIR *
IIRBase_InterfaceList::get_nth_element( IIR_Int32 position ){
  IIR *element = IIRBase_DeclarationList::get_nth_element( position );

  ASSERT( element != NULL );

  return element;  
}


void
IIRBase_InterfaceList::prepend( IIR_InterfaceDeclaration *element ) {
  IIR *test = element;
  ASSERT( test != NULL ); 

  IIRBase_DeclarationList::prepend( element );
}


void
IIRBase_InterfaceList::append( IIR_InterfaceDeclaration *element ) {
  IIR *test = element;
  ASSERT( test != NULL );
  
  IIRBase_DeclarationList::append( element );
}


void 
IIRBase_InterfaceList::insert_after( IIR_InterfaceDeclaration* existing_element,
				     IIR_InterfaceDeclaration* new_element) {
  IIR *new_element_test = new_element;
  ASSERT( new_element_test != NULL );
  IIR *existing_element_test = existing_element_test;
  ASSERT( existing_element_test != NULL );
  
  IIRBase_DeclarationList::insert_after( existing_element, new_element );
}

IIR*
IIRBase_InterfaceList::predecessor( IIR_InterfaceDeclaration *element ){
  IIR *test = element;
  ASSERT( test != NULL );
  
  IIR *retval = dynamic_cast<IIR_Declaration *>(IIRBase_DeclarationList::predecessor( element ));

  test = retval;
  ASSERT( test != NULL );
  
  return retval;
}

IIR*
IIRBase_InterfaceList::last() {
  IIR *retval = last( );
  ASSERT( retval != NULL );

  return retval;
}


IIR_Int32
IIRBase_InterfaceList::get_position( IIR_InterfaceDeclaration *element ) {
  IIR *test = element;
  ASSERT( test != NULL );

  return IIRBase_DeclarationList::get_position( element );
}

void 
IIRBase_InterfaceList::publish_vhdl(ostream &vhdl_out) {
  IIRBase_InterfaceDeclaration* interface_element = NULL;

  interface_element = dynamic_cast<IIRBase_InterfaceDeclaration *>(first());
  while (interface_element != NULL) {
    interface_element->publish_vhdl(vhdl_out);
    interface_element = dynamic_cast<IIRBase_InterfaceDeclaration *>(successor(interface_element));
    if (interface_element != NULL) {
      vhdl_out << "; ";
    }
  }
}

void 
IIRBase_InterfaceList::publish_vhdl_decl(ostream &vhdl_out) {
  IIRBase_InterfaceDeclaration* interface_element = NULL;

  interface_element = dynamic_cast<IIRBase_InterfaceDeclaration *>(first());
  while (interface_element != NULL) {
    interface_element->publish_vhdl_decl(vhdl_out);
    interface_element = dynamic_cast<IIRBase_InterfaceDeclaration *>(successor(interface_element));
    if (interface_element != NULL) {
      vhdl_out << "; ";
    }
  }
}
