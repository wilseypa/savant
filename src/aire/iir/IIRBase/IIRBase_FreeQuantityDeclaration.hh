
#ifndef IIRBASE_FREE_QUANTITY_DECLARATION_HH
#define IIRBASE_FREE_QUANTITY_DECLARATION_HH

// Copyright (c) 2002 The University of Cincinnati.
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

#include "savant_config.hh"
#include "IIR_FreeQuantityDeclaration.hh"
#include "IIRBase_QuantityDeclaration.hh"

class IIRBase_FreeQuantityDeclaration : public virtual IIRBase_QuantityDeclaration, public virtual IIR_FreeQuantityDeclaration {

public:
  /** Returns the IIR_Kind of this node. */
  IIR_Kind get_kind() const {
    return IIR_FREE_QUANTITY_DECLARATION;
  }

  const IIR_Char *get_kind_text() const {
    return "IIR_FreeQuantityDeclaration";
  }
  
  /**
  Precondition : The type of the expression must be that of the quantity. 
                 LRM [ $ 4.3.1.6 - 440 ]
  Postcondition: Initializes the free quantity to the value specified in 
		 the Initial Value Expression.                          */

  void set_value(IIR* value);

  IIR* get_value();

  IIR *convert_tree(plugin_class_factory *factory);

  void publish_vhdl_decl(ostream &);
protected:
  IIRBase_FreeQuantityDeclaration();
  virtual ~IIRBase_FreeQuantityDeclaration() = 0;

private:
  IIR* value;

};

#endif
