// Copyright (c) The University of Cincinnati.  
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

#include "IIRBase_StringLiteral.hh"
#include "plugin_class_factory.hh"

IIRBase_StringLiteral::IIRBase_StringLiteral() {}
IIRBase_StringLiteral::~IIRBase_StringLiteral() {}

void 
IIRBase_StringLiteral::release() {
  delete this;
}

IIR_StringLiteral *
IIRBase_StringLiteral::get( const IIR_Char *new_text, IIR_Int32 new_length, plugin_class_factory *factory){
  IIRBase_StringLiteral *retval = dynamic_cast<IIRBase_StringLiteral *>(factory->new_IIR_StringLiteral());
  retval->set_text( new_text, new_length );

  return retval;
}
