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
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_ConditionalWaveform.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_WaveformElement.hh"
#include "resolution_func.hh"
#include "set.hh"
#include <iostream>
#include "IIRScram_WaveformList.hh"
#include "StandardPackage.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"

IIRScram_ConditionalWaveform::IIRScram_ConditionalWaveform() {
  set_waveform(new IIRScram_WaveformList());
}

IIRScram_ConditionalWaveform::~IIRScram_ConditionalWaveform(){
  //Release the list memory
  delete get_waveform();
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_ConditionalWaveform::_get_rval_set(constraint_functor *functor){
  return dynamic_cast<IIRScram_WaveformElement *>(get_waveform()->first())->_get_rval_set(functor);
}


IIRScram *
IIRScram_ConditionalWaveform::_semantic_transform( savant::set<IIRScram_TypeDefinition> *my_rvals ){
  IIRScram_WaveformElement *current_waveform = NULL;
  current_waveform = dynamic_cast<IIRScram_WaveformElement *>(get_waveform()->first());
  while( current_waveform != NULL ){
    IIRScram *temp_waveform = current_waveform->_semantic_transform( my_rvals );
    get_waveform()->_replace( current_waveform, temp_waveform );		       
    current_waveform = dynamic_cast<IIRScram_WaveformElement *>(get_waveform()->successor( dynamic_cast<IIRScram_WaveformElement *>(temp_waveform)));
  }

  return this;
}


IIRScram *
IIRScram_ConditionalWaveform::_rval_to_decl( IIRScram_TypeDefinition *my_type ){
  IIRScram_WaveformElement *current_waveform = NULL;
  current_waveform = dynamic_cast<IIRScram_WaveformElement *>(get_waveform()->first());
  while( current_waveform != NULL ){
    IIRScram *temp_waveform = current_waveform->_rval_to_decl( my_type );
    get_waveform()->_replace( current_waveform, temp_waveform );		       
    current_waveform = dynamic_cast<IIRScram_WaveformElement *>(get_waveform()->successor( dynamic_cast<IIRScram_WaveformElement *>(temp_waveform) ));
  }
  return this;
}

void 
IIRScram_ConditionalWaveform::_type_check( savant::set<IIRScram_TypeDefinition> *my_type ){
  StandardPackage *package = _get_design_file()->get_standard_package();
  IIRScram_TypeDefinition *bool_rval = dynamic_cast<IIRScram_TypeDefinition *>(package->get_boolean_type());

  savant::set<IIRScram_TypeDefinition> temp_set( bool_rval );

  if( get_condition() != NULL ){
    set_condition( _get_condition()->_semantic_transform( &temp_set ));
    _get_condition()->_type_check( &temp_set );
    set_condition( _get_condition()->_rval_to_decl( bool_rval ) );
  }

  IIRScram_WaveformElement *current_waveform = NULL;
  current_waveform = dynamic_cast<IIRScram_WaveformElement *>(get_waveform()->first());
  while( current_waveform != NULL ){
    current_waveform->_type_check( my_type );
    current_waveform = dynamic_cast<IIRScram_WaveformElement *>(get_waveform()->successor( current_waveform ));
  }
}

visitor_return_type *
IIRScram_ConditionalWaveform::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ConditionalWaveform(this, arg);
}

IIRScram *
IIRScram_ConditionalWaveform::_get_condition() {
  return dynamic_cast<IIRScram *>(get_condition());
}

IIRScram_WaveformList *
IIRScram_ConditionalWaveform::_get_waveform(){
  return dynamic_cast<IIRScram_WaveformList *>(get_waveform());
}
