
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
#include "IIRBase_ConditionalWaveform.hh"
#include "IIR_WaveformList.hh"

IIRBase_ConditionalWaveform::IIRBase_ConditionalWaveform() :
  waveform(0) {
  set_condition(NULL);
}

IIRBase_ConditionalWaveform::~IIRBase_ConditionalWaveform(){
}

void 
IIRBase_ConditionalWaveform::set_condition( IIR *condition ){
  this->condition = condition;
}

IIR *
IIRBase_ConditionalWaveform::get_condition(){
  return condition;
}

// List Accessor(s)
IIR_WaveformList *
IIRBase_ConditionalWaveform::get_waveform() {
  ASSERT(waveform != NULL);
  return waveform;
}


void
IIRBase_ConditionalWaveform::set_waveform(IIR_WaveformList *new_waveform) {
  ASSERT(new_waveform != NULL);
  delete waveform;
  waveform = new_waveform;
}

IIR *
IIRBase_ConditionalWaveform::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ConditionalWaveform *new_node = dynamic_cast<IIRBase_ConditionalWaveform *>(IIRBase_Tuple::convert_tree(factory));

  // Process the variables
  new_node->waveform = dynamic_cast<IIR_WaveformList *>(waveform->convert_tree(factory));
  new_node->condition = convert_node(condition, factory);

  return new_node;
}

IIR_Boolean 
IIRBase_ConditionalWaveform::is_resolved(){
  IIR_Boolean retval = TRUE;

  if( get_condition() != NULL && get_condition()->is_resolved() == FALSE ){
    retval = FALSE;
  }
  else if( get_waveform()->is_resolved() == FALSE ){
    retval = FALSE;
  }

  return retval;
}

ostream &
IIRBase_ConditionalWaveform::print( ostream &os ){
  os << *get_waveform();

  if( get_condition() != NULL ){
    os << "when ";
    os << *get_condition();
  }

  return os;
}

void 
IIRBase_ConditionalWaveform::publish_vhdl(ostream &vhdl_out) {
  get_waveform()->publish_vhdl(vhdl_out);
  if(get_condition() != NULL) {
    vhdl_out << " when ";
    get_condition()->publish_vhdl(vhdl_out);
  }
}
