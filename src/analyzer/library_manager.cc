
// Copyright (c) 1996-2003 The University of Cincinnati.
// All rights reserved. 

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE
// OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

// Author: Radharamanan Radhakrishnan  
//         Dale E. Martin              dmartin@cliftonlabs.com
//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "savant.hh"
#include <clutils/FileManager.h>
#include "library_manager.hh"
#include "scram.hh"
#include "set.hh"
#include "symbol_table.hh"
#include "ScramStandardPackage.hh"
#include "scram_plugin_class_factory.hh"
#include "error_func.hh"
#include "symbol_lookup.hh"
#include "constraint_functors.hh"

#include <cstring>
#include <errno.h>
#include <vector>
#include <string>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sstream>

using std::ostringstream;

#include "IIR_IndexedName.hh"
#include "IIR_LibraryUnitList.hh"
#include "IIR_SelectedName.hh"
#include "IIR_ArchitectureDeclaration.hh"
#include "IIR_ConfigurationDeclaration.hh"
#include "IIR_DesignFile.hh"
#include "IIR_PackageDeclaration.hh"
#include "IIR_PackageBodyDeclaration.hh"
#include "IIR_SimpleName.hh"
#include "IIRBase_EntityDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_LibraryDeclaration.hh"
#include "IIRScram_LibraryUnit.hh"
#include "IIRScram_Name.hh"

// These should be replaced with something like an "os_interface_manager"

extern bool verbose_output;

const string &
library_manager::get_library_suffix(){
  static const string library_suffix = "._savant_lib";
  return library_suffix;
}

const string &
library_manager::get_entity_suffix(){
  static const string entity_suffix = "_entity.vhdl";
  return entity_suffix;
}

const string &
library_manager::get_configuration_suffix(){
  static const string config_suffix = "_config.vhdl";
  return config_suffix;
}

const string &
library_manager::get_package_suffix(){
  static const string package_suffix = "_package.vhdl";
  return package_suffix;
}

const string &
library_manager::get_package_body_suffix(){
  static const string package_body_suffix = "_package_body.vhdl";
  return package_body_suffix;
}

const string &
library_manager::get_secondary_units_suffix(){
  static const string secondary_units_suffix = "_secondary_units";
  return secondary_units_suffix;
}

library_manager *
library_manager::instance(){
  static library_manager *singleton = new library_manager();
  return singleton;
}

library_manager::library_manager() :
  my_symbol_table( new symbol_lookup() ),
  libraries( new savant::set<IIR_LibraryDeclaration>() ) {
}

void
library_manager::init_std_library(StandardPackage *package) {
  static IIR_Boolean        initialized = false;

  // This stuff sets up the standard library
  if (initialized == false) {
    IIR_LibraryDeclaration *std_library = dynamic_cast<IIR_LibraryDeclaration *>(package->get_std_decl());
    ASSERT( std_library != NULL );
    const string std_dir = find_library_directory( std_library->get_declarator(), true );
    std_library->set_path_to_directory( std_dir );
    libraries->add( std_library );
    initialized = true;
  }
}

library_manager::~library_manager(){
  delete libraries;
  libraries = NULL;
  delete my_symbol_table;
  my_symbol_table = NULL;
}

bool
library_manager::check_root_dir( const string root_dir, bool complain ){
  const string file_name = "textio_package.vhdl";
  string full_path_to_file;
  const string sep = FileManager::instance()->getDirectorySeparator();
  ostringstream err;

  bool error = false;

  if( FileManager::instance()->checkFileStatus( root_dir, 
						FileManager::DIRECTORY ) != FileManager::OK ){
    if( complain == true ){
      err << "|" << root_dir << "| isn't a valid directory.";
    }
    error = true;
  }
  
  if( error == false ){
    full_path_to_file = 
      root_dir + sep + "lib" + sep + "std" + get_library_suffix()
      + sep + file_name;
    
    if( FileManager::instance()->checkFileStatus( full_path_to_file, 
						  FileManager::REGULAR_FILE ) != FileManager::OK ){      
      if( complain == true ){
	err << "Directory |" << root_dir << "| doesn't appear to contain the file |" 
	    << full_path_to_file  << "| which should be in the Savant library directory.";
      }
      error = true;
    }
  }
  
  if( error == true && complain == true ){
    report_error( err.str(), -1, NULL, FATAL );
  }

  return !error;
}


const string
library_manager::check_default_directories( bool complain ){
  string retval;
  const string sep = FileManager::instance()->getDirectorySeparator();

  vector<string> my_lib_dirs( FileManager::instance()->getLibraryDirectories() );
  // Now we'll add our install directory
  my_lib_dirs.push_back( BUILD_SAVANTROOT );
  for( vector<string>::iterator current = my_lib_dirs.begin();
       current != my_lib_dirs.end();
       current++ ){
    const string full_path = *current + sep + "savant" + sep;
    if( check_root_dir( full_path, complain ) == true ){
      retval = full_path;
      break;
    }
  }

  return retval;
}

const string
library_manager::get_savant_root_directory(){
  static string savant_root_dir = "";
  string retval = "";
  
  if( savant_root_dir != "" ){
    retval = savant_root_dir;
  }
  else{
    retval = check_environment_variable( false );
    if( retval == "" ){
      retval = check_default_directories( false );
    }

    if( retval == "" ){
      ostringstream err1, err2;
      err1 << "Unable to locate savant library directory.  Currently, scram will:\n"
	   << "1) Check the SAVANTROOT environment variable.  Problems with this method"
	   << " included:";
      report_error( err1.str(), -1, NULL, FATAL );
      check_environment_variable( true );
      err2 << "2) Looking in a list of standard directories. Problems with this method were:";
      report_error( err2.str(), -1, NULL, FATAL );
      check_default_directories( true );

      exit( -1 );
    }
    else{
      savant_root_dir = retval;
    }
  }

  return retval;
}


const string
library_manager::check_environment_variable( bool complain ){
  string retval;
  const string varname = "SAVANTROOT";
  const string sep = FileManager::instance()->getDirectorySeparator();
  ostringstream err;

  bool error = false;
  const char *value = getenv( varname.c_str() );
  if( value != 0 ){
    const string savant_root_var = string(value);
    if( check_root_dir( savant_root_var, complain ) == true ){
      retval = savant_root_var;
    }
    else{
      error = true;
    }
  }
  else{
    if( complain == true ){
      cerr << "SAVANTROOT is not defined." << endl;
    }
    error = true;
  }

  
  if( error == true && complain == true ){
    // Then we're going to need to print out a rather verbose error message
    // explaining to the user how they should have set the environment variable.
    int uid = getuid();
    struct passwd *pwd_entry;
    pwd_entry = getpwuid( uid );
    string name, dir;
    if( pwd_entry == NULL ){
      name = "johndoe";
      name = "/home/johndoe";
    }
    else{
      name = pwd_entry->pw_name; 
      dir = pwd_entry->pw_dir;
    }
    
    err << "  If you installed Savant in a \"non-standard\" place, please set SAVANTROOT"
	<< " to the top directory of the savant hierarchy. "
	<< "For example, if you have installed savant in your home "
	<< "directory, you might issue one of the following commands to "
	<< "to set this variable:\n"
	<< "setenv SAVANTROOT " << dir << sep << "savant\n"
	<< "or\n"
	<< "SAVANTROOT=" << dir << sep << "savant; export SAVANTROOT\n"
	<< "See the man page or other documentation for your shell for details.";
      
    endpwent();
        
    report_error( err.str(), -1, NULL, FATAL );
  }
  
  return retval;
}

// int
// library_manager::create_work_dir(){
//   register int error_flag = 0;

//   error_flag = FileManager::instance()->make_directory( get_work_dir_name() );

//   return error_flag;
// }

// create the design library as specified by the lib name

IIR_LibraryDeclaration *
library_manager::create_design_library( const string &physical_library_name,
					plugin_class_factory *factory ){
  const string fullname = physical_library_name + get_library_suffix();
  FileManager::instance()->makeDirectory( fullname );

  IIR_LibraryDeclaration *retval = factory->new_IIR_LibraryDeclaration();
  // TODO:  Remove SCRAM reference
  ASSERT (retval != NULL);
  retval->set_declarator( IIRScram_Identifier::get( physical_library_name, factory ) );
  retval->set_path_to_directory( fullname );
  libraries->add( retval );

  return retval;
}

// this methods gets a library unit and depending on the type does the
// appropriate name mangling and returns a handle to a ostream.
ostream *
library_manager::get_file_handle( IIR_LibraryUnit *lib_unit ){
  IIR_LibraryDeclaration *work_library = lib_unit->get_library();
  ASSERT( work_library != 0 );
  ASSERT( lib_unit != 0 );
  const string library_dir = work_library->get_path_to_directory();
  
  string file_name;
  switch( lib_unit->get_kind() ){
  case IIR_ENTITY_DECLARATION:{
    file_name = build_entity_file_name( lib_unit->get_declarator(), library_dir );
    break;
  }

 case IIR_CONFIGURATION_DECLARATION:{
    file_name = build_configuration_file_name( lib_unit->get_declarator(), library_dir );
    break;   
  }

  case IIR_PACKAGE_DECLARATION:{
    file_name = build_package_file_name( lib_unit->get_declarator(), library_dir );
    break;
  }

  case IIR_ARCHITECTURE_DECLARATION:{
    IIR_ArchitectureDeclaration *as_arch = dynamic_cast<IIR_ArchitectureDeclaration*>(lib_unit);
    file_name = build_arch_file_name( as_arch );
    break;
  }

  case IIR_PACKAGE_BODY_DECLARATION:{
    file_name = build_package_body_file_name( lib_unit->get_declarator(), work_library );
    break;
  }

  default:{
    ostringstream err;
    err << "Internal error in library_manager::setOutputFile - don't know what to do"
	<< " with kind " << lib_unit->get_kind_text();
    abort();
    break;
  }
  }

  return new ofstream( file_name.c_str() );
}

// calls publish_vhdl_decl so that analyzed design units can be stored in
// the work directory
void
library_manager::parse_into_work_dir( IIR_LibraryUnit *unit_to_publish ){
  ASSERT( unit_to_publish != 0 );

  my_symbol_table->lookup_add( unit_to_publish );

  create_directories( unit_to_publish );
  ostream *file_handle = get_file_handle( unit_to_publish );
  if( file_handle  && file_handle->good() ){
    // TODO: Remove Scram
    dynamic_cast<IIRBase_LibraryUnit *>(unit_to_publish)->publish_vhdl_decl( *file_handle );
    file_handle->flush();
    delete file_handle;
  }
  else {
    perror( string( "Error trying to publish unit |" +
		    dynamic_cast<IIRScram_TextLiteral *>(unit_to_publish->get_declarator())->convert_to_string() + "|" ).c_str() );
  }
}
			 
IIR_LibraryUnit *
library_manager::parse_primary_unit( IIR_LibraryDeclaration     *lib_decl,
                                     const string               path_to_file,
                                     StandardPackage            *package,
                                     plugin_class_factory    *factory) { 
  
  // So, the path sent to us is a relative path and doesn't include the savant lib
  // directory.  If we don't find the file, we'll need to look in the SAVANT root
  // directory.  (Eventually we'll need to look in a user defined list of other 
  // possibilities.)
  IIR_LibraryUnit *retval = NULL;
  string current_path = path_to_file;
  if( FileManager::instance()->checkFileStatus( current_path,
						FileManager::REGULAR_FILE ) != FileManager::OK ){
    current_path = get_savant_root_directory() + "/lib/" + path_to_file;
    if( FileManager::instance()->checkFileStatus( current_path,
						  FileManager::REGULAR_FILE ) != FileManager::OK ){
      current_path = "";
    }
  }
  
  if( current_path != "" ){
    retval = parse_file( current_path, lib_decl, package, factory);
  
    if( retval != NULL ){
      my_symbol_table->lookup_add( retval );
    }
  }
  
  return retval;
}

IIR_LibraryUnit *
library_manager::parse_primary_unit( IIR_LibraryDeclaration     *lib_decl,
				     IIR_Name                   *name,
				     IIR_Kind                   unitType,
                                     StandardPackage            *package,
                                     plugin_class_factory       *factory,
				     IIR_Boolean                complain_on_error){
  ASSERT( lib_decl != 0 );
  ASSERT( name != 0 );

  IIR_LibraryUnit *retval = NULL;
  if( name->get_kind() == IIR_SIMPLE_NAME ){
    // TODO: Remove scram
    IIR_SimpleName *as_simple_name = dynamic_cast<IIR_SimpleName *>(name);
    const string path_to_file = build_entity_file_name( as_simple_name->get_prefix_string(),
      dynamic_cast<IIR_LibraryDeclaration *>(lib_decl)->get_path_to_directory() );

    retval = parse_primary_unit( lib_decl, path_to_file, package, factory );
  }
  else if( name->get_kind() == IIR_SELECTED_NAME ){
    // TODO: Remove Scram
    IIR_SelectedName *as_selected_name = dynamic_cast<IIR_SelectedName *>(name);
    ASSERT( as_selected_name->get_prefix()->get_kind() == IIR_SIMPLE_NAME );
    ASSERT( as_selected_name->get_suffix()->get_kind() == IIR_SIMPLE_NAME );
    
    IIR_TextLiteral *logical_lib_name = as_selected_name->get_prefix_string();

    //  Find the library declaration - it has the mapping to the 
    // library directory in it.
    IIR_LibraryDeclaration *lib_decl = find_library( logical_lib_name, factory );
    if( lib_decl != NULL ){
      // TODO: Remove Scram
      const string lib_dir_name = lib_decl->get_path_to_directory();
      const string entity_file_name = build_entity_file_name( (dynamic_cast<IIR_SimpleName *>(as_selected_name->get_suffix()))->get_prefix_string(), lib_dir_name );

      // TODO: Remove Scram
      dynamic_cast<IIRScram_Name *>(name)->_get_symbol_table()->open_scope( lib_decl );
      retval = parse_primary_unit( lib_decl, entity_file_name, package, factory );
      dynamic_cast<IIRScram_Name *>(name)->_get_symbol_table()->close_scope( lib_decl );
      if( retval != NULL ){
	lib_decl->get_primary_units()->append( retval );
      }
    }
  }
  else{
    ostringstream err;
    // TODO: Remove Scram
    err << "Internal error in library_manager::parse_primary_unit(symbol_table *sym_tab,"
	<< "IIR *name, IIR_Kind unitType) - don't know how to look up name " << *name
	<< " - only know how to look up simple and selected names!";
    report_error( name, err.str() );
  }

  return retval;
}

// goes and retrieves a particular primary unit given a secondary unit
IIR_LibraryUnit *
library_manager::parse_primary_unit( IIR_LibraryDeclaration     *lib_decl,
				     IIR_TextLiteral            *primary_unit_name,
				     IIR_Kind                   unitType,
                                     StandardPackage            *package,
                                     plugin_class_factory       *factory,
				     IIR_Boolean                complain_on_error ){

  ASSERT( lib_decl != 0 );
  ASSERT( primary_unit_name != 0 );

  IIR_LibraryUnit *retval = 0;
  string file_name;
  // TODO: Remove Scram
  const string unit_name_as_string = primary_unit_name->convert_to_string();
  file_name = dynamic_cast<IIR_LibraryDeclaration *>(lib_decl)->get_path_to_directory() + "/" + unit_name_as_string;
  switch(unitType){
  case IIR_ENTITY_DECLARATION:
    file_name += get_entity_suffix();
    break;
  case IIR_PACKAGE_DECLARATION:
    file_name += get_package_suffix();
    break;
  case IIR_CONFIGURATION_DECLARATION:
    file_name += get_configuration_suffix();
    break;    
  default:
    ostringstream err;
    err << "Library Manager : parse_primary_unit(" << unitType << ") not implemented yet ";
    report_error( primary_unit_name, err.str() );
    break;
  }

  retval = parse_primary_unit( lib_decl, file_name, package, factory );

  return retval;
}

IIR_LibraryUnit *
library_manager::parse_primary_unit( IIR_LibraryDeclaration     *lib_decl,
				     IIR_Name                   *unit_name,
                                     StandardPackage            *package,
                                     plugin_class_factory    *factory,
				     IIR_Boolean                complain_on_error ){
  IIR_LibraryUnit *retval = NULL;
  // So, this method needs to find the primary unit specificed in "unit_name".
  // It's possible that unit name is some sort of complex name, so we'll get 
  // the suffix and search for it in the declarations we find.
  // If we're looking for "work.foo" and there is a configuration foo, and
  // an entity foo, and a package foo, obviously then this method needs to
  // complain.
  
  IIR_EntityDeclaration *entity_decl;
  IIR_PackageDeclaration *package_decl;
  IIR_ConfigurationDeclaration *configuration_decl;

  // TODO: Remove Scram
  IIR_TextLiteral *unit_declarator = unit_name->get_prefix_string();

  entity_decl = 
    dynamic_cast<IIR_EntityDeclaration *>(parse_primary_unit( lib_decl,
                                                              unit_declarator, 
                                                              IIR_ENTITY_DECLARATION,
                                                              package,
                                                              factory));
  
  package_decl = 
    dynamic_cast<IIR_PackageDeclaration *>(parse_primary_unit( lib_decl,
                                                               unit_declarator,
                                                               IIR_PACKAGE_DECLARATION,
                                                               package,
                                                               factory));
  
  configuration_decl =
    dynamic_cast<IIR_ConfigurationDeclaration*>(parse_primary_unit( lib_decl, 
                                                                    unit_declarator,
                                                                    IIR_CONFIGURATION_DECLARATION,
                                                                    package,
                                                                    factory));
    
  if( unit_name->get_suffix() == NULL || 
      unit_name->get_suffix()->get_kind() == IIR_DESIGNATOR_BY_ALL ){
    // If there was more than one potential primary unit, then we need to
    // complain.
    savant::set<IIR_Declaration> decls;
    if( entity_decl != NULL ){
      decls.add( entity_decl );
    }
    if( package_decl != NULL ){
      decls.add( package_decl );
    }
    if( configuration_decl != NULL ){
      decls.add( configuration_decl );
    }
    switch( decls.size() ){
    case 0:{
      if( complain_on_error == TRUE ){
	report_undefined_symbol( lib_decl, unit_name );
      }
      break;
    }
    case 1:{
      retval = dynamic_cast<IIR_LibraryUnit *>(decls.getElement());
      break;
    }
    default:{
      report_ambiguous_error( lib_decl, unit_name, &decls );
      break;
    }
    }
  }

  return retval;
}


const string
library_manager::build_package_body_file_name( IIR_TextLiteral *package_body_name,
					       IIR_LibraryDeclaration *lib_decl ){

  // TODO: Remove Scram
  const string converted_package_name = package_body_name->convert_to_string();
  
  // This is the stream that we'll build the file name in.
  string retval;
  retval = build_secondary_unit_directory_name( package_body_name,
						lib_decl ) +
    "/" + converted_package_name + get_package_body_suffix();
  
  return retval;
}

const string
library_manager::build_arch_file_name( IIR_TextLiteral *entity_name,
				       IIR_TextLiteral *arch_name,
				       IIR_LibraryDeclaration *lib_decl ){
  ASSERT( entity_name != 0 );
  ASSERT( arch_name != 0 );
  return build_secondary_unit_directory_name( entity_name,
					      lib_decl ) +
    "/" + entity_name->convert_to_string() + "_" +
    arch_name->convert_to_string() + "_arch.vhdl";
}

const string
library_manager::build_arch_file_name( IIR_ArchitectureDeclaration *arch ){
  const string converted_entity_name = arch->get_entity()->get_declarator()->convert_to_string();
  const string converted_arch_name = arch->get_declarator()->convert_to_string();

  return build_arch_file_name( arch->get_entity()->get_declarator(),
			       arch->get_declarator(),
			       arch->get_library() );
}

const string
library_manager::build_configuration_file_name( IIR_TextLiteral *configuration_name,
						const string library_directory ){
  // TODO: Remove Scram
  string retval;
  retval = 
    library_directory + "/" + configuration_name->convert_to_string() 
    + get_configuration_suffix();
  return retval;
}

const string
library_manager::build_package_file_name( IIR_TextLiteral *package_name,
					  const string library_directory ){
  const string package_file_name =  library_directory 
    + "/"  + package_name->convert_to_string() + get_package_suffix();
  return package_file_name;

}

const string
library_manager::build_entity_file_name( IIR_TextLiteral *entity_name, 
					 const string library_directory ){
  const string entity_file_name = library_directory + 
    "/" + entity_name->convert_to_string() + get_entity_suffix();
  return entity_file_name;
}

const string
library_manager::build_library_directory_name( IIR_TextLiteral *library_name ){
  string retval;

  const string as_c_string = library_name->convert_to_string();
  retval = as_c_string + get_library_suffix();

  return retval;
}

const string
library_manager::build_secondary_unit_directory_name( IIR_TextLiteral *primary_name,
						      IIR_LibraryDeclaration *lib_decl ){
  return dynamic_cast<IIR_LibraryDeclaration *>(lib_decl)->get_path_to_directory() + "/" +
    lib_decl->get_declarator()->convert_to_string() + 
    "_" + primary_name->convert_to_string() +
    get_secondary_units_suffix() + 
    get_library_suffix();
}

const string
library_manager::build_secondary_unit_directory_name( IIR_LibraryUnit *library_unit ){
  string retval;

  IIR_LibraryDeclaration *lib_decl = library_unit->get_library();
  ASSERT(lib_decl != NULL);
  if( library_unit->is_primary_unit() || 
      dynamic_cast<IIR_PackageBodyDeclaration *>(library_unit) ){
    retval = build_secondary_unit_directory_name( library_unit->get_declarator(),
						  lib_decl );
  }
  else{
    ASSERT( library_unit->is_architecture_declaration() );
    retval = build_secondary_unit_directory_name( dynamic_cast<IIR_ArchitectureDeclaration *>(library_unit)->get_entity()->get_declarator(),
						  lib_decl );
  }
  return retval;
}

IIR_ArchitectureDeclaration *
library_manager::parse_architecture( IIR_EntityDeclaration      *entity, 
				     IIR_TextLiteral            *architecture_name,
                                     StandardPackage            *package,
                                     plugin_class_factory    *factory){
  IIR_TextLiteral *entity_name = entity->get_declarator();
  IIR_LibraryDeclaration *lib_decl = entity->get_library();
  return parse_architecture( lib_decl, entity_name, architecture_name, package, factory );
}


// goes out and retrieves secondary units
IIR_ArchitectureDeclaration *
library_manager::parse_architecture( IIR_LibraryDeclaration     *lib_decl,
				     IIR_TextLiteral            *entity_name,
				     IIR_TextLiteral            *architecture_name,
                                     StandardPackage            *package,
                                     plugin_class_factory    *factory){

  IIR_ArchitectureDeclaration *retval = NULL;
  const string arch_file_name = build_arch_file_name( entity_name, 
						      architecture_name,
						      lib_decl );

  IIR_LibraryUnit *parsed_unit = parse_file( arch_file_name, lib_decl, package, factory );
  if( parsed_unit != NULL ){
    if( parsed_unit->get_kind() == IIR_ARCHITECTURE_DECLARATION ){
      retval = dynamic_cast<IIR_ArchitectureDeclaration *>(parsed_unit);
      my_symbol_table->lookup_add( retval );
    }
    else{
      ostringstream err;
      err << "Internal error in library_manager::parse_architecture - library file"
	  << arch_file_name << " didn't contain an architecture declaration - "
	  << " it contained a " << parsed_unit->get_kind_text() 
	  << " and I don't know what to do!";
      
      report_error( architecture_name, err.str() );
      abort();
    }
  }
  else{
    ostringstream err;
    err << "Library manager could not find library corresonding to architecture |"
	<< *architecture_name << "| for entity |" << *entity_name << "| - expected it "
	<< "to be in file |" << arch_file_name << "|.  Perhaps you need to parse the"
	<< " vhdl file containing this architecture?";
    report_error( architecture_name, err.str() );
  }

  return retval;
}
 
IIR_ArchitectureDeclaration *
library_manager::parse_architecture( IIR_EntityDeclaration      *entity_decl, 
				     IIR_Name                   *architecture_name,
                                     StandardPackage            *package,
                                     plugin_class_factory    *factory){
  
  ASSERT( architecture_name != NULL );
  ASSERT( architecture_name->get_kind() == IIR_SIMPLE_NAME );  
  
  // TODO: Remove Scram
  IIR_SimpleName *as_simple_name = dynamic_cast<IIR_SimpleName *>(architecture_name);
  ASSERT( as_simple_name != 0 );
  ASSERT( as_simple_name->get_prefix() != NULL );
  ASSERT( dynamic_cast<IIR_TextLiteral *>(as_simple_name->get_prefix()) );
  IIR_TextLiteral *arch_as_text_literal =
    dynamic_cast<IIR_TextLiteral *>(as_simple_name->get_prefix());

  ASSERT( entity_decl->get_library() != NULL );
  return parse_architecture( entity_decl->get_library(),
			     entity_decl->get_declarator(), 
			     arch_as_text_literal,
                             package,
                             factory);
}

IIR_LibraryUnit *
library_manager::parse_file( const string               path, 
                             IIR_LibraryDeclaration     *library, 
                             StandardPackage            *package,
                             plugin_class_factory    *factory){
  IIR_LibraryUnit *retval = NULL;
  scram *tmp_scram = new scram( false, 
                                library,
                                factory,
                                package);
  IIR_DesignFile *design_file =
    tmp_scram->parse_file( path,
			   dynamic_cast<IIR_LibraryDeclaration *>(library) );

  if( design_file != NULL ){
    ASSERT( design_file->get_library_units()->size() == 1 );
    retval = dynamic_cast<IIR_LibraryUnit *>(design_file->get_library_units()->first());
  }

  return retval;
}

void 
library_manager::create_directories( IIR_LibraryUnit *lib_unit ){

  ASSERT( lib_unit != 0 );
  // TODO:  Scram
  IIR_LibraryDeclaration *work_library = lib_unit->get_library();
  ASSERT( work_library != 0 );

  string directory_name;
  if( lib_unit->is_primary_unit() ){
    directory_name = work_library->get_path_to_directory();
  }
  else{
    ASSERT( lib_unit->is_secondary_unit() );
    directory_name = build_secondary_unit_directory_name( lib_unit );
  }

  FileManager::instance()->makeDirectory( directory_name );
}

IIR_LibraryDeclaration *
library_manager::find_or_create_library( const string &physical_library_name, plugin_class_factory *factory ){
  IIR_LibraryDeclaration *work_library = find_library( physical_library_name, factory );
  if( work_library == 0 ){
    work_library = create_design_library( physical_library_name, factory );
  }  
  return work_library;
}

IIR_LibraryDeclaration *
library_manager::find_library( const string &library_name,
			       plugin_class_factory *factory ){
  IIR_LibraryDeclaration *retval = NULL;

  IIR_Identifier *temp_id = IIRBase_Identifier::get( library_name, factory );
  retval = find_library( temp_id, factory );
  // This is safe - find library method clones the name if it needs too.
  delete temp_id;

  return retval;
}

IIR_LibraryDeclaration *
library_manager::find_library( IIR_TextLiteral *library_name,
			       plugin_class_factory *factory ){
  IIR_LibraryDeclaration *retval = NULL;  

  IIR_LibraryDeclaration *current =
    dynamic_cast<IIR_LibraryDeclaration *>(libraries->getElement());
  while( current != NULL ){
    // TODO: Remove Scram
    if( IIRBase_TextLiteral::cmp( library_name, current->get_declarator() ) == 0 ){
      retval = current;
      break;
    }
    current = 
      dynamic_cast<IIR_LibraryDeclaration *>(libraries->getNextElement());
  }
  
  if( retval == NULL ){
    // OK, then we need to find the library directory for this logical library,
    // complain if it doesn't exist, and create a library declaration if it does.
    const string lib_directory = find_library_directory( library_name, false );
    if( lib_directory != "" ){
      retval = factory->new_IIR_LibraryDeclaration();
      // TODO:  Scram
      retval->set_declarator( IIRBase_Identifier::get( library_name->convert_to_string(),
						       factory ) );
      retval->set_path_to_directory( lib_directory );
      libraries->add( retval );
    }
  }

  return retval;
}

const string
library_manager::find_library_directory( IIR_TextLiteral *library_name,
					 bool complain_on_error ){
  string retval;
  
  // Build the subdir name that would be associated with this library.
  const string physical_lib_name = build_library_directory_name( library_name );

  // Now we're going to walk through the list of directories that libraries
  // could potentially be stored in, and try to find the library in one of
  // them.  Once we find it, we'll quit.
  string full_path;
  FileManager::FileStatus stat = FileManager::ERROR;

  const vector<string> &search_dirs = get_search_dirs();
  if( verbose_output == true ){
    // TODO:  Scram
    cerr << "Searching for the directory for library |" << *library_name 
	 << "|.  Looking in:\n";
  }

  for( vector<string>::const_iterator i = search_dirs.begin();
       i != search_dirs.end();
       i++ ){
    full_path = *i + FileManager::instance()->getDirectorySeparator()
      + physical_lib_name;

    if( verbose_output == true ){
      cerr << "  " << full_path << " - ";
    }

    stat = 
      FileManager::instance()->checkFileStatus( full_path, FileManager::DIRECTORY );
    if( stat == FileManager::OK ){
      if( verbose_output == true ){
	cerr << "FOUND" << endl;
      }
      break;
    }
    else{
      if( verbose_output == true ){
	cerr << "NOT FOUND" << endl;
      }
    }
  }
  if( stat == FileManager::OK ){
    retval = full_path;
  }
  else if ( complain_on_error == true ){
    ostringstream err;
    // TODO:  Scram
    err << "Cannot find directory corresponding to library |" << *library_name
	<< "|.  Run with \"-v\" flag to see search path.";
    report_error( library_name, err.str() );
  }

  return retval;
}

IIR_TextLiteral *
library_manager::find_unit_declarator( IIR *unit_name ){
  IIR_TextLiteral *unit_declarator = NULL;

  // TODO:  Scram
  if( dynamic_cast<IIR_Name *>(unit_name) ){
    unit_declarator = get_unit_name( dynamic_cast<IIR_Name *>(unit_name) );
  }
  else if( dynamic_cast<IIR_TextLiteral *>(unit_name) ){
    unit_declarator = dynamic_cast<IIR_TextLiteral *>(unit_name);
  }
  else if( dynamic_cast<IIR_Declaration *>(unit_name) ){
    unit_declarator = dynamic_cast<IIR_Declaration *>(unit_name)->get_declarator();
  }
  else{
    ostringstream err;
    err << "Internal error in library_manager::_find_unit_declarator - don't know "
	<< "what to do with unit name kind |" << unit_name->get_kind_text() << "|.";
    report_error( unit_name, err.str() );
    abort();
  }

  return unit_declarator;
}

IIR_LibraryDeclaration *
library_manager::find_library( IIR_Boolean complain_on_error,
			       IIR *unit_name, 
			       IIR_LibraryDeclaration *fallback_library,
			       plugin_class_factory *factory ){
  IIR_TextLiteral *library_declarator = 0;
  IIR_LibraryDeclaration *retval = 0;

  // TODO:  Scram
  if( dynamic_cast<IIR_Name *>(unit_name) ){
    // Then look and see if a library has been explicitly supplied in the name.
    library_declarator = get_library_name( dynamic_cast<IIR_Name *>(unit_name) );
    if( library_declarator != 0 ){
      retval = find_library( library_declarator, factory );
      if( retval == 0 && complain_on_error ){
	ostringstream err;
	err << "Could not find library |"  << *library_declarator << "|, referenced "
	    << "by |" << *unit_name << "|.";
	report_error( unit_name, err.str() );
      }
    }
  }
  // If they didn't explicitly name a library and they told us a fallback,
  // use the fallback.
  if( library_declarator == 0 && fallback_library != 0 ){
    retval = fallback_library;
  }
  return retval;
}


IIR_LibraryUnit *
library_manager::lookup_unit( IIR_Boolean               complain_on_error,
			      IIR                       *unit_name,
			      IIR_LibraryDeclaration    *work_library,
			      IIR_Kind                  unit_kind,
                              StandardPackage           *package,
                              plugin_class_factory   *factory){
  
  ASSERT( unit_name != NULL );
  ASSERT( work_library != NULL );
  IIR_LibraryUnit *retval = NULL;

  IIR_TextLiteral *unit_declarator = find_unit_declarator( unit_name );
  IIR_LibraryDeclaration *target_library = find_library( complain_on_error,
							 unit_name, 
							 work_library, 
							 factory );
  if( unit_declarator == NULL ){
    return NULL;
  }

  // TODO:  Scram
  constraint_functor *functor = NULL;
  switch( unit_kind ){
  case IIR_ENTITY_DECLARATION:{
    functor = new is_entity_declaration_functor();
    break;
  }
  case IIR_PACKAGE_DECLARATION:{
    functor = new is_package_declaration_functor();
    break;
  }
  case IIR_CONFIGURATION_DECLARATION:{
    functor = new is_configuration_declaration_functor();
    break;
  }
  default:{
    ostringstream err;
    err << "Internal error in library_manager::lookup_unit - don't know"
	<< "what to do with kind |" << unit_kind << "|.";
    report_error( unit_name, err.str() );
    abort();
  }
  }

  savant::set<IIR_Declaration> *decls = 
    new savant::set<IIR_Declaration>(*(my_symbol_table->find_set( unit_declarator )));
  IIR_Declaration *current = dynamic_cast<IIR_Declaration *>(decls->getElement());
  while( current != NULL ){
    ASSERT( dynamic_cast<IIR_LibraryUnit *>(current) );
    IIR_LibraryUnit *as_lib_unit = dynamic_cast<IIR_LibraryUnit *>(current);
    IIR_LibraryDeclaration *its_lib = as_lib_unit->get_library();
    if( (*functor)(current) && its_lib == target_library ){
      retval = dynamic_cast<IIR_LibraryUnit *>(current);
      break;
    }
    current = dynamic_cast<IIR_Declaration *>(decls->getNextElement());
  }
  
  delete decls;

  if( !retval && target_library ){
    IIR_LibraryUnit *temp_retval;
    
    temp_retval = parse_primary_unit( target_library, 
				      unit_declarator, 
				      unit_kind, 
                                      package,
                                      factory,
				      complain_on_error);

    ASSERT( temp_retval == NULL || temp_retval->get_kind() == unit_kind );
    retval = temp_retval;

    if( retval == NULL && complain_on_error == TRUE ){
      ostringstream err;
      err << "No primary unit |" << *unit_name << "| found.";
      report_error( unit_name, err.str() );
    }
  }

  return retval;
}

IIR_ArchitectureDeclaration *
library_manager::lookup_default_architecture( IIR_EntityDeclaration *entity_decl ){
  ASSERT( entity_decl != 0 );

  // So, we need to go find the most recently analyzed arch for this entity...
  IIR_ArchitectureDeclaration   *retval = NULL;
  // So, we want to build a secondary unit path, and then find all of the
  // arches in there and grab the most recent.
  const string secondary_unit_path = build_secondary_unit_directory_name( entity_decl );
  string filename;
  filename = FileManager::instance()->findNewestFile( ".*_arch.vhdl",
						      secondary_unit_path);
  if( filename != "" ){
    string full_path;
    full_path = secondary_unit_path + "/" + filename;
    // TODO:  Scram
    IIR_LibraryDeclaration *library_decl = entity_decl->get_library();
    IIR_LibraryUnit *parsed_unit = parse_file( full_path, library_decl,
					       ScramStandardPackage::instance(),
					       scram_plugin_class_factory::instance() );
    ASSERT( !parsed_unit || parsed_unit->get_kind() == IIR_ARCHITECTURE_DECLARATION );
    retval = dynamic_cast<IIR_ArchitectureDeclaration *>(parsed_unit);
    plugin_class_factory *factory =
      dynamic_cast<IIRBase_EntityDeclaration *>(entity_decl)->get_design_file()->get_class_factory();
    if( factory != scram_plugin_class_factory::instance() && retval ){
      // Then we need to clone this guy into the right plugin before we return it.
      IIR_ArchitectureDeclaration *new_tree =
	dynamic_cast<IIR_ArchitectureDeclaration *>(retval->convert_tree( factory ));
      ASSERT( new_tree != 0 );
      delete retval;
      retval = new_tree;
    }
  }

  return retval;
}

IIR_ArchitectureDeclaration *
library_manager::lookup_architecture( IIR_Boolean               complain_on_error, 
				      IIR_EntityDeclaration     *entity, 
				      IIR_TextLiteral           *architecture_declarator){

  ASSERT( entity != NULL );
  ASSERT( architecture_declarator != NULL );

  IIR_ArchitectureDeclaration   *retval = NULL;
  StandardPackage               *package = dynamic_cast<IIR_EntityDeclaration *>(entity)->get_design_file()->get_standard_package();
  plugin_class_factory          *factory = dynamic_cast<IIR_EntityDeclaration *>(entity)->get_design_file()->get_class_factory();

  savant::set<IIR_Declaration> *decls = 
    new savant::set<IIR_Declaration>(*(my_symbol_table->find_set( architecture_declarator )));

  if( decls != NULL && decls->size() > 0 ){
    IIR_Declaration *current_decl = decls->getElement();
    while( current_decl != NULL ){
      if( current_decl->is_architecture_declaration() ){
	IIR_ArchitectureDeclaration *current_arch_decl = 
	  dynamic_cast<IIR_ArchitectureDeclaration *>(current_decl);
	if( current_arch_decl->get_entity() != entity ){
	  decls->remove( current_decl);
	}
      }
      current_decl = decls->getNextElement();
    }    

    IIR_Declaration *current = decls->getElement();
    for( int i = 0; i < decls->size() - 1; i++ ){
      current = decls->getNextElement();
      ASSERT( current && dynamic_cast<IIR_ArchitectureDeclaration *>(current) );
    }
    delete decls;
    retval = dynamic_cast<IIR_ArchitectureDeclaration *>(current);    
  }

  if( retval == NULL ){
    // Then we need to go to the library manager and try to find the
    // architecture there.
    retval = parse_architecture( entity, architecture_declarator, package, factory );
  }
    
  if(  retval == NULL && complain_on_error == TRUE ){
    ostringstream err;
    err << "No architecture |" << *architecture_declarator << "| declared for entity |"
        << *entity->get_declarator() << "|.";
    report_error( architecture_declarator, err.str() );
  }

  return retval;
}

IIR_ArchitectureDeclaration *
library_manager::lookup_architecture( IIR_Boolean               complain_on_error, 
				      IIR_EntityDeclaration     *entity,
				      IIR_Name                  *architecture_name){
  IIR_ArchitectureDeclaration *retval = NULL;

  ASSERT( complain_on_error == TRUE ||  complain_on_error == FALSE );
  ASSERT( entity != NULL );
  ASSERT( architecture_name != NULL );
  ASSERT( entity->get_library() != NULL );
  
  IIR_TextLiteral *architecture_declarator = get_unit_name( architecture_name );

  // Let's see if the arch name has explicitly called out a library to use.
  IIR_TextLiteral *named_library_declarator = get_library_name( architecture_name );
  if( named_library_declarator != NULL ){
    if( IIRBase_TextLiteral::cmp( named_library_declarator, 
                                  entity->get_library()->get_declarator() ) != 0 ){
      // Then we had better complain.
      ostringstream err;
      err << "Error - the name |" << *architecture_name << "| specifies library |" 
	  << *named_library_declarator << "|, but entity |" << *entity 
	  << "| is in library |" << *entity->get_library()->get_declarator() << "| -"
	  << " can't use an architecture from a different library.";
      report_error( architecture_name, err.str() );
    }
  }  
  retval = lookup_architecture( complain_on_error, entity, architecture_declarator);

  return retval;
}

IIR_PackageDeclaration *
library_manager::lookup_package( IIR_Boolean                    complain_on_error,
				 IIR                            *package_name,
				 IIR_LibraryDeclaration         *lib_decl,
                                 StandardPackage                *package,
                                 plugin_class_factory        *factory){

  IIR_PackageDeclaration *retval = NULL;

  retval = dynamic_cast<IIR_PackageDeclaration *>(lookup_unit( complain_on_error,
                                                               package_name,
                                                               lib_decl,
                                                               IIR_PACKAGE_DECLARATION,
                                                               package,
                                                               factory));

  return retval;
}

IIR_EntityDeclaration *
library_manager::lookup_entity( IIR_Boolean                     complain_on_error,
				IIR                             *entity_name,
				IIR_LibraryDeclaration          *lib_decl,
                                StandardPackage                 *package,
                                plugin_class_factory         *factory){
  IIR_EntityDeclaration *retval = NULL;

  retval = dynamic_cast<IIR_EntityDeclaration *>(lookup_unit( complain_on_error,
                                                              entity_name,
                                                              lib_decl,
                                                              IIR_ENTITY_DECLARATION,
                                                              package,
                                                              factory));
  
  return retval;  
}

IIR_ConfigurationDeclaration *
library_manager::lookup_configuration( IIR_Boolean              complain_on_error,
				       IIR_Name                 *configuration_name,
				       IIR_LibraryDeclaration   *lib_decl,
                                       StandardPackage          *package,
                                       plugin_class_factory  *factory){

  IIR_ConfigurationDeclaration *retval = NULL;
  retval = dynamic_cast<IIR_ConfigurationDeclaration *>(lookup_unit( complain_on_error,
									  configuration_name,
									  lib_decl,
									  IIR_CONFIGURATION_DECLARATION,
									  package,
									  factory));

  return retval;  
}

IIR_TextLiteral *
library_manager::get_library_name( IIR_Name *name ){
  IIR_TextLiteral *retval = NULL;

  switch( name->get_kind() ){
  case IIR_SIMPLE_NAME:{
    break;
  }
  case IIR_SELECTED_NAME:{
    if( name->get_prefix()->get_kind() == IIR_SIMPLE_NAME &&
	name->get_suffix()->get_kind() == IIR_SIMPLE_NAME ){
      retval = name->get_prefix()->get_prefix_string();
    }
    break;
  }
  default:{
    
  }
  }
  return retval;
}

IIR_TextLiteral *
library_manager::get_unit_name( IIR_Name *name ){
  IIR_TextLiteral *retval = NULL;

  switch( name->get_kind() ){
  case IIR_SIMPLE_NAME:{
    retval = name->get_prefix_string();
    break;
  }
  case IIR_SELECTED_NAME:{
    if( name->get_prefix()->get_kind() == IIR_SIMPLE_NAME &&
	name->get_suffix()->get_kind() == IIR_SIMPLE_NAME ){
      retval = name->get_suffix()->get_prefix_string();
    }
    break;
  }
  default:{
    
  }
  }
  
  return retval;
}

void
library_manager::add_declaration( IIR_LibraryUnit *to_add ){
  ASSERT( my_symbol_table != NULL );
  ASSERT( to_add != NULL );
  my_symbol_table->lookup_add( to_add );
}

const vector<string> &
library_manager::get_search_dirs(){
  // These static entries only initialize once by definition.
  static vector<string> retval;
  static bool needToInit = true;
  if( needToInit == true ){
    // Order matters here.  We'll do user specified places first,
    // and then look in the standard places.

    retval.push_back( "." );
    retval.insert( retval.end(), 
		   parse_vhdl_library_path( ).begin(), 
		   parse_vhdl_library_path().end());
    if( get_savant_root_directory() != "" ){
      retval.push_back( get_savant_root_directory() + 
			FileManager::instance()->getDirectorySeparator() +
			"lib" );
    }

    const vector<string> &lib_dirs = FileManager::instance()->getLibraryDirectories();
    for( vector<string>::const_iterator i = lib_dirs.begin();
	 i != lib_dirs.end();
	 i++ ){
      // We append "savant/lib" onto whatever lib dirs the file manager
      // has.  If the user put their libs somewhere else, they should have
      // specified in VHDL_LIBRARY_PATH.
      retval.push_back( *i + 
			FileManager::instance()->getDirectorySeparator() 
			+ "savant" + FileManager::instance()->getDirectorySeparator() 
			+ "lib" );
    }
    // if -v, print out the search directories.

    if( verbose_output == true ){
      cerr << "Searching these subdirectories for libraries:\n";
      for( vector<string>::const_iterator i = retval.begin();
	   i != retval.end();
	   i++ ){
	cerr << "  "  << *i << "\n";
      }
      cerr << endl;
    }
    
    needToInit = false;
  }
  return retval;
}

const vector<string> &
library_manager::parse_vhdl_library_path(){
  static vector<string> retval;
  static bool need_to_init = true;
  if( need_to_init == true ){
    need_to_init = false;
    string vhdl_library_path_string;
    vhdl_library_path_string = "";
    if( getenv("VHDL_LIBRARY_PATH") != 0 ){
      vhdl_library_path_string = getenv("VHDL_LIBRARY_PATH");
      unsigned int begin_index = 0;
      unsigned int end_index = 0;
      for( unsigned int i = 0; i < vhdl_library_path_string.size(); i++ ){
	if( vhdl_library_path_string[i] == ':' ){
	  end_index = i - 1;
	  retval.push_back( vhdl_library_path_string.substr( begin_index, 
							     end_index - begin_index + 1 ) );
	  begin_index = i + 1;
	}
      }
      if(vhdl_library_path_string.size() > begin_index){
        retval.push_back( vhdl_library_path_string.substr( begin_index, 
                                                           vhdl_library_path_string.size() - begin_index ) ); //FAB
      }
    }
  }
  return retval;
}

savant::set<IIR_LibraryDeclaration> *
library_manager::get_libraries(){
  return new set<IIR_LibraryDeclaration>( *libraries );
}
