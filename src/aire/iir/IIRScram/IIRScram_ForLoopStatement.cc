
// Copyright (c) 1996-2003 The University of Cincinnati.  
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
//          Timothy J. McBrayer
//          Malolan Chetlur    
//          Krishnan Subramani 
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam
//---------------------------------------------------------------------------

#include "IIRScram_ForLoopStatement.hh"
#include "IIRScram_ConstantDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_SequentialStatementList.hh"
#include "IIRScram_ScalarTypeDefinition.hh"
#include "symbol_table.hh"

IIRScram_ForLoopStatement::IIRScram_ForLoopStatement() {
  set_sequence_of_statements(new IIRScram_SequentialStatementList());
}

IIRScram_ForLoopStatement::~IIRScram_ForLoopStatement() {
  //Release the list memory
  delete get_sequence_of_statements();
}

void 
IIRScram_ForLoopStatement::_type_check(){
  ASSERT( _get_iteration_scheme() != NULL );  
  _get_iteration_scheme()->set_subtype( _type_check_iteration_scheme(_get_iteration_scheme() ) );
}

IIR_Boolean 
IIRScram_ForLoopStatement::_type_check_return_statements( savant::set<IIRScram_TypeDefinition> *context_set, 
							  IIRScram_SubprogramDeclaration *subprogram_decl ){
  IIR_Boolean retval;

  ASSERT( _get_iteration_scheme() != NULL && _get_iteration_scheme()->is_resolved() == TRUE );
  
  _get_symbol_table()->open_scope( this );
  _get_symbol_table()->make_visible( _get_iteration_scheme());
  retval = IIRScram_SequentialStatement::_type_check_return_statements( context_set, 
                                                                        _get_sequence_of_statements(), 
                                                                        subprogram_decl );
  _get_symbol_table()->close_scope( this );

  return retval;
}

void
IIRScram_ForLoopStatement::_build_iteration_scheme( IIR_TextLiteral *id,
						    IIR_ScalarTypeDefinition *subtype ){
  IIRScram_ConstantDeclaration *iterator = new IIRScram_ConstantDeclaration();
  iterator->set_is_implicit( true );
  iterator->set_declarator(id);
  iterator->set_declarative_region( this );

  copy_location( id, iterator );

  if( subtype != NULL ){
    ASSERT( subtype->is_scalar_type()==TRUE );
    iterator->set_subtype( subtype );
  }
  
  iterator->_add_declaration();
  
  set_iteration_scheme(iterator);
}


visitor_return_type *
IIRScram_ForLoopStatement::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ForLoopStatement(this, arg);
}

// IIRBase Function Wrapper(s)
IIRScram_SequentialStatementList *
IIRScram_ForLoopStatement::_get_sequence_of_statements() {
  return dynamic_cast<IIRScram_SequentialStatementList *>(get_sequence_of_statements());
}

IIRScram_ConstantDeclaration *
IIRScram_ForLoopStatement::_get_iteration_scheme() {
  return dynamic_cast<IIRScram_ConstantDeclaration *>(get_iteration_scheme());
}

IIRScram_List *
IIRScram_ForLoopStatement::_get_statement_list() {
  return dynamic_cast<IIRScram_List *>(get_sequence_of_statements());
}
