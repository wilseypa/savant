
#ifndef IIRBASE_IDENTIFIER_HH
#define IIRBASE_IDENTIFIER_HH

// Copyright (c) 1996-2003 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_TextLiteral.hh"
#include "IIR_Identifier.hh"
#include "savant.hh"

class plugin_class_factory;

class IIRBase_Identifier : public virtual IIRBase_TextLiteral, public virtual IIR_Identifier{

public:
  IIR_Kind get_kind() const {return IIR_IDENTIFIER;}
  const IIR_Char *get_kind_text() const {return "IIR_Identifier";}

  static IIR_Identifier *get( const IIR_Char *text, IIR_Int32 text_length, plugin_class_factory *factory );
  static IIR_Identifier *get( const string &text, plugin_class_factory *factory );

  void release();

protected:
  IIRBase_Identifier();
  virtual ~IIRBase_Identifier() = 0;
    
private:
};
#endif
