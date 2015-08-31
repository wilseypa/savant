
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
//          Malolan Chetlur     
//          Timothy J. McBrayer 
//          Krishnan Subramani  
//          Umesh Kumar V. Rajasekaran
//          Radharamanan Radhakrishnan
//          Narayanan Thondugulam
//	    Magnus Danielson	cfmd@swipnet.se
//---------------------------------------------------------------------------

#include "IIRScram_Attribute.hh"
#include "IIRScram_ConcurrentStatement.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_SignalDeclaration.hh"
#include "IIRScram_TextLiteral.hh"

#include "set.hh"
#include "symbol_table.hh"
#include "error_func.hh"
#include "savant.hh"

IIRScram_SignalDeclaration::IIRScram_SignalDeclaration() :
  _my_clone(0){}

IIRScram_SignalDeclaration::~IIRScram_SignalDeclaration(){}

IIRScram*
IIRScram_SignalDeclaration::_clone() {
  if (_my_clone == NULL) {
    _my_clone = new IIRScram_SignalDeclaration();
    IIRScram_ObjectDeclaration::_clone(_my_clone);

    _my_clone->IIRBase_SignalDeclaration::set_value(_get_value());
    _my_clone->set_signal_kind(get_signal_kind());
  }
  return _my_clone;
}

visitor_return_type *
IIRScram_SignalDeclaration::_accept_visitor( node_visitor *visitor,
					     visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_SignalDeclaration(this, arg);
}


IIRScram*
IIRScram_SignalDeclaration::_get_value() {
  return dynamic_cast<IIRScram *>(IIRBase_SignalDeclaration::get_value());
}

