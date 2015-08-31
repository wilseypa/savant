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
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------
#include "IIRScram_AttributeSpecificationList.hh"
#include "IIRScram_SignalInterfaceDeclaration.hh"
#include "IIRScram_DesignatorExplicit.hh"
#include "IIRScram_ConcurrentStatement.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_TextLiteral.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_Attribute.hh"

#include "set.hh"
#include "symbol_table.hh"
#include "error_func.hh"
#include "savant.hh"

#include <sstream>
using std::ostringstream;

IIRScram_SignalInterfaceDeclaration::IIRScram_SignalInterfaceDeclaration() :
  _my_clone(0){}


IIRScram_SignalInterfaceDeclaration::~IIRScram_SignalInterfaceDeclaration(){}

IIRScram*
IIRScram_SignalInterfaceDeclaration::_clone() {
  if (_my_clone == NULL) {
    _my_clone = new IIRScram_SignalInterfaceDeclaration();
    IIRScram_Declaration::_clone(_my_clone);
    _my_clone->set_subtype(_get_subtype());
    _my_clone->IIRBase_InterfaceDeclaration::set_value(_get_value());
    _my_clone->set_signal_kind(get_signal_kind());
    _my_clone->set_attributes(get_attributes());
  }
  return _my_clone;
}

void 
IIRScram_SignalInterfaceDeclaration::_type_check( IIRScram_InterfaceDeclaration::_InterfaceListType list_type ){
  IIRScram_InterfaceDeclaration::_type_check();

  if( _get_subtype()->is_access_type() == TRUE || _get_subtype()->is_file_type() == TRUE ){
    ostringstream err;
    err << "Signal interface declaration |" << *_get_declarator() << "| must have a subtype "
	<< "indication that defines a subtype that is neither an access type or a file type.";
    report_error( this, err.str() );
  }

  if(list_type == IIRScram_InterfaceDeclaration::PARAMETER_INTERFACE_LIST && _get_value() != NULL){
    ostringstream err;
    err << "Formal signal parameter |" << *_get_declarator() << "| may not have a default "
	<< "value specified.";
    report_error( this, err.str() );
  }
}

visitor_return_type *
IIRScram_SignalInterfaceDeclaration::_accept_visitor( node_visitor *visitor,
						      visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_SignalInterfaceDeclaration(this, arg);
}


