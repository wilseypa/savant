
// Copyright (c) 1995-2003 The University of Cincinnati.
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
// DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey    philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer
//          Narayanan Thondugulam
//          Magnus Danielson      cfmd@swipnet.se

#include "savant_config.hh"
#include <signal.h>
#include "version.hh"
#include "savant.hh"
#include "savant_config.hh"
#include "scram.hh"
#include "IIR_DesignFile.hh"
#include "IIRScram_DesignFileList.hh"
#include "IIR_LibraryUnit.hh"
#include "IIR_EntityDeclaration.hh"
#include "IIR_ArchitectureDeclaration.hh"
#include "symbol_table.hh"
#include "dl_list.hh"
#include "IIR_EnumerationLiteral.hh"
#include "IIR_Identifier.hh"
#include "language_processing_control.hh"
#include <cctype>
#include <fstream>
#include <clutils/ArgumentParser.h>
#include "StandardPackage.hh"

#include "IIRScram_DesignFile.hh"
#include "scram_plugin_class_factory.hh"
#include "ScramStandardPackage.hh"

// Library/Plugin stuff
#include <ltdl.h>
#include "clutils/PluginManager.h"
#include "clutils/PluginBase.h"
#include "plugin_interface.hh"

// temporary elaboration info stuff
#include "elaborate_info.hh"
elaborate_info elab_info;

// to invoke the library manager
#include "library_manager.hh"

// These are global flags.
bool debug_symbol_table;
bool publish_vhdl;
bool publish_cc;
bool no_file_output;
bool print_warranty;
bool keep_design_units;
bool ignore_standard_library;
bool no_mangling;
bool verbose_output;
bool gen_cc_ref;

// for library manager
string design_library_name;
bool echo_library_dir;

dl_list<char> lib_list;

// global flag for parse errors.  Parse errors include semantic errors
// like undefined symbols and such
bool parse_error = false;

// This object will record which language the analyzer should be
// configured to recognize.
language_processing_control *lang_proc = NULL;

// If the command line switch to capture comments is turned on, this flag
// will be set to true; otherwise it will be set to false. 
bool *capture_comments = false;

void 
help_func(){
    cerr << SAVANT_VERSION << "\n\n";
    cerr <<"THE UNIVERSITY OF CINCINNATI (UC) MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT\nTHE SUITABILITY OF THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT\nNOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A\nPARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY\nDAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING RESULT OF USING, MODIFYING\nOR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.\n";
    cerr << "\nReport problems, comments, etc. to the savant mailing list \"savant-users@cliftonlabs.com\".\n\n";
}

#if defined(__GNUG__)
#define IOS_BIN ios::bin
#else
#define IOS_BIN ios::binary
#endif

#ifdef DEVELOPER_ASSERTIONS
#define _CC_OUT _cc_out
#else
#define _CC_OUT IIRScram::_cc_out
#endif	  

int 
main (int argc, char *argv[]) {
  // here are defaults for global argument variables
  debug_symbol_table      = false;
  echo_library_dir        = false;
  publish_vhdl            = false;
  publish_cc              = false;
  no_file_output          = false;
  print_warranty          = false;
  keep_design_units       = false;
  ignore_standard_library = false;
  no_mangling             = false;
  verbose_output          = false;
  gen_cc_ref              = false;

  // Name of the plugin to change the parse tree to.
  string plugins      = "";

  // true if command line argument --version is present
  bool print_version      = false;

  // these variables are used by the arg_parser to record command line
  // arguments.  DO NOT reference them, use the lang_processing object
  // to discover information for language processing
  bool vhdl_93  = false;
  bool vhdl_ams = false;
  bool vhdl_2001 = false;
  // Again, DO NOT reference the above named variables for anything more
  // than configuring the language_processing_control object.
  
  static ArgumentParser::ArgRecord arg_list[] = {
    {"--capture-comments","capture comments and store them in the design file IIR node", &capture_comments, ArgumentParser::BOOLEAN},
    {"--debug-symbol-table","print out debugging info relating to symbol table", &debug_symbol_table, ArgumentParser::BOOLEAN},
    {"--debug-gen-cc-ref","make code gen. and VHDL line references in c++ code", &gen_cc_ref, ArgumentParser::BOOLEAN},  
    {"--design-library-name", "design library name", &design_library_name, ArgumentParser::STRING},
    {"--echo-library-directory", "show the builtin library path as was specified at build time", &echo_library_dir, ArgumentParser::BOOLEAN},
    {"--publish-vhdl","publish VHDL", &publish_vhdl, ArgumentParser::BOOLEAN},
    {"--publish-cc","publish c++", &publish_cc, ArgumentParser::BOOLEAN},
    {"--plugins","comma seperated list of plugin(s) to use", &plugins, ArgumentParser::STRING},
    {"--no-file-output", "send publish_cc output to stdout instead of files", &no_file_output, ArgumentParser::BOOLEAN},
    {"--warranty-info", "print information about (lack of) warranty", &print_warranty, ArgumentParser::BOOLEAN},
    {"--vhdl-93", "setup the analyzer to process the VHDL 93 language standard (default)", &vhdl_93, ArgumentParser::BOOLEAN},
    {"--vhdl-ams", "setup the analyzer to process the VHDL AMS language standard", &vhdl_ams, ArgumentParser::BOOLEAN},
    {"--vhdl-2001", "setup the analyzer to process the VHDL 2001 language standard", &vhdl_2001, ArgumentParser::BOOLEAN},
    {"--version", "print version number and exit.", &print_version, ArgumentParser::BOOLEAN },
    {"--verbose", "verbose output", &verbose_output, ArgumentParser::BOOLEAN },
    {"","", 0}
  };

  ArgumentParser ap( arg_list ); // , help_func );
  vector<string> argVec = ArgumentParser::vectorifyArguments( argc, argv, true );
  ap.checkArgs( argVec );

  if (print_version) {
    cerr << VERSION << "\n";
    exit(-1);
  }

  if( argc <= 1 ){
    ap.printUsage( argv[0], cerr );
    exit( -1 );
  }

  if( echo_library_dir ){
    cout << BUILD_SAVANTROOT << "/savant/lib" << endl;
    return 0;
  }

  // Invoke the language processing object.  If no other languages are
  // selected, then recognize VHDL 93.
  if (vhdl_ams) {
    lang_proc = new language_processing_control(language_processing_control::VHDL_AMS);
  } else if (vhdl_2001) {
    lang_proc = new language_processing_control(language_processing_control::VHDL_2001);
  } else {
    lang_proc = new language_processing_control(language_processing_control::VHDL_93);
  }

  if (lib_list.size() != 0) {
     cerr << "Libraries specified: ";
     char* lib = lib_list.first();
     while (lib != NULL) {
        cerr << lib << " ";
        lib = lib_list.successor(lib);
     }
     cerr << "\n";
  }
    
  if( print_warranty == true ){
    help_func();
    exit( -1 );
  }

  IIR_DesignFileList *iir_design_files_processed = NULL;    
  string work_lib_name = "work";
  if( design_library_name != "" ){
    work_lib_name = design_library_name;
  }  

  char *plugin_dir = getenv( "SAVANT_PLUGIN_PATH" );
  
  library_manager::instance()->init_std_library(ScramStandardPackage::instance());

  scram parser( true, work_lib_name,
		scram_plugin_class_factory::instance(),
		ScramStandardPackage::instance() );

  if(argc > 1) {
    iir_design_files_processed = parser.parse_files( argVec );  

    if( parse_error == FALSE ){
      cerr << "Parse complete - no errors." << endl;
    }
    else{
      exit( -1 );
    }
  }

  if( iir_design_files_processed != NULL ){
    // Initialize the library module manager to search for the plugin in the plugins directory
    plugin_interface            *plugin = NULL; 

    if (plugin_dir != NULL)
      PluginManager::instance()->addSearchDir(plugin_dir);

    // First add the name of the publish cc/tyvis to list as a special case
    list<string>        plugin_names;
    if (publish_cc == true)
      plugin_names.push_back("libtyvisplugin.la");
    
    //   Now go through the list, and add all the names to the list
    // We're forced to use C style strings to avoid bugs in STL's 
    // substr function
    char                *tempStr        = strdup(plugins.c_str());
    char                *curPluginName  = strtok(tempStr, ",");
    while (curPluginName != NULL) {      
      plugin_names.push_back(curPluginName);
      curPluginName = strtok(NULL, ",");
    }
    free(tempStr);

    // Now we'll walk the list, and process the tree for VHDL
    if (publish_vhdl == true) {
      IIR *to_publish = iir_design_files_processed->first();
      while( to_publish != NULL ){      
	ASSERT( dynamic_cast<IIR_DesignFile *>( to_publish ) );
        to_publish->publish_vhdl( cout );
        cout.flush();
        to_publish =
	  iir_design_files_processed->successor( dynamic_cast<IIR_DesignFile *>(to_publish) );
      }
    }
    
    PluginBase *module = NULL;
    for (list<string>::iterator iter = plugin_names.begin(); iter != plugin_names.end(); iter++) {
      if ((module = PluginManager::instance()->loadPlugin(*iter)) == NULL) {
        cout << "Error: " << PluginManager::instance()->getLastError() << endl;
        exit (1);
      }
      
      // Just got a module pointer, cast it over to our interface
      plugin = dynamic_cast<plugin_interface *>(module); 
    
      // Now we'll walk the list, and process the tree(s) for plugins
      IIR_DesignFile *to_publish = dynamic_cast<IIR_DesignFile *>(iir_design_files_processed->first());
      while( to_publish != NULL ){              
        if ((publish_cc == true) && (iter == plugin_names.begin())){        
          cerr << "Starting C++ code generation..." << endl;
          char last_unit = false;
          if( iir_design_files_processed->successor( to_publish ) == NULL ){
            last_unit = true;
          }
          char **arg_list = new char *;
          arg_list[0] = new char[10];
          arg_list[0] = &last_unit;
          plugin->process_tree(to_publish, 1, arg_list);
          cerr << "Code generation finished." << endl;
        } else {
          // Normal plugin
          cerr << "Starting plugin " << *iter << endl;
          plugin->process_tree(to_publish, 0, NULL);
          cerr << "Plugin processing completed." << endl;
        }

        to_publish = dynamic_cast<IIR_DesignFile *>(iir_design_files_processed->successor( to_publish ));
      }

      PluginManager::instance()->unloadPlugin(*iter);
    }
  }

  return 0;
}

