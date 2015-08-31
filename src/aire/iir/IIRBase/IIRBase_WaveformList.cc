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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIR_WaveformElement.hh"
#include "IIRBase_WaveformList.hh"

IIRBase_WaveformList::IIRBase_WaveformList() {}
IIRBase_WaveformList::~IIRBase_WaveformList() {}


IIR_WaveformElement*
IIRBase_WaveformList::first() {
  return dynamic_cast<IIR_WaveformElement*>(IIR_List::first());
}


IIR_WaveformElement*
IIRBase_WaveformList::successor(IIR_WaveformElement* node) {
  return dynamic_cast<IIR_WaveformElement*>(IIR_List::successor((IIR*)node));
}

IIR_Boolean
IIRBase_WaveformList::is_above_attribute_found() {
  IIR_Boolean retval = FALSE;
  IIR_WaveformElement* element = first();
  for(; element != NULL; element = successor(element)) {
    retval = retval || element->is_above_attribute_found();
  }
  return retval;
}

void 
IIRBase_WaveformList::publish_vhdl(ostream &vhdl_out) {
  IIR_WaveformElement *element = first();
  while (element != NULL) {
    element->publish_vhdl(vhdl_out);
    element = successor(element);
    if (element) {vhdl_out << ", ";}
  }
}
