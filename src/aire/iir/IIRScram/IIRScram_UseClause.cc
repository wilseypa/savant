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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_DesignFile.hh"
#include "IIRScram_UseClause.hh"
#include "IIRScram_Name.hh"
#include "IIRScram_PackageDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_SelectedName.hh"
#include "IIRScram_SimpleName.hh"
#include "IIRScram_LibraryDeclaration.hh"

#include "symbol_table.hh"
#include "set.hh"
#include "error_func.hh"

#include <sstream>
using std::ostringstream;

#include "scram_plugin_class_factory.hh"

extern bool debug_symbol_table;

IIRScram_UseClause::IIRScram_UseClause(){
  static const string tmp_declarator = "use clause declarator";
  static IIRScram_Identifier *use_clause_declarator = dynamic_cast<IIRScram_Identifier *>(IIRScram_Identifier::get( tmp_declarator, scram_plugin_class_factory::instance() ));
  set_declarator( use_clause_declarator );
}

void
IIRScram_UseClause::_type_check(){
  savant::set<IIRScram_Declaration> *use_clause_decls = _get_selected_name()->_symbol_lookup();

  if( use_clause_decls == NULL ){
    ostringstream err;
    err << "Unable to locate logical library |" << *_get_selected_name() << "|."
	<< " Perhaps this library hasn't been successfully analyzed yet.";
    report_error( this, err.str() );
    return;
  }

  IIRScram_Name *tmp_name =  _get_selected_name();
  ASSERT( tmp_name->get_kind() == IIR_SELECTED_NAME );

  IIRScram_Declaration *decl = use_clause_decls->getElement();
  while( decl != NULL ){
    tmp_name->_decl_to_decl( decl );
    
    if( debug_symbol_table == true ){
      cerr << _get_symbol_table() << " - processing use clause - making |" 
	   << tmp_name << "| visible!\n";
    }
    if( decl->is_package_declaration() == TRUE ){
      _make_interface_visible( _get_symbol_table() );      
    }
    else{
      _get_symbol_table()->make_visible( decl );
    }
    decl =  use_clause_decls->getNextElement();    
  }

  delete use_clause_decls;

  ASSERT( _get_selected_name()->is_resolved() == TRUE );
}

void 
IIRScram_UseClause::_make_interface_visible( symbol_table *sym_tab ){
  ASSERT( _get_selected_name()->is_resolved() == TRUE );
  savant::set<IIRScram_Declaration> *decls = _get_selected_name()->_symbol_lookup();
  if( decls != 0 ){
    ASSERT( decls->size() == 1 );
    IIRScram_Declaration *decl = decls->getElement();
    if( sym_tab->in_use_list( decl ) == FALSE ){
      sym_tab->add_to_use_list( decl );
      decl->_make_interface_visible( sym_tab );
    }
  }
  delete decls;
}

IIRScram *
IIRScram_UseClause::_clone() {
  return this;
}

visitor_return_type *
IIRScram_UseClause::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_UseClause(this, arg);
};

IIRScram_Name *
IIRScram_UseClause::_get_selected_name() {
  return dynamic_cast<IIRScram_Name *>(get_selected_name());
}
