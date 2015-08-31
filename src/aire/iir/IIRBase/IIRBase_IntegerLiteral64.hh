
#ifndef IIRBASE_INTEGER_LITERAL64_HH
#define IIRBASE_INTEGER_LITERAL64_HH

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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_Literal.hh"
#include "IIR_IntegerLiteral64.hh"

class IIRBase_IntegerLiteral64 : public virtual IIRBase_Literal, public virtual IIR_IntegerLiteral64{

public:
  IIR_Kind get_kind() const { return IIR_INTEGER_LITERAL64; }
  const IIR_Char *get_kind_text() const { return "IIR_IntegerLiteral64"; }

  static IIR_IntegerLiteral64* get(IIR_Int64);
  void release();

  IIR_Int64 value();
  void set_value(IIR_Int64);

  IIR *convert_tree(plugin_class_factory *factory);

  void publish_vhdl(ostream &);
protected:
  IIRBase_IntegerLiteral64();
  virtual ~IIRBase_IntegerLiteral64() = 0;
    
private:
  IIR_Int64 val;
};
#endif
