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

//---------------------------------------------------------------------------

#include "IIRScram_SelectedWaveform.hh"
#include "IIRScram_List.hh"
#include "IIRScram_ChoiceList.hh"
#include "IIRScram_Choice.hh"
#include "IIRScram_WaveformList.hh"
#include "IIRScram_WaveformElement.hh"
#include "savant.hh"

IIRScram_SelectedWaveform::IIRScram_SelectedWaveform() {
  set_waveform(new IIRScram_WaveformList());
}

IIRScram_SelectedWaveform::~IIRScram_SelectedWaveform() {
  //Release the list memory
  delete get_waveform();
}

visitor_return_type *
IIRScram_SelectedWaveform::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_SelectedWaveform(this, arg);
}

// IIRBase Function Wrapper(s)
IIRScram *
IIRScram_SelectedWaveform::_get_choice() {
  return dynamic_cast<IIRScram *>(get_choice());
}

IIRScram_WaveformList *
IIRScram_SelectedWaveform::_get_waveform() {
  return dynamic_cast<IIRScram_WaveformList *>(get_waveform());
}
