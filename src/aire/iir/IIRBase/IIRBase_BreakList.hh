
#ifndef IIRBASE_BREAK_LIST_HH
#define IIRBASE_BREAK_LIST_HH

// Copyright (c) The University of Cincinnati.
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

#include "savant_config.hh"
#include "IIR_BreakList.hh"
#include "IIRBase_List.hh"
#include "IRBasicDataTypes.hh"
  
class IIR_BreakElement;

/** The extension base for BreakList. This is a list of all Break Elements
    present in a break statement. */
class IIRBase_BreakList : public virtual IIR_BreakList, public virtual IIRBase_List {

public:
  /** Returns the IIR_Kind of this node. */
  IIR_Kind get_kind() const {
    return  IIR_BREAK_LIST;
  }
  
  const IIR_Char *get_kind_text() const { return "IIR_BreakList"; }

  IIRBase_BreakList();
  virtual ~IIRBase_BreakList()= 0;
  
  /** Append the BreakElement to the break list. */
  void append( IIR_BreakElement* );
  
  /** Returns the first Break Element in the break list. */
  IIR_BreakElement* first();

  /** Returns the next break element from the break list. */
  IIR_BreakElement* successor( IIR_BreakElement* );
 
  void publish_vhdl(ostream &);
protected:

private:
  
};
#endif
