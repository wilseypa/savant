
#ifndef IIRBASE_ASSOCIATION_LIST_HH
#define IIRBASE_ASSOCIATION_LIST_HH

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
//          Timothy J. McBrayer tmcrbaye@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_List.hh"
#include "IIR_AssociationList.hh"

class IIR_AssociationElement;

class IIRBase_AssociationList : public virtual IIRBase_List,
				public virtual IIR_AssociationList{
public:
  IIR_Kind get_kind() const {return IIR_ASSOCIATION_LIST;}
  const IIR_Char *get_kind_text() const {return "IIR_AssociationList";}

  IIR_AssociationElement *first();
  IIR_AssociationElement *successor(IIR_AssociationElement*);

  IIR_Boolean is_resolved();
  IIR_Boolean is_above_attribute_found();

  IIR_Boolean is_locally_static();

  ostream &print( ostream & );  
  void publish_vhdl(ostream &);
  void publish_vhdl_without_formals(ostream &);
protected:
  IIRBase_AssociationList();
  virtual ~IIRBase_AssociationList() = 0;
    
private:
};
#endif
