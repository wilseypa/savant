#ifndef IIRSCRAM_NATURE_DECLARATION_HH
#define IIRSCRAM_NATURE_DECLARATION_HH

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
 
// Authors: Sivakumar Gowrisankar             gowriss@ececs.uc.edu
//          Vinod Chamarty                    chamarv@ececs.uc.edu
//          Vasudevan Shanmugasundaram
//          Kathiresan Nellayappan
 
//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Declaration.hh"
#include "IIRBase_NatureDeclaration.hh"

class IIRScram_TerminalDeclaration;
class IIRScram_TypeDefinition;

class IIRScram_NatureDeclaration : public virtual IIRScram_Declaration, public virtual IIRBase_NatureDeclaration { 

public:
  IIRScram_NatureDeclaration();
  ~IIRScram_NatureDeclaration();

  
  /** Returns the type of declaration - nature in this case */ 

  IIRScram_TypeDefinition *_get_rval();

  /** Returns False if it is not array nature */
  //currently incomplete. until array natures are implemented.

  void _type_check();

  // Wrappers for IIRBase functions
  IIRScram_AttributeSpecificationList * _get_attributes();
  IIRScram_NatureDefinition *           _get_nature();

protected:
private:
};

#endif
