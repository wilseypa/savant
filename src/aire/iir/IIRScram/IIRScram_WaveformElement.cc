
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

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_WaveformElement.hh"
#include "IIRScram_WaveformElement.hh"
#include "IIRScram_List.hh"
#include "IIRScram_Declaration.hh"
#include "IIRScram_StringLiteral.hh"
#include "IIRScram_PhysicalSubtypeDefinition.hh"
#include "StandardPackage.hh"

void
IIRScram_WaveformElement::_type_check( savant::set<IIRScram_TypeDefinition> *context_set ) {
  StandardPackage               *package = _get_design_file()->get_standard_package();

  _get_value()->_type_check( context_set );
  if( _get_time() != NULL ){
    IIRScram_TypeDefinition *time_rval = 
      dynamic_cast<IIRScram_PhysicalSubtypeDefinition *>(package->get_time_type());
    set_time( _get_time()->_semantic_transform( time_rval ));
    _get_time()->_type_check( time_rval );
    set_time( _get_time()->_rval_to_decl( time_rval ));
  }
}

savant::set<IIRScram_TypeDefinition>*
IIRScram_WaveformElement::_get_rval_set(constraint_functor *functor) {
  return _get_value()->_get_rval_set(functor);
}

IIRScram *
IIRScram_WaveformElement::_semantic_transform( savant::set<IIRScram_TypeDefinition> *context_set ){
  set_value( _get_value()->_semantic_transform( context_set ) );

  return dynamic_cast<IIRScram *>(this);
}

IIRScram *
IIRScram_WaveformElement::_rval_to_decl( IIRScram_TypeDefinition *my_rval ){
  set_value( _get_value()->_rval_to_decl( my_rval ) );
  
  return this;
}

IIR_Boolean
IIRScram_WaveformElement::_is_readable(){
  if( _get_value() != NULL ){
    return _get_value()->_is_readable();
  }
  else{
    return TRUE;
  }
}

IIRScram*
IIRScram_WaveformElement::_clone() {
  IIRScram_WaveformElement *newwave;
  IIRScram *value, *time;

  newwave = new IIRScram_WaveformElement();
  IIRScram::_clone(newwave);

  value = _get_value();
  if (value != NULL) {
    value = value->_clone();
  }
  newwave->set_value(value);

  time = _get_time();
  if (time != NULL) {
    time = time->_clone();
  }
  newwave->set_time(time);

  return newwave;
}

visitor_return_type *
IIRScram_WaveformElement::_accept_visitor( node_visitor *visitor, visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_WaveformElement(this, arg);
}

IIRScram *
IIRScram_WaveformElement::_get_value() {
  return dynamic_cast<IIRScram *>(IIRBase_WaveformElement::get_value());
}

IIRScram *
IIRScram_WaveformElement::_get_time() {
  return dynamic_cast<IIRScram *>(get_time());
}
