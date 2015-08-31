
// Copyright (c) 1996-2003 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer 
//          Malolan Chetlur     
//          Radharamanan Radhakrishnan
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam 
//          Swaminathan Subramanian
//	    Magnus Danielson    cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_ArchitectureDeclaration.hh"
#include "IIRScram_CommentList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_DesignFileList.hh"
#include "IIRScram_EntityDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_LibraryDeclaration.hh"
#include "IIRScram_LibraryUnitList.hh"

#include "scram.hh"
#include "set.hh"

#include "savant_config.hh"
#include "language_processing_control.hh"
#include "library_manager.hh"

IIRScram_DesignFile::IIRScram_DesignFile() {
  set_comments(new IIRScram_CommentList());
  set_library_units(new IIRScram_LibraryUnitList());
}

IIRScram_DesignFile::~IIRScram_DesignFile() {
  //Release the list memory
  delete get_comments();
  delete get_library_units();
}

void 
IIRScram_DesignFile::_set_file_name( const string &new_file_name ){
  set_name( IIRScram_Identifier::get( new_file_name, get_class_factory() ) );
}

symbol_table *
IIRScram_DesignFile::_get_symbol_table(){
  ASSERT( my_parser != NULL );
  ASSERT( my_parser->get_symbol_table() != NULL );
  return my_parser->get_symbol_table();
}

IIRScram_LibraryDeclaration *
IIRScram_DesignFile::_get_work_library(){
  ASSERT( my_parser != NULL );
  return dynamic_cast<IIRScram_LibraryDeclaration *>(my_parser->get_work_library());
}

visitor_return_type *
IIRScram_DesignFile::_accept_visitor( node_visitor *visitor,
				      visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_DesignFile(this, arg);
}

// IIRBase Function Wrapper(s)
IIRScram_CommentList *
IIRScram_DesignFile::_get_comments() {
  return dynamic_cast<IIRScram_CommentList *>(get_comments());
}

IIRScram_LibraryUnitList *
IIRScram_DesignFile::_get_library_units() {
  return dynamic_cast<IIRScram_LibraryUnitList *>(get_library_units());
}

IIRScram *
IIRScram_DesignFile::_get_name() {
  return dynamic_cast<IIRScram *>(get_name());
}
