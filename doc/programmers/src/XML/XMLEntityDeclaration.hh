#ifndef XMLENTITYDECLARATION_HH
#define XMLENTITYDECLARATION_HH

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

#include "savant/IIRBase_EntityDeclaration.hh"
#include "XMLLibraryUnit.hh"

class XmlFile;
class XMLGenericList;
class XMLPortList;
class XMLDeclarationList;
class XMLArchitectureStatementList;
class XMLDesignUnitList;

class XMLEntityDeclaration : public virtual IIRBase_EntityDeclaration, public virtual XMLLibraryUnit {
public:
  XMLEntityDeclaration();
  ~XMLEntityDeclaration();

  // AIRE function wrappers
  XMLGenericList * _get_generic_clause();
  XMLPortList * _get_port_clause();
  XMLDeclarationList * _get_entity_declarative_part();
  XMLArchitectureStatementList * _get_entity_statement_part();
  XMLDesignUnitList * _get_architectures();

  void xmlGeneration(XmlFile &file);
};
#endif
