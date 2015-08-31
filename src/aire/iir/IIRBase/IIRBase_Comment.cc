
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
//          Narayanan Thondugulam 

//---------------------------------------------------------------------------

#include "IIRBase_Comment.hh"
#include "error_func.hh"
#include <sstream>
using std::ostringstream;

IIRBase_Comment::IIRBase_Comment(){
}

IIRBase_Comment::~IIRBase_Comment(){
  delete text;
}

IIR_Char *
IIRBase_Comment::get_text(){
  return text;
}

IIR_Int32 
IIRBase_Comment::get_text_length(){
  return text_length;
}

void 
IIRBase_Comment::set_element( IIR_Int32 subscript, IIR_Char value ){
  _check_bounds( subscript );
  text[ subscript ] = value;
}

IIR_Char& 
IIRBase_Comment::operator[]( IIR_Int32 subscript ){
  _check_bounds( subscript );
  return text[ subscript ];
}

void 
IIRBase_Comment::release(){
  delete this;
}

void 
IIRBase_Comment::_check_bounds( IIR_Int32 subscript ){
  if( subscript < 0 || subscript > text_length ){
    ostringstream err;
    err << "Error! IIRBase_Comment array subscript out of bounds!";
    report_error( this, err.str() );
    abort();
  }  
}

void
IIRBase_Comment::set_text( IIR_Char *txt, IIR_Int32 text_len ){
  text = txt;
  text_length = text_len;
}

IIR *
IIRBase_Comment::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_Comment *new_node = dynamic_cast<IIRBase_Comment *>(IIRBase_Literal::convert_tree(factory));

  // Process the variables
  new_node->text = strdup(text);
  new_node->text_length = text_length;

  return new_node;
}

void 
IIRBase_Comment::publish_vhdl(ostream &vhdl_out) {
  IIR_Int32 i;
  IIR_Int32 length = get_text_length();
  for ( i=0; i < length; i++ ){
    vhdl_out << this->operator[](i);
  }
}
