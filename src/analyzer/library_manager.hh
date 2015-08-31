#ifndef LIBRARY_MANAGER_HH
#define LIBRARY_MANAGER_HH

// Copyright (c) 1996-2001 The University of Cincinnati.
// All rights reserved. 

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found
// in the file "LGPL", distributed with this archive.

// Authors: Radharamanan Radhakrishnan  
//          Philip A. Wilsey            philip.wilsey@ieee.org

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "savant.hh"
#include "IRBasicDataTypes.hh"
#include <string>
#include <vector>
#include <fstream>


class symbol_table;
class symbol_lookup;
class IIR_ArchitectureDeclaration;
class IIR_ConfigurationDeclaration;
class IIR_Declaration;
class IIR_EntityDeclaration;
class IIR_IndexedName;
class IIR_LibraryDeclaration;
class IIR_LibraryUnit;
class IIR_Name;
class IIR_PackageDeclaration;
class IIR_SimpleName;
class IIR_TextLiteral;
class scram;
class plugin_class_factory;
class StandardPackage;

namespace savant {
  template <class type> class set;
}

using std::vector;
using std::string;
using std::ofstream;

/** This class implements the library functionality as specified in the
   LRM.  It is intended to be used as a singleton instance for all
   parsers, and can be accessed in both the parser class and via a
   static IIR member.  

   Note that the library manager is as lazy as possible about finding
   things - library declaration will initially be empty, and as things
   within it are accessed, it will grow.  For instance, work._savant_lib
   might have thousands of things in it.  Even if it does, the first time
   this library is accessed via "find_library", the declaration will be
   empty.  If at some point "work.foo.bar" is accessed, the work library
   declaration will now contain foo which will contain bar.  And, if I then
   access "work.foo.baz", the there will be one reference to foo, and
   within foo, both "bar" and "baz".  If I access "work.foo.all", then
   everything within "work.foo" will appear in the library.
*/
class library_manager {
  friend class IIR_LibraryDeclaration;
  friend class scram;

public:
  /** Get a handle to the library_manager singleton. */
  static library_manager *instance();
  
  ~library_manager();
  
  /** Creates the work directory into which analyzed design units are
    stored.

    If user doesn't specify a work directory name through the -lib
    option the actual name "work" will be used. */
//  int create_work_dir();
  
  /** This methods gets a library unit and depending on the type does the
      appropriate name mangling and returns a handle to a ostream. */
  ostream *get_file_handle( IIR_LibraryUnit *lib_unit );
  
  /** Calls publish vhdl so that analyzed design units can be stored in the
      work directory. */
  void parse_into_work_dir( IIR_LibraryUnit *unit_to_publish );
  
  /** Get a handle to the VHDL package "std.standard".  */
//   IIR_PackageDeclaration *get_standard_package(){
//     return my_standard_package;
//   }
  
  /** This method looks for the logical library passed in.  If it exists,
      it returns it.  Otherwise, it does everything it can to create it and
      return it.  */
  IIR_LibraryDeclaration *find_or_create_library( const string &physical_library_name,
						  plugin_class_factory * );

  //@{
  /** The following method finds the library referenced, and returns a
      pointer to it.  (If a library is referenced that the library
      manager can't find the directory for, it will return NULL, and the
      caller should complain.) */
  IIR_LibraryDeclaration *find_library( IIR_TextLiteral *library_name, plugin_class_factory * );
  IIR_LibraryDeclaration *find_library( const string &library_name, plugin_class_factory *); 

  /** This method is used by the the library_manager to ascertain what
      library to find things in.  Given a selected name, it will use the
      prefix of the name to try to find the library.  If it's given a
      simple name, it will fallback to the "fallback_library", which should
      be the "work" library in general.
  */
  IIR_LibraryDeclaration *find_library( IIR_Boolean complain_on_error,
				        IIR *unit_name,
					IIR_LibraryDeclaration *fallback_library,
					plugin_class_factory * );

  //@}

  /** This method looks up the most recently analyzed architecture for this
     entity declaration and returns it.  The library searched is that of
     the entity declaration.  */
  IIR_ArchitectureDeclaration *lookup_default_architecture( IIR_EntityDeclaration       *entity_decl);

  /** This method finds the last declared architecture of the name it's
      called on for the entity passed in.  If complain on error is TRUE.
      it will generate an error message when it fails.  The library
      searched will be that of the entity. */
  IIR_ArchitectureDeclaration *lookup_architecture( IIR_Boolean                 complain_on_error,
                                                    IIR_EntityDeclaration       *,
                                                    IIR_Name                    *architecture_name);

  /** @see library_manager#lookup_architecture */
  IIR_ArchitectureDeclaration *lookup_architecture( IIR_Boolean                 complain_on_error,
                                                    IIR_EntityDeclaration       *,
                                                    IIR_TextLiteral             *architecture_name);
  
  /** Find the package specified.  
  
  @param complain_on_error Pass it true and it will complain if the package
  isn't found.  False and no error message will be generated.

  @param package_name The name has to be an IIR_Name, or an
  IIR_TextLiteral, or an assertion will fail.  A selected name may contain
  a library prefix.

  @param work_library If no library is specified in the name, we fall back
  to the work library passed in for our search for this unit.
*/
  IIR_PackageDeclaration *lookup_package( IIR_Boolean,
                                          IIR                           *package_name,
                                          IIR_LibraryDeclaration        *work_library,
                                          StandardPackage               *package,
                                          plugin_class_factory       *factory);

  /** Find the entity specified.  
  
  @param complain_on_error Pass it true and it will complain if the package
  isn't found.  False and no error message will be generated.

  @param package_name The name has to be an IIR_Name, or an
  IIR_TextLiteral, or an assertion will fail.  A selected name may contain
  a library prefix.

  @param work_library If no library is specified in the name, we fall back
  to the work library passed in for our search for this unit.
  */
  IIR_EntityDeclaration *lookup_entity( IIR_Boolean                     complain_on_error,
                                        IIR                             *entity_name,
                                        IIR_LibraryDeclaration          *work_library,
                                        StandardPackage                 *package,
                                        plugin_class_factory         *factory);

  /** Find the configuration specified.  
  
  @param complain_on_error Pass it true and it will complain if the package
  isn't found.  False and no error message will be generated.

  @param package_name The name has to be an IIR_Name, or an
  IIR_TextLiteral, or an assertion will fail.  A selected name may contain
  a library prefix.

  @param work_library If no library is specified in the name, we fall back
  to the work library passed in for our search for this unit.
  */
  IIR_ConfigurationDeclaration *lookup_configuration( IIR_Boolean                    complain_on_error,
							   IIR_Name                       *configuration_name,
							   IIR_LibraryDeclaration    *work_library,
							   StandardPackage                *package,
							   plugin_class_factory           *factory);

  /** Add this declaration to our list of cached library units. */
  void add_declaration( IIR_LibraryUnit * );

  /** This method searches for the savant root directory.  It first will
      try the SAVANTROOT environment variable, and then it will try a list
      of standard directories that it knows about.  It will return NULL if
      it can't find a valid match, and the directory name if it can. */
  static const string get_savant_root_directory();
  
  /** Returns the file suffix used for stored entities. */
  static const string &get_entity_suffix();

  /** Returns the file suffix used for stored configurations.  */
  static const string &get_configuration_suffix();

  /** Returns the file suffix used for stored packages.  */
  static const string &get_package_suffix();

  /** Returns the file suffix used for stored package bodies.  */
  static const string &get_package_body_suffix();

  /** Returns the file suffix used for secondary unit directories.  */
  static const string &get_secondary_units_suffix();

  /** Returns the file suffix used for library directories.  */
  static const string &get_library_suffix();

  /** Returns a set of all known libraries.  The caller needs to delete
     the set that is returned.  */
  savant::set<IIR_LibraryDeclaration> *get_libraries();

  /** Adds the standard package to the list of libraries managed */
  void init_std_library(StandardPackage *package);

private:
  /** This is private - use "instance" to get a singleton.  */
  library_manager();
    
  /** The symbol_lookup I use to cache units. */
  symbol_lookup *my_symbol_table;

  /** The set of found libraries. */
  savant::set<IIR_LibraryDeclaration> *libraries;

  /** A handle to the standard package. */
//   IIR_PackageDeclaration *my_standard_package;
  
  void create_directories( IIR_LibraryUnit *lib_unit );

  /**
     Return the full path name for the VHDL file to publish this
     architecture into.
  */
  const string build_arch_file_name( IIR_ArchitectureDeclaration *for_arch  );
  /**
     Return the full path name for the VHDL file to publish this
     architecture into.
  */
  const string build_arch_file_name( IIR_TextLiteral *entity_name,
				     IIR_TextLiteral *arch_name,
				     IIR_LibraryDeclaration *lib_decl );

  const string build_package_body_file_name( IIR_TextLiteral *package_body_name,
					     IIR_LibraryDeclaration *lib_decl );


  const string build_entity_file_name( IIR_TextLiteral *entity_name,
				       const string library_directory );

  const string build_configuration_file_name( IIR_TextLiteral *configuration_name,
					      const string library_directory );

  const string build_package_file_name( IIR_TextLiteral *package_name,
					const string library_directory );

  const string build_library_directory_name( IIR_TextLiteral *library_name );
  
  /** Builds the directory name appropriate for secondary units for the
      library unit passed in.  Either a primary unit or a secondary unit
      may be passed into this function.  For a primary unit, the
      directory name for its secondary unit will be generated.  For a
      secondary unit, the directory that it itself should go in will be
      generated.
     
      @param for_unit The unit for which we want the appropriate
      directory for its secondary units.  */
  const string build_secondary_unit_directory_name( IIR_LibraryUnit *for_unit );
  const string build_secondary_unit_directory_name( IIR_TextLiteral *primary_name,
						    IIR_LibraryDeclaration *lib_decl );


  const string find_library_directory( IIR_TextLiteral *library_name,
				       bool complain_on_error );

  /** This method searches the IIR * passed in an gets the unit name
      from it.  Currently it handles IIR_Names, IIR_TextLiterals, and
      IIR_Declarations.  Anything else causes a runtime error.  */
  IIR_TextLiteral *find_unit_declarator( IIR *unit_name );

  
  /** This method will looks for library units. First it checks the
      local hash table, and then it will check the filesystem for the
      library analyzed.

      @param complain_on_error if true, if the unit can't be found an
      appropriate error message is generated.

      @param unit_name specifies the unit to find.  It can be an IIR_Name,
      an IIR_TextLiteral, or an IIR_Declaration.  In the case of a
      declaration, the declarator of the declaration will be used as the
      name.  If it's a selected name, it's expected that the prefix will
      name a known library.

      @param library_declaration Pass in the work library.  If no library
      is specified explicitly in the name, we'll fall back to the work
      library to know what library we're looking in for this unit.
      
      @param unit_kind This is the kind of unit we're looking for.
      Possible values include IIR_ENTITY_DECLARATION,
      IIR_PACKAGE_DECLARATION, and IIR_CONFIGURATION_DECLARATION.  Anything
      else will generate a runtime error.  */
  IIR_LibraryUnit *lookup_unit( IIR_Boolean                     complain_on_error,
                                IIR                             *unit_name,
                                IIR_LibraryDeclaration          *work_library,
                                IIR_Kind                        unit_kind,
                                StandardPackage                 *package,
                                plugin_class_factory         *factory);

  //@{

  /** The following methods use different types of information to go
      find and analyzer primary units from libraries.  */

  /** Goes and retrieves a particular primary unit by path. */
  IIR_LibraryUnit *parse_primary_unit( IIR_LibraryDeclaration           *, 
                                       const string                     path_to_file,
                                       StandardPackage                  *package,                                    
                                       plugin_class_factory          *factory);

  /** Goes and retrieves a particular primary unit given a secondary
      unit. */
  IIR_LibraryUnit *parse_primary_unit( IIR_LibraryDeclaration           *, 
                                       IIR_TextLiteral                  *unit_name, 
                                       IIR_Kind                         unitType,
                                       StandardPackage                  *package,
                                       plugin_class_factory          *factory,
                                       IIR_Boolean                      complain_on_error = TRUE );

  /** Finds unit_name from the specified library.  Only looks for the
      kind passed in. */
  IIR_LibraryUnit *parse_primary_unit( IIR_LibraryDeclaration           *,
                                       IIR_Name                         *unit_name,
                                       IIR_Kind                         unitType,
                                       StandardPackage                  *package,
                                       plugin_class_factory          *factory,
                                       IIR_Boolean                      complain_on_error = TRUE );

  /** Finds unit_name from the specified library.  If there are multiple
      possibilies found, it will complain no matter what the
      "complain_on_error" flag is set to. */
  IIR_LibraryUnit *parse_primary_unit( IIR_LibraryDeclaration           *,
                                       IIR_Name                         *unit_name,
                                       StandardPackage                  *package,
                                       plugin_class_factory          *factory,
                                       IIR_Boolean                      complain_on_error = TRUE );

  //@}

  // goes out and retrieves secondary units
  IIR_ArchitectureDeclaration *parse_architecture( IIR_LibraryDeclaration       *,
                                                   IIR_TextLiteral              *entity_name, 
                                                   IIR_TextLiteral              *architecture_name,
                                                   StandardPackage              *package,
                                                   plugin_class_factory      *factory);

  IIR_ArchitectureDeclaration *parse_architecture( IIR_EntityDeclaration        *entity, 
                                                   IIR_TextLiteral              *architecture_name,
                                                   StandardPackage              *package,
                                                   plugin_class_factory      *factory);
  
  IIR_ArchitectureDeclaration *parse_architecture( IIR_EntityDeclaration        *entity_decl, 
                                                   IIR_Name                     *architecture_name,
                                                   StandardPackage              *package,
                                                   plugin_class_factory      *factory);

  /** Parses the file found in the path into the library passed in.  If
      there is any problem parsing the file NULL is returned.  */
  IIR_LibraryUnit *parse_file( const string             path, 
                               IIR_LibraryDeclaration   *library,
                               StandardPackage          *package,
                               plugin_class_factory  *factory);

  //@{
  /** These methods operate either on a simple name, or a selected name.
      What's passed in will normally be either <unit_name>, or
      <library_name>.<unit_name>.  In the first case, a library name will
      never be returned.  If any other type of name is passed in, the result
      will always be null. */
  IIR_TextLiteral *get_library_name( IIR_Name * );
  IIR_TextLiteral *get_unit_name( IIR_Name * );
  //@}
  
  /** This method takes a string with the name of a directory as input and
      checks to see if this directory is a valid savantroot directory.  It
      returns true if it is, and false if it's not. */
  static bool check_root_dir( const string, bool complain );

  /** This method checks for SAVANTROOT to see if it's defined valid.  If
      you pass it a "true" and the variable isn't defined, or it's defined
      but invalid, it will report very verbosely what the problem is. */
  static const string check_environment_variable( bool );

  /** This method looks in the list of standard directories for the savant
      root dir.  It returns the directory if it finds it, and NULL if it
      doesn't. */
  static const string check_default_directories( bool complain );

  /** This method returns a null terminated array of strings containing the
      directories that we need to search when looking for libraries.
      Currently directories get listed in here via VHDL_LIBRARY_PATH,
      SAVANTROOT, and the hardcoded locations in the
      file_manager::get_library_directories(). */
  static const vector<string> &get_search_dirs();

  /** This method parse the environment varible VHDL_LIBRARY_PATH, which
      should be a colon separated list of directory names.  If a NULL
      argument is passed in, only the count of entries is returned.  If a
      non-NULL argument is passed in, the entries from the environment
      variable are written into the array passed in. */
  static const vector<string> &parse_vhdl_library_path( );

  /** Create the design library so that _publish_vhdl and _publish_cc
      can dump their output into this directory. */
  IIR_LibraryDeclaration *create_design_library( const string &physical_library_name, plugin_class_factory *);
};
#endif
