
#ifndef IIRBASE_ASSOCIATION_ELEMENT_BY_OPEN_HH
#define IIRBASE_ASSOCIATION_ELEMENT_BY_OPEN_HH

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
#include "IIRBase_AssociationElement.hh"
#include "IIR_AssociationElementOpen.hh"

class IIRBase_AssociationElementOpen : public virtual IIRBase_AssociationElement, public virtual IIR_AssociationElementOpen{

public:
  IIR_Kind get_kind() const {return IIR_ASSOCIATION_ELEMENT_BY_OPEN;}
  const IIR_Char *get_kind_text() const {return "IIR_AssociationElementOpen";}

  IIR_Boolean is_locally_static(){ return TRUE; }

  ostream& print(ostream&);
  void publish_vhdl(ostream &);
  void publish_vhdl_without_formals(ostream &);
protected:
  IIRBase_AssociationElementOpen();
  virtual ~IIRBase_AssociationElementOpen() = 0;
    
private:

};
#endif
