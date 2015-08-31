
#ifndef IIR_BASIC_DATA_TYPES_HH
#define IIR_BASIC_DATA_TYPES_HH

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
#include "IRKind.hh"
#include <string>
using std::string;
#include <iostream>
using std::ostream;

typedef bool      IIR_Boolean;
#ifndef TRUE
#define TRUE true
#define FALSE false
#endif

#if SIZEOF_LONG == 8
#define INT_64 long
#else
#define INT_64 long long
#endif

typedef char       IIR_Char;
typedef int        IIR_Int32;
typedef INT_64     IIR_Int64;
typedef float      IIR_FP32;
typedef double     IIR_FP64;

enum IIR_SignalKind {
  IIR_NO_SIGNAL_KIND,
  IIR_REGISTER_KIND,
  IIR_BUS_KIND
};

enum IIR_Mode {
  IIR_UNKNOWN_MODE,
  IIR_IN_MODE,
  IIR_OUT_MODE,
  IIR_INOUT_MODE,
  IIR_BUFFER_MODE,
  IIR_LINKAGE_MODE
};

inline 
const string 
get_iir_mode_string( IIR_Mode mode ){
  string retval;

  switch( mode ){
  case IIR_IN_MODE:
    retval = "IIR_IN_MODE";
    break;
  case IIR_OUT_MODE:
    retval = "IIR_OUT_MODE";
    break;
  case IIR_INOUT_MODE:
    retval = "IIR_INOUT_MODE";
    break;
  case IIR_BUFFER_MODE:
    retval = "IIR_BUFFER_MODE";
    break;
  case IIR_LINKAGE_MODE:
    retval = "IIR_LINKAGE_MODE";
    break;
  case IIR_UNKNOWN_MODE:
  default:
    retval = "IIR_UNKNOWN_MODE";
  }

  return retval;
}

inline
ostream &operator<<( ostream &os, IIR_Mode mode ){
  os << get_iir_mode_string( mode );
  return os;
}

enum IIR_Pure {
  IIR_PURE_FUNCTION,
  IIR_IMPURE_FUNCTION
};

enum IIR_DelayMechanism {
  IIR_INERTIAL_DELAY,
  IIR_TRANSPORT_DELAY
};

class IIR;
typedef IIR* IIR_pointer;

#endif









