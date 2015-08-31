
#ifndef IIRBASE_ARRAY_SUBNATURE_DEFINITION_HH
#define IIRBASE_ARRAY_SUBNATURE_DEFINITION_HH

// Copyright (c) 2002-2003 The University of Cincinnati.
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

// Author: Sivakumar Gowrisankar             gowriss@ececs.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_ArraySubnatureDefinition.hh"
#include "IIRBase_ArrayNatureDefinition.hh"

class IIRBase_ArraySubnatureDefinition : public virtual IIRBase_ArrayNatureDefinition, public virtual IIR_ArraySubnatureDefinition {

public:
  IIR_Kind get_kind() const { return IIR_ARRAY_SUBNATURE_DEFINITION; }
  const IIR_Char *get_kind_text() const { return "IIR_ArraySubnatureDefinition"; }

  IIR_Boolean is_subtype();
  IIR_Boolean is_array_type() { return TRUE; }

  void publish_vhdl(ostream &);
  void publish_vhdl_decl(ostream &);
  void publish_vhdl_subtype_decl(ostream &);
  void publish_vhdl_type_decl(ostream &);
protected:
  IIRBase_ArraySubnatureDefinition();
  virtual ~IIRBase_ArraySubnatureDefinition() = 0;
    
private:

};
#endif
