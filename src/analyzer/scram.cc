
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

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu

//---------------------------------------------------------------------------
#include "scram.hh"
#include "savant.hh"
#include "symbol_table.hh"
#include <FlexLexer.h>
#include "VHDLLexer.hh"
#include "VHDLParser.h"
#include "error_func.hh"


#include "library_manager.hh"
#include "ScramStandardPackage.hh"
#include "plugin_class_factory.hh"

#include "IIRBase_DesignFile.hh"
#include "IIR_DesignFileList.hh"
#include "IIRBase_LibraryDeclaration.hh"

extern bool verbose_output;
extern bool standard_fir;

scram::scram( bool                      init_need_to_write_libraries, 
              IIR_LibraryDeclaration    *work_library, 
              plugin_class_factory      *factory, 
              StandardPackage           *package,
              bool                      need_to_load_std_lib ) : 
  need_to_write_libraries( init_need_to_write_libraries ),
  my_work_library( work_library ),
  my_std_package( package ),
  my_class_factory( factory ),
  transmuted_node( NULL ){
  my_symbol_table = new symbol_table(package, need_to_load_std_lib);
  my_design_files = factory->new_IIR_DesignFileList();
}

scram::scram( bool init_need_to_write_libraries, 
	      const string &work_library_name,
              plugin_class_factory *factory, 
              StandardPackage *package) : 
  my_symbol_table( new symbol_table(package) ),
  need_to_write_libraries( init_need_to_write_libraries ),
  my_work_library( 0 ),
  my_std_package( package ),
  my_class_factory( factory ),
  transmuted_node( NULL ){

  my_work_library = library_manager::instance()->find_or_create_library( work_library_name, factory );
  ASSERT( my_work_library != 0 );
  my_symbol_table->add_declaration( my_work_library );
  my_design_files = factory->new_IIR_DesignFileList();
}

scram::~scram(){
  delete my_symbol_table;
  my_symbol_table = NULL;
  my_std_package = NULL;
  my_class_factory = NULL;
}

IIR_DesignFileList *
scram::parse_files( const vector<string> &fileList ){
  for( vector<string>::const_iterator currentFile = fileList.begin();
       currentFile < fileList.end();
       currentFile++ ){
    cerr << "Processing file " << *currentFile << endl;
    IIR_DesignFile *parsed_file = parse_file( *currentFile, my_work_library );
    my_design_files->append( parsed_file );
  }
  
  return my_design_files;
}

IIR_DesignFile *
scram::parse_file( const string &filename, IIR_LibraryDeclaration *lib ){
  ifstream yyin( filename.c_str() );

  if( verbose_output == true ){
    cerr << "Parse_file parsing " << filename << endl;
  }

  if (yyin == NULL) {
    ostringstream err;
    err << "FATAL ERROR, COULD NOT OPEN FILE: " << filename;
    report_error( err.str() );
    exit( 1 );
  } 

  IIRScram_DesignFile *vhdl_design_file = new IIRScram_DesignFile();
  ASSERT(vhdl_design_file != NULL);
  vhdl_design_file->set_parser( this );
  vhdl_design_file->set_standard_package( get_standard_package() );
  vhdl_design_file->set_class_factory( get_class_factory() );
  vhdl_design_file->set_name( IIRBase_Identifier::get(filename, get_class_factory() ) );
  if( my_work_library->get_design_file() == 0 ){
    my_work_library->set_design_file( vhdl_design_file );
  }

  VHDLLexer scan( &yyin , vhdl_design_file->get_comments());
  ANTLRTokenBuffer pipe(&scan);
  scan.resetLexerFileLocators(filename);

  VHDLParser parser(&pipe);
  parser.init();
  parser.setEofToken(ENDFILE);

  parser.design_file( vhdl_design_file,
		      my_symbol_table,
		      lib,
		      need_to_write_libraries,
		      my_class_factory,
		      my_std_package);

  yyin.close();

  return vhdl_design_file;
}

IIR_LibraryDeclaration *
scram::get_work_library() const {
  return my_work_library;
}

scram *
scram::convert_node(plugin_class_factory *factory) {
  if (transmuted_node != NULL) {
    return transmuted_node;
  } else {
    // Transmute node
    scram *result = new scram(*this);
    
    result->need_to_write_libraries = need_to_write_libraries;
    if( my_work_library ){
      result->my_work_library = dynamic_cast<IIR_LibraryDeclaration *>(dynamic_cast<IIRBase_LibraryDeclaration *>(my_work_library)->convert_node(my_work_library, factory));
    }
    if( my_std_package ){
      result->my_std_package = 
	dynamic_cast<StandardPackage *>(my_std_package->convert_tree( factory));
    }

    if( my_design_files ){
      result->my_design_files = dynamic_cast<IIR_DesignFileList *>(dynamic_cast<IIRBase_DesignFileList *>(my_design_files)->convert_node(my_design_files, factory));
    }
    
    result->my_class_factory = factory;

    transmuted_node = result;
    return result;
  }
}
