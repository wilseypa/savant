#ifndef ERROR_FUNC_HH
#define ERROR_FUNC_HH

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


// Error reporting is done following the gnu guidlines.  Here is what they
// have to say:

// Formatting Error Messages
// *************************

//    Error messages from compilers should look like this:

//      SOURCE-FILE-NAME:LINENO: MESSAGE

//    Error messages from other noninteractive programs should look like
// this:

//      PROGRAM:SOURCE-FILE-NAME:LINENO: MESSAGE

// when there is an appropriate source file, or like this:

//      PROGRAM: MESSAGE

// when there is no relevant source file.

// In an interactive program (one that is reading commands from a
// terminal), it is better not to include the program name in an error
// message.  The place to indicate which program is running is in the
// prompt or with the screen layout.  (When the same program runs with
// input from a source other than a terminal, it is not interactive and
// would do best to print error messages using the noninteractive style.)

// The string MESSAGE should not begin with a capital letter when it
// follows a program name and/or file name.  Also, it should not end with a
// period.

// Error messages from interactive programs, and other messages such as
// usage messages, should start with a capital letter.  But they should not
// end with a period.

#include "savant_config.hh"
#include <string>

class IIR;
class IIR_Name;
class IIR_Identifier;
class IIR_TypeDefinition;
class IIR_Declaration;
class ANTLRToken;
class plugin_class_factory;

namespace savant {
  template <class type> class set;
}

using std::string;

enum severity { WARNING, FATAL };

void
report_error( const char *message,
              int line_number,
              severity how_serious);
void 
report_error( const char *message, 
	      int line_number = -1, 
	      IIR_Identifier *file_name = NULL,
	      severity = FATAL );

void 
report_error( const string &message, 
	      int line_number = -1,
	      IIR_Identifier *file_name = NULL,
	      severity = FATAL );

void 
report_error ( ANTLRToken *tok, const string &, severity = FATAL );

void 
report_error ( ANTLRToken *tok, const char *msg, severity = FATAL );

void 
report_error ( IIR *if_node, const string &message, severity = FATAL );

void 
report_error ( IIR *if_node, const char *msg, severity = FATAL );

void 
report_undefined_symbol( IIR * );

void 
report_undefined_symbol( IIR_Declaration *, IIR_Name * );

void 
report_undefined_symbol( savant::set<IIR_TypeDefinition> *, IIR * );

void 
report_ambiguous_error( IIR *error_info, savant::set<IIR_Declaration> *error_set );

void 
report_ambiguous_error( IIR *error_info, savant::set<IIR_TypeDefinition> *error_set );

void 
report_ambiguous_error( IIR_Declaration *prefix,
			IIR_Name *suffix,
			savant::set<IIR_Declaration> *error_set );

void
report_undefined_function(char *func_name);

#endif

