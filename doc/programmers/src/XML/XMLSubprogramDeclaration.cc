
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
#include "XMLInterfaceList.hh"
#include "XMLDeclarationList.hh"
#include "XMLSequentialStatementList.hh"
#include "XMLAttributeSpecificationList.hh"
#include "XMLSubprogramDeclaration.hh"
#include "XMLInterfaceList.hh"
#include "XMLDeclarationList.hh"
#include "XMLSequentialStatementList.hh"
#include "XMLAttributeSpecificationList.hh"

XMLSubprogramDeclaration::XMLSubprogramDeclaration() {}
XMLSubprogramDeclaration::~XMLSubprogramDeclaration() {}

XMLInterfaceList *
XMLSubprogramDeclaration::_get_interface_declarations() {
  return dynamic_cast<XMLInterfaceList *>(get_interface_declarations());
}
XMLDeclarationList *
XMLSubprogramDeclaration::_get_subprogram_declarations() {
  return dynamic_cast<XMLDeclarationList *>(get_subprogram_declarations());
}
XMLSequentialStatementList *
XMLSubprogramDeclaration::_get_subprogram_body() {
  return dynamic_cast<XMLSequentialStatementList *>(get_subprogram_body());
}
XMLAttributeSpecificationList *
XMLSubprogramDeclaration::_get_attributes() {
  return dynamic_cast<XMLAttributeSpecificationList *>(get_attributes());
}

void
XMLSubprogramDeclaration::xmlGeneration(XmlFile &file) {
  if (!bVisited) {
    // Process the node itself
    XML::xmlGeneration(file);

    // Process the variables
    _get_interface_declarations()->xmlGeneration(file);
    _get_subprogram_declarations()->xmlGeneration(file);
    _get_subprogram_body()->xmlGeneration(file);
    _get_attributes()->xmlGeneration(file);
  }
}
