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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu
//          Swaminathan Subramanian ssubrama@ececs.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_AttributeSpecificationList.hh"
#include "IIRScram_TypeDeclaration.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_TextLiteral.hh"
#include "IIRScram_LibraryDeclaration.hh"

#include "symbol_table.hh"
#include "savant.hh"



IIRScram_TypeDeclaration::IIRScram_TypeDeclaration() : 
  _fully_defined_type(NULL){
  set_attributes(new IIRScram_AttributeSpecificationList());
}

IIRScram_TypeDeclaration::~IIRScram_TypeDeclaration() {
  //Release the list memory
  delete get_attributes();
}

IIR_Boolean
IIRScram_TypeDeclaration::_designates_incomplete_type(){
  if( _get_type_definition() != NULL && _get_type_definition()->_designates_incomplete_type() == TRUE ){
    return TRUE;
  }
  else{
    return FALSE;
  }
}


IIR_Int32 
IIRScram_TypeDeclaration::get_num_indexes(){
  if( _get_type_definition() != NULL ){
    return _get_type_definition()->get_num_indexes();
  }
  else{
    return -1;
  }
}

void 
IIRScram_TypeDeclaration::_come_into_scope( symbol_table *sym_tab ){
  // We need to see if this is actually a subtype declaration, due to the
  // organization of AIRE.
  IIRScram_TypeDefinition *type = _get_type_definition();
  if( is_subtype_declaration() == FALSE ){
    if(  type != NULL && type ->is_incomplete_type_definition() == FALSE ){
      ASSERT( type->is_subtype() == TRUE ||
	      type->is_record_type() == TRUE ||
	      type->is_file_type() == TRUE  );
      type->_come_into_scope( sym_tab, dynamic_cast<IIRScram_TypeDeclaration *>(this) );
      
      if( type->_is_iir_access_type_definition() == TRUE &&
	  type->_designates_incomplete_type() == TRUE ){
	sym_tab->get_designates_incomplete_type()->add( dynamic_cast<IIRScram_TypeDeclaration *>(this) );
      }
    }
    
    if( is_incomplete_type_declaration() == TRUE ){
      sym_tab->get_incomplete_types()->add( dynamic_cast<IIRScram_TypeDeclaration *>(this) );
    }
  }
}

void 
IIRScram_TypeDeclaration::_come_out_of_scope( symbol_table *sym_tab ){
  if( _get_type_definition() != NULL ){
    _get_type_definition()->_come_out_of_scope( sym_tab );
  }

  if( _designates_incomplete_type() == TRUE ){
    sym_tab->get_designates_incomplete_type()->remove( dynamic_cast<IIRScram_TypeDeclaration *>(this) );    
  }
}

void
IIRScram_TypeDeclaration::_type_check(){
  ASSERT( _get_type_definition() != NULL );
  _get_type_definition()->_type_check();
}

IIRScram*
IIRScram_TypeDeclaration::_clone() {
  return this;
}

visitor_return_type *
IIRScram_TypeDeclaration::_accept_visitor( node_visitor *visitor,
					   visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_TypeDeclaration(this, arg);
}

IIR_Boolean
IIRScram_TypeDeclaration::_can_be_in_same_region( IIRScram_Declaration *to_check ){
  if(( is_incomplete_type_declaration() == TRUE && 
       to_check->is_incomplete_type_declaration() == FALSE ) ||
     ( is_incomplete_type_declaration() == FALSE && 
       to_check->is_incomplete_type_declaration() == TRUE )){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

// IIRBase Function Wrapper(s)
IIRScram_AttributeSpecificationList* 
IIRScram_TypeDeclaration::_get_attribute_specification_list() { 
  return dynamic_cast<IIRScram_AttributeSpecificationList *>(get_attributes());
}

IIRScram_TypeDefinition *
IIRScram_TypeDeclaration::_get_type_definition() {
  return dynamic_cast<IIRScram_TypeDefinition *>(get_type());
}
