
#ifndef IIRBASE_STATEMENT_HH
#define IIRBASE_STATEMENT_HH

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
#include "IIRBase.hh"
#include "IIR_Statement.hh"

class IIR_Label;

class IIRBase_Statement : public virtual IIRBase, public virtual IIR_Statement{
public:

  void set_label( IIR_Label *label);
  IIR_Label *get_label() const;

  IIR *convert_tree(plugin_class_factory *factory);

  savant::set<IIR_Declaration> *find_declarations( IIR_Name * );

  /** For assertion statements this method is overloaded to return the
      assertion condtion.  For anything else it returns 0. */
  IIR *get_assertion_condition(){ return 0; }
  
  /** For report and assertion statements this method is overloaded to
      return the report expression.  For anything else it returns 0. */
  IIR *get_report_expression(){ return 0; }
  /** For report and assertion statements this method is overloaded to
      return the report expression. For anything else it returns 0. */
  IIR *get_severity_expression(){ return 0; }

  /**  This is overloaded for assertion and report statements.  Generate
      runtime error for anything else.  */
  void set_assertion_condition( IIR * );

  /**  This is overloaded for assertion and report statements.  Generate
      runtime error for anything else.  */
  void set_report_expression( IIR * );

  /**  This is overloaded for assertion and report statements.  Generate
      runtime error for anything else.  */
  void set_severity_expression( IIR * );

  virtual void set_reject_time_expression( IIR * );
  virtual void set_target( IIR * );

  ostream &print( ostream & );

  /** This method overloads the generic access method
      IIRBase::get_declarator() to return an declarator associated with the
      IIR hierarchy derived from "this" class.  The declarator associated with a
      Statement is its lablel.  Hence, this method merely returns the mangled
      label associated with this class [obtained by a call to
      IIRBase_Statement::get_label()->get_declarator].

      @return A IIR_TextLiteral* that points to the mangled declarator
      associated with this class.  The caller must not modify or delete the
      pointer returned by a call to this method virtual
  */
  IIR_TextLiteral* get_declarator();
  void publish_vhdl_stmt_label(ostream &);
  void publish_vhdl_delay_mechanism( ostream &, IIR_DelayMechanism, IIR * );

protected:
  IIRBase_Statement();
  virtual ~IIRBase_Statement() = 0;
    
private:
  
  IIR_Label *my_label;
};

#endif
