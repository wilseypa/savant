
// Copyright (c) 2003 The University of Cincinnati.
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

// Author: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------

#include "IIRBase_BreakList.hh"
#include "IIRBase_BreakElement.hh"
  
IIRBase_BreakList::IIRBase_BreakList() {}

IIRBase_BreakList::~IIRBase_BreakList() {}

void
IIRBase_BreakList::append(IIR_BreakElement* to_append) {
  dl_list<IIR>::append( to_append );
}

IIR_BreakElement *
IIRBase_BreakList::successor(IIR_BreakElement* succeed_me) {
  return dynamic_cast<IIR_BreakElement *>(dl_list<IIR>::successor( succeed_me));
}
  
IIR_BreakElement*
IIRBase_BreakList::first() {
  return dynamic_cast<IIR_BreakElement *>(dl_list<IIR>::first());
}

void
IIRBase_BreakList::publish_vhdl(ostream &vhdl_out) {
  IIRBase_BreakElement *node;
  IIRBase_BreakElement *temp_node;
  temp_node = dynamic_cast<IIRBase_BreakElement *>(first());
  for( node = dynamic_cast<IIRBase_BreakElement *>(first());
       node != NULL; 
       node = dynamic_cast<IIRBase_BreakElement *>(successor(node)) ) {
    if(node != temp_node) {
      vhdl_out << " , ";
    }
    node->publish_vhdl(vhdl_out);
  }
}
