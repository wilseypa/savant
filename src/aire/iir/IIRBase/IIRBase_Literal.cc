
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

#include "IIRBase_Literal.hh"

#include "IIR_DesignFile.hh"
#include "IIR_PhysicalSubtypeDefinition.hh"
#include "IIR_TypeDefinition.hh"

#include "StandardPackage.hh"

using std::cerr;
using std::endl;

IIRBase_Literal::IIRBase_Literal() {}
IIRBase_Literal::~IIRBase_Literal() {}

IIR_Int32 
IIRBase_Literal::_char_to_int(IIR_Char digit) {
  IIR_Int32 retval = 0;

  switch (digit) {
  case '0':
    retval = 0;
    break;
  case '1':
    retval = 1;
    break;
  case '2':
    retval = 2;
    break;
  case '3':
    retval = 3;
    break;
  case '4':
    retval = 4;
    break;
  case '5':
    retval = 5;
    break;
  case '6':
    retval = 6;
    break;
  case '7':
    retval = 7;
    break;
  case '8':
    retval = 8;
    break;
  case '9':
    retval = 9;
    break;
  case 'a':
  case 'A':
    retval = 10;
    break;
  case 'b':
  case 'B':
    retval = 11;
    break;
  case 'c':
  case 'C':
    retval = 12;
    break;
  case 'd':
  case 'D':
    retval = 13;
    break;
  case 'e':
  case 'E':
    retval = 14;
    break;
  case 'f':
  case 'F':
    retval = 15;
    break;
  default:
    //_char_to_int: cannot convert char to a digit
    ASSERT(0);
    break;
  }
  return retval;
}

IIR_Boolean 
IIRBase_Literal::is_locally_static(){
  // To be LRM compliant, technically time literals are not locally static.
  // Our theory about this is that this is because simulators are allow to
  // run at aribtrary resolutions - 1 fs might translate to 0 ns or
  // something.  Savant is not like that so we're going to oversimplify and
  // say that time literals are locally static too.
  return TRUE;

//   ASSERT( get_subtype() != 0 );
//   if( !get_design_file() ){
//     cerr << "About to crash - " << get_implementation_class() << endl;
//   }
//   ASSERT( get_design_file() != 0 );
//   ASSERT( get_design_file()->get_standard_package() != 0 );
//   IIR_TypeDefinition *time_type =
//     dynamic_cast<IIR_TypeDefinition *>(get_design_file()->get_standard_package()->get_time_type());
//   ASSERT( time_type != 0 );
//   return !get_subtype()->is_compatible( time_type );
}

IIR_Boolean
IIRBase_Literal::is_resolved(){
  if( get_subtype() == NULL ){
    return FALSE;
  }
  else{
    return TRUE;
  }
}
