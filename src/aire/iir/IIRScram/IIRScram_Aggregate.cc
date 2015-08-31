
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
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------
#include "IIRScram_Aggregate.hh"
#include "IIRScram_AssociationElementByExpression.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_ArrayTypeDefinition.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_ElementDeclaration.hh"
#include "IIRScram_EnumerationTypeDefinition.hh"
#include "IIRScram_IntegerLiteral32.hh"
#include "IIRScram_Name.hh"
#include "IIRScram_RecordTypeDefinition.hh"
#include "IIRScram_ScalarTypeDefinition.hh"
#include "IIRScram_TextLiteral.hh"

#include "error_func.hh"
#include "symbol_table.hh"
#include <sstream>

IIRScram_Aggregate::IIRScram_Aggregate(){
  set_element_association_list(new IIRScram_AssociationList());
}

IIRScram_Aggregate::~IIRScram_Aggregate(){}

IIR_Boolean 
IIRScram_Aggregate::_is_readable( ){
  IIR_Boolean retval = TRUE;
  IIRScram_AssociationElement *current_assoc;
  IIRScram_AssociationList *list = dynamic_cast<IIRScram_AssociationList *>(get_element_association_list());

  current_assoc = dynamic_cast<IIRScram_AssociationElement *>(list->first());
  while( current_assoc != NULL ){
    if( current_assoc->_is_readable() == FALSE ){
      retval = FALSE;
    }
    current_assoc = dynamic_cast<IIRScram_AssociationElement *>(list->successor( current_assoc ));
  }

  return retval;
}


IIR_Boolean 
IIRScram_Aggregate::_is_writable( ){
  IIR_Boolean retval = TRUE;
  IIRScram_AssociationElement *current_assoc;
  IIRScram_AssociationList *list = dynamic_cast<IIRScram_AssociationList *>(get_element_association_list());

  current_assoc = dynamic_cast<IIRScram_AssociationElement *>(list->first());
  while( current_assoc != NULL ){
    if( current_assoc->_is_writable() == FALSE ){
      retval = FALSE;
    }
    current_assoc = dynamic_cast<IIRScram_AssociationElement *>(list->successor( current_assoc ));
  }

  return retval;
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_Aggregate::_get_rval_set( constraint_functor * ){
  // This implements lines 390 - 395, page 103 of the '93 LRM
  savant::set<IIRScram_TypeDefinition> *retval = new savant::set<IIRScram_TypeDefinition>;

  // Add all in scope array types.
  savant::set<IIRScram_ArrayTypeDefinition> *array_types = _get_symbol_table()->get_in_scope_array_types()->convert_set<IIRScram_ArrayTypeDefinition>();
  IIRScram_TypeDefinition *current = array_types->getElement();
  while( current != NULL ){
    ASSERT( current->is_array_type() == TRUE );
    retval->add( current );
    current = array_types->getNextElement();
  }
  
  // Add all in scope record types.
  savant::set<IIRScram_RecordTypeDefinition> *record_types = _get_symbol_table()->get_in_scope_record_types()->convert_set<IIRScram_RecordTypeDefinition>();
  current = record_types->getElement();
  while( current != NULL ){
    ASSERT( current->is_record_type() == TRUE );
    retval->add( current );
    current = record_types->getNextElement();
  }
  delete record_types;

  return retval;
}

void 
IIRScram_Aggregate::_type_check( savant::set<IIRScram_TypeDefinition> * ){
  // First set of type checks.
  IIR_Boolean           have_seen_named = false;
  IIR_Boolean           have_seen_others = false;
  IIRScram_AssociationList *list = dynamic_cast<IIRScram_AssociationList *>(get_element_association_list());

  IIRScram_AssociationElement *current = dynamic_cast<IIRScram_AssociationElement *>(list->first());

  while( current != NULL ){
    if( current->is_named() == TRUE ){
      have_seen_named = TRUE;
    }
    if( current->_is_positional() == TRUE && have_seen_named == TRUE ){
      ostringstream err;
      err << "Positional associations cannot follow named associations in an aggregate.";
      report_error( current, err.str() );
    }

    if( have_seen_others == TRUE ){
      // That means (due to the order of these if statements) that there was something
      // after the others!
      ostringstream err;
      err << "No association can follow an \"others\" association in an aggregate.";
      report_error( current, err.str() );      
    }

    if( current->is_by_others() == TRUE ){
      have_seen_others = TRUE;
    }
    current = dynamic_cast<IIRScram_AssociationElement *>(list->successor( current ));
  }
}

void 
IIRScram_Aggregate::_rval_to_decl_process_named_part( IIRScram_TypeDefinition *my_type, 
						      IIRScram_AssociationElement *starting_with ){
  ASSERT( my_type->_is_iir_record_type_definition() == TRUE );

  IIRScram_AssociationElement *current_association = starting_with;
  while( current_association != NULL ){
    if( current_association->get_formal() != NULL ){
      IIRScram *current_formal = dynamic_cast<IIRScram *>(current_association->get_formal());
      
      switch( current_formal->get_kind() ){
      case IIR_SIMPLE_NAME:{
	savant::set<IIRScram_Declaration> *element_decls = NULL;
        
        if ( my_type->find_declarations( dynamic_cast<IIRScram_Name *>(current_formal) ) != NULL ){
	  element_decls = my_type->find_declarations( dynamic_cast<IIRScram_Name *>(current_formal) )->convert_set<IIRScram_Declaration>();
        }

	if( element_decls == NULL ){
	  ostringstream err;
	  err << "Internal error - |" << *current_formal << "| was not found in record type |"
	      << *my_type << "| in IIRScram_Aggregate::_rval_to_decl_process_named_part.";
	  report_error( this, err.str() );
	}
	else{
	  ASSERT( element_decls->size() == 1 );
	  IIRScram_Declaration *element_decl = element_decls->getElement();
	  delete element_decls;
	  
	  current_association->set_formal( element_decl );
	  IIRScram_TypeDefinition *actual_type = element_decl->_get_subtype();
	  
	  ASSERT( current_association->get_kind() == IIR_ASSOCIATION_ELEMENT_BY_EXPRESSION );	
	  current_association->set_actual( current_association->_get_actual()->_semantic_transform( actual_type ) );
	  current_association->_get_actual()->_type_check( actual_type );
	  current_association->set_actual( current_association->_get_actual()->_rval_to_decl( actual_type ) );
	  
	}
	break;
      }
      case IIR_OTHERS_INITIALIZATION:{
	ostringstream err;
	err << "Internal error - others not supported in aggregate initialization of records, yet!";
	report_error( this, err.str() );
	break;
      }
      default:{
	if( current_formal->is_resolved() == TRUE ){
	  // OK, formal is already resolved; we need to deal with the actual.
	  IIRScram_TypeDefinition *actual_type = current_formal->_get_subtype();
	  ASSERT( current_association->get_kind() == IIR_ASSOCIATION_ELEMENT_BY_EXPRESSION );	
	  current_association->set_actual( current_association->_get_actual()->_semantic_transform( actual_type ) );
	  current_association->_get_actual()->_type_check( actual_type );
	  current_association->set_actual( current_association->_get_actual()->_rval_to_decl( actual_type ) );
	}
	else{
	  ostringstream err;
	  err << "Internal error - unexpected formal node type " << current_formal->get_kind_text()
	      << "(node == |" << *current_formal << "|)"
	      << " in IIRScram_Aggregate::_rval_to_decl_process_named_part.";
	  report_error( this, err.str() );
	}
      }
      }
    }
    else{
      ostringstream err;
      if( current_association->get_kind() == IIR_ASSOCIATION_ELEMENT_BY_EXPRESSION &&
	  current_association->_get_actual() != NULL &&
	  current_association->_get_actual()->get_kind() == IIR_OTHERS_INITIALIZATION ){
	err << "Others initialization isn't handled in this context yet.";
	report_error( this, err.str() );
      }
      else{
	err << "Internal error in IIRScram_Aggregate::_rval_to_decl_process_named_part - "
	    << "formal is null and actual is ";
	if( current_association->_get_actual() == NULL ){
	  err << "NULL";
	}
	else{
	  err << "an " << current_association->_get_actual()->get_kind_text()
	      << "(the node is |" << current_association->_get_actual() << "|),";
	}
      }
    }

    current_association = dynamic_cast<IIRScram_AssociationElement *>(get_element_association_list()->successor( current_association ));
  }
}

IIRScram *
IIRScram_Aggregate::_rval_to_decl( IIRScram_TypeDefinition *my_type ){
  ASSERT( my_type->is_array_type() == TRUE || my_type->is_record_type() );
  
  enum processing_mode_t { ARRAY, RECORD, ERROR };

  processing_mode_t processing_mode = ERROR;
  if( my_type->is_array_type() == TRUE ){
    processing_mode = ARRAY;
  }
  else if( my_type->is_record_type() == TRUE ){
    processing_mode = RECORD;
  }

  ASSERT( processing_mode != ERROR );
  IIRScram_TypeDefinition *actual_type = NULL;
  IIRScram_TypeDefinition *formal_type = NULL;

  int i;
  for( i = 0; i < get_element_association_list()->size(); i++ ){
    IIRScram_AssociationElement *current_association 
      = dynamic_cast<IIRScram_AssociationElement *>(get_element_association_list()->get_nth_element( i ));
    
    if( processing_mode == ARRAY ){
      formal_type = my_type->_get_resolved_index_subtype();
      if( current_association->is_by_others() == TRUE ){
	actual_type = my_type;
      }
      else{
	actual_type = my_type->_get_element_subtype();
      }
    }
    else{
      // This code isn't handling named associations, at the moment!
      IIRScram_RecordTypeDefinition *my_record_type = dynamic_cast<IIRScram_RecordTypeDefinition *>(my_type);
      actual_type = my_record_type->_get_element_subtype( i );
      formal_type = my_record_type->_get_element_subtype( i );
    }
    
    ASSERT( actual_type != NULL );
    ASSERT( formal_type != NULL );

    if( current_association->get_formal() != NULL ){
      if( processing_mode == ARRAY ){
	IIRScram *old_formal = dynamic_cast<IIRScram *>(current_association->get_formal());

	IIRScram *new_formal = old_formal->_semantic_transform( formal_type );
	new_formal->_type_check( formal_type );
	new_formal = new_formal->_rval_to_decl( formal_type );

	current_association->set_formal( new_formal );
      }
      else{
	_rval_to_decl_process_named_part( my_type, current_association );
	break;
      }
    }
    
    if( current_association->get_kind() == IIR_ASSOCIATION_ELEMENT_BY_EXPRESSION ){
      current_association->set_actual( current_association->_get_actual()->_semantic_transform( actual_type ) );
      current_association->_get_actual()->_type_check( actual_type );
      current_association->set_actual( current_association->_get_actual()->_rval_to_decl( actual_type ) );
    }
  }
    
  set_subtype( my_type );

  ASSERT( is_resolved() == TRUE );

  return this;
}


// This method publishes a default range to the aggregate.  The default range
// is not specified in the LRM.  I used (1, to, n) -- SK.

IIRScram *
IIRScram_Aggregate::_clone(){
  IIRScram_Aggregate *retval = new IIRScram_Aggregate();
  IIRScram_Expression::_clone( retval );

  IIRScram_AssociationList *new_list = new IIRScram_AssociationList();
  
  for (IIRScram_AssociationElement *cur_elem = dynamic_cast<IIRScram_AssociationElement *>(_get_element_association_list()->first());
       cur_elem != NULL; 
       cur_elem = dynamic_cast<IIRScram_AssociationElement *>(_get_element_association_list()->successor(cur_elem))) {
    new_list->append(cur_elem);
  }
  retval->set_element_association_list(new_list);

  return retval;
}

IIRScram_AssociationList *
IIRScram_Aggregate::_get_element_association_list() {
  return dynamic_cast<IIRScram_AssociationList *>(get_element_association_list());
}

visitor_return_type *
IIRScram_Aggregate::_accept_visitor( node_visitor *visitor,
				     visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
 
  return visitor->visit_IIR_Aggregate(this, arg);
}

