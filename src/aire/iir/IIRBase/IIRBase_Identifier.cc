
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

#include "savant.hh"
#include "IIRBase_Identifier.hh"
#include "IIR_Identifier.hh"
#include "plugin_class_factory.hh"

IIRBase_Identifier::IIRBase_Identifier(){}

IIRBase_Identifier::~IIRBase_Identifier(){}

void 
IIRBase_Identifier::release(){
  delete this;
}

IIR_Identifier *
IIRBase_Identifier::get( const IIR_Char *new_text, 
			 IIR_Int32 new_length,
			 plugin_class_factory *factory ){
  IIR_Identifier *retval = factory->new_IIR_Identifier();  
  dynamic_cast<IIRBase_Identifier *>(retval)->set_text( new_text, new_length );
  return retval;
}

IIR_Identifier *
IIRBase_Identifier::get( const string &text, plugin_class_factory *factory ){
  return get( text.c_str(), text.length(), factory );
}
