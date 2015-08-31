#ifndef XMLCONFIGURATIONSPECIFICATION_HH
#define XMLCONFIGURATIONSPECIFICATION_HH

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

#include "savant/IIRBase_ConfigurationSpecification.hh"
#include "XMLDeclaration.hh"

class XmlFile;
class XMLDesignatorList;
class XMLAssociationList;
class XMLAssociationList;

class XMLConfigurationSpecification : public virtual IIRBase_ConfigurationSpecification, public virtual XMLDeclaration {
public:
  XMLConfigurationSpecification();
  ~XMLConfigurationSpecification();

  // AIRE function wrappers
  XMLDesignatorList * _get_instantiation_list();
  XMLAssociationList * _get_generic_map_aspect();
  XMLAssociationList * _get_port_map_aspect();

  void xmlGeneration(XmlFile &file);
};
#endif
