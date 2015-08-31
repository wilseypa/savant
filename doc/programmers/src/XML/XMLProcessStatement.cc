
// Copyright (c) 2004 The University of Cincinnati.  
 // All rights reserved.
 // 
 // UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
 // SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 // IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 // OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 // LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
 // DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 // 
 // By using or copying this Software, Licensee agrees to abide by the
 // intellectual property laws, and all other applicable laws of the U.S.,
 // and the terms of this license.
 // 
 // You may modify, distribute, and use the software contained in this
 // package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
 // version 2, June 1991. A copy of this license agreement can be found in
 // the file "LGPL", distributed with this archive.
 // 
 // --------------------------------------------------------------------------

#include "XmlFile.hh"
#include "XMLDeclarationList.hh"
#include "XMLSequentialStatementList.hh"
#include "XMLProcessStatement.hh"
#include "XMLDeclarationList.hh"
#include "XMLSequentialStatementList.hh"

XMLProcessStatement::XMLProcessStatement() {}
XMLProcessStatement::~XMLProcessStatement() {}

XMLDeclarationList *
XMLProcessStatement::_get_process_declarative_part() {
  return dynamic_cast<XMLDeclarationList *>(get_process_declarative_part());
}
XMLSequentialStatementList *
XMLProcessStatement::_get_process_statement_part() {
  return dynamic_cast<XMLSequentialStatementList *>(get_process_statement_part());
}

void
XMLProcessStatement::xmlGeneration(XmlFile &file) {
  if (!bVisited) {
    file.openScope(get_kind_text());

    // Process the variables
    if (get_process_declarative_part()->size() > 0) {
      file.openScope("Declarations");
      _get_process_declarative_part()->xmlGeneration(file);
      file.closeScope();
    }

    if (get_process_statement_part()->size() > 0) {
      file.openScope("Statements");
      _get_process_statement_part()->xmlGeneration(file);
      file.closeScope();
    }

    file.closeScope();
  }
}
