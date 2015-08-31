
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

#include "IIR.hh"
#include "IIR_Identifier.hh"
#include "IIR_TypeDefinition.hh"
#include "IIR_SelectedName.hh"
#include "IIR_Declaration.hh"
#include "IIRScram_Name.hh"
#include "IIRScram_SelectedName.hh"

#include "plugin_class_factory.hh"
#include "set.hh"
#include "error_func.hh"
#include "VHDLToken.hh"

#include <sstream>
using std::ostringstream;

extern bool parse_error;

void
report_error( const char *message,
              int line_number,
              severity how_serious) {

  if( how_serious == FATAL ){
    parse_error = true;
  }
  
  if( line_number != -1 ){
    cerr << line_number << ":";
  }

  if( how_serious == WARNING ){
    cerr << "warning: ";
  }

  cerr << message << endl;
}

void 
report_error( const char *message, 
	      int line_number, 
	      IIR_Identifier *file_name, 
	      severity how_serious ){

  if( file_name != NULL ){
    cerr << *file_name << ":";
  }

  report_error(message, line_number, how_serious);
}

void 
report_error( const string &message,
	      int line_number, 
	      IIR_Identifier *file_name, 
	      severity how_serious ){
  if( how_serious == FATAL ){
    parse_error = true;
  }
  
  report_error( message.c_str(), line_number, file_name, how_serious );
}

void 
report_error (ANTLRToken *tok, const string &message,  severity how_serious ) {
  if( how_serious == FATAL ){
    parse_error = true;
  }

  if (tok->getFileName() != NULL){
    cerr << tok->getFileName() << ":";
  }

  report_error(message.c_str(), tok->getLine(), how_serious );
}

void 
report_error (ANTLRToken *tok, const char *msg, severity how_serious) {
  if( how_serious == FATAL ){
    parse_error = true;
  }

  if (tok->getFileName() != NULL)
    cerr << tok->getFileName();
 
  report_error(msg, tok->getLine(), how_serious );
}

void 
report_error( IIR *if_node, 
	      const string &message,
	      severity how_serious ){
  if( how_serious == FATAL ){
    parse_error = true;
  }

  report_error( message, if_node->get_line_number(), if_node->get_file_name(), how_serious );
}

void 
report_error( IIR *if_node, const char *msg, severity how_serious ) {
  if( how_serious == FATAL ){
    parse_error = true;
  }

  report_error(msg, if_node->get_line_number(), if_node->get_file_name());
}

void 
report_undefined_symbol( IIR *name ){
  ostringstream err;
  err << "|" << *name << "| is undefined in this scope.";
  report_error( name, err.str() );
}

void 
report_undefined_symbol( IIR_Declaration *prefix, IIR_Name *suffix ){
  ostringstream err;
  err << "|" << *prefix << "." << *suffix << "| is undefined in this scope.";
  report_error( suffix, err.str() );
}

void 
report_undefined_symbol( savant::set<IIR_TypeDefinition> *type_def_set, IIR *name ){
  if( type_def_set == NULL || type_def_set->size() == 0 ){
    ostringstream err;
    err << "|" << *name << "| is undefined in this scope.";
    report_error( name, err.str() );
  }
  // else no error
}


void 
report_ambiguous_error( IIR *error_info, savant::set<IIR_Declaration> *error_set ){
  ostringstream err;

  ASSERT( error_set != NULL );
  ASSERT( error_set->size() > 1 );
  ASSERT( error_set->getElement() != NULL );

  err << "Can't disambiguate symbol |" 
      << *dynamic_cast<IIR_TextLiteral *>(error_set->getElement()->get_declarator()) 
      << "| from the following choices:";

  int i;
  IIR_Declaration *current_decl = error_set->getElement();
  for( i = 0; i < error_set->size(); i++ ){
    if( current_decl != NULL ){
      err << "\n|" << *current_decl <<"|";
      
      if(  current_decl->get_file_name() != NULL ){
        // TODO: Remove Scram
	err << ", declared in file |" << *current_decl->get_file_name() << "|";
      }

      if( current_decl->get_line_number() != -1 ){
	err << ", line " <<  current_decl->get_line_number();
      }
      err << ".";
    }
    current_decl = error_set->getNextElement();
  }
  
  report_error( error_info, err.str() );
}

void 
report_ambiguous_error( IIR *error_info, savant::set<IIR_TypeDefinition> *error_set ){
  IIR_TypeDefinition *current;
  
  ostringstream err;
  err << "Cannot determine unique type for |" 
      << *error_info << "|.  Choices include:\n";

  current = error_set->getElement();
  while( current != NULL ){
    // I broke this up to make it possible to debug it.
    err << "Type |" 
        << *current->get_declarator();
    err << "|, with type <" 
        << *current << ">"; 
    if( current->get_file_name() != NULL ){
      err << ", declared in file |" << *current->get_file_name() << "|";
    }

    if( current->get_line_number() != -1 ){
      err << ", line " <<  current->get_line_number();
    }

    err << ".";

    current = error_set->getNextElement();
    if( current != NULL ){
      err << "\n";
    }
  }

  report_error( error_info, err.str() );
}


void 
report_ambiguous_error( IIR_Declaration *prefix, 
			IIR_Name *suffix, 
			savant::set<IIR_Declaration> *error_set ){

  IIR_SelectedName *error_info = new IIRScram_SelectedName();
  error_info->set_prefix( prefix );
  error_info->set_suffix( suffix );
  
  // This should copy only the line number info over.
  //  ((IIRScram *)error_info)->_clone( dynamic_cast<IIRScram_Name *>(suffix) );
  report_ambiguous_error( error_info, error_set );
  delete error_info;
}

void
report_undefined_function(char *function_name, IIR* node) {
  ostringstream os;
  os << function_name << " not defined for node: " << node->get_kind_text();
  report_error( node, os.str() );
  abort();
}
