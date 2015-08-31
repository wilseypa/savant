
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

#include "savant.hh"
#include "IIR_Declaration.hh"
#include "IIRBase_NatureDefinition.hh"

IIRBase_NatureDefinition::IIRBase_NatureDefinition() {}

IIRBase_NatureDefinition::~IIRBase_NatureDefinition() {}


IIR_TypeDefinition *
IIRBase_NatureDefinition::get_final_subtype() {
  _report_undefined_fn("get_final_subtype()");
  return  NULL;
}

void
IIRBase_NatureDefinition::publish_vhdl(ostream& vhdl_out) {
  if(get_declaration() != NULL) {
    get_declaration()->publish_vhdl(vhdl_out);
  } 
  else {
    ASSERT(get_base_type() != NULL);
    get_base_type()->publish_vhdl(vhdl_out);
  }
}
