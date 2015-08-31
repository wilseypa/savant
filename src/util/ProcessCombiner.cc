#ifdef PROCESS_COMBINATION
// Copyright (c) 1998-1999 The University of Cincinnati.  
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

// Author: Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------
#include <iostream>
#include "savant.hh"
#include "symbol_table.hh"
#include "IRBasicDataTypes.hh"
#include "ProcessCombiner.hh"
#include "IIR_IndexedName.hh"
#include "IIR_ProcessStatement.hh"
#include "IIR_WaitStatement.hh"
#include "IIR_VariableDeclaration.hh"
#include "IIR_EventAttribute.hh"
#include "IIR_IfStatement.hh"
#include "IIR_AndOperator.hh"
#include "IIR_OrOperator.hh"
#include "IIR_DesignatorExplicit.hh"
#include "IIR_EnumerationTypeDefinition.hh"
#include "IIR_PhysicalSubtypeDefinition.hh"
#include "StandardPackage.hh"
#include "IIR_FunctionCall.hh"
#include "IIR_Label.hh"
#include "IIR_IntegerLiteral.hh"
#include "IIR_EqualityOperator.hh"
#include "IIR_AdditionOperator.hh"
#include "IIR_VariableAssignmentStatement.hh"
#include "IIR_Identifier.hh"
#include "IIR_SubprogramDeclaration.hh"
#include <sstream>


ProcessCombiner::ProcessCombiner() {
  process = NULL;
  size = 0;
}


ProcessCombiner::ProcessCombiner( ProcessCombiner &pc ) {
  process = pc.process;
  init_stmt_list = pc.init_stmt_list;
  size = pc.size;
}

  
ProcessCombiner::~ProcessCombiner() {}
  

ProcessCombiner& 
ProcessCombiner::operator=( ProcessCombiner& pc ) {
  process = pc.process;
  init_stmt_list = pc.init_stmt_list;
  size = pc.size;
  return *this;
}


// combine to_combine into 'this'--for processes with unconditional waits
void
ProcessCombiner::combine_uncondwait( IIR_ProcessStatement *to_combine ) {
  IIR_WaitStatement *wait[2];

  size++;
  if ( NULL == process ) {
    process = to_combine;
    return;
  }

  wait[0] = (IIR_WaitStatement*)process->process_statement_part.last();
  wait[1] = (IIR_WaitStatement*)to_combine->process_statement_part.last();

  ASSERT( wait[0]->get_kind() == IIR_WAIT_STATEMENT );
  ASSERT( wait[1]->get_kind() == IIR_WAIT_STATEMENT );

  ASSERT( wait[0]->get_timeout_clause() == NULL );
  ASSERT( wait[0]->get_condition_clause() == NULL );
  ASSERT( wait[0]->sensitivity_list.size() == 0);
  ASSERT( wait[1]->get_timeout_clause() == NULL );
  ASSERT( wait[1]->get_condition_clause() == NULL );
  ASSERT( wait[1]->sensitivity_list.size() == 0);

  IIR_Declaration *decl;
  IIR_SequentialStatement *stmt;

  decl = to_combine->process_declarative_part.first();
  while ( decl != NULL ) {
    process->process_declarative_part.append( decl );
    decl = to_combine->process_declarative_part.successor( decl );
  }

  process->process_statement_part.remove( wait[0] );
  
  stmt = to_combine->process_statement_part.first();
  while ( stmt->get_kind() != IIR_WAIT_STATEMENT ) {
    process->process_statement_part.append( stmt );
    stmt = to_combine->process_statement_part.successor( stmt );
  }
  process->process_statement_part.append( wait[0] );
}


// This method combines the argument process to_combine into
void 
ProcessCombiner::combine( IIR_ProcessStatement *to_combine ) {
  IIR_Char *text = NULL;
  IIR_IfStatement *ifstmt;
  IIR_SequentialStatement *stmtptr;
  IIR_VariableAssignmentStatement *assign;
  IIR_Declaration *decl;
  IIR_DesignatorExplicit *waitsig;
  IIR_WaitStatement *wait, *newwait;

  size++;
  if ( NULL == process ) {
    IIR_Label *label;

#if COMBINE_DEBUG
    cerr << "starting a new combined process\n";
#endif
    process = new IIR_ProcessStatement;
    to_combine->copy_location( to_combine, process );

    ostringstream newname;
    newname << "combined_process" << process;
    text = newname.str();
    label = new IIR_Label;
    to_combine->copy_location( to_combine, label );
    label->set_declarator(IIR_Identifier::get(text, strlen(text)));
    process->set_label(label);

    // Create the variable 'first_time' when creating a new combined process
    ostringstream varname;
    IIR_VariableDeclaration *vardecl = new IIR_VariableDeclaration();
    process->copy_location( process, vardecl );
    varname << "first_time";
    text = varname.str();
    vardecl->set_declarator( IIR_Identifier::get( text, strlen(text)) );
    vardecl->set_subtype( StandardPackage::boolean_type );
    vardecl->set_value( StandardPackage::boolean_type->get_right() );
    vardecl->_set_declarative_region( process );
    process->process_declarative_part.append( vardecl );

    // create the new if statement to switch off of first_time
    ifstmt = new IIR_IfStatement;
    process->copy_location( process, ifstmt );
    ifstmt->set_condition( vardecl );
    process->process_statement_part.append( ifstmt );

    // Set up helper class data members
    init_stmt_list = &ifstmt->then_sequence;
    run_stmt_list = &ifstmt->else_sequence;

    // create 'first_time := false;' and put into init_stmt_list
    assign = new IIR_VariableAssignmentStatement;
    process->copy_location( process, assign );
    assign->set_target( vardecl );
    assign->set_expression( StandardPackage::boolean_type->get_left() );
    init_stmt_list->append( assign );

    // Create an empty wait statement and add it to the newly created
    // process as the last statement.
    wait = new IIR_WaitStatement;
    to_combine->copy_location( to_combine, wait );
    process->process_statement_part.append( wait );
    process->_wait_stmt_list.append( wait );
  }

#if COMBINE_DEBUG
  cerr << "Combining ";
  if ( NULL != to_combine->get_label() ) {
    cerr << *to_combine->get_label();
  }
  else {
    cerr << "UNNAMED";
  }
  cerr << " into ";
  if ( NULL != process->get_label() ) {
    cerr << *process->get_label();
  }
  else {
    cerr << "UNNAMED";
  }
  cerr << "\n";
#endif

  // Add to_combine's decls into the combined process
  decl = to_combine->process_declarative_part.first();
  while ( decl != NULL ) {
    process->process_declarative_part.append( decl );
    decl = to_combine->process_declarative_part.successor( decl );
  }

  // Wrap and add to_combine's sequential statements.
  IIR_VariableDeclaration *timevar;
  IIR_EventAttribute *attrib;
  IIR *condition = NULL;
  IIR_FunctionCall *nowfunc;
  IIR_AndOperator *andstmt;
  IIR_OrOperator *orstmt;

  // Grab the wait statements for convenience
  wait = (IIR_WaitStatement*)process->process_statement_part.last();
  newwait = (IIR_WaitStatement*)to_combine->process_statement_part.last();
  ASSERT( IIR_WAIT_STATEMENT == newwait->get_kind() );

  // deal with the sensitivity list
  switch ( newwait->sensitivity_list.size() ) {
  case 0:
    break;
  case 1:
    // The condition of the if is just <element>'ACTIVE
    attrib = new IIR_EventAttribute;
    to_combine->copy_location( to_combine, attrib );
    waitsig = (IIR_DesignatorExplicit*)newwait->sensitivity_list.first();
    attrib->_set_implicit_declaration( (IIR_Declaration*)waitsig->get_name() );
    attrib->set_prefix( waitsig->get_name() );
    condition = attrib->_rval_to_decl( StandardPackage::boolean_type );
    break;
  default:
    // The condition of the if is (a'ACTIVE or b'ACTIVE or ... )
    waitsig = (IIR_DesignatorExplicit*)newwait->sensitivity_list.first();
    attrib = new IIR_EventAttribute;
    to_combine->copy_location( to_combine, attrib );
    attrib->_set_implicit_declaration( (IIR_Declaration*)waitsig->get_name() );
    attrib->set_prefix( waitsig->get_name() );
    condition = attrib->_rval_to_decl( StandardPackage::boolean_type );

    waitsig = (IIR_DesignatorExplicit*)newwait->sensitivity_list.successor( waitsig );
    while ( NULL != waitsig ) {
      orstmt = new IIR_OrOperator;
      to_combine->copy_location( to_combine, orstmt );
      orstmt->set_subtype( StandardPackage::boolean_type );
      orstmt->set_left_operand( condition );
      attrib = new IIR_EventAttribute;
      to_combine->copy_location( to_combine, attrib );
      attrib->_set_implicit_declaration( (IIR_Declaration*)waitsig->get_name() );
      attrib->set_prefix( waitsig->get_name() );
      orstmt->set_right_operand( attrib->_rval_to_decl( StandardPackage::boolean_type ) );
      condition = orstmt;
      waitsig = (IIR_DesignatorExplicit*)newwait->sensitivity_list.successor( waitsig );
    }
    break;
  }

  // deal with the condition clause
  if ( NULL != newwait->get_condition_clause() ) {
    andstmt = new IIR_AndOperator;
    to_combine->copy_location( to_combine, andstmt );
    andstmt->set_subtype( StandardPackage::boolean_type );
    andstmt->set_left_operand( condition );
    andstmt->set_right_operand( newwait->get_condition_clause() );
    condition = andstmt;
  }

  // 'or' a call to (now = timevar) in with the rest of the
  // condition, if needed.
  if ( NULL != newwait->get_timeout_clause() ) {
    ostringstream varname;
    // create variable for timeout checking and put in declarative_part
    timevar = new IIR_VariableDeclaration;
    to_combine->copy_location( to_combine, timevar );
    varname << "timevar" << timevar;
    text = varname.str();
    timevar->set_declarator( IIR_Identifier::get( text, strlen(text)) );
    timevar->set_subtype( StandardPackage::time_type );
    timevar->set_value( newwait->get_timeout_clause() );
    timevar->_set_declarative_region( to_combine );
    to_combine->process_declarative_part.append( timevar );

    // Create function call to 'now' for time checking
    nowfunc = new IIR_FunctionCall;
    to_combine->copy_location( to_combine, nowfunc );
    nowfunc->set_implementation( (IIR_SubprogramDeclaration*)StandardPackage::now_decl );

    orstmt = new IIR_OrOperator;
    to_combine->copy_location( to_combine, orstmt );
    orstmt->set_subtype( StandardPackage::boolean_type );
    orstmt->set_left_operand( condition );
      
    // create call of equality_operator for (now = timevar)
    IIR_EqualityOperator *eqop = new IIR_EqualityOperator;
    to_combine->copy_location( to_combine, eqop );
    eqop->set_subtype( StandardPackage::boolean_type );
    eqop->set_left_operand( nowfunc );
    eqop->set_right_operand( timevar );

    orstmt->set_right_operand( eqop );
    condition = orstmt;
  }

  // create the new, process-body-enclosing if statement
  ifstmt = new IIR_IfStatement;
  to_combine->copy_location( to_combine, ifstmt );
  ifstmt->set_condition( condition );

  // The body of the new if_statement is the contents of the process,
  // minus the wait.  Also, add these statements to init_stmt_list to
  // handle simulation startup.
  stmtptr = to_combine->process_statement_part.first();
  while ( stmtptr != newwait) { // newwaitis the last statement!
    ifstmt->then_sequence.append( stmtptr );
    init_stmt_list->append( stmtptr );
    stmtptr = to_combine->process_statement_part.successor( stmtptr );
  }

  // If there's a timeout, create a statement to update timevar.
  // timevar = now + wait.timeout_clause
  if ( NULL != newwait->get_timeout_clause() ) {
    // Create the RHS of the assignment stmt
    IIR_AdditionOperator *addop = new IIR_AdditionOperator;
    to_combine->copy_location( to_combine, addop );
    addop->set_subtype( StandardPackage::time_type );
    addop->set_left_operand( nowfunc );
    addop->set_right_operand( newwait->get_timeout_clause() );

    // Create the assignment stmt itself and bolt it into the wrapped
    // process's body.
    IIR_VariableAssignmentStatement *assign;
    assign = new IIR_VariableAssignmentStatement;
    to_combine->copy_location( to_combine, assign );
    assign->set_target( timevar );
    assign->set_expression( addop );
    ifstmt->then_sequence.append( assign );
  }

  // Insert the wrapped process into the combined process body
  run_stmt_list->append( ifstmt );

  // Create trailing wait statement for the combined process.
  // Because of cloning and transmogrification, designatorExplicit's
  // that refer to the same signal can exist in different process's wait
  // list.  The following code only adds a signal to the wait list of
  // the new process if it's not already in there, as determined by the
  // name of the signal the designator refers to.  If wait lists get
  // very long, this could be fairly evil code--O(n^2)!
  waitsig = (IIR_DesignatorExplicit*)newwait->sensitivity_list.first();
  while ( NULL != waitsig ) {
    IIR *waitsigdecl;
    bool sig_already_in_list;
    IIR_DesignatorExplicit *listelem;
    IIR *ledecl;

    sig_already_in_list = false;
    ASSERT( waitsig->get_kind() == IIR_DESIGNATOR_EXPLICIT );
    waitsigdecl = waitsig->get_name();
    ASSERT( waitsigdecl->get_kind() == IIR_SIGNAL_DECLARATION 
	    || waitsigdecl->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION
	    || waitsigdecl->get_kind() == IIR_QUIET_ATTRIBUTE
	    || waitsigdecl->get_kind() == IIR_TRANSACTION_ATTRIBUTE
	    || waitsigdecl->get_kind() == IIR_STABLE_ATTRIBUTE
	    || waitsigdecl->get_kind() == IIR_INDEXED_NAME );

    listelem = (IIR_DesignatorExplicit*)wait->sensitivity_list.first();
    while ( listelem != NULL ) {
      ledecl = listelem->get_name();

      // First check to see if they're the same kind
      if ( waitsigdecl->get_kind() == ledecl->get_kind() ) {
	if ( ledecl->get_kind() == IIR_QUIET_ATTRIBUTE
	     || ledecl->get_kind() == IIR_STABLE_ATTRIBUTE
	     || ledecl->get_kind() == IIR_TRANSACTION_ATTRIBUTE ) {
	  // get the base signal of an attribute
	  waitsigdecl = ((IIR_Attribute*)waitsigdecl)->get_prefix();
	  ledecl = ((IIR_Attribute*)ledecl)->get_prefix();
	}
	else if ( ledecl->get_kind() == IIR_INDEXED_NAME ) {
	  IIR_IntegerLiteral *waitlit, *lelit;
	  waitlit = (IIR_IntegerLiteral*)((IIR_IndexedName*)waitsigdecl)->get_suffix();
	  lelit = (IIR_IntegerLiteral*)((IIR_IndexedName*)ledecl)->get_suffix();
	  ASSERT( waitlit->get_kind() == IIR_INTEGER_LITERAL );
	  ASSERT( lelit->get_kind() == IIR_INTEGER_LITERAL );

	  if ( waitlit->_get_value() == lelit->_get_value() ) {
	    // get the base signal of an indexed_name
	    waitsigdecl = ((IIR_IndexedName*)waitsigdecl)->get_prefix();
	    ledecl = ((IIR_IndexedName*)ledecl)->get_prefix();
	  }
	  else {
	    // the indices are different, so don't even bother comparing
	    // the names
	    listelem = (IIR_DesignatorExplicit*)wait->sensitivity_list.successor( listelem );
	    continue;
	  }
	}

	ASSERT( waitsigdecl->get_kind() == IIR_SIGNAL_DECLARATION
		|| waitsigdecl->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION );
	ASSERT( ledecl->get_kind() == IIR_SIGNAL_DECLARATION
		|| ledecl->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION );

	if (!IIR_TextLiteral::_cmp(((IIR_Declaration*)waitsigdecl)->get_declarator(), 
				   ((IIR_Declaration*)ledecl)->get_declarator() )) {
	  sig_already_in_list = true;
	  break;
	}
      }
      listelem = (IIR_DesignatorExplicit*)wait->sensitivity_list.successor( listelem );
    }

    if ( sig_already_in_list == false ) {
      wait->sensitivity_list.append( waitsig );
    }

    waitsig = (IIR_DesignatorExplicit*)newwait->sensitivity_list.successor( waitsig );
    }
}
#endif
