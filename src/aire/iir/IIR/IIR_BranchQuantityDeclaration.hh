
#ifndef IIR_BRANCH_QUANTITY_DECLARATION_HH
#define IIR_BRANCH_QUANTITY_DECLARATION_HH

// Copyright (c) 2002-2003 The University of Cincinnati.
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
 
// Authors: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIR_QuantityDeclaration.hh"

class IIR_Name;
class IIR_DesignatorList;

class IIR_BranchQuantityDeclaration : public virtual IIR_QuantityDeclaration {

public:
  IIR_BranchQuantityDeclaration() {}
  virtual ~IIR_BranchQuantityDeclaration() {}

  // List Accessor(s)
  virtual IIR_DesignatorList    *get_across_aspect_identifier_list() = 0;
  virtual IIR_DesignatorList    *get_through_aspect_designator_list() = 0;
  virtual void                  set_across_aspect_identifier_list(IIR_DesignatorList *) = 0;
  virtual void                  set_through_aspect_designator_list(IIR_DesignatorList *) = 0;

  /**
  Precondition: The type of the expression must be that of the quantity.
		 LRM [ $ 4.3.1.6 - 440 ]
		 The type of the across quantity is determined as in 
		 LRM [ $ 4.3.1.6 - 415 ]
  Postcondition: Initializes the branch quantity to the value specified in
                 the Initial Value Expression.                         */
 
  virtual void set_across_aspect_expression(IIR* across_aspect_expression) = 0;
  virtual IIR* get_across_aspect_expression() = 0;

  virtual void set_through_aspect_expression(IIR* through_aspect_expression) = 0;
  virtual IIR* get_through_aspect_expression() = 0;

  /** 
  Precondition:  The declaration must include a plus terminal name.
  Postcondition: The plus terminal and minus terminal of a branch quantity
		 are determined as in LRM [ $ 4.3.1.6 - 425 ]          */
    
  virtual void set_plus_terminal_name(IIR* plus_terminal_name) = 0;
  virtual IIR* get_plus_terminal_name() = 0;
  
  /**
  Precondition:  A Branch Quantity Declaration exists.
  Postcondition: If the branch quantity declaration does not include an 
		 explicit minus terminal name,  the minus terminal is 
		 equivalent to the reference terminal of the simple
		 nature of the plus terminal's nature. LRM [ $ 4.3.1.6 - 405 ] 	*/

  virtual void set_minus_terminal_name(IIR* minus_terminal_name) = 0;
  virtual IIR* get_minus_terminal_name() = 0;

  virtual void set_across_aspect_tolerance(IIR* across_aspect_tolerance) = 0;
  virtual IIR* get_across_aspect_tolerance() = 0;

  virtual void set_through_aspect_tolerance(IIR* through_aspect_tolerance) = 0;
  virtual IIR* get_through_aspect_tolerance() = 0;
};
#endif
