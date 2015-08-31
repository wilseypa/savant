#ifndef XMLBRANCHQUANTITYDECLARATION_HH
#define XMLBRANCHQUANTITYDECLARATION_HH

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

#include "savant/IIRBase_BranchQuantityDeclaration.hh"
#include "XMLQuantityDeclaration.hh"

class XmlFile;
class XMLDesignatorList;
class XMLDesignatorList;

class XMLBranchQuantityDeclaration : public virtual IIRBase_BranchQuantityDeclaration, public virtual XMLQuantityDeclaration {
public:
  XMLBranchQuantityDeclaration();
  ~XMLBranchQuantityDeclaration();

  // AIRE function wrappers
  XMLDesignatorList * _get_across_aspect_identifier_list();
  XMLDesignatorList * _get_through_aspect_designator_list();

  void xmlGeneration(XmlFile &file);
};
#endif
