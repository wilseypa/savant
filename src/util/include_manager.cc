// Copyright (c) The University of Cincinnati.
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

#include "include_manager.hh"
#include "hash_table.hh"
#include "IIRScram.hh"

include_manager::include_manager() : 
  my_included_files( *new hash_table<included_file_record> ){}

include_manager::~include_manager(){}

void 
include_manager::add_include( const string file_to_include, 
			      bool system_include ){
  included_file_record *rec = my_included_files.hash_look( file_to_include.c_str() );
  if( rec->get_already_included() == false ){
    rec->set_already_included();
    if( system_include == true ){
      rec->set_system_include();
    }
  }
}

void
include_manager::publish_includes( ostream &os ){
  dl_list<included_file_record> *as_list = my_included_files.convert_to_list();
  
  included_file_record *current = as_list->first();
  while( current != NULL ){
    bool system_include = current->get_system_include();
    os << "#include ";
    if( system_include == true ){
      os << "<";
    }
    else{
      os << "\"";
    }
    os << current->get_included_file_name();
    if( system_include == true ){
      os << ">";
    }
    else{
      os << "\"";
    }
    os << "\n";
    current = as_list->successor( current );
  }

  delete as_list;
}

void
include_manager::included_file_record::set_key( const string key,  const int len ){
  included_file_name = key;
}
