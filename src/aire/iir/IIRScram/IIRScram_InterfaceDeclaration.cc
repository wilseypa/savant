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
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_AttributeSpecificationList.hh"
#include "IIRScram_InterfaceDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_ArrayTypeDefinition.hh"
#include "IIRScram_AccessTypeDefinition.hh"
#include "IIRScram_ProcessStatement.hh"
#include "IIRScram_ArchitectureDeclaration.hh"
#include "IIRScram_DesignFile.hh"
#include "error_func.hh"
#include "savant.hh"

#include <sstream>
using std::ostringstream;

IIRScram_InterfaceDeclaration::~IIRScram_InterfaceDeclaration() {}

IIR_Mode
IIRScram_InterfaceDeclaration::_get_mode(){
  return get_mode();
}

void 
IIRScram_InterfaceDeclaration::_type_check(){
  IIRScram_ObjectDeclaration::_type_check();

  if( get_mode() == IIR_LINKAGE_MODE && 
      _get_value() != NULL ){
    ostringstream err;
    err << "Interface |" << *_get_declarator() << "| has been declared with linkage "
	<< "mode and therefore cannot have a default expression.";
    report_error( this, err.str() );
  }
}

IIR_Boolean 
IIRScram_InterfaceDeclaration::_is_readable(){
  if( get_mode() == IIR_IN_MODE || get_mode() == IIR_INOUT_MODE || get_mode() == IIR_BUFFER_MODE ){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

IIR_Boolean 
IIRScram_InterfaceDeclaration::_is_writable(){
  if( get_mode() == IIR_OUT_MODE || get_mode() == IIR_INOUT_MODE || get_mode() == IIR_BUFFER_MODE ){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

IIR_Int32 
IIRScram_InterfaceDeclaration::get_num_indexes(){
  return _get_subtype()->get_num_indexes();
}

IIRScram_TypeDefinition *
IIRScram_InterfaceDeclaration::_get_type_of_element( int index ){
  if( index > get_num_indexes() ){
    return NULL;
  }

  IIRScram_TypeDefinition *current_subtype = _get_subtype();
  if( index == 0 ){
    return current_subtype;
  }

  int i;
  for( i = 0; i < index - 1; i++ ){
    ASSERT( current_subtype->is_array_type() == TRUE );

    current_subtype = current_subtype->_get_element_subtype();
      
  }
  
  IIRScram_TypeDefinition *retval = current_subtype->_get_element_subtype();
  
  return retval;
}

void
IIRScram_InterfaceDeclaration::_clone( IIRScram *copy_into ) {
  ASSERT( copy_into->_is_iir_interface_declaration() == TRUE );
  IIRScram_Declaration::_clone( copy_into );

  IIRScram_InterfaceDeclaration *as_interface = dynamic_cast<IIRScram_InterfaceDeclaration *>(copy_into);

  as_interface->set_mode( get_mode() );
  as_interface->set_subtype( _get_subtype() );
  as_interface->IIRBase_InterfaceDeclaration::set_value( _get_value() );
  as_interface->set_attributes(get_attributes());
}


IIR_Boolean 
IIRScram_InterfaceDeclaration::_is_optional(){
  if( _get_value() == NULL ){
    return FALSE;
  }
  else{
    return TRUE;
  }
}

IIRScram *
IIRScram_InterfaceDeclaration::_get_value() {
  return dynamic_cast<IIRScram *>(IIRBase_InterfaceDeclaration::get_value());
}
