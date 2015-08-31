
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
#include "XMLPackageBodyDeclaration.hh"
#include "XMLDeclarationList.hh"
#include "savant/IIR_TextLiteral.hh"

XMLPackageBodyDeclaration::XMLPackageBodyDeclaration() {}
XMLPackageBodyDeclaration::~XMLPackageBodyDeclaration() {}

XMLDeclarationList *
XMLPackageBodyDeclaration::_get_package_declarative_part() {
  return dynamic_cast<XMLDeclarationList *>(get_package_declarative_part());
}

void
XMLPackageBodyDeclaration::xmlGeneration(XmlFile &file) {
  if (!bVisited) {
    // Process the node itself
    string content;
    content = "package body ";
    content += get_declarator()->convert_to_string();
    content += " is";
    file.openScope(get_kind_text(), content);
    //   Process the variables
    _get_package_declarative_part()->xmlGeneration(file);

    file.closeScope();
  }
}
