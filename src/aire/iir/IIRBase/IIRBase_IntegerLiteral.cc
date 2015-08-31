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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant.hh"
#include "error_func.hh"
#include "IIRBase_IntegerLiteral.hh"
#include "IIR_IntegerLiteral.hh"
#include <cstring>
#include <sstream>
using std::ostringstream;

IIRBase_IntegerLiteral::IIRBase_IntegerLiteral() :
  base( 10 ),
  mantissa( NULL ),
  mantissa_length( 0 ),
  exponent( NULL ),
  exponent_length( 0 ){}

IIRBase_IntegerLiteral::~IIRBase_IntegerLiteral() {}

void
IIRBase_IntegerLiteral::release() {
  delete this;
}


const string
IIRBase_IntegerLiteral::print( IIR_Int32 ){
  ostringstream os;
  os << "print(IIR_Int32) not defined for IIR node: " << get_kind_text();
  report_error( this, os.str() );
  return "";
}


void
IIRBase_IntegerLiteral::set_base(IIR_Int32 b) {
  base = b;
}


IIR_Int32
IIRBase_IntegerLiteral::get_base() {
  return base;
}


void
IIRBase_IntegerLiteral::set_mantissa(IIR_Char* m, IIR_Int32 ml) {
  mantissa = m;
  mantissa_length = ml;
}


IIR_Char*
IIRBase_IntegerLiteral::get_mantissa() {
  return mantissa;
}


IIR_Int32
IIRBase_IntegerLiteral::get_mantissa_length() {
  return mantissa_length;
}


void
IIRBase_IntegerLiteral::set_exponent(IIR_Char* e, IIR_Int32 el) {
  exponent = e;
  exponent_length = el;
}


IIR_Char*
IIRBase_IntegerLiteral::get_exponent() {
  return exponent;
}


IIR_Int32
IIRBase_IntegerLiteral::get_exponent_length() {
  return exponent_length;
}

IIR *
IIRBase_IntegerLiteral::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_IntegerLiteral *new_node = dynamic_cast<IIRBase_IntegerLiteral *>(IIRBase_Literal::convert_tree(factory));

  // Process the variables
  new_node->base = base;
  new_node->mantissa = mantissa;
  new_node->mantissa_length = mantissa_length;
  new_node->exponent = exponent;
  new_node->exponent_length = exponent_length;

  return new_node;
}

IIR_Int32
IIRBase_IntegerLiteral::get_integer_value(){
  register int i;
  IIR_Int32 value = 0;
  IIR_Int32 base = get_base();
  IIR_Char* man = get_mantissa();
  register int sign = 1;

  ASSERT(get_mantissa_length() > 0);

  if(man[0] == '-') {
    sign = -1;
    value = sign * _char_to_int(man[1]);
  } else {
    sign = 1;
    value = _char_to_int(man[0]);
    if(get_mantissa_length() > 1) {
      value = value * base + _char_to_int(man[1]);
    }
  }
  for (i = 2; i < get_mantissa_length(); i++) {
    value = value * base + sign *_char_to_int(man[i]);
  }
  if (get_exponent_length() > 0) {
    IIR_Char* exp = get_exponent();
    IIR_Int32 exp_val;
    if (exp[0] == '+') {
      i = 2;
      exp_val = _char_to_int(exp[1]);
    }
    else if (exp[0] == '-') {
      i = 2;
      exp_val = _char_to_int(exp[1]);
    }
    else {
      i = 1;
      exp_val = _char_to_int(exp[0]);
    }
    for (/* i already set */; i < get_exponent_length(); i++) {
      exp_val = exp_val * 10 + _char_to_int(exp[i]);
    }
    // exp_val is now the base-10 representation of the exponent.  The
    // value of this node is value * base^exp_val.  Care must be taken if
    // the exponent is < 0.
    if (exp[0] == '-') {
      for (i = 0; i < exp_val; i++) {
	value = value / base;
      }
    }
    else {
      for (i = 0; i < exp_val; i++) {
	value = value * base;
      }
    }
  }
  return value;
}

const string
IIRBase_IntegerLiteral::print_value(IIR_Int32 length) {
  ostringstream valbuf;
  ostringstream retbuf;
  string valstring;

  valbuf << get_integer_value();
  valstring = valbuf.str();

  if( (unsigned int)length > valstring.length() ) { 
    // pad with spaces if necessary
    for (unsigned int i = 0; i < length - valstring.length(); i++) {
      retbuf << " ";
    }
  }
  retbuf << valstring;

  return retbuf.str();
}

ostream &
IIRBase_IntegerLiteral::print( ostream &os ) {
  register int i;
  IIR_Char* man = get_mantissa();
  IIR_Char* exp = get_exponent();

  if (get_base() != 10) {
    os << get_base() << "#";
  }
  for (i = 0; i < get_mantissa_length(); i++) {
    os << man[i];
  }
  if (get_base() != 10) {
    os << "#";
  }
  if (get_exponent() != NULL) {
    os << "E";
    for (i = 0; i < get_exponent_length(); i++) {
      os << exp[i];
    }
  }
  return os;
}

void 
IIRBase_IntegerLiteral::publish_vhdl_range(ostream &vhdl_out){
  publish_vhdl( vhdl_out );
}

void 
IIRBase_IntegerLiteral::publish_vhdl(ostream &vhdl_out) {
  register int i;
  IIR_Char* man = get_mantissa();
  IIR_Char* exp = get_exponent();
  char force_paranthesis = 0;

  if( is_negative() ){
    force_paranthesis = 1;
    vhdl_out << "(";
  }
  if (get_base() != 10) {
    vhdl_out << get_base() << "#";
  }
  for (i = 0; i < get_mantissa_length(); i++) {
    vhdl_out << man[i];
  }
  if (get_base() != 10) {
    vhdl_out << "#";
  }
  if (get_exponent() != NULL && get_exponent_length() > 0 ) {
    vhdl_out << "E";
    for (i = 0; i < get_exponent_length(); i++) {
      vhdl_out << exp[i];
    }
  }
  if (force_paranthesis == 1) {
    vhdl_out << ")";
  }
}

IIR_Boolean
IIRBase_IntegerLiteral::is_negative(){
  IIR_Char* man = get_mantissa();
  if (man[0] == '-') {
    return TRUE;
  }
  return FALSE;
}
