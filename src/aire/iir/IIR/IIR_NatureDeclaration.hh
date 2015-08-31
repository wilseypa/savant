
#ifndef IIR_NATURE_DECLARATION_HH
#define IIR_NATURE_DECLARATION_HH

// Copyright (c) 2002 The University of Cincinnati.
// All rights reserved.
 
// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
// NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
 
// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S., and
// the terms of this license.

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2, June
// 1991. A copy of this license agreement can be found in the file "LGPL",
// distributed with this archive.
 
// Authors: Sivakumar Gowrisankar             gowriss@ececs.uc.edu
//          Vinod Chamarty                    chamarv@ececs.uc.edu
//          Vasudevan Shanmugasundaram
//          Kathiresan Nellayappan
 
//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_Declaration.hh"
#include "IRBasicDataTypes.hh"
#include "IIR_NatureDefinition.hh"

class IIR_NatureDefinition;
class IIR_AttributeSpecificationList;
class IIR_AttributeSpecificationList;
class IIR_TerminalDeclaration;

class IIR_NatureDeclaration : public virtual IIR_Declaration {
public:
  virtual ~IIR_NatureDeclaration() {}

  // List accessor(s)
  virtual IIR_AttributeSpecificationList  *get_attributes() = 0;

  /** Set the Nature of the terminal */
  virtual void set_nature(IIR_NatureDefinition* nature) = 0;

  /** Get nature of the terminal */
  virtual IIR_NatureDefinition *get_nature() = 0;

  /** Returns the reference terminal */
  virtual IIR_TerminalDeclaration* get_reference_terminal() = 0;

  /** Set the reference terminal */
  virtual void set_reference_terminal(IIR_TerminalDeclaration *) = 0;
};

#endif
