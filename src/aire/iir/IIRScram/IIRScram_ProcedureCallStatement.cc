
// Copyright (c) 1996-2003 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
// DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found
// in the file "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin      dmartin@cliftonlabs.com
//          Timothy J. McBrayer
//          Malolan Chetlur    
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam
//---------------------------------------------------------------------------

#include "IIRScram_AssociationElementByExpression.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_DeclarationList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_FunctionCall.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_IndexedName.hh"
#include "IIRScram_InterfaceDeclaration.hh"
#include "IIRScram_InterfaceList.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_List.hh"
#include "IIRScram_ProcedureCallStatement.hh"
#include "IIRScram_ProcedureCallStatement.hh"
#include "IIRScram_ProcedureDeclaration.hh"
#include "IIRScram_SimpleName.hh"
#include "IIRScram_TypeDeclaration.hh"
#include "IIRScram_TypeDefinition.hh"
#include "set.hh"
#include "error_func.hh"
#include "resolution_func.hh"
#include "savant.hh"

#include <sstream>
using std::ostringstream;

extern bool parse_error;

IIRScram_ProcedureCallStatement::IIRScram_ProcedureCallStatement() {
  set_actual_parameter_part(new IIRScram_AssociationList());
}

IIRScram_ProcedureCallStatement::~IIRScram_ProcedureCallStatement(){}

void 
IIRScram_ProcedureCallStatement::_type_check(){
  // Blatantly stolen from IIRScram_ProcedureCallStatement.  Changes need to be
  // propagate back to that file.

  savant::set<IIRScram_TypeDefinition> proc_rval_set(dynamic_cast<IIRScram_TypeDefinition *>(IIRScram_ProcedureDeclaration::get_procedure_return_type())); 
  set_procedure_name( _get_procedure_name()->_semantic_transform( &proc_rval_set ));
  
  if( get_procedure_name()->get_kind() != IIR_FUNCTION_CALL ){
    savant::set<IIRScram_Declaration> *my_decls = NULL;
    if( get_procedure_name()->get_kind() == IIR_INDEXED_NAME ){
      my_decls = (dynamic_cast<IIRScram_IndexedName *>(get_procedure_name()))->_get_prefix()->_symbol_lookup();
    }
    else{
      my_decls = _get_procedure_name()->_symbol_lookup();
    }

    if( my_decls == NULL ){
      report_undefined_symbol( _get_procedure_name() );
      return;
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
							NULL, this );
      _get_actual_parameter_part()->_fill_in_defaults( this,
						       my_decl->_get_interface_declarations() );
      break;
    }
    default:{
      report_ambiguous_error( _get_procedure_name(), my_decls->convert_set<IIR_Declaration>() );
    }
    }
  
    delete my_decls;
  }
  else{
    
    IIRScram_FunctionCall *old_proc_name =  dynamic_cast<IIRScram_FunctionCall *>(_get_procedure_name());
    set_procedure_name( old_proc_name->get_implementation() );
    
    IIRScram_AssociationList *new_list = new IIRScram_AssociationList;
    IIRScram_AssociationList *old_list = old_proc_name->_get_parameter_association_list();
    for (IIRScram_AssociationElement *ptr = dynamic_cast<IIRScram_AssociationElement *>(old_list->first());
         ptr != NULL; ptr = dynamic_cast<IIRScram_AssociationElement *>(old_list->successor(ptr))) {
      new_list->append(ptr);
    }
    set_actual_parameter_part(new_list);

    delete old_proc_name;
  }
    
  ASSERT( _get_procedure_name()->is_resolved() == TRUE );  
}

IIRScram*
IIRScram_ProcedureCallStatement::_clone() {
  IIRScram_ProcedureCallStatement *callstmt = new IIRScram_ProcedureCallStatement();

  IIRScram_SequentialStatement::_clone(callstmt);
  callstmt->set_procedure_name(get_procedure_name());
  
  IIRScram_AssociationElement *newassoc, *assoc = 
    dynamic_cast<IIRScram_AssociationElement *>(get_actual_parameter_part()->first());
  while (assoc != NULL) {
    newassoc = dynamic_cast<IIRScram_AssociationElement*>(assoc->_clone());
    callstmt->get_actual_parameter_part()->append(newassoc);
    assoc = dynamic_cast<IIRScram_AssociationElement*>(get_actual_parameter_part()->successor(assoc));
  }

  return callstmt;
}

visitor_return_type *IIRScram_ProcedureCallStatement::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ProcedureCallStatement(this, arg);
};

// IIRBase Function Wrapper(s)
IIRScram_AssociationList *
IIRScram_ProcedureCallStatement::_get_actual_parameter_part() {
  return dynamic_cast<IIRScram_AssociationList *>(get_actual_parameter_part());
}

IIRScram *
IIRScram_ProcedureCallStatement::_get_procedure_name() {
  return dynamic_cast<IIRScram *>(get_procedure_name());
}
