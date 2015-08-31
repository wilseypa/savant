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

#include "savant.hh"
#include "error_func.hh"
#include "IIR_FloatingPointLiteral.hh"
#include "IIRBase_FloatingPointLiteral.hh"
#include "IIR_FloatingPointLiteral.hh"
#include <iomanip>
#include <sstream>
#include <string>

using std::ostringstream;

IIRBase_FloatingPointLiteral::IIRBase_FloatingPointLiteral() 
  : base( 10 ),
    mantissa( 0 ),
    mantissa_length( 0 ),
    exponent( 0 ),
    exponent_length( 0 ){ }

IIRBase_FloatingPointLiteral::~IIRBase_FloatingPointLiteral() {}

void
IIRBase_FloatingPointLiteral::release() {
  delete this;
}

const string
IIRBase_FloatingPointLiteral::print_value(IIR_Int32 length) {
  ostringstream retbuf;
  retbuf << std::setprecision(length) << get_floating_point_value();
  return retbuf.str();
}

void
IIRBase_FloatingPointLiteral::set_base(IIR_Int32 b) {
  base = b;
}

IIR_Int32
IIRBase_FloatingPointLiteral::get_base() {
  return base;
}

void
IIRBase_FloatingPointLiteral::set_mantissa(IIR_Char* m, IIR_Int32 ml) {
  mantissa = m;
  mantissa_length = ml;
}

IIR_Char*
IIRBase_FloatingPointLiteral::get_mantissa() {
  return mantissa;
}

IIR_Int32
IIRBase_FloatingPointLiteral::get_mantissa_length() {
  return mantissa_length;
}

void
IIRBase_FloatingPointLiteral::set_exponent(IIR_Char* e, IIR_Int32 el) {
  exponent = e;
  exponent_length = el;
}

IIR_Char*
IIRBase_FloatingPointLiteral::get_exponent() {
  return exponent;
}

IIR_Int32
IIRBase_FloatingPointLiteral::get_exponent_length() {
  return exponent_length;
}

IIR *
IIRBase_FloatingPointLiteral::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_FloatingPointLiteral *new_node = dynamic_cast<IIRBase_FloatingPointLiteral *>(IIRBase_Literal::convert_tree(factory));

  // Process the variables
  new_node->base = base;
  new_node->mantissa = mantissa;
  new_node->mantissa_length = mantissa_length;
  new_node->exponent = exponent;
  new_node->exponent_length = exponent_length;

  return new_node;
}

IIR_FP64
IIRBase_FloatingPointLiteral::get_floating_point_value() {
  int i;
  IIR_FP64 value = 0.0;
  IIR_Int32 base = get_base();
  IIR_Char* man = get_mantissa();
  int sign = 1;

  ASSERT(get_mantissa_length() > 0);

  if (man[0] == '-') {
    sign = -1;
    value = 0.0;
  }
  else {
    value = _char_to_int(man[0]);
  }
  // calculate part left of the point
  for (i = 1; i < get_mantissa_length(); i++) {
    if (man[i] == '.') {
      i++;
      break;
    }
    value = value * base + sign * _char_to_int(man[i]);
  }
  // add on the part right of the point
  double divisor = base;
  for (/* continue with old value of i */; i < get_mantissa_length(); i++) {
    value = value + sign * _char_to_int(man[i])/divisor;
    divisor = divisor * base;
  }
  if (get_exponent_length() > 0) {
    IIR_Char* exp = get_exponent();
    IIR_Int32 exp_val;

    if (exp[0] == '+' || exp[0] == '-') {
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

ostream &
IIRBase_FloatingPointLiteral::print( ostream &os ){
  os << print_value( 2 );

  return os;
}

void 
IIRBase_FloatingPointLiteral::publish_vhdl(ostream &vhdl_out) {
  register int i;
  IIR_Char* man = get_mantissa();
  IIR_Char* exp = get_exponent();
  char force_paranthesis = 0;
  
  if( is_negative() ) {
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
IIRBase_FloatingPointLiteral::is_negative(){
  if ( get_floating_point_value() < 0 ){
    return TRUE;
  }
  return FALSE;
}
