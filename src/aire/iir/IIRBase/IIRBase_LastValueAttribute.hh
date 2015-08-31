
#ifndef IIRBASE_LAST_VALUE_ATTRIBUTE_HH
#define IIRBASE_LAST_VALUE_ATTRIBUTE_HH

// Copyright (c) 1996-1999 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
// DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.


// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     mal@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_Attribute.hh"
#include "IIR_LastValueAttribute.hh"

class IIRBase_LastValueAttribute : public virtual IIRBase_Attribute,
				   public virtual IIR_LastValueAttribute{
public:
  IIR_Kind get_kind() const {return IIR_LAST_VALUE_ATTRIBUTE;}
  const IIR_Char *get_kind_text() const {return "IIR_LastValueAttribute";}

  IIR_Boolean is_signal(){ return FALSE; }
  IIR_Boolean is_function_attribute(){ return TRUE; }

  IIR_TextLiteral *build_attribute_name();
  void publish_vhdl(ostream &);
protected:
  IIRBase_LastValueAttribute();
  virtual ~IIRBase_LastValueAttribute() = 0;
    
private:
};
#endif
