
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
#include "XMLGenericList.hh"
#include "XMLAssociationList.hh"
#include "XMLPortList.hh"
#include "XMLAssociationList.hh"
#include "XMLDeclarationList.hh"
#include "XMLArchitectureStatementList.hh"
#include "XMLBlockStatement.hh"
#include "XMLGenericList.hh"
#include "XMLAssociationList.hh"
#include "XMLPortList.hh"
#include "XMLAssociationList.hh"
#include "XMLDeclarationList.hh"
#include "XMLArchitectureStatementList.hh"

XMLBlockStatement::XMLBlockStatement() {}
XMLBlockStatement::~XMLBlockStatement() {}

XMLGenericList *
XMLBlockStatement::_get_generic_clause() {
  return dynamic_cast<XMLGenericList *>(get_generic_clause());
}
XMLAssociationList *
XMLBlockStatement::_get_generic_map_aspect() {
  return dynamic_cast<XMLAssociationList *>(get_generic_map_aspect());
}
XMLPortList *
XMLBlockStatement::_get_port_clause() {
  return dynamic_cast<XMLPortList *>(get_port_clause());
}
XMLAssociationList *
XMLBlockStatement::_get_port_map_aspect() {
  return dynamic_cast<XMLAssociationList *>(get_port_map_aspect());
}
XMLDeclarationList *
XMLBlockStatement::_get_block_declarative_part() {
  return dynamic_cast<XMLDeclarationList *>(get_block_declarative_part());
}
XMLArchitectureStatementList *
XMLBlockStatement::_get_block_statement_part() {
  return dynamic_cast<XMLArchitectureStatementList *>(get_block_statement_part());
}

void
XMLBlockStatement::xmlGeneration(XmlFile &file) {
  if (!bVisited) {
    // Process the node itself
    XML::xmlGeneration(file);

    // Process the variables
    _get_generic_clause()->xmlGeneration(file);
    _get_generic_map_aspect()->xmlGeneration(file);
    _get_port_clause()->xmlGeneration(file);
    _get_port_map_aspect()->xmlGeneration(file);
    _get_block_declarative_part()->xmlGeneration(file);
    _get_block_statement_part()->xmlGeneration(file);
  }
}
