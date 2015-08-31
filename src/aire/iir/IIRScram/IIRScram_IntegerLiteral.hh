
#ifndef IIRSCRAM_INTEGER_LITERAL_HH
#define IIRSCRAM_INTEGER_LITERAL_HH

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
//          Timothy J. McBrayer 
//          Malolan Chetlur     
//          Umesh Kumar V. Rajasekaran
//          Krishnan Subramani  
//          Radharamanan Radhakrishnan

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Literal.hh"
#include "IIRBase_IntegerLiteral.hh"

class IIRScram_Declaration;
class IIRScram_TypeDefinition;

class IIRScram_IntegerLiteral : public virtual IIRScram_Literal, public virtual IIRBase_IntegerLiteral{

public:
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  static IIRScram_IntegerLiteral *get( IIR_Int32 base, 
                                       IIR_Char *mantissa,  
                                       IIR_Int32 mantissa_length,
                                       IIR_Char *exponent, 
                                       IIR_Int32 exponent_length);


  /** Overloaded to cause a runtime error if a non-integer type is set on
      an integer literal.  */
  void set_subtype( IIR_TypeDefinition * );

  savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor = 0); 
  void _type_check(savant::set<IIRScram_TypeDefinition>*) {}
  IIR_Boolean _is_integer_literal();
  IIRScram *_clone() { return this; }

  IIRScram_IntegerLiteral *_get_integer_static_value();

protected:    
private:
};
#endif
