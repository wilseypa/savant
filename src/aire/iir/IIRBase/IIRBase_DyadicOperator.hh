
#ifndef IIRBASE_DYADIC_OPERATOR_HH
#define IIRBASE_DYADIC_OPERATOR_HH

// Copyright (c) 1996-2003 The University of Cincinnati.  
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
#include "IIR_DyadicOperator.hh"
#include "IIRBase_Operator.hh"

class IIR_SubprogramDeclaration;

class IIRBase_DyadicOperator : public virtual IIRBase_Operator,
			       public virtual IIR_DyadicOperator{

public:

  IIR_Kind get_kind() const { return IIR_DYADIC_OPERATOR;  }
  const IIR_Char *get_kind_text() const { return "IIR_DyadicOperator"; }

  void set_implementation( IIR_SubprogramDeclaration *implementation );
  IIR_SubprogramDeclaration *get_implementation();
  
  void set_left_operand( IIR *left_operand );
  IIR *get_left_operand();
  
  void set_right_operand( IIR *right_operand );
  IIR *get_right_operand();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_resolved();
  IIR_Boolean is_locally_static();
  IIR_Boolean is_operator() { return TRUE; }
  IIR_Boolean is_above_attribute_found();
  virtual IIR_Boolean is_left_associative(){ return TRUE; }
  virtual bool is_associative( IIR_Kind oper_kind );

  ostream &print( ostream & );

  void publish_vhdl(ostream &);
protected:
  IIRBase_DyadicOperator();
  virtual ~IIRBase_DyadicOperator() = 0;
  
private:
  IIR_SubprogramDeclaration *implementation;
  IIR *left_operand;
  IIR *right_operand;
};
#endif
