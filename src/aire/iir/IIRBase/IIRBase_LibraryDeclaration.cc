
// Copyright (c) 1996-1999 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
// DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.


// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     mal@ece.uc.edu

//---------------------------------------------------------------------------
#include "library_manager.hh"
#include "savant.hh"
#include "set.hh"
#include "IIRBase_LibraryDeclaration.hh"
#include "IIR_ConfigurationDeclaration.hh"
#include "IIR_DesignFile.hh"
#include "IIR_EntityDeclaration.hh"
#include "IIR_LibraryUnitList.hh"
#include "IIR_Name.hh"
#include "IIR_PackageDeclaration.hh"

#include <clutils/FileManager.h>




IIRBase_LibraryDeclaration::IIRBase_LibraryDeclaration()  :
  primary_units(0),
  path_to_directory( "" ){}

IIRBase_LibraryDeclaration::~IIRBase_LibraryDeclaration() {
  delete primary_units;
  primary_units = 0;
}

// List Accessor(s)
IIR_LibraryUnitList *
IIRBase_LibraryDeclaration::get_primary_units() {
  ASSERT(primary_units != NULL);
  return primary_units;
}

void
IIRBase_LibraryDeclaration::set_primary_units(IIR_LibraryUnitList *new_primary_units) {
  ASSERT(new_primary_units != NULL);
  delete primary_units;
  primary_units = new_primary_units;
}

IIR *
IIRBase_LibraryDeclaration::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_LibraryDeclaration *new_node = dynamic_cast<IIRBase_LibraryDeclaration *>(IIRBase_Declaration::convert_tree(factory));

  // Process the variables
  new_node->primary_units = dynamic_cast<IIR_LibraryUnitList *>(convert_node(primary_units, factory));
  new_node->path_to_directory = path_to_directory;

  return new_node;
}

void 
IIRBase_LibraryDeclaration::set_path_to_directory( const string &new_path ){ 
  path_to_directory = FileManager::instance()->getRealPath( new_path );
}

const string &
IIRBase_LibraryDeclaration::get_path_to_directory(){
  return path_to_directory;
}

bool
IIRBase_LibraryDeclaration::is_work_library(){
  ASSERT( get_design_file() != 0 );
  return get_design_file()->get_work_library() == this;
}


IIR_Declaration::declaration_type 
IIRBase_LibraryDeclaration::get_declaration_type(){
   return LIBRARY;
}

savant::set<IIR_Declaration> *
IIRBase_LibraryDeclaration::find_declarations( IIR_Name *to_find){
  savant::set<IIR_Declaration> *retval = new savant::set<IIR_Declaration>;

  IIR_EntityDeclaration *entity_decl = NULL;
  IIR_PackageDeclaration *package_decl = NULL; 
  IIR_ConfigurationDeclaration *configuration_decl = NULL;  
  
  savant::set<IIR_Declaration> *unit_decls = get_primary_units()->find_declarations( to_find );
  if( unit_decls != NULL ){
    retval->add( unit_decls );
  }

  entity_decl = 
    dynamic_cast<IIR_EntityDeclaration *>(library_manager::instance()->lookup_entity( FALSE,
                                                                                      to_find,
                                                                                      dynamic_cast<IIR_LibraryDeclaration *>(this),
                                                                                      get_design_file()->get_standard_package(),
                                                                                      get_design_file()->get_class_factory()));
  
  if( entity_decl != NULL ){
    retval->add( entity_decl );
  }

  package_decl = 
    dynamic_cast<IIR_PackageDeclaration *>(library_manager::instance()->lookup_package( FALSE,
                                                                                        to_find,
                                                                                        dynamic_cast<IIR_LibraryDeclaration *>(this),
                                                                                        get_design_file()->get_standard_package(),
                                                                                        get_design_file()->get_class_factory()));

  if( package_decl != NULL ){
    retval->add( package_decl );
  }
  
  configuration_decl = 
    dynamic_cast<IIR_ConfigurationDeclaration *>(library_manager::instance()->lookup_configuration( FALSE, 
                                                                                                    to_find, 
                                                                                                    dynamic_cast<IIR_LibraryDeclaration *>(this),
                                                                                                    get_design_file()->get_standard_package(),
                                                                                                    get_design_file()->get_class_factory()));

  if( configuration_decl != NULL ){
    retval->add( configuration_decl );
  }

  if( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }
  
  return retval;
}

void 
IIRBase_LibraryDeclaration::publish_vhdl_decl( ostream &os ){
  os << "library ";
  publish_vhdl( os );
}
