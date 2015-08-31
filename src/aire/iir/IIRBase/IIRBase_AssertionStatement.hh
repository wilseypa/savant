
#ifndef IIRBASE_ASSERTION_STATEMENT_HH
#define IIRBASE_ASSERTION_STATEMENT_HH

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
#include "IIRBase_SequentialStatement.hh"
#include "IIR_AssertionStatement.hh"

class IIRBase_AssertionStatement : public virtual IIRBase_SequentialStatement, public virtual IIR_AssertionStatement{

public:
  IIR_Kind get_kind() const {return IIR_ASSERTION_STATEMENT;}
  const IIR_Char *get_kind_text() const {return "IIR_AssertionStatement";}

  void set_assertion_condition( IIR* assertion_condition);
  IIR* get_assertion_condition();

  void set_report_expression( IIR* report_expression);
  IIR* get_report_expression();

  void set_severity_expression( IIR* expression);
  IIR* get_severity_expression();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_above_attribute_found();
  
  void publish_vhdl(ostream &);
protected:
  IIRBase_AssertionStatement();
  virtual ~IIRBase_AssertionStatement() = 0;
    
private:
  IIR* assertion_condition;
  IIR* report_expression;
  IIR* expression;
};
#endif
