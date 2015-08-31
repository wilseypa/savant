
#ifndef IIRBASE_BRANCH_QUANTITY_DECLARATION_HH
#define IIRBASE_BRANCH_QUANTITY_DECLARATION_HH

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
#include "IIR_BranchQuantityDeclaration.hh"
#include "IIRBase_QuantityDeclaration.hh"
#include "IRBasicDataTypes.hh"

class IIRBase_BranchQuantityDeclaration : public virtual IIRBase_QuantityDeclaration, public virtual IIR_BranchQuantityDeclaration {

public:
  /** Returns the IIR_Kind of this node. */
  IIR_Kind
  get_kind() const {
    return IIR_BRANCH_QUANTITY_DECLARATION ;
  }

  const IIR_Char *get_kind_text() const { return "IIR_BranchQuantityDeclaration"; }

  /**
  Precondition: The type of the expression must be that of the quantity.
		 LRM [ $ 4.3.1.6 - 440 ]
		 The type of the across quantity is determined as in 
		 LRM [ $ 4.3.1.6 - 415 ]
  Postcondition: Initializes the branch quantity to the value specified in
                 the Initial Value Expression.                         */

  void set_across_aspect_expression(IIR* across_aspect_expression);
  IIR* get_across_aspect_expression();

  void set_through_aspect_expression(IIR* through_aspect_expression);
  IIR* get_through_aspect_expression();

  /** 
  Precondition:  The declaration must include a plus terminal name.
  Postcondition: The plus terminal and minus terminal of a branch quantity
		 are determined as in LRM [ $ 4.3.1.6 - 425 ]          */

  void set_plus_terminal_name(IIR* plus_terminal_name);
  IIR* get_plus_terminal_name();
  
  /**
  Precondition:  A Branch Quantity Declaration exists.
  Postcondition: If the branch quantity declaration does not include an 
		 explicit minus terminal name,  the minus terminal is 
		 equivalent to the reference terminal of the simple
		 nature of the plus terminal's nature. LRM [ $ 4.3.1.6 - 405 ] 	*/

  void set_minus_terminal_name(IIR* minus_terminal_name);
  IIR* get_minus_terminal_name();

  // Accessor functions
  IIR_DesignatorList *get_across_aspect_identifier_list();
  IIR_DesignatorList *get_through_aspect_designator_list();
  void set_across_aspect_identifier_list(IIR_DesignatorList *);
  void set_through_aspect_designator_list(IIR_DesignatorList *);
  
  void set_across_aspect_tolerance(IIR* across_aspect_tolerance);
  IIR* get_across_aspect_tolerance();

  void set_through_aspect_tolerance(IIR* through_aspect_tolerance);
  IIR* get_through_aspect_tolerance();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean _is_across_quantity();
  
  void publish_vhdl_decl(ostream &);
protected:
  IIRBase_BranchQuantityDeclaration();
  virtual ~IIRBase_BranchQuantityDeclaration() = 0;

private:
  IIR_DesignatorList* across_aspect_identifier_list;
  IIR_DesignatorList* through_aspect_designator_list;
  IIR* across_aspect_expression;
  IIR* through_aspect_expression;
  IIR* plus_terminal_name;
  IIR* minus_terminal_name;
  IIR* across_aspect_tolerance;
  IIR* through_aspect_tolerance;

};
#endif
