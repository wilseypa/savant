
// Copyright (c) 1996-2003 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer 
//          Malolan Chetlur     
//          Krishnan Subramani  
//          Radharamanan Radhakrishnan
//          Narayanan Thondugulam
//          Swaminathan Subramanian 
//	    Magnus Danielson	cfmd@swipnet.se
//	    Harish Venkataramani venkath@ececs.uc.edu
//          Sivakumar Gowrisankar gowriss@ececs.uc.edu
//---------------------------------------------------------------------------

#include "IIRScram_ArchitectureDeclaration.hh"
#include "IIRScram_ArchitectureStatement.hh"
#include "IIRScram_ArchitectureStatementList.hh"
#include "IIRScram_AliasDeclaration.hh"
#include "IIRScram_AssociationElement.hh"
#include "IIRScram_Attribute.hh"
#include "IIRScram_AttributeSpecification.hh"
#include "IIRScram_BlockStatement.hh"
#include "IIRScram_BranchQuantityDeclaration.hh"
#include "IIRScram_ComponentDeclaration.hh"
#include "IIRScram_ComponentInstantiationStatement.hh"
#include "IIRScram_ConcurrentGenerateIfStatement.hh"
#include "IIRScram_ConcurrentGenerateForStatement.hh"
#include "IIRScram_ConfigurationSpecification.hh"
#include "IIRScram_Designator.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EntityDeclaration.hh"
#include "IIRScram_FileDeclaration.hh"
#include "IIRScram_FreeQuantityDeclaration.hh"
#include "IIRScram_GenericList.hh"
#include "IIRScram_TextLiteral.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_Name.hh"
#include "IIRScram_PortList.hh"
#include "IIRScram_ProcessStatement.hh"
#include "IIRScram_SignalInterfaceDeclaration.hh"
#include "IIRScram_SignalDeclaration.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_UseClause.hh"
#include "IIRScram_WaitStatement.hh"

#include "error_func.hh"
#include "resolution_func.hh"
#include "symbol_table.hh"

#include "language_processing_control.hh"

using std::ends;

IIRScram_ArchitectureDeclaration::IIRScram_ArchitectureDeclaration(){
  set_architecture_declarative_part(new IIRScram_DeclarationList());
  set_architecture_statement_part(new IIRScram_ArchitectureStatementList());
}

IIRScram_ArchitectureDeclaration::~IIRScram_ArchitectureDeclaration() {
  //Release the list memory
  delete get_architecture_declarative_part();
  delete get_architecture_statement_part();
}

void 
IIRScram_ArchitectureDeclaration::_type_check( ){
  _get_architecture_declarative_part()->_type_check_configuration_specifications( dynamic_cast<IIRScram_List *>(get_architecture_statement_part()) );
  _get_architecture_declarative_part()->_type_check_disconnection_specifications(  );
  _get_architecture_declarative_part()->_type_check_attribute_specifications( dynamic_cast<IIRScram_List *>(get_architecture_statement_part()) );
  _get_architecture_statement_part()->_type_check_instantiate_statements();
}

IIRScram_GenericList *
IIRScram_ArchitectureDeclaration::_get_generic_list(){
  ASSERT( _get_entity() != NULL );
  return _get_entity()->_get_generic_list();
}

IIRScram_DeclarationList*
IIRScram_ArchitectureDeclaration::_get_declaration_list() {
  return dynamic_cast<IIRScram_DeclarationList *>(get_architecture_declarative_part());
}

void 
IIRScram_ArchitectureDeclaration::_make_interface_visible( symbol_table *sym_tab ){
  // This isn't _my_ interface...
  //   if( get_entity() != NULL ){
  //     get_entity()->_make_interface_visible( sym_tab );
  //   }
  sym_tab->make_visible( _get_architecture_declarative_part() );
  IIRScram_ArchitectureStatement *current_statement = 
    dynamic_cast<IIRScram_ArchitectureStatement *>(get_architecture_statement_part()->first());

  while( current_statement != NULL ){
    if( current_statement->_get_label() != NULL ){
      sym_tab->make_visible( current_statement->_get_label() );
    }
    current_statement = dynamic_cast<IIRScram_ConcurrentStatement *>(get_architecture_statement_part()->successor( current_statement ));
  }
}

#ifdef PROCESS_COMBINATION
void
IIRScram_ArchitectureDeclaration::_combine() {
  IIRScram_ArchitectureStatementList onewaitlist, uncondwaitlist;
  IIRScram_ArchitectureStatement *next;
  IIRScram_ProcessStatement *to_combine;
  ProcessCombiner *cproc;

  cerr << "The elaborated design has "
       << get_architecture_statement_part()->size() << " processes: ";

  // move all 1-wait processes from arch_stmt_part to onewaitlist
  to_combine = (IIRScram_ProcessStatement*)get_architecture_statement_part()->first();
  while ( to_combine != NULL ) {
    next = get_architecture_statement_part()->successor(to_combine);
    ASSERT( IIR_PROCESS_STATEMENT == to_combine->get_kind() );
    
    to_combine->_build_wait_list();
    if ( to_combine->_wait_stmt_list.size() == 1 ) {
      IIRScram_WaitStatement *waitstmt = to_combine->_wait_stmt_list.first();
      if (waitstmt->get_timeout_clause() == NULL
	  && waitstmt->get_sensitivity_list()->size() == 0
	  && waitstmt->get_condition_clause() == NULL ) {
	// Put processes with one uncinditional wait in uncondwaitlist
	uncondwaitlist.append( to_combine );
      }
      else {
	onewaitlist.append( to_combine );
      }
      get_architecture_statement_part()->remove( to_combine );
    }
    to_combine = (IIRScram_ProcessStatement*)next;
  }
  
  cerr << uncondwaitlist.size() 
       << " with a single unconditional wait,\nand "
       << onewaitlist.size()
       << " with a single combinable wait statement.\n";
  cerr << "Partitioning design into " << num_partitions << " partitions";

  // combine processes in unconditional wait list--put into arch_stmt_part
  if ( NULL != uncondwaitlist.first() ) {
    ProcessCombiner uncondwaitcombiner;
    to_combine = (IIRScram_ProcessStatement*)uncondwaitlist.first();

    while ( NULL != to_combine ) {
      next = uncondwaitlist.successor( to_combine );
      uncondwaitcombiner.combine_uncondwait( to_combine );
      uncondwaitlist.remove( to_combine );
      to_combine = (IIRScram_ProcessStatement*)next;
    }
    get_architecture_statement_part()->append( uncondwaitcombiner.get_process() );
  }

  // OK, this check probably isn't necessary...
  if ( NULL != onewaitlist.first() ) {
    int partition = 0;
    cproc = new ProcessCombiner[num_partitions];
    to_combine = (IIRScram_ProcessStatement*)onewaitlist.first();

    while ( NULL != to_combine ) {
      next = onewaitlist.successor( to_combine );
      if ( !to_combine->_convert_to_TWF() ) {
	// If the process can't be converted to TWF, remove it from the
	// onewaitlist and add it back to the architecture
	get_architecture_statement_part()->append( to_combine );
	onewaitlist.remove( to_combine );
      }
      to_combine = (IIRScram_ProcessStatement*)next;
    }
    
    
    // Partitoning algorithms start here.  Probably should be elsewhere.
    to_combine = (IIRScram_ProcessStatement*)onewaitlist.first();
    if ( partition_algorithm != NULL 
	 && !strncmp( partition_algorithm, "ra", 2 )) {
      cerr << " with random partitioning.\n";
      while ( NULL != to_combine ) {
	next = onewaitlist.successor( to_combine );
	partition = (int)(((float)num_partitions * (float)rand()) 
			  / (RAND_MAX + 1.0));
	cproc[partition].combine( to_combine );
	onewaitlist.remove( to_combine );
	to_combine = (IIRScram_ProcessStatement*)next;
      }
    }
    else if ( partition_algorithm != NULL
	      && !strncmp( partition_algorithm, "c", 1 )) {
      cerr << " with output-cone partitioning.\n";
      cone_partition( (IIRScram_ArchitectureDeclaration*)this, onewaitlist, cproc );
    }
    else { // Round Robin partitioning is the default
      cerr << " with round-robin partitioning.\n";
      
      while ( NULL != to_combine ) {
	next = onewaitlist.successor( to_combine );
	cproc[partition].combine( to_combine );
	partition = (partition + 1)%num_partitions;
	onewaitlist.remove( to_combine );
	to_combine = (IIRScram_ProcessStatement*)next;
      }
    }

    // add combined processes back to architecture
    for (partition = 0; partition < num_partitions; partition++ ) {
      get_architecture_statement_part()->append( cproc[partition].get_process() );
    }
    delete [] cproc;
  }
}

void
IIRScram_ArchitectureDeclaration::_static_elaborate(IIRScram_ArchitectureDeclaration *arch, 
						    IIRScram_DeclarationList *cfglist,
						    char *hier_location) {
  IIRScram_Declaration *decl, *declclone, *impdecl;
  IIRScram_Identifier *new_signal_id, *old_id;

  decl = get_architecture_declarative_part()->first();
  while (decl != NULL) {
    if (decl->get_kind() == IIR_COMPONENT_DECLARATION 
	|| decl->get_kind() == IIR_CONFIGURATION_SPECIFICATION) {
      declclone = decl;
    }
    else {
      declclone = (IIRScram_Declaration*)((IIRScram*)decl)->_clone();
      // mangle names for certain declarations
      if (declclone->get_kind() == IIR_SIGNAL_DECLARATION 
	  || declclone->get_kind() == IIR_FILE_DECLARATION
          || declclone->get_kind() == IIR_ALIAS_DECLARATION) {
	declclone->_static_elaborate_decl(hier_location);
      }
    }

    if( declclone->_get_implicit_declarations() != NULL ){
      // mangle names for all implicit decls
      impdecl = declclone->_get_implicit_declarations()->getElement();
      while (impdecl != NULL) {
	impdecl->_static_elaborate_decl(hier_location);
	impdecl = declclone->_get_implicit_declarations()->getNextElement();
      }
    }

    arch->get_architecture_declarative_part()->append(declclone);
    decl = get_architecture_declarative_part()->successor(decl);
  }

  decl = get_context_items()->first();
  while ( decl != NULL ) {
    ASSERT( IIR_USE_CLAUSE == decl->get_kind() );
    if (arch->get_context_items()->get_position( decl ) == -1 ) {
      arch->get_context_items()->append( decl );
    }
    decl = get_context_items()->successor( decl );
  }

  IIRScram_ArchitectureStatement *arch_stmt;
  IIRScram *clone;
  get_entity()->_static_elaborate(arch, cfglist, hier_location);

  arch_stmt = dynamic_cast<IIRScram_ArchitectureStatement *>(get_architecture_statement_part()->first());
  while (arch_stmt != NULL) {
    if (arch_stmt->get_kind() == IIR_PROCESS_STATEMENT ||
	arch_stmt->get_kind() == IIR_SENSITIZED_PROCESS_STATEMENT ||
	arch_stmt->get_kind() == IIR_CONCURRENT_SELECTED_SIGNAL_ASSIGNMENT ||
	arch_stmt->get_kind() == IIR_CONCURRENT_CONDITIONAL_SIGNAL_ASSIGNMENT) {
      clone = arch_stmt->_clone();
      clone->_static_elaborate(arch, cfglist, hier_location);
      arch->get_architecture_statement_part()->append(clone);
    }
    else {
      arch_stmt->_static_elaborate(arch, cfglist, hier_location);
    }
    arch_stmt = dynamic_cast<IIRScram_ArchitectureStatement *>(get_architecture_statement_part()->successor(arch_stmt));
  }

  decl = get_architecture_declarative_part()->first();
  while (decl != NULL) {
    switch (decl->get_kind()) {
    case IIR_SIGNAL_DECLARATION:
      static_cast<IIRScram_SignalDeclaration*>(decl)->_my_clone = NULL;
      break;
    case IIR_FILE_DECLARATION:
      static_cast<IIRScram_FileDeclaration*>(decl)->_my_clone = NULL;
      break;
    case IIR_ALIAS_DECLARATION:
      static_cast<IIRScram_AliasDeclaration*>(decl)->_my_clone = NULL;
      break;
    case IIR_COMPONENT_DECLARATION:
    case IIR_CONFIGURATION_SPECIFICATION:
      arch->get_architecture_declarative_part()->remove(decl);
      break;
    default:
      break;
    }
    decl = get_architecture_declarative_part()->successor(decl);
  }
}
#endif

visitor_return_type *
IIRScram_ArchitectureDeclaration::_accept_visitor( node_visitor *visitor, 
						   visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ArchitectureDeclaration(this, arg);
}

IIRScram_DeclarationList *
IIRScram_ArchitectureDeclaration::_get_architecture_declarative_part() {
  return dynamic_cast<IIRScram_DeclarationList *>(get_architecture_declarative_part());
}

IIRScram_ArchitectureStatementList *
IIRScram_ArchitectureDeclaration::_get_architecture_statement_part() {
  return dynamic_cast<IIRScram_ArchitectureStatementList *>(get_architecture_statement_part());
}

IIRScram_List *
IIRScram_ArchitectureDeclaration::_get_statement_list(){
  return dynamic_cast<IIRScram_List *>(get_architecture_statement_part());
}

IIRScram_EntityDeclaration*
IIRScram_ArchitectureDeclaration::_get_entity() {
  return dynamic_cast<IIRScram_EntityDeclaration *>(get_entity());
}

IIRScram_PortList *
IIRScram_ArchitectureDeclaration::_get_port_list(){
  ASSERT( _get_entity() != NULL );
  return _get_entity()->_get_port_list();
}
