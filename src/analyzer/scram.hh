#ifndef SCRAM_HH
#define SCRAM_HH

// Copyright (c) 1995-2001 The University of Cincinnati.
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Author: Dale E. Martin          dmartin@cliftonlabs.com

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "savant.hh"
#include <string>
#include <vector>

template <class type> class dl_list;
class IIR_DesignFile;
class IIR_DesignFileList;
class IIR_LibraryDeclaration;
class IIR_LibraryDeclaration;
class symbol_table;
class library_manager;
class plugin_class_factory;
class StandardPackage;

using std::string;
using std::vector;

/** This class encapsulates a VHDL Parser. */

class scram {
public:
  /** Constructor - called by main */
  scram( bool init_need_to_write_libraries,
	 const string &work_library_name,
	 plugin_class_factory *factory,
	 StandardPackage *package);

  /** Constructor - called by library manager */
  scram( bool init_need_to_write_libraries,
	 IIR_LibraryDeclaration *work_library,
	 plugin_class_factory *factory, StandardPackage *package,
	 bool need_to_load_std_lib = true);

  ~scram();
    
  /** This method parses the files passed in and returns a list of savant_if
      IIR_DesignFiles. */
  IIR_DesignFileList *parse_files( const vector<string> &fileList );
  IIR_DesignFile *parse_file( const string &path, IIR_LibraryDeclaration * );

  /** This method returns the IIR_LibraryDeclaration that was used for this
      execution of the parser for the VHDL library "work". */
  IIR_LibraryDeclaration *get_work_library() const;

  /** Return the symbol_table associated with this parser. */
  symbol_table                  *get_symbol_table() const { return my_symbol_table; }

  /** Return the VHDL Standard Package implementaion associated with this parser */
  StandardPackage               *get_standard_package() const { return my_std_package; }

  /** Return the class factory associated with this parser */
  plugin_class_factory       *get_class_factory() const { return my_class_factory; }

  /** Does this parser need to write out VHDL libraries? */
  void set_need_to_write_libraries(bool value){
    need_to_write_libraries=value;
  }

  scram                         *convert_node(plugin_class_factory *);

private:
  symbol_table                  *my_symbol_table;
  bool                          need_to_write_libraries;
  IIR_LibraryDeclaration        *my_work_library;
  StandardPackage               *my_std_package;
  plugin_class_factory          *my_class_factory;
  IIR_DesignFileList            *my_design_files;

  scram                         *transmuted_node;
};

#endif
