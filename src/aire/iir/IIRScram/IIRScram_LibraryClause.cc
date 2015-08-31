
// Copyright (c) 1996-2000 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
// DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.


// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     mal@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_LibraryClause.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_LibraryDeclaration.hh"
#include "IIRScram_SimpleName.hh"
#include "library_manager.hh"
#include "scram_plugin_class_factory.hh"
#include "symbol_table.hh"
#include "set.hh"
#include "error_func.hh"

#include <sstream>
using std::ostringstream;

void 
IIRScram_LibraryClause::_type_check(){
  IIR_Boolean is_std_lib = FALSE;
  IIRScram *logical_name = _get_logical_name();
  ASSERT( logical_name->is_text_literal() == TRUE );

  IIR_TextLiteral *as_literal = dynamic_cast<IIR_TextLiteral *>(logical_name);
  
  if( IIRBase_TextLiteral::cmp( as_literal, "std" ) == 0 ){  
    is_std_lib = TRUE;
  }

  // Calling this method in this manner will cause the library to be found
  // and be added to the symbol table if needed.  
  IIRScram_LibraryDeclaration *lib_decl =
    dynamic_cast<IIRScram_LibraryDeclaration *>(library_manager::instance()->find_library( as_literal, scram_plugin_class_factory::instance() ));
  if( lib_decl == NULL ){
    ostringstream err;
    err << "Could not locate a library directory corresponding to logical library name |" 
	<< *logical_name << "|.  Perhaps you need to create it with the option "
	<< "--design-library-name, or add a directory to the environment variable "
	<< "VHDL_LIBRARY_PATH";
    report_error( logical_name, err.str() );
  }
  else{
    if( is_std_lib == FALSE ){
      copy_location( this, lib_decl );
      lib_decl->_add_declaration();    
    }
  }

  set_library_declaration( lib_decl );  
}

visitor_return_type *
IIRScram_LibraryClause::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_LibraryClause(this, arg);
};

IIRScram_Identifier *
IIRScram_LibraryClause::_get_logical_name() {
  return dynamic_cast<IIRScram_Identifier *>(get_logical_name());
}
