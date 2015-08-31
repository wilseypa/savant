
#ifndef IIRSCRAM_BRANCH_QUANTITY_DECLARATION_HH
#define IIRSCRAM_BRANCH_QUANTITY_DECLARATION_HH

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
#include "IIRBase_BranchQuantityDeclaration.hh"
#include "IIRScram_QuantityDeclaration.hh"
#include <vector>

using std::vector;

class IIRScram_BranchQuantityDeclaration : public virtual IIRScram_QuantityDeclaration, public virtual IIRBase_BranchQuantityDeclaration {

public:
  IIRScram_BranchQuantityDeclaration();
  ~IIRScram_BranchQuantityDeclaration();

  IIR_Int32 get_plus_terminal_id();
  IIR_Int32 get_minus_terminal_id();
  IIR_Int32 get_num_across_elements();
  IIR_Int32 get_num_through_elements();
  void _type_check();
  IIR_Boolean _is_branchQ() {return TRUE;}
  IIR_Boolean _is_readable();

  // Wrapper functions
  IIRScram * _get_across_aspect_expression();
  IIRScram * _get_through_aspect_expression();
  IIRScram * _get_across_aspect_tolerance();
  IIRScram * _get_through_aspect_tolerance();
  IIRScram_Name* _get_plus_terminal_name();
  IIRScram_Name* _get_minus_terminal_name();

protected:

private:
};
#endif


