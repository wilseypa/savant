
#ifndef IIRBASE_ASSOCIATION_ELEMENT_HH
#define IIRBASE_ASSOCIATION_ELEMENT_HH

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
#include "IIRBase_Tuple.hh"
#include "IIR_AssociationElement.hh"

class IIRBase_AssociationElement : public virtual IIRBase_Tuple,
				   public virtual IIR_AssociationElement{

public:
  void set_formal(IIR*);
  IIR* get_formal();

  IIR *convert_tree(plugin_class_factory *factory);

  // These virtual method must never be called.  It is overloaded for
  // IIRBase_AssociationElementByExpression
  IIR* get_actual() { return NULL; }
  void set_actual( IIR* ) { ASSERT(0); }

  // This is overloaded in IIRBase_AssociationElementByExpression.
  IIR_Boolean is_resolved(){ return TRUE; }
  IIR_Boolean is_named();
  IIR_Boolean is_by_others();

  virtual IIR_Boolean is_locally_static() = 0;

  virtual void publish_vhdl_without_formals(ostream &);
protected:
  IIRBase_AssociationElement();
  virtual ~IIRBase_AssociationElement() = 0;
    
private:
  IIR *formal;
};
#endif
