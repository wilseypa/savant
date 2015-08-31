#ifndef IIRSCRAM_STATEMENT_HH
#define IIRSCRAM_STATEMENT_HH

// Copyright (c) 1996-2001 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING
// OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found
// in the file "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer
//          Malolan Chetlur    
//          Umesh Kumar V. Rajasekaran

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram.hh"
#include "IIRBase_Statement.hh"

template <class type> class dl_list;

class IIRScram_CaseStatementAlternativeList;
class IIRScram_Label;
class IIR_LibraryUnit;
class IIRScram_List;
class IIRScram_Name;
class IIRScram_SimpleName;
class IIRScram_Statement;
class IIRScram_StatementList;
class IIRScram_SubprogramDeclaration;
class IIRScram_TextLiteral;
class IIRScram_TypeDefinition;
class IIRScram_WaitStatement;
class IIRScram_WaveformList;

class IIRScram_Statement : public virtual IIRScram, public virtual IIRBase_Statement{

public:
  IIR_Boolean _is_iir_statement(){ return TRUE; }
  
  virtual void _type_check();
				
  // This method does the type checking and resolution for a boolean
  // condition.  Pass in a conditional, and it will return it
  // resolved.  It will report any errors it finds (like that value
  // not being boolean).  This method is called by IIR_IfStatement,
  // IIR_ElsifStatement, and IIR_WhileLoopStatement...  (For it to be called 
  // from IIR_Elsif, this must be public!
  static IIRScram *_type_check_and_resolve_boolean_condition( IIRScram *condition );
	
  // These virtual methods are needed to support the type checking functions in the
  // protected section
  virtual IIRScram *_get_target();
  virtual IIR_DelayMechanism _get_delay_mechanism();
  virtual IIRScram *_get_reject_time_expression();
	
  // These methods are needed for the type checking of case statements that occurs in
  // IIRScram_CaseStatement, and IIRScram_ConcurrentSelectedSignalAssignment.
  virtual IIRScram *_get_case_statement_expression();
  virtual void _set_case_statement_expression( IIRScram * );

  /** For assertion statements this method is overloaded to return the
      assertion condtion.  For anything else it returns 0. */
  virtual IIRScram *_get_assertion_condition(){ return 0; }
  
  /** For report and assertion statements this method is overloaded to
      return the report expression.  For anything else it returns 0. */
  virtual IIRScram *_get_report_expression(){ return 0; }

  /** For report and assertion statements this method is overloaded to
      return the report expression. For anything else it returns 0. */
  virtual IIRScram *_get_severity_expression(){ return 0; }

  virtual IIRScram_Label *_find_instantiate_label( IIRScram_SimpleName * );

  virtual void _make_interface_visible( symbol_table * );

  IIRScram_Label *_get_label() const;

  /**
     Returns the library unit that contains this statement.
  */
  IIR_LibraryUnit *_get_design_unit();

  /** Returns the design unit name that this statement is associated
      with. */
  const string _get_design_unit_name();

protected:

  virtual ~IIRScram_Statement() = 0;

  // These methods are used in the type checking of signal assignment statements,
  // and concurrent selected signal assignment statements.
  void _type_check_target_and_waveform( IIRScram_WaveformList * );
  void _type_check_mechanism_and_time( IIRScram_WaveformList * );

  // This method handles the type checking of case statement expressions and their 
  // alternatives.  The return value is the resolved expression (if there is no error),
  // and NULL if there is an error.  The list is type checked in place.
  void _type_check_case_statement_expression( IIRScram_CaseStatementAlternativeList * );

  // The following methods apply to assertion statements, concurrent assertion
  // statements, and report statements.
  void _type_check_assertion_condition();
  void _type_check_report_expression();
  void _type_check_severity_expression();

  // This method prints the statement label for all statements.

  // This method prints the delay mechanism
  // (transport/reject...inertial) for all statements. 

  
private:
};
#endif
