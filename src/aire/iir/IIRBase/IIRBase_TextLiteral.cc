
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

#include "error_func.hh"
#include "IIR_Name.hh"
#include "IIRBase_String.hh"
#include "IIRBase_TextLiteral.hh"

#include <sstream>

IIRBase_TextLiteral::IIRBase_TextLiteral() :
  text(0){}

IIRBase_TextLiteral::~IIRBase_TextLiteral(){}

IIR_Char *
IIRBase_TextLiteral::get_text(){
  return const_cast<char *>(text->get_text().c_str());
}

IIR_Int32 
IIRBase_TextLiteral::get_text_length(){
  return text->get_text_length();
}

IIR_Char &
IIRBase_TextLiteral::operator[]( IIR_Int32 subscript ){
  check_bounds( subscript );
  return text->operator[]( subscript );
}

void 
IIRBase_TextLiteral::check_bounds( IIR_Int32 subscript ){
  if( subscript < 0 || subscript > (get_text_length() - 1) ){
    ostringstream err;
    err << "Error! IIRBase_TextLiteralLiteral array subscript out of bounds!";
    report_error( this, err.str() );
    abort();
  }  
}

const string
IIRBase_TextLiteral::convert_to_string(){
  return text->convert_to_string();
}

const string
IIRBase_TextLiteral::convert_to_library_name(){
  return convert_to_string();
}

IIR *
IIRBase_TextLiteral::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_TextLiteral *new_node = dynamic_cast<IIRBase_TextLiteral *>(IIRBase_Literal::convert_tree(factory));

  // Process the variables
  new_node->set_text(text->get_text().c_str(), text->get_text_length());

  return new_node;
}

int 
IIRBase_TextLiteral::cmp(IIR_TextLiteral *a, IIR_TextLiteral *b) {
  int size_a, size_b;
  
  ASSERT( a != 0 );
  ASSERT( b != 0 );

  size_a = a->get_text_length();
  size_b = b->get_text_length();

  if ( size_a != size_b ){
    if ( size_a < size_b ){
      return -1;
    }
    else{
      return 1;
    }
  }

  IIR_Char *text_a = a->get_text();
  IIR_Char *text_b = b->get_text();
  
  if( text_a == text_b ){
    return 0;
  }
  else{
    return memcmp( text_a, text_b, size_a );
  }
}

int 
IIRBase_TextLiteral::cmp( IIR_TextLiteral *a, const char *b ) {
  int size_a, size_b;
  size_a = a->get_text_length();
  size_b = strlen(b);

  if( size_a > size_b ){
    return 1;
  }
  if (size_b > size_a) {
    return -1;
  }

  char *text_a = a->get_text();

  int i;
  for( i = 0; i < size_a; i++ ){
    if( text_a[i] != b[i] ){
      return text_a[i] - b[i];
    }
  }
  return 0;
}

int 
IIRBase_TextLiteral::cmp(IIR_TextLiteral *a, IIR_Name *b){
  int retval;

  if ( b->get_kind() != IIR_SIMPLE_NAME ){
    retval = -1;
  }
  else if ( b->get_prefix()->is_text_literal() == false ){
    retval = -1;
  }
  else {
    retval = IIRBase_TextLiteral::cmp( a, dynamic_cast<IIR_TextLiteral *>(b->get_prefix()) );
  }

  return retval;
}

void 
IIRBase_TextLiteral::set_text( const IIR_Char *const new_text, const IIR_Int32 new_length ){
  ASSERT( new_length > 0 );
  ASSERT( new_text != NULL);

  text = get_string_table().hash_look( new_text, new_length );
}

hash_table<IIRBase_String> &
IIRBase_TextLiteral::get_string_table(){
  static hash_table<IIRBase_String> *our_string_table = new hash_table<IIRBase_String>;

  return *our_string_table;
}

ostream &
IIRBase_TextLiteral::print( ostream &os ){
  os.write( get_text(), get_text_length() );

  return os;
}

void 
IIRBase_TextLiteral::publish_vhdl(ostream &vhdl_out) {
  print( vhdl_out );
}
