
#ifndef IIRBASE_NATURE_DEFINITION_HH
#define IIRBASE_NATURE_DEFINITION_HH

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
 
//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_NatureDefinition.hh"
#include "IIRBase_TypeDefinition.hh"
#include "IRBasicDataTypes.hh"

class IIRBase_NatureDefinition : public virtual IIRBase_TypeDefinition,
				 public virtual IIR_NatureDefinition {

public:
  IIR_Kind get_kind() const { return IIR_NATURE_DEFINITION ; }
  const IIR_Char *get_kind_text() const { return "IIR_NatureDefinition"; }

  IIR_Boolean is_array_type() { return FALSE; }

  virtual IIR_TypeDefinition *get_final_subtype();

  void publish_vhdl(ostream&);
protected:

  IIRBase_NatureDefinition();
  virtual ~IIRBase_NatureDefinition() = 0;

private:

};

#endif
