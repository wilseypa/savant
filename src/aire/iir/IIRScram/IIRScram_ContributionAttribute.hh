
#ifndef IIRSCRAM_CONTRIBUTION_ATTRIBUTE_HH
#define IIRSCRAM_CONTRIBUTION_ATTRIBUTE_HH

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

// Author: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_Attribute.hh"
#include "IIRBase_ContributionAttribute.hh"

template <class type> class dl_list;

/** The extension base for contribution attribute of terminals
    (T'contribution).  This class describes T'Contribution. For a terminal
    T, the attribute T'Contribution yields a through quantity, whose plus
    terminal is T and whose minus terminal is the reference terminal of
    nature of T. */
class IIRScram_ContributionAttribute : public virtual IIRBase_ContributionAttribute, public virtual IIRScram_Attribute {

public:
  IIRScram_ContributionAttribute() {}
  virtual ~IIRScram_ContributionAttribute() {}
  
  /** @name Method for publishing VHDL code. */

  /** Returns a pointer to the Quantity created by the build free quantity
     declaration. */
  IIRScram_Declaration *_get_implicit_declaration( const string & , IIRScram_TypeDefinition * );
  
  /** Returns the "through" type of the nature of the terminal. The
      implicit quantity is of the through type of the nature of terminal
      T. */
  IIRScram_TypeDefinition *_get_subtype();
  
protected:
private:
  
};
#endif

