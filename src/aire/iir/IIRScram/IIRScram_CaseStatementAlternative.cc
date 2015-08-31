
// Copyright (c) 1996-2002 The University of Cincinnati.  
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
//          Narayanan Thondugulam
//          Krishnan Subramani  
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram.hh"
#include "IIRScram_CaseStatementAlternative.hh"
#include "IIRScram_SequentialStatement.hh"
#include "IIRScram_SequentialStatementList.hh"

IIRScram_CaseStatementAlternative::IIRScram_CaseStatementAlternative() {
  set_sequence_of_statements(new IIRScram_SequentialStatementList());
}

IIRScram_CaseStatementAlternative::~IIRScram_CaseStatementAlternative() {
  //Release the list memory
  delete get_sequence_of_statements();
}

IIR_Boolean 
IIRScram_CaseStatementAlternative::_type_check_return_statements( savant::set<IIRScram_TypeDefinition> *context_set, 
			       IIRScram_SubprogramDeclaration *subprogram_decl ){
  IIR_Boolean retval = FALSE;

  retval = IIRScram_SequentialStatement::
    _type_check_return_statements(context_set,
				  _get_sequence_of_statements(),
				  subprogram_decl );
  return retval;
}

void
IIRScram_CaseStatementAlternative::_clone(IIRScram* cl) {
  IIRScram_CaseStatementAlternative *clone = dynamic_cast<IIRScram_CaseStatementAlternative*>(cl);
  IIRScram::_clone(clone);

  IIRScram_SequentialStatement *seqclone, *stmt = dynamic_cast<IIRScram_SequentialStatement *>(get_sequence_of_statements()->first());
  while (stmt != NULL) {
    seqclone = dynamic_cast<IIRScram_SequentialStatement*>(stmt->_clone());
    clone->get_sequence_of_statements()->append(seqclone);
    stmt = dynamic_cast<IIRScram_SequentialStatement *>(get_sequence_of_statements()->successor(stmt));
  }
}


IIRScram*
IIRScram_CaseStatementAlternative::_clone() {
  _report_undefined_scram_fn("_clone()");
  return NULL;
}


IIRScram_SequentialStatementList *
IIRScram_CaseStatementAlternative::_get_sequence_of_statements() {
  return dynamic_cast<IIRScram_SequentialStatementList *>(get_sequence_of_statements());
}
