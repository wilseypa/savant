
// Copyright (c) 1996-2008 The University of Cincinnati.  
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

#include "IIRBase_CaseStatementAlternativeByOthers.hh"
#include "IIR_SequentialStatementList.hh"

IIRBase_CaseStatementAlternativeByOthers::IIRBase_CaseStatementAlternativeByOthers(){}
IIRBase_CaseStatementAlternativeByOthers::~IIRBase_CaseStatementAlternativeByOthers(){}

ostream &
IIRBase_CaseStatementAlternativeByOthers::print( ostream &os ){
  os << "others ";
  return os;
}

void 
IIRBase_CaseStatementAlternativeByOthers::publish_vhdl(ostream &vhdl_out) {
  vhdl_out << "when others\n";

  // In selected signal assignment statements, the sequence_of_statements
  // list is empty.  In case statements the sequence_of_statements must be
  // published.  If the sequence of statements is empty, the analyzer must
  // insert a null statement into the statement list or else republishing
  // the vhdl will come out incorrectly (without the "=>").
  if( get_sequence_of_statements()->first() != NULL ){
    vhdl_out << " =>\n";
    get_sequence_of_statements()->publish_vhdl(vhdl_out);
  }
}
