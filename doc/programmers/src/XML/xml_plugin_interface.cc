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

#include "xml_plugin_interface.hh"
#include "xml_plugin_class_factory.hh"
#include "savant/IIRBase.hh"

#include "XMLDesignFile.hh"

IIR*
xml_plugin_interface::process_tree(IIR *old_tree, int argc, char *argv[]) {
  plugin_class_factory   *factory = new xml_plugin_class_factory();
  IIR                    *new_tree = NULL;

  // Transmute the AIRE tree into a new tree containing the plugin nodes
  new_tree = dynamic_cast<IIRBase *>(old_tree)->convert_tree(factory);

  // Start XML generation
  dynamic_cast<XMLDesignFile *>(new_tree)->xmlGeneration();

  // Return the newly generated tree to the compiler
  return new_tree;
}

/** @return a string saying what the module is for. */
const string
xml_plugin_interface::getPluginType() const {
  return string("Savant AIRE Plugin");
}

/** @return the name of the plugin. */
const string
xml_plugin_interface::getPluginName() const {
  return string("XML Plugin");
}

extern "C" {
  // Used by libtool to create a new version of the module
  void *allocatelibxmlplugin() {
    return new xml_plugin_interface();
  }
}
