#ifndef IIRSCRAM_STRING_HH
#define IIRSCRAM_STRING_HH

// Copyright (c) 1996-2000 The University of Cincinnati.  
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

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include <string>
#include "IRBasicDataTypes.hh"

using std::string;

class IIRBase_String {
public:
  IIRBase_String(){};
  ~IIRBase_String(){};
  
  void 
  set_key( const string new_text, const int ){
    my_text = new_text;
  }

  int
  test_key( const string compare_text, const int ){
    return my_text.compare( compare_text );
  }

  const string &get_text(){
    return my_text;
  }

  int get_text_length(){
    return my_text.length();
  }

  IIR_Char &operator[]( int offset ){
    return my_text[ offset ];
  }

  const string convert_to_string(){
    string retval = "";
    int my_length = get_text_length();
    for( int i = 0; i < my_length; i++ ){
      if(my_text[i] == '"') {
	retval += "\\";
      }
      retval += my_text[i];
    }
    return retval;
  }

private:
  string my_text;
};
#endif
