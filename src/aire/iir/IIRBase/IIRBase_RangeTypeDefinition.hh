
#ifndef IIRBASE_RANGE_TYPE_DEFINITION_HH
#define IIRBASE_RANGE_TYPE_DEFINITION_HH

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

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_ScalarTypeDefinition.hh"
#include "IIR_RangeTypeDefinition.hh"

class IIRBase_RangeTypeDefinition : public virtual IIRBase_ScalarTypeDefinition, public virtual IIR_RangeTypeDefinition{

public:

  IIR_Kind get_kind() const {return IIR_RANGE_TYPE_DEFINITION;}
  const IIR_Char *get_kind_text() const {return "IIR_RangeTypeDefinition";}

  // XXX - this is a kludge.  This shouldn't need to be here.  Essentially
  // a range type is a type that we don't know if it is discrete or not...
  IIR_Boolean is_discrete_type(){ return TRUE; };
  void publish_vhdl(ostream &);
  void publish_vhdl_decl(ostream &);
  void publish_vhdl_constraint(ostream &);
protected:
  
  IIRBase_RangeTypeDefinition();
  virtual ~IIRBase_RangeTypeDefinition() = 0;
    
private:

};
#endif
