
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

#include "IIR_Identifier.hh"
#include "IIRBase_IdentifierList.hh"

IIRBase_IdentifierList::IIRBase_IdentifierList(){
}

IIRBase_IdentifierList::~IIRBase_IdentifierList(){
}

IIR_Identifier *
IIRBase_IdentifierList::first(){
  return dynamic_cast<IIR_Identifier *>(IIRBase_List::first());
}

IIR_Identifier *
IIRBase_IdentifierList::successor( IIR_Identifier *to_succeed ){
  return dynamic_cast<IIR_Identifier *>(IIRBase_List::successor( to_succeed ));
}

void 
IIRBase_IdentifierList::append( IIR_Identifier *to_append ){
  IIRBase_List::append( to_append );
}
