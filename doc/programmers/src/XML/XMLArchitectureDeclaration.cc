
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

#include "XMLArchitectureStatementList.hh"
#include "XMLArchitectureDeclaration.hh"
#include "XMLDeclarationList.hh"
#include "XMLEntityDeclaration.hh"
#include "XMLTextLiteral.hh"

XMLArchitectureDeclaration::XMLArchitectureDeclaration() {}
XMLArchitectureDeclaration::~XMLArchitectureDeclaration() {}

XMLDeclarationList *
XMLArchitectureDeclaration::_get_architecture_declarative_part() {
  return dynamic_cast<XMLDeclarationList *>(get_architecture_declarative_part());
}
XMLArchitectureStatementList *
XMLArchitectureDeclaration::_get_architecture_statement_part() {
  return dynamic_cast<XMLArchitectureStatementList *>(get_architecture_statement_part());
}

void
XMLArchitectureDeclaration::xmlGeneration(XmlFile &file) {
  if (!bVisited) {
    // Process the node itself
    string content;
    content = "architecture ";
    content += get_declarator()->convert_to_string();
    content += " of ";
    content += get_entity()->get_declarator()->convert_to_string();
    content += " is";
    file.openScope(get_kind_text(), content);

    //   Process the variables
    if (get_architecture_declarative_part()->size() > 0) {
      file.openScope("Declarations");
      _get_architecture_declarative_part()->xmlGeneration(file);
      file.closeScope();
    }

    if (get_architecture_statement_part()->size() > 0) {
      file.openScope("Concurrent Statements");
      _get_architecture_statement_part()->xmlGeneration(file);
      file.closeScope();
    }

    file.closeScope();
  }
}
