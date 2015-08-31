
#ifndef IIRBASE_SELECTED_WAVEFORM_LIST_HH
#define IIRBASE_SELECTED_WAVEFORM_LIST_HH

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

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_List.hh"
#include "IIR_SelectedWaveformList.hh"

class IIR_SelectedWaveform;

class IIRBase_SelectedWaveformList : public virtual IIRBase_List, public virtual IIR_SelectedWaveformList{
public:

  IIR_Kind get_kind() const {return IIR_SELECTED_WAVEFORM_LIST;}
  const IIR_Char *get_kind_text() const {return "IIR_SelectedWaveformList";}

  IIR_SelectedWaveform *first();
  IIR_SelectedWaveform *last();
  IIR_SelectedWaveform *successor( IIR_SelectedWaveform* node );

protected:
  
  IIRBase_SelectedWaveformList();
  virtual ~IIRBase_SelectedWaveformList() = 0;
    
private:

};

#endif
