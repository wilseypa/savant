
#ifndef ARG_PARSER_HH
#define ARG_PARSER_HH

// Copyright (c) 1995-2001 The University of Cincinnati.
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

// Authors: Dale E. Martin      dmartin@cliftonlabs.com
//          Philip A. Wilsey    philip.wilsey@ieee.org
//          Timothy J. McBrayer 

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "bool.hh"

#include <cstdlib>
#include <cstring>
#include <iostream>
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;

class arg_parser {

  /** 

  This file contains the declarations for a class which accepts a list of
  arguments with addresses of the variables they affect, and parses argv
  and argc to check for them.  Errors are dealt with as well.  The
  variables can either be boolean, char*, or dl_list<char*>; which type a
  variable is is determined by a value of the enumerated type
  arg_parser::arg_type.

  Here is an example of the use of this class:
  
  bool arg1;      // These must be static or global scope...
  bool arg2;
  char *arg3;
  
  arg_parser::arg_record arg_list[] = {
  { "-arg1", &arg1, arg_parser::BOOLEAN }, 
  { "-arg2", &arg2, arg_parser::BOOLEAN },
  { "-arg3", &arg3, arg_parser::STRING },
  { NULL, NULL }
  };


  int main( int argc, char *argv[] ){
  arg1 = true;    // default initialization must occur before the
  arg2 = false;   // arg_parser is called!
  arg3 = NULL;
  
  arg_parser ap( arg_list );
  ap.check_args( argc, argv );
  */

  friend ostream &operator<<(ostream &, arg_parser &);

public:
  enum arg_type {BOOLEAN, INTEGER, STRING, STRING_LIST};

  struct arg_record {
    const char *arg_text;
    const char *arg_help;
    void *data;
    arg_type type;
  };

  arg_parser( arg_record *record_ptr, void (*init_help_func)() ){
    get_arg_array(record_ptr);
    help_func = init_help_func;
  }
  
  ~arg_parser() {}
    
  /** The int is the number of args (argc), the char ** is argv, and the
      bool is whether to complain and exit on error or not... */
  void check_args(int &, char **, bool = true );
  
  void print_usage( char *binary_name );
  
private:
  arg_record *array_of_arg_records;
  int num_args;
  void (*help_func)();
  
  /** This method is used to pull arguments from the command line as
      they're processed... */
  void remove_arg( int arg_to_remove, int &argc, char **argv);
  
  /** This method checks the arguments passed in to see if there are any in
    the form "-blah" and complains, if the global var
    "complain_and_exit_on_error" is set to true. */
  void check_remaining( int argc, char **argv,
			bool complain_and_exit_on_error);

  void get_arg_array(arg_record[]);
  
};

inline 
ostream &operator<<(ostream &os, arg_parser &ap){
  const int num_spaces = 3;
  const unsigned int indentation = 2;
  
  /* calculate the length of the longest argument */
  int i = 0;
  unsigned int maxlen = 0;
  while( ap.array_of_arg_records[i].arg_text != NULL ){
    if( strlen(ap.array_of_arg_records[i].arg_text) > maxlen ){
      maxlen = strlen(ap.array_of_arg_records[i].arg_text);
    }
    i++;
  }
  
  // print the argument array
  unsigned int j;
  i = 0;
  while( ap.array_of_arg_records[i].arg_text != NULL ){
    
    // indent the proper amount
    for( j = 0; j < indentation; j++ ){
      os << " ";
    }
    
    // here is the argument
    os << ap.array_of_arg_records[i].arg_text;
    
    // print out the padding - leave num_spaces spaces between args and 
    // help text...
    for( j = 0; j < maxlen - strlen( ap.array_of_arg_records[i].arg_text )
		  + num_spaces ; j++ ){
      os << " ";
    }
    
    // here is the help string.
    os << ap.array_of_arg_records[i].arg_help << endl;
    i++;
  }
  
  for( j = 0; j < indentation; j++ ){
    os << " ";
  }
  
  os << "--help";
  for( j = 0; j < maxlen - strlen("--help")  + num_spaces ; j++ ){
    os << " ";
  }
  os << "print this message" << endl;
  
  return os;
}

#endif
