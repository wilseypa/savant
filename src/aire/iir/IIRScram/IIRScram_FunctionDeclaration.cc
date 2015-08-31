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
//          Malolan Chetlur     mal@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Radharamanan Radhakrishnan ramanan@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_FunctionDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_StringLiteral.hh"
#include "IIRScram_Attribute.hh"
#include "IIRScram_ArrayTypeDefinition.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_InterfaceDeclaration.hh"
#include "IIRScram_InterfaceList.hh"
#include "IIRScram_SequentialStatementList.hh"
#include "IIRScram_SignalDeclaration.hh"
#include "set.hh"
#include "symbol_table.hh"
#include "error_func.hh"

#include <sstream>
using std::ostringstream;

IIRScram_FunctionDeclaration::~IIRScram_FunctionDeclaration() {}

// If this function could be used as a resolution function, publish it
// with the required signature.
// A function could be a resolution funcion if ALL the following
// conditions are satisfied (Section 2.4 of LRM)
// 1. It takes single argument of type "constant",
// 2. The argument is an unconstrained array type, and
// 3. The type of an element of the array is the same as the return type
//    of the function

// If this function could be used as a type conversionfunction, publish it
// with the required signature.
// A function could be a type conversion funcion if ALL the following
// conditions are satisfied (Section 4.3.2.2 of LRM)
// 1. It takes single argument.
  

// This function publishes the constructor of signals in the constructor
// of the state.

IIR_Int32
IIRScram_FunctionDeclaration::get_num_indexes(){
  return _get_return_type()->get_num_indexes();
}


IIRScram_TypeDefinition *
IIRScram_FunctionDeclaration::_get_type_of_element( int index ){
  // Stolen almost verbatim from IIRScram_ObjectDeclaration
  IIRScram_TypeDefinition *current_subtype = NULL;

  if( _num_required_args() == 0 ){
    if( index > get_num_indexes() ){
      return NULL;
    }
    
    current_subtype = _get_return_type();
    if( index == 0 ){
      return current_subtype;
    }
  
    int i;
    for( i = 0; i < index - 1; i++ ){
      ASSERT( current_subtype->is_array_type() == TRUE );
      current_subtype = current_subtype->_get_element_subtype();
    }
  }
  else{
    return _get_return_type();
  }

  return current_subtype;
}

IIR_Boolean 
IIRScram_FunctionDeclaration::_could_be_conversion_function( ){
  IIR_Boolean retval = FALSE;
  if( get_interface_declarations()->size() == 1 ){
    // We know the argument is the right type, and the return type is
    // right, or we wouldn't have resolved it to this.
    retval = TRUE;
  }
  
  return retval;
}

void 
IIRScram_FunctionDeclaration::_type_check_resolution_function(IIRScram_TypeDefinition *subtype_indication){
  ostringstream err;
  err << "Function |" << *dynamic_cast<IIRScram_TextLiteral *>(get_declarator())
      << "| is not a valid resolution function as ";
    
  if( get_pure() != IIR_PURE_FUNCTION ){
    err << "it isn't pure.";
    report_error( subtype_indication, err.str() );
  }
  else if( get_interface_declarations()->size() != 1 ){
    err << "it has " << get_interface_declarations()->size() 
	<< " parameters instead of the required 1.";
    report_error( subtype_indication, err.str() );
  }
  else{
    // Make sure that the interface elements is constant class
    IIRScram_InterfaceDeclaration *parameter_decl = dynamic_cast<IIRScram_InterfaceDeclaration *>(get_interface_declarations()->first());
    if( parameter_decl->get_mode() != IIR_IN_MODE ){
      err << "its parameter isn't mode IN.";
      report_error( subtype_indication, err.str() );
    }
    IIRScram_TypeDefinition *parameter_type = parameter_decl->_get_subtype();
    if( parameter_type->_is_iir_array_type_definition() == false ||
	parameter_type->is_unconstrained_array_type() == false ||
	parameter_type->get_num_indexes() != 1 ){
      err << "its parameter isn't a one dimensional unconstrained array type.";
      report_error( subtype_indication, err.str() );
    }
  }
}
  
IIRScram *
IIRScram_FunctionDeclaration::_clone() {
  return this;
}

visitor_return_type *
IIRScram_FunctionDeclaration::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_FunctionDeclaration(this, arg);
};

IIRScram_DeclarationList *
IIRScram_FunctionDeclaration::_get_subprogram_declarations() {
  return dynamic_cast<IIRScram_DeclarationList *>(get_subprogram_declarations());
}

IIRScram_TypeDefinition* 
IIRScram_FunctionDeclaration::_get_return_type() {
  return dynamic_cast<IIRScram_TypeDefinition *>(get_return_type());
}
