
// Copyright (c) The University of Cincinnati.  
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

#include "IIRScram_ArchitectureStatement.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_SignalDeclaration.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "StandardPackage.hh"
#include "symbol_table.hh"
#include "error_func.hh"
#include "constraint_functors.hh"
#include <sstream>
using std::ostringstream;

IIRScram_ArchitectureStatement::IIRScram_ArchitectureStatement() {}
IIRScram_ArchitectureStatement::~IIRScram_ArchitectureStatement() {}

void 
IIRScram_ArchitectureStatement::_resolve_guard_signal( symbol_table *sym_tab ){
  // Lookup all signals named "guard"
  IIRScram_SignalDeclaration            *guard_signal = NULL;
  savant::set<IIRScram_Declaration>     *guard_decls = NULL;
  constraint_functor                    *functor = NULL;

  guard_decls = new savant::set<IIRScram_Declaration>(*(sym_tab->find_set( "guard" )->convert_set<IIRScram_Declaration>()));
  if( guard_decls == NULL ){
    ostringstream err;
    err << "No signal |guard|, implicit or explicit, has been declared.";
    report_error( this, err.str() );
    goto finish;
  }
  
  functor = new is_signal_functor();
  guard_decls->reduce_set( functor );
  delete functor;
  ASSERT( guard_decls->size() == 1 || guard_decls->size() == 0 );

  if( guard_decls->size() == 1 ){
    // Get rid of any that aren't boolean typed.
    guard_signal = dynamic_cast<IIRScram_SignalDeclaration *>(guard_decls->getElement());
    if( guard_signal->_get_subtype() != 
        dynamic_cast<IIRScram_EnumerationSubtypeDefinition *>(_get_design_file()->get_standard_package()->get_boolean_type())){
      guard_signal = NULL;
    }
  }

  if( guard_signal == NULL ){
    ostringstream err;
    err << "Signal |guard| must be a signal of builtin type |boolean|.";
    report_error( this, err.str() );    
  }
  else{
    set_guard_signal( guard_signal );
  }

 finish:
  delete guard_decls;
}
