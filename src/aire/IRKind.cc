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

// Authors: Philip A. Wilsey    phil.wilsey@uc.edu
//          Dale E. Martin      dmartin@cliftonlabs.com

//---------------------------------------------------------------------------

#include <cstdlib>
#include "IRKind.hh"
using std::cerr;

ostream &
operator <<(ostream &os, const IIR_Kind kind){
  switch(kind) {
  case IIR_ARCHITECTURE_DECLARATION:
    os << "architecture";
    break;
  case IIR_COMPONENT_DECLARATION:
    os << "component";
    break;
  case IIR_CONFIGURATION_DECLARATION:
    os << "configuration";
    break;
  case IIR_CONSTANT_DECLARATION:
    os << "constant";
    break;
  case IIR_ENTITY_DECLARATION:
    os << "entity";
    break;
  case IIR_FILE_DECLARATION:
    os << "file";
    break;
  case IIR_FUNCTION_DECLARATION:
    os << "function";
    break;
  case IIR_GROUP_DECLARATION:
    os << "group";
    break;
  case IIR_LABEL:
    os << "label";
    break;
  case IIR_LITERAL:
    os << "literal";
    break;
  case IIR_PACKAGE_DECLARATION:
    os << "package";
    break;
  case IIR_PHYSICAL_UNIT:
    os << "unit";
    break;
  case IIR_PROCEDURE_DECLARATION:
    os << "procedure";
    break;
  case IIR_SELECTED_NAME:
    os << "selected name";
    break;
  case IIR_SUBTYPE_DECLARATION:
    os << "subtype";
    break;
  case IIR_TYPE_DECLARATION:
    os << "type";
    break;
  case IIR_SIGNAL_DECLARATION:
    os << "signal";
    break;
  case IIR_VARIABLE_DECLARATION:
    os << "variable";
    break;
  default:
    cerr << "operator<<(ostream &, const IRKind) : Invalid IIR_Kind\n";
    abort();
  }

  return os;
}
