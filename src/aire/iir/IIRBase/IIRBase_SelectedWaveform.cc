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
//          Malolan Chetlur     mal@ece.uc.edu
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------





#include "savant.hh"
#include "IIRBase_SelectedWaveform.hh"
#include "IIR_WaveformList.hh"

IIRBase_SelectedWaveform::IIRBase_SelectedWaveform() :
  waveform(0) {
  my_choice = NULL;
}

IIRBase_SelectedWaveform::~IIRBase_SelectedWaveform(){
}

IIR *
IIRBase_SelectedWaveform::get_choice(){
  return my_choice;
}

void 
IIRBase_SelectedWaveform::set_choice( IIR *choice ){
  my_choice = choice;
}

// List Accessor(s)
IIR_WaveformList *
IIRBase_SelectedWaveform::get_waveform() {
  ASSERT(waveform != NULL);
  return waveform;
}


void
IIRBase_SelectedWaveform::set_waveform(IIR_WaveformList *new_waveform) {
  ASSERT(new_waveform != NULL);
  delete waveform;
  waveform = new_waveform;
}

IIR *
IIRBase_SelectedWaveform::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_SelectedWaveform *new_node = dynamic_cast<IIRBase_SelectedWaveform *>(IIRBase_Tuple::convert_tree(factory));

  // Process the variables
  new_node->waveform = dynamic_cast<IIR_WaveformList *>(convert_node(waveform, factory));
  new_node->my_choice = convert_node(my_choice, factory);

  return new_node;
}

IIR_Boolean
IIRBase_SelectedWaveform::is_resolved(){
  IIR_Boolean retval = TRUE;
  if( get_choice()->is_resolved() == FALSE ){
    retval = FALSE;
  }
  
  if( get_waveform()->is_resolved() == FALSE ){
    retval = FALSE;
  }

  return retval;
}

void 
IIRBase_SelectedWaveform::publish_vhdl(ostream &vhdl_out) {
  get_waveform()->publish_vhdl(vhdl_out);
  vhdl_out << " ";
  get_choice()->publish_vhdl(vhdl_out);
}
