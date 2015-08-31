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

// Authors: Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRBase_Choice.hh"
#include "IIRBase_ChoiceList.hh"

IIRBase_ChoiceList::IIRBase_ChoiceList() {}
IIRBase_ChoiceList::~IIRBase_ChoiceList() {}


IIR_Choice* 
IIRBase_ChoiceList::first() {
  return dynamic_cast<IIR_Choice*>(IIRBase_List::first());
}


IIR_Choice*
IIRBase_ChoiceList::successor(IIR_Choice* node) {
  return dynamic_cast<IIR_Choice*>(IIRBase_List::successor((IIR*)node));
}


void 
IIRBase_ChoiceList::publish_vhdl(ostream &vhdl_out) {
  register int numberOfChoices = 1;
  IIRBase_Choice *choice = dynamic_cast<IIRBase_Choice *>(first());
  choice->publish_vhdl(vhdl_out);
  choice = dynamic_cast<IIRBase_Choice *>(successor(choice));
  while(numberOfChoices < size()){
    vhdl_out << " | ";
    choice->publish_vhdl(vhdl_out);
    numberOfChoices++;
    choice = dynamic_cast<IIRBase_Choice *>(successor(choice));
  }
}
