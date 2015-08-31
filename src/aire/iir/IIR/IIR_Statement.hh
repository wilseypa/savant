
#ifndef IIR_STATEMENT_HH
#define IIR_STATEMENT_HH

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
#include "IIR.hh"

class IIR_Name;
class IIR_Label;
namespace savant {
  template <class type> class set;
}

class IIR_Statement : public virtual IIR{
public:
  virtual ~IIR_Statement() {}
    
  virtual void set_label( IIR_Label *label) = 0;
  virtual IIR_Label *get_label() const = 0;

  virtual savant::set<IIR_Declaration> *find_declarations( IIR_Name * ) = 0;

  /** For assertion statements this method is overloaded to return the
      assertion condtion.  For anything else it returns 0. */
  virtual IIR *get_assertion_condition() = 0;
  
  /** For report and assertion statements this method is overloaded to
      return the report expression.  For anything else it returns 0. */
  virtual IIR *get_report_expression() = 0;

  /** For report and assertion statements this method is overloaded to
      return the report expression. For anything else it returns 0. */
  virtual IIR *get_severity_expression() = 0;

  /**  This is overloaded for assertion and report statements.  Generate
      runtime error for anything else.  */
  virtual void set_assertion_condition( IIR * ) = 0;

  /**  This is overloaded for assertion and report statements.  Generate
      runtime error for anything else.  */
  virtual void set_report_expression( IIR * ) = 0;

  /**  This is overloaded for assertion and report statements.  Generate
      runtime error for anything else.  */
  virtual void set_severity_expression( IIR * ) = 0;

  virtual void set_reject_time_expression( IIR * ) = 0 ;
  virtual void set_target( IIR * ) = 0;
};

#endif
