
#ifndef IIR_COMMENT_HH
#define IIR_COMMENT_HH

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

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_TextLiteral.hh"

class IIR_Comment : public virtual IIR_TextLiteral{

public:
  virtual ~IIR_Comment() {}

  virtual IIR_Char *get_text() = 0;
  virtual IIR_Int32 get_text_length() = 0;

  virtual void set_element( IIR_Int32 subscript, IIR_Char value ) = 0;
  virtual IIR_Char& operator[]( IIR_Int32 subscript ) = 0;

  virtual void set_text( IIR_Char *txt, IIR_Int32 text_len ) = 0;

  virtual void release() = 0;

protected:  

private:
};
#endif
