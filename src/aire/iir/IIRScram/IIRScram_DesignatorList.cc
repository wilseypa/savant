
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
//          Narayanan Thondugulam
//          Krishnan Subramani  
//          Magnus Danielson    cfmd@swipnet.se

//---------------------------------------------------------------------------
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_ComponentInstantiationStatement.hh"
#include "IIRScram_DesignatorExplicit.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_SimpleName.hh"
#include "IIRScram_TextLiteral.hh"
#include "error_func.hh"
#include "set.hh"

#include <sstream>
using std::ostringstream;

IIRScram_DesignatorList::~IIRScram_DesignatorList() {}

IIRScram_Label *
IIRScram_DesignatorList::_process_instantiate_statement( IIRScram_Declaration *instantiated_unit,
							 IIRScram *statement ){
  ASSERT( instantiated_unit != NULL );
  ASSERT( statement != NULL );

  IIRScram_Label *retval = NULL;

  if( statement->get_kind() == IIR_COMPONENT_INSTANTIATION_STATEMENT ){
    IIRScram_ComponentInstantiationStatement *as_instantiate_statement = NULL;
    as_instantiate_statement = dynamic_cast<IIRScram_ComponentInstantiationStatement *>(statement);
    ASSERT( as_instantiate_statement->_get_instantiated_unit()->_is_iir_declaration() == TRUE );
    if( as_instantiate_statement->_get_instantiated_unit() == instantiated_unit ){
      ASSERT( as_instantiate_statement->_get_label() != NULL );
      ASSERT( as_instantiate_statement->_get_label()->_get_statement() != NULL );
      retval = as_instantiate_statement->_get_label();
    }
  }

  return retval;
}

void 
IIRScram_DesignatorList::_process_explicit_list( IIRScram_Declaration *instantiated_unit,
						 IIRScram_List *statement_list,
						 IIRScram *configuration ){
  IIRScram_SimpleName *label_name = NULL;
  (void)instantiated_unit;  // quiet down the compiler

  IIRScram_Designator *current_designator = dynamic_cast<IIRScram_Designator *>(first());
  while( current_designator != NULL ){
    ASSERT( current_designator->get_kind() == IIR_DESIGNATOR_EXPLICIT );
    IIRScram_DesignatorExplicit *explicit_designator = dynamic_cast<IIRScram_DesignatorExplicit *>(current_designator);
    ASSERT( explicit_designator->get_name() != NULL );
    ASSERT( explicit_designator->get_name()->get_kind() == IIR_SIMPLE_NAME );
    label_name = dynamic_cast<IIRScram_SimpleName *>(explicit_designator->get_name());

    IIRScram_Label *instantiate_label = statement_list->_find_instantiate_label( label_name );

    if( instantiate_label == NULL ){
      ostringstream err;
      err << "No label |" << *label_name << "| found.";
      report_error( label_name, err.str() );
      break;
    }
    else{
      explicit_designator->set_name( label_name->_decl_to_decl( instantiate_label ) );
      ASSERT( instantiate_label->get_statement()->get_kind() ==
	      IIR_COMPONENT_INSTANTIATION_STATEMENT );
      IIRScram_ComponentInstantiationStatement *statement = NULL;
      statement = dynamic_cast<IIRScram_ComponentInstantiationStatement *>(instantiate_label->get_statement());
      statement->set_configuration( configuration );
    }
    current_designator = dynamic_cast<IIRScram_Designator *>(successor( current_designator ));
  }
}

void 
IIRScram_DesignatorList::_process_by_all_or_others( IIRScram_Declaration *instantiated_unit,
						    IIRScram_List *statement_list,
						    IIR_Boolean by_all,
						    IIRScram *configuration ){
  IIRScram_DesignatorList new_designator_list;
  IIRScram_Label *new_label = NULL;

  IIRScram *current_statement = dynamic_cast<IIRScram *>(statement_list->first());
  while( current_statement != NULL ){
    new_label = _process_instantiate_statement( instantiated_unit, 
						current_statement );

    if( new_label != NULL ){
      ASSERT( new_label->get_statement()->get_kind() == IIR_COMPONENT_INSTANTIATION_STATEMENT );
      IIRScram_ComponentInstantiationStatement *statement = NULL;
      statement = dynamic_cast<IIRScram_ComponentInstantiationStatement *>(new_label->get_statement());
      if( by_all == TRUE || statement->_get_configuration() == NULL ){
	IIRScram_DesignatorExplicit *new_designator = new IIRScram_DesignatorExplicit();
	copy_location( new_label, new_designator );
	new_designator->set_name( new_label );
	statement->set_configuration( configuration );
	new_designator_list.append( new_designator );
      }
    }
    current_statement = dynamic_cast<IIRScram *>(statement_list->successor( current_statement ));
  }

  if( new_designator_list.size() > 0 ){
    // Destroy the current list.
    ASSERT( size() == 1 );
    IIRScram_Designator *current = dynamic_cast<IIRScram_Designator *>(first());
    remove( current );
    delete current;

    current = dynamic_cast<IIRScram_Designator *>(new_designator_list.first());
    while( current != NULL ){
      append( current );
      current = dynamic_cast<IIRScram_Designator *>(new_designator_list.successor( current ));
    }
  }
}

void 
IIRScram_DesignatorList::_type_check_as_instantiation_list( IIRScram *instantiated_unit,
							    IIRScram_List *statement_list,
							    IIRScram *configuration ){
  ASSERT( instantiated_unit != NULL );
  ASSERT( instantiated_unit->_is_iir_declaration() == TRUE );
  IIRScram_Declaration *as_decl = dynamic_cast<IIRScram_Declaration *>(instantiated_unit);

  IIRScram_Designator *current_designator = dynamic_cast<IIRScram_Designator *>(first());
  if( current_designator != NULL ){
    switch( current_designator->get_kind() ){
    case IIR_DESIGNATOR_BY_ALL:
      _process_by_all_or_others( as_decl, statement_list, TRUE, configuration );
      break;
      
    case IIR_DESIGNATOR_BY_OTHERS:
      _process_by_all_or_others( as_decl, statement_list, FALSE, configuration );
      break;
      
    case IIR_DESIGNATOR_EXPLICIT:
      _process_explicit_list( as_decl, statement_list, configuration );    
      break;
      
    default:
      ostringstream err;
      err << "Internal error in IIRScram_DesignatorList::_type_check_as_instantiation_list "
	  << "- don't know what to do with node type " << current_designator->get_kind_text();
      report_error( current_designator, err.str() );
    }
  }

#ifdef DEVELOPER_ASSERTIONS
  current_designator = dynamic_cast<IIRScram_Designator *>(first());
  while( current_designator != NULL ){
    if ( current_designator->get_kind() == IIR_DESIGNATOR_EXPLICIT ) {
      IIRScram_DesignatorExplicit *as_explicit = dynamic_cast<IIRScram_DesignatorExplicit *>(current_designator);
      ASSERT( as_explicit->get_name() != NULL );
      ASSERT( as_explicit->get_name()->get_kind() == IIR_LABEL );
      IIRScram_Label *current_label = dynamic_cast<IIRScram_Label *>(as_explicit->get_name());
      ASSERT( current_label->get_statement()->get_kind() == IIR_COMPONENT_INSTANTIATION_STATEMENT );
      ASSERT( (dynamic_cast<IIRScram_ComponentInstantiationStatement *>(current_label->get_statement())->_get_configuration() != NULL ));
    }
    current_designator = dynamic_cast<IIRScram_Designator *>(successor( current_designator ));
  }
#endif
}


visitor_return_type *
IIRScram_DesignatorList::_accept_visitor( node_visitor *visitor,
					  visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_DesignatorList(this, arg);
}
