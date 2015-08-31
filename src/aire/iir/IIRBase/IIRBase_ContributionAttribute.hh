
#ifndef IIRBASE_CONTRIBUTION_ATTRIBUTE_HH
#define IIRBASE_CONTRIBUTION_ATTRIBUTE_HH

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
#include "IIR_ContributionAttribute.hh"
#include "IIRBase_Attribute.hh"
#include "IRBasicDataTypes.hh"

/** The extension base for contribution attribute of terminals
    (T'contribution).  This class describes T'Contribution. For a terminal
    T, the attribute T'Contribution yields a through quantity, whose plus
    terminal is T and whose minus terminal is the reference terminal of
    nature of T. */
class IIRBase_ContributionAttribute : public virtual IIR_ContributionAttribute, public virtual IIRBase_Attribute {

public:
  /** Returns the IIR_Kind of this node. */
  IIR_Kind get_kind() const {
    return IIR_CONTRIBUTION_ATTRIBUTE;
  }

  const IIR_Char *get_kind_text() const {
    return "IIR_ContributionAttribute";
  }
  
  /** This returns an IIR_TextLiteral when a Contribution attribute is
    instantiated. */
  IIR_TextLiteral *build_attribute_name();
  void publish_vhdl(ostream &);
protected:
  IIRBase_ContributionAttribute();
  virtual ~IIRBase_ContributionAttribute() =0;

private:
};
#endif
