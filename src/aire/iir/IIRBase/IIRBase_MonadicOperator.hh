
#ifndef IIRBASE_MONADIC_OPERATOR_HH
#define IIRBASE_MONADIC_OPERATOR_HH

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
//          Malolan Chetlur     mal@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_Operator.hh"
#include "IIR_MonadicOperator.hh"

class IIR_SubprogramDeclaration;

class IIRBase_MonadicOperator : public virtual IIRBase_Operator,
				public virtual IIR_MonadicOperator{

public:
  IIR_Boolean is_locally_static();

  void set_implementation( IIR_SubprogramDeclaration* implementation);
  IIR_SubprogramDeclaration* get_implementation();
  void set_operand( IIR* operand);
  IIR* get_operand();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_resolved();
  IIR_Boolean is_operator() { return TRUE; }
  IIR_Boolean is_above_attribute_found();

  void publish_vhdl(ostream &);
protected:
  
  IIRBase_MonadicOperator();
  virtual ~IIRBase_MonadicOperator() = 0;
    
private:
  
  IIR* operand;
  IIR_SubprogramDeclaration* implementation;

};
#endif
