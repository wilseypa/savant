
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
#include "XMLDeclarationList.hh"
#include "XMLDesignUnitList.hh"
#include "XMLEntityDeclaration.hh"
#include "XMLGenericList.hh"
#include "XMLPortList.hh"
#include "XMLTextLiteral.hh"

XMLEntityDeclaration::XMLEntityDeclaration() {}
XMLEntityDeclaration::~XMLEntityDeclaration() {}

XMLGenericList *
XMLEntityDeclaration::_get_generic_clause() {
  return dynamic_cast<XMLGenericList *>(get_generic_clause());
}
XMLPortList *
XMLEntityDeclaration::_get_port_clause() {
  return dynamic_cast<XMLPortList *>(get_port_clause());
}
XMLDeclarationList *
XMLEntityDeclaration::_get_entity_declarative_part() {
  return dynamic_cast<XMLDeclarationList *>(get_entity_declarative_part());
}
XMLArchitectureStatementList *
XMLEntityDeclaration::_get_entity_statement_part() {
  return dynamic_cast<XMLArchitectureStatementList *>(get_entity_statement_part());
}
XMLDesignUnitList *
XMLEntityDeclaration::_get_architectures() {
  return dynamic_cast<XMLDesignUnitList *>(get_architectures());
}

void
XMLEntityDeclaration::xmlGeneration(XmlFile &file) {
  if (!bVisited) {
    // Process the node itself   
    string content;
    content = "entity ";
    content += get_declarator()->convert_to_string();
    content += " is";
    file.openScope(get_kind_text(), content);
    
    //   Process the variables
    if (get_generic_clause()->size() > 0) {
      file.openScope("Generic");
      _get_generic_clause()->xmlGeneration(file);
      file.closeScope();
    }

    if (get_port_clause()->size() > 0) {
      file.openScope("Port");
      _get_port_clause()->xmlGeneration(file);
      file.closeScope();
    }

    if (get_entity_declarative_part()->size() > 0) {
      file.openScope("Declarations");
      _get_entity_declarative_part()->xmlGeneration(file);
      file.closeScope();
    }

    if (get_entity_statement_part()->size() > 0) {
      file.openScope("Statements");
      _get_entity_statement_part()->xmlGeneration(file);
      file.closeScope();
    }

    if (get_architectures()->size() > 0) {
      file.openScope("Architectures");
      _get_architectures()->xmlGeneration(file);
      file.closeScope();
    }

    file.closeScope();
  }
}
