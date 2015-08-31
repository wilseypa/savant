
#ifndef IIRSCRAM_SCALAR_NATURE_DEFINITION_HH
#define IIRSCRAM_SCALAR_NATURE_DEFINITION_HH

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
#include "IIRScram_NatureDefinition.hh"
#include "IIRBase_ScalarNatureDefinition.hh"

class IIRScram_TypeDefinition;

class IIRScram_ScalarNatureDefinition : public virtual IIRScram_NatureDefinition,
					public virtual IIRBase_ScalarNatureDefinition {

public:
  /** This function publishes the vhdl for across and free type_mark declared 
      for a nature definition. */

  // Helper Functions
  IIRScram_TypeDefinition               *_get_through();
  IIRScram_TypeDefinition               *_get_across();
  IIRScram_TerminalDeclaration          *_get_reference_terminal();

protected:
private:

};

#endif
