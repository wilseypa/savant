
#ifndef IIRBASE_REPORT_STATEMENT_HH
#define IIRBASE_REPORT_STATEMENT_HH

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
#include "IIR_ReportStatement.hh"

class IIRBase_ReportStatement : public virtual IIRBase_SequentialStatement, public virtual IIR_ReportStatement{
public:

  IIR_Kind get_kind() const {return IIR_REPORT_STATEMENT;}
  const IIR_Char *get_kind_text() const {return "IIR_ReportStatement";}

  void set_report_expression( IIR* report_expression);
  IIR* get_report_expression();
  void set_severity_expression( IIR* severity_expression);
  IIR* get_severity_expression();

  IIR_Boolean is_above_attribute_found();

  IIR *convert_tree(plugin_class_factory *factory);

  void publish_vhdl(ostream &);
protected:
  
  IIRBase_ReportStatement();
  virtual ~IIRBase_ReportStatement() = 0;
    
private:
  
  IIR* report_expression;
  IIR* severity_expression;

};
#endif
