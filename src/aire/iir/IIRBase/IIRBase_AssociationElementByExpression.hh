
#ifndef IIRBASE_ASSOCIATION_ELEMENT_BY_EXPRESSION_HH
#define IIRBASE_ASSOCIATION_ELEMENT_BY_EXPRESSION_HH

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

#include "savant_config.hh"
#include "IIRBase_AssociationElement.hh"
#include "IIR_AssociationElementByExpression.hh"

class IIRBase_AssociationElementByExpression : public virtual IIRBase_AssociationElement, public virtual IIR_AssociationElementByExpression{

public:
  IIR_Kind get_kind() const {return IIR_ASSOCIATION_ELEMENT_BY_EXPRESSION;}
  const IIR_Char *get_kind_text() const {return "IIR_AssociationElementByExpression";}
  void set_actual(IIR*);
  IIR* get_actual();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_resolved();
  IIR_Boolean is_signal();
  IIR_Boolean is_variable();
  IIR_Boolean is_above_attribute_found();
  IIR_Boolean is_locally_static();

  ostream &print( ostream & );
  void publish_vhdl(ostream &);
  void publish_vhdl_without_formals(ostream &);
protected:
  IIRBase_AssociationElementByExpression();
  virtual ~IIRBase_AssociationElementByExpression() = 0;
    
private:
  IIR *actual;

};
#endif
