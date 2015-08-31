
#ifndef IIR_TEXTLITERAL_HH
#define IIR_TEXTLITERAL_HH

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
#include "IIR_Literal.hh"
#include <string>

using namespace std;

class IIR_TextLiteral : public virtual IIR_Literal{
public:
  virtual ~IIR_TextLiteral() {}
    
  virtual IIR_Char *get_text() = 0;
  virtual IIR_Int32 get_text_length() = 0;

  virtual IIR_Char &operator[]( IIR_Int32 subscript ) = 0;

  /** Compares text literals. */

  /** This method converts an IIR_Identifier into a C++ string. */
  virtual const string convert_to_string() = 0;
  virtual const string convert_to_library_name() = 0;
};

#endif
