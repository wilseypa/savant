
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
#include "XMLPortList.hh"
#include "XMLAttributeSpecificationList.hh"
#include "XMLComponentDeclaration.hh"
#include "XMLGenericList.hh"
#include "XMLPortList.hh"
#include "XMLAttributeSpecificationList.hh"

XMLComponentDeclaration::XMLComponentDeclaration() {}
XMLComponentDeclaration::~XMLComponentDeclaration() {}

XMLGenericList *
XMLComponentDeclaration::_get_local_generic_clause() {
  return dynamic_cast<XMLGenericList *>(get_local_generic_clause());
}
XMLPortList *
XMLComponentDeclaration::_get_local_port_clause() {
  return dynamic_cast<XMLPortList *>(get_local_port_clause());
}
XMLAttributeSpecificationList *
XMLComponentDeclaration::_get_attributes() {
  return dynamic_cast<XMLAttributeSpecificationList *>(get_attributes());
}

void
XMLComponentDeclaration::xmlGeneration(XmlFile &file) {
  if (!bVisited) {
    // Process the node itself
    XML::xmlGeneration(file);

    // Process the variables
    _get_local_generic_clause()->xmlGeneration(file);
    _get_local_port_clause()->xmlGeneration(file);
    _get_attributes()->xmlGeneration(file);
  }
}
