
// Copyright (c) 1996-2001 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING
// OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found
// in the file "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     
//          Umesh Kumar V. Rajasekaran
//          Krishnan Subramani  
//          Narayanan Thondugulam

//---------------------------------------------------------------------------
#include "IIRScram_ArchitectureStatementList.hh"
#include "IIRScram_AssociationElement.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_ConcurrentProcedureCallStatement.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_FunctionCall.hh"
#include "IIRScram_IndexedName.hh"
#include "IIRScram_InterfaceDeclaration.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_ProcedureCallStatement.hh"
#include "IIRScram_ProcedureDeclaration.hh"
#include "IIRScram_ProcessStatement.hh"
#include "IIRScram_SequentialStatementList.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_WaitStatement.hh"
#include "error_func.hh"
#include "resolution_func.hh"
#include "set.hh"

#include <sstream>
using std::ostringstream;

IIRScram_ConcurrentProcedureCallStatement::IIRScram_ConcurrentProcedureCallStatement() {
  set_actual_parameter_part(new IIRScram_AssociationList());
  set_process_statement_part(new IIRScram_ArchitectureStatementList());
}

IIRScram_ConcurrentProcedureCallStatement::~IIRScram_ConcurrentProcedureCallStatement(){}

void 
IIRScram_ConcurrentProcedureCallStatement::_type_check(){
  // Blatantly stolen from IIRScram_ProcedureCallStatement.  Changes need to be
  // propagate back to that file.
  savant::set<IIRScram_TypeDefinition> proc_rval_set(dynamic_cast<IIRScram_TypeDefinition *>(IIRScram_ProcedureDeclaration::get_procedure_return_type())); 
  set_procedure_name( _get_procedure_name()->_semantic_transform( &proc_rval_set ));
  
  if( get_procedure_name()->get_kind() != IIR_FUNCTION_CALL ){
    savant::set<IIRScram_Declaration> *my_decls;
    if( get_procedure_name()->get_kind() == IIR_INDEXED_NAME ){
      my_decls = (dynamic_cast<IIRScram_IndexedName *>(get_procedure_name()))->_get_prefix()->_symbol_lookup();
    }
    else{
      my_decls = _get_procedure_name()->_symbol_lookup();
    }

    if( my_decls == NULL ){
      report_undefined_symbol( _get_procedure_name() );
    }

    IIRScram_Declaration *current_decl = my_decls->getElement();
    while( current_decl != NULL ){
      if( current_decl->get_kind() != IIR_PROCEDURE_DECLARATION ){
	my_decls->remove( current_decl );
      }
      current_decl = my_decls->getNextElement();
    }
    
    resolve_subprogram_decls( my_decls, 
                              _get_actual_parameter_part(), 
                              &proc_rval_set );
    
    switch( my_decls->size() ){
    case 0:{
      ostringstream err;
      err << "No declaration of procedure with signature matching |"
	  << *_get_procedure_name() << "|.";
      report_error( this, err.str() );
      break;
    }
    case 1:{
      set_procedure_name( _get_procedure_name()->_decl_to_decl( my_decls->getElement() ) );

      IIRScram *temp_name = _get_procedure_name();
      ASSERT( temp_name->is_subprogram() == TRUE );
      IIRScram_SubprogramDeclaration *my_decl = dynamic_cast<IIRScram_SubprogramDeclaration *>(temp_name);

      _get_actual_parameter_part()->_resolve_and_order( my_decl->_get_interface_declarations(),
							NULL, this);
      break;
    }
    default:{
      report_ambiguous_error( _get_procedure_name(), my_decls->convert_set<IIR_Declaration>() );
    }
    }
  
    delete my_decls;
  }
  else{
    
    IIRScram_FunctionCall *old_proc_name =  dynamic_cast<IIRScram_FunctionCall *>(get_procedure_name());
    set_procedure_name( old_proc_name->get_implementation() );
    
    set_actual_parameter_part(dynamic_cast<IIRScram_AssociationList *>(IIRScram_List::_listcopy(old_proc_name->_get_parameter_association_list(), get_design_file()->get_class_factory())));

    delete old_proc_name;
  }
  ASSERT( _get_procedure_name()->is_resolved() == TRUE );  
}


visitor_return_type *
IIRScram_ConcurrentProcedureCallStatement::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ConcurrentProcedureCallStatement(this, arg);
};

IIRScram *
IIRScram_ConcurrentProcedureCallStatement::_get_procedure_name() {
  return dynamic_cast<IIRScram *>(get_procedure_name());
}

IIRScram_AssociationList *
IIRScram_ConcurrentProcedureCallStatement::_get_actual_parameter_part() {
  return dynamic_cast<IIRScram_AssociationList *>(get_actual_parameter_part());
}
