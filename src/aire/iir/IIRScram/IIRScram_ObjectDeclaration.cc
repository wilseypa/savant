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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_AccessTypeDefinition.hh"
#include "IIRScram_AttributeSpecificationList.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_ObjectDeclaration.hh"

#include "set.hh"
#include "resolution_func.hh"
#include "error_func.hh"

#include <sstream>
using std::ostringstream;

IIRScram_ObjectDeclaration::IIRScram_ObjectDeclaration() {
  set_attributes(new IIRScram_AttributeSpecificationList());
}

IIRScram_ObjectDeclaration::~IIRScram_ObjectDeclaration() {
  //Release the list memory
  delete get_attributes();
}

IIR_Int32 
IIRScram_ObjectDeclaration::get_num_indexes(){
  return _get_subtype()->get_num_indexes();
}

IIRScram_TypeDefinition *
IIRScram_ObjectDeclaration::_get_type_of_element( int index ){
  IIRScram_TypeDefinition *retval;
  retval = _get_subtype()->_get_type_of_element(index);

  return retval;
}

void 
IIRScram_ObjectDeclaration::_type_check(){
  if( get_value() != NULL ){
    savant::set<IIRScram_TypeDefinition> *initializer_types = 
      dynamic_cast<IIRScram *>(get_value())->_get_rval_set();
    if( initializer_types == NULL ){
      report_undefined_symbol( get_value() );
      return;
    }

    IIR_Boolean exact_match = FALSE;
    IIRScram_TypeDefinition *current_type = initializer_types->getElement();
    while( current_type != NULL ){
      if( current_type == _get_subtype() ){
	exact_match = TRUE;
	break;
      }
      current_type = initializer_types->getNextElement();
    }
    
    IIR_Boolean one_matched = FALSE;
    if( exact_match == FALSE ){
      current_type = initializer_types->getElement();
      while( current_type != NULL ){
	if( current_type->is_compatible( _get_subtype() ) != NULL ){
	  one_matched = TRUE;
	  break;
	}
	current_type = initializer_types->getNextElement();
      }
    }

    if( exact_match == TRUE ){
      set_value( _get_value()->_semantic_transform( current_type ) );
      _get_value()->_type_check( current_type );
      set_value( _get_value()->_rval_to_decl( current_type ) );      
    }
    else if( one_matched == TRUE ){
      set_value( _get_value()->_semantic_transform( _get_subtype() ) );
      _get_value()->_type_check( _get_subtype() );
      set_value( _get_value()->_rval_to_decl( _get_subtype() ) );
    }
    else{
      ostringstream err;
      err << "Initializer |" << *_get_value() << "| is incompatible with type |"
          << *_get_subtype()->_get_declarator() << "|.";
      report_error( this, err.str() );
    }

    delete initializer_types;
  }
  // There's no initializer.
  if( (is_interface() == FALSE && (is_variable() == TRUE || is_signal() == TRUE))
      || is_element() == TRUE ){
    if( _get_subtype()->is_access_type() == FALSE && 
	_get_subtype()->is_unconstrained_array_type() == TRUE ){
      ostringstream err;
      err << "A signal or variable object with an array type must be constrained.";
      report_error( this, err.str() ); 
    }
  }
  
}

const IIR_Char*
IIRScram_ObjectDeclaration::_get_mangling_prefix(){
  return "";
}

void
IIRScram_ObjectDeclaration::_clone( IIRScram *clone ) {
  ASSERT( clone->_is_iir_object_declaration() == TRUE );
  IIRScram_ObjectDeclaration *as_object = dynamic_cast<IIRScram_ObjectDeclaration *>(clone);

  IIRScram_Declaration::_clone(clone);

  as_object->set_attributes(get_attributes());
  as_object->set_subtype(_get_subtype());
}


IIRScram_AttributeSpecificationList *
IIRScram_ObjectDeclaration::_get_attribute_specification_list() { 
  return dynamic_cast<IIRScram_AttributeSpecificationList *>(get_attributes()); 
}
