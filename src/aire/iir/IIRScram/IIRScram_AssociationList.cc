
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
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_AssociationList.hh"
#include "IIRScram_AssociationElementByExpression.hh"
#include "IIRScram_AssociationElementOpen.hh"
#include "IIRScram_ComponentDeclaration.hh"
#include "IIRScram_ComponentInstantiationStatement.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_FunctionCall.hh"
#include "IIRScram_FunctionDeclaration.hh"
#include "IIRScram_IndexedName.hh"
#include "IIRScram_InterfaceDeclaration.hh"
#include "IIRScram_PortList.hh"
#include "IIRScram_SignalDeclaration.hh"
#include "IIRScram_SignalInterfaceDeclaration.hh"
#include "IIRScram_TextLiteral.hh"
#include "IIRScram_TypeDefinition.hh"

#include "error_func.hh"
#include "resolution_func.hh"
#include "symbol_table.hh"
#include "set.hh"

#include <sstream>

IIRScram_AssociationList::~IIRScram_AssociationList() {}

void 
IIRScram_AssociationList::append( IIRScram_AssociationElement *to_append ){
  if( to_append != NULL ){
    ASSERT( to_append->_is_association() == TRUE );
  }

  IIRBase_AssociationList::append( to_append );
}

void 
IIRScram_AssociationList::prepend( IIRScram_AssociationElement *to_prepend ){
  if( to_prepend != NULL ){
    ASSERT( to_prepend->_is_association() == TRUE );
  }

  IIRBase_AssociationList::prepend( to_prepend );
}

IIR *
IIRScram_AssociationList::get_nth_element( int to_get ){
  IIRScram *retval = dynamic_cast<IIRScram *>(IIRBase_AssociationList::get_nth_element( to_get ));
  if( retval != NULL ){
    ASSERT( retval->_is_association() == TRUE );
  }
  
  return retval;
}

void 
IIRScram_AssociationList::_replace( IIRScram_AssociationElement *to_replace,
				    IIRScram_AssociationElement *replace_with ){
  ASSERT( to_replace->_is_association() == TRUE );
  ASSERT( replace_with->_is_association() == TRUE );

  IIRBase_AssociationList::_replace( to_replace, replace_with );
}

IIR_Int32
IIRScram_AssociationList::_process_positional_part( IIRScram_InterfaceList *formal_list, 
						    IIR_Boolean resolve ){
  IIR_Int32 num_resolved = 0;
  // This method will return the position number of the last positional element processed.
  int local_count = 0;
  IIRScram_InterfaceDeclaration *current_formal = dynamic_cast<IIRScram_InterfaceDeclaration *>(formal_list->first());
  IIRScram_AssociationElement *current_local = dynamic_cast<IIRScram_AssociationElement *>(first());
  while( current_local != NULL && 
	 current_local->_is_positional() == TRUE ){

    IIR_Boolean found_match = FALSE;
    IIRScram_TypeDefinition *current_local_type = NULL;

    if( current_local->get_kind() == IIR_ASSOCIATION_ELEMENT_BY_EXPRESSION ){
      // Process all of the positional associations
      if( current_formal != NULL && found_match == FALSE ){
	// Does the type of our local match that of the parameter?
	IIRScram_TypeDefinition *current_formal_type = current_formal->_get_subtype();
	savant::set<IIRScram_TypeDefinition> *current_local_rvals = current_local->_get_rval_set();
	if( current_local_rvals == NULL ){
	  if( resolve == TRUE ){
	    ostringstream err;
	    err << "Internal error in IIRScram_AssociationList::_process_positional_part"
		<< "- no rval found for an local!";
	    report_error( current_local, err.str() );
	    abort();
	  }
	  else{
	    report_undefined_symbol( current_local );
	    return -1;
	  }
	}
	current_local_type = current_local_rvals->getElement();
	while( current_local_type != NULL ){
	  if( current_local_type->is_compatible( current_formal_type ) != NULL ){
	    found_match = TRUE;
	    break;
	  }
	  current_local_type = current_local_rvals->getNextElement();
	}
	
        delete current_local_rvals;

	if( found_match == TRUE ){
	  if( resolve == TRUE ){
	    current_local->set_formal( current_formal );      
	    IIRScram *new_actual;
	    new_actual = current_local->_get_actual()->_semantic_transform( current_local_type );
	    new_actual->_type_check( current_local_type );
	    current_local->set_actual( new_actual->_rval_to_decl( current_local_type ) );
	  }
	  num_resolved++;
	}
	else{
	  if( current_formal->_is_optional() == FALSE ){
	    if( resolve == TRUE ){
	      // Then something went wrong - we shouldn't have been called seeing
	      // how this interface list doesn't even go with this association list!
	      ostringstream err;
	      err << "Internal error in IIRScram_AssociationList::_process_positional_part"
		  << "- no matched found for required local!";
	      report_error( current_local, err.str() );
	      abort();
	    }
	    else{
	      // we're not resolving - we're just checking.
	      return -1;
	    }
	  }
	}
      }
    }
    else{
      ASSERT( current_local->get_kind() == IIR_ASSOCIATION_ELEMENT_BY_OPEN);
      num_resolved++;
      if( resolve == TRUE ){
	current_local->set_formal( current_formal );            
      }
    }
  
    current_local = dynamic_cast<IIRScram_AssociationElement *>(successor( current_local ));
    // Either we got a match or the parameter is optional, or we would have aborted.
    local_count++;
    if( current_formal != NULL ){
      current_formal = dynamic_cast<IIRScram_InterfaceDeclaration *>(formal_list->successor(current_formal));
    }
    else{
      break;
    }
  }

  return num_resolved;
}

void
IIRScram_AssociationList::_resolve_and_order( IIRScram_InterfaceList    *formal_list, 
					      IIRScram_InterfaceList    *local_list,
					      IIRScram *line_info ){
  IIR_Boolean result = _check_or_resolve( formal_list, local_list, TRUE );
  if( result == TRUE ){
    _fill_in_defaults( line_info, formal_list );
  }
}

IIR_Boolean 
IIRScram_AssociationList::_check_valid_arguments( IIRScram_InterfaceList        *formal_list,
						  IIRScram_InterfaceList        *local_list){
  //  ASSERT( is_resolved() == FALSE );
  return _check_or_resolve( formal_list, local_list, FALSE );
}

IIRScram_Name *
IIRScram_AssociationList::_get_formal_designator_from_indexed_name( IIRScram_IndexedName *name ){

  IIRScram_Name *retval = name;
  // An indexed name in the formal can be many things.  It can be:
  // (pg. 62 of the LRM)
  // conversion_function( formal_designator )
  // type_conversion( formal_designator )
  // or 
  // formal_designator
  // The formal designator can an array access or a slice, too.

  // Let's look up the prefix, and if we find a type or function
  // declaration for the prefix, then the suffix is the formal designator.
  // Otherwise, the whole indexed name is.


  IIRScram_Name *to_lookup = name;
  while( to_lookup->get_kind() == IIR_INDEXED_NAME ){
    ASSERT( to_lookup->_get_prefix() != NULL );
    ASSERT( to_lookup->_get_prefix()->_is_iir_name() == TRUE );
    to_lookup = dynamic_cast<IIRScram_Name *>(to_lookup->_get_prefix());
  }
  
  IIR_Boolean suffix_is_formal_designator = FALSE;
  savant::set<IIRScram_Declaration> *prefix_decls = to_lookup->_symbol_lookup();
  if( prefix_decls == NULL ){
    // Then we couldn't find the prefix in the symbol table.  It's not 
    // a conversion of any sort.
    return retval;
  }

  IIRScram_Declaration *current_decl = prefix_decls->getElement();
  while( current_decl != NULL ){
    if( (current_decl->is_function_declaration() == TRUE && 
	 (dynamic_cast<IIRScram_FunctionDeclaration *>(current_decl))->_could_be_conversion_function() == TRUE) ||
	current_decl->is_type() == TRUE ){
      // Then the suffix is the formal designator
      suffix_is_formal_designator = TRUE;
      break;
    }
    current_decl = prefix_decls->getNextElement();
  }
  
  delete prefix_decls;

  if( suffix_is_formal_designator == TRUE ){
    // If the suffix isn't a name, we're in trouble!
    IIRScram *temp = name->_get_suffix();  
    if( temp->_is_iir_name() == FALSE ){
      retval = NULL;
    }
    else{
      retval = dynamic_cast<IIRScram_Name *>(temp);
    }
  }

  return retval;
}

IIRScram *
IIRScram_AssociationList::_get_actual_designator_from_indexed_name( IIRScram_IndexedName *name ){
  IIRScram *retval = name;
  IIRScram *prefix = name->_get_prefix();
  IIRScram *suffix = name->_get_suffix();

  if( suffix->get_kind() != IIR_ASSOCIATION_LIST ||
      (dynamic_cast<IIRScram_AssociationList *>(suffix))->size() != 1 ){
    savant::set<IIRScram_Declaration> *decls = prefix->_symbol_lookup();
    // might be type conversion or conversion function
    IIR_Boolean prefix_match = FALSE;
    if( decls != NULL ){
      IIRScram_Declaration *current = decls->getElement();
      while( current != NULL ){
	if( current->get_kind() == IIR_FUNCTION_DECLARATION &&
	    (dynamic_cast<IIRScram_FunctionDeclaration *>(current))->_could_be_conversion_function() == TRUE ){
	  prefix_match = TRUE;
	  break;
	}
	else if( current->get_kind() == IIR_TYPE_DECLARATION ||
		 current->get_kind() == IIR_SUBTYPE_DECLARATION ){
	  prefix_match = TRUE;
	  break;
	}
	current = decls->getNextElement();
      }
    }
    
    if( prefix_match == TRUE ){
      retval = suffix;
    }
    delete decls;
  }

  return retval;
}

IIR_Boolean
IIRScram_AssociationList::_check_or_resolve( IIRScram_InterfaceList     *formal_list,
					     IIRScram_InterfaceList     *local_list,
					     IIR_Boolean                resolve ){
  
  int num_resolved = _process_positional_part( formal_list, resolve );
  if( num_resolved == -1 ){
    // This means there was a problem with the VHDL.
    if( resolve == TRUE ){
      ostringstream err;
      err << "Internal error in IIRScram_AssociationList::_check_or_resolve -"
	  << " _process_positional_part returned -1 when resolving.";
      report_error( this, err.str() );
      abort();
    }
    else{
      return FALSE;
    }
  }
  // If we made it here, the positional part of the VHDL was just fine.
  // Now lets check to see if we've got any more positional associations
  // after this.  We're not allowed to.
  IIRScram_AssociationElement *first_to_look_at = dynamic_cast<IIRScram_AssociationElement *>(get_nth_element( num_resolved ));
  IIRScram_AssociationElement *current_association = dynamic_cast<IIRScram_AssociationElement *>(first_to_look_at);
  while( current_association != NULL ){
    if( current_association->_is_positional() == TRUE ){
      if( resolve == TRUE ){
	ostringstream err;
	err << "Positional associations cannot follow named associations"
	    << " in an association list.";
	report_error( current_association, err.str() );
      }
      else{
	return FALSE;
      }
    }
    current_association = dynamic_cast<IIRScram_AssociationElement *>(successor( current_association ));
  }

  // Now, we need to start looking at the named associations, and picking
  // out the formals.  The formals may be a simple name from an interface
  // list, a conversion function, or, a type conversion.
  current_association = first_to_look_at;
  while( current_association != NULL){
    IIRScram *formal_designator = NULL;
    IIRScram *actual_designator = NULL;
    IIRScram *formal_part = NULL;
    IIRScram *actual_part = NULL;
    // These are declarations that were found through selection, and
    // MADE VISIBLE.  This means that if they are non-NULL, that we
    // need to make them not visible at the end.
    IIRScram_Declaration *actual_declaration = NULL;
    IIRScram_Declaration *formal_declaration = NULL;

    // (We already looked for NULL formals, and if we made it here, there
    // shouldn't be any.
    formal_part = current_association->_get_formal();
    ASSERT( formal_part != NULL );
    // So, we have a formal.  But, the formal MIGHT have a conversion
    // function associated with it.  So, if we have an indexed name,
    // we must look at the suffix to determine if the formal is there.
    
    formal_designator = _find_formal_designator( formal_part );
    if( formal_designator == NULL ){
      if( resolve == TRUE ){
	ostringstream err;
	err << "Couldn't find formal designator in IIRScram_AssociationList::_check_or_resolve"
	    << ", and resolve is TRUE!";
	report_error( this, err.str() );
	return FALSE;
      }
      else{
	return FALSE;
      }
    }
    
    formal_declaration = _find_formal_declaration( formal_designator, formal_list );
    if( formal_declaration == NULL ){
      if( resolve == TRUE ){
	ostringstream err;
	err << "|" << *formal_designator << "| does not designate a formal parameter in "
	    << "this scope.";

	report_error( this, err.str() );
	return FALSE;
      }
      else{
	return FALSE;
      }
    }

    ASSERT( formal_declaration->_is_iir_interface_declaration() == TRUE || 
	    formal_declaration->_is_iir_element_declaration() == TRUE  );

    // At this point, we have the formal declaration in
    // "formal_declaration", and we have the formal part in "formal_part".
    // We still want to determine the type of the formal part - this is
    // something that's hard to do - we can't just call "_get_rval_set" on
    // the formal part, because:
    // 1) If the formal is visible only through selection, it will fail to
    //    find the type.
    // 2) If there are conversion functions on both sides, we want the type
    //    of the declaration.  Otherwise, we want the type of the whole
    //    formal part....
    
    actual_part = current_association->_get_actual();
    IIR_Boolean need_to_hide_formal = FALSE;
    IIR_Boolean need_to_hide_actual = FALSE;

    if( actual_part != NULL ){
      // Then it's not open.
      actual_designator = _find_actual_designator( actual_part );
      
      if( local_list != NULL && actual_part->get_kind() == IIR_SIMPLE_NAME ){
	// There are only certain places that an actual by selection can
	// appear.  Looking at page 62 of the 93 LRM, do the substitution
	// of "signal_name" for "actual_designator" in the grammar, and
	// that's where it could be.  So, it could be in a name, (like the
	// prefix of an indexed name), or simple name, the suffix of an
	// indexed name (as part of a type conversion or conversion
	// function.)  So, it must be part of a name.
	
	if( actual_designator != NULL && actual_designator->_is_iir_name() == TRUE ){
	  // Now, let's see if we can find it in the interface list.
	  actual_declaration = _find_declaration( dynamic_cast<IIRScram_Name *>(actual_designator),
						  local_list);
	}
      }      
    }

    savant::set<IIRScram_TypeDefinition> *formal_types_to_consider = new savant::set<IIRScram_TypeDefinition>;
    need_to_hide_formal = _find_formal_types( current_association,
					      actual_part, 
					      actual_designator,
					      formal_part,
					      formal_designator,
					      formal_declaration,
					      formal_types_to_consider);
    
    if( formal_types_to_consider == NULL ){
      if( resolve == TRUE ){
	report_undefined_symbol( formal_part );
	return FALSE;
      }
      else{
	return FALSE;
      }
    }
    
    if( actual_part != NULL ){
      // Now we can fully resolve the actual, using the information we have
      // about the formal from before.

      if( actual_declaration != NULL ){
	// We're going to put this SINGLE declaration back into visibility
	// so that the type checking that occurs after this can see it.
	if( current_association->_get_symbol_table()->is_visible( actual_declaration ) == FALSE ){
	  current_association->_get_symbol_table()->make_visible( actual_declaration );
	  need_to_hide_actual = TRUE;
	}
      }
    
      savant::set<IIRScram_TypeDefinition> *actual_part_rvals = actual_part->_get_rval_set();
      if( actual_part_rvals == NULL ){
	if( resolve == TRUE ){
	  report_undefined_symbol( actual_part );
	}
	return FALSE;
      }

      reconcile_sets( formal_types_to_consider, actual_part_rvals );
      ASSERT( formal_types_to_consider->size() <= 1 );
      switch( formal_types_to_consider->size() ){
      case 0:{
	if( resolve == TRUE ){
	  ostringstream err;
	  err << "Type of formal designator |" << *formal_designator << "| and actual part |"
	      << *actual_part << "| aren't compatible, as they must in this context.";
	  report_error( formal_designator, err.str() );
	}
	return FALSE;
	break;
      }
      case 1:{
	IIRScram_TypeDefinition *actual_part_type = formal_types_to_consider->getElement();
	// Just trying to be efficient with set constructors, here.
	IIRScram *new_actual = NULL;

	// We have to do this this way, because "actual_part" needs to
	// be resolved no matter what.  But, we don't want it resolved
	// if we're not resolving, so we don't set it in the association
	// unless we're supposed to.  Also, "semantic transform" deletes
	// the old value in some cases, so we need to clone it if we
	// want to save it.
	if( resolve == FALSE ){
	  new_actual = actual_part->_clone();
	}

	actual_part = actual_part->_semantic_transform( formal_types_to_consider );
	actual_part->_type_check( formal_types_to_consider );
	actual_part = actual_part->_rval_to_decl( actual_part_type );

	if( resolve == TRUE ){
	  ASSERT( actual_part->is_resolved() == TRUE );
	  
	  new_actual = actual_part;
	}
	current_association->set_actual( new_actual );
      }
      }

      if( need_to_hide_actual == TRUE ){
	//	current_association->_get_symbol_table()->remove_from_visibility( actual_declaration );
	current_association->_get_symbol_table()->remove_from_scope( actual_declaration );
      }

      // Now we can fully resolve the formal, given the data in "actual_designator".
      savant::set<IIRScram_TypeDefinition> *actual_types_to_consider = NULL;
      if( (formal_part != formal_designator) && (actual_part != actual_designator) ){
	actual_types_to_consider = actual_designator->_get_rval_set();
	ASSERT( actual_types_to_consider != NULL );
      }
      else{
	ASSERT( actual_part->is_resolved() == TRUE );
	actual_types_to_consider = new savant::set<IIRScram_TypeDefinition>( actual_part->_get_subtype() );
      }

      if( current_association->_get_symbol_table()->is_visible( formal_declaration ) == FALSE ){
	current_association->_get_symbol_table()->make_visible( formal_declaration );
	need_to_hide_formal = TRUE;
      }

      savant::set<IIRScram_TypeDefinition> *formal_part_rvals = formal_part->_get_rval_set();

      if( formal_part_rvals == NULL ){
	if( resolve == TRUE ){
	  report_undefined_symbol( formal_part );
	}
	return FALSE;
      }

      reconcile_sets( actual_types_to_consider, formal_part_rvals );
      ASSERT( actual_types_to_consider->size() <= 1 );
      switch( actual_types_to_consider->size() ){
      case 0:{
	if( resolve == TRUE ){
	  ostringstream err;
	  err << "Type of formal part |" << *formal_designator << "| and actual designator |"
	      << actual_designator << "| don't match, as they must in this context.";
	  report_error( this, err.str() );
	}
	else{
	  return FALSE;
	}
	break;
      }
      case 1:{
	if( resolve == TRUE ){
	  formal_part = formal_part->_semantic_transform( actual_types_to_consider );
	  formal_part->_type_check( actual_types_to_consider );
	  formal_part = formal_part->_rval_to_decl( actual_types_to_consider->getElement() );      
	  ASSERT( formal_part->is_resolved() == TRUE );
	  current_association->set_formal( formal_part );
	}
      }
	break;
      }

      if( resolve == TRUE ){
	ASSERT( current_association->is_resolved() == TRUE );
      }

      delete formal_part_rvals;
      delete actual_part_rvals;
      delete actual_types_to_consider;
    }
    else{
      // This means this assocation is open We need to check and see if
      // this interface is allowed to be open...
      ASSERT( formal_declaration != NULL );

      if( current_association->_get_symbol_table()->is_visible( formal_declaration ) == FALSE ){
	current_association->_get_symbol_table()->make_visible( formal_declaration );
	need_to_hide_formal = TRUE;
      }

      ASSERT( formal_part == formal_designator );
      switch( formal_types_to_consider->size() ){
      case 0:{
	if( resolve == TRUE ){
	  ostringstream err;
	  err << "Internal error in IIRScram_AssociationList::_check_or_resolve - "
	      << "found no formal types for open association |" << *current_association
	      << "|.";
	  report_error( current_association, err.str() );
	  abort();
	}
	return FALSE;
      }
      case 1:{
	if( resolve == TRUE ){
	  formal_part = formal_part->_semantic_transform( formal_types_to_consider );
	  formal_part->_type_check( formal_types_to_consider );
	  formal_part = formal_part->_rval_to_decl( formal_types_to_consider->getElement() );      
	  ASSERT( formal_part->is_resolved() == TRUE );
	  current_association->set_formal( formal_part );
	}
	// else everything is OK, go to the next association
	break;
      }
      default:{
	if( resolve == TRUE ){
	  report_ambiguous_error( formal_part, formal_types_to_consider->convert_set<IIR_TypeDefinition>() );
	}
        delete formal_types_to_consider;
	return FALSE;
      }
      }
    }

    if( need_to_hide_formal == TRUE ){
      //      current_association->_get_symbol_table()->remove_from_visibility( formal_declaration );
      current_association->_get_symbol_table()->remove_from_scope( formal_declaration );
    }
    delete formal_types_to_consider;

    current_association = dynamic_cast<IIRScram_AssociationElement *>(successor( current_association ));
  }

#ifdef DEVELOPER_ASSERTIONS
  if( resolve == TRUE ){
    ASSERT( is_resolved() == TRUE );
    IIRScram_AssociationElement *current = dynamic_cast<IIRScram_AssociationElement *>(first());
    while( current != NULL ){
      ASSERT( current->_get_formal() != NULL );
      // This isn't true if it's OPEN
      //      ASSERT( current->_get_actual() != NULL );
      //      ASSERT( current->get_kind() == IIR_ASSOCIATION_ELEMENT_BY_EXPRESSION );
      ASSERT( current->is_resolved() == TRUE );
      // This is good for debugging, but it's not always true.  (For
      // example, it's not true for a recursive function call.)
      //      ASSERT( current->_get_formal() != current->_get_actual() );
      current = dynamic_cast<IIRScram_AssociationElement *>(successor( current ));
    }
  }
#endif
  
  // OK, now we need to make sure that every required formal has an local
  // associated with it.  We already know that all locals supplied match
  // their parameters, or we wouldn't have made it down here.
  int num_required = 0;
  IIRScram_InterfaceDeclaration *current_formal = dynamic_cast<IIRScram_InterfaceDeclaration *>(formal_list->first());
  while( current_formal != NULL ){
    if( current_formal->_is_optional() == FALSE ){
      num_required++;
    }
    current_formal = dynamic_cast<IIRScram_InterfaceDeclaration *>(formal_list->successor( current_formal ));
  }

  if( size() < num_required ){
    if( resolve == FALSE ){
      return FALSE;
    }
  }

  return TRUE;
}

IIRScram_InterfaceDeclaration *
IIRScram_AssociationList::_find_declaration_in_formal( IIRScram_AssociationElement *find_in ){
  IIRScram_Declaration *retval = NULL;

  IIRScram *current_formal = find_in->_get_formal();  
  ASSERT( current_formal != NULL );

  retval = current_formal->_find_formal_declaration();

  ASSERT( retval != NULL );
  ASSERT( retval->_is_iir_interface_declaration() == TRUE );
  
  return dynamic_cast<IIRScram_InterfaceDeclaration *>(retval);
}

void
IIRScram_AssociationList::_fill_in_defaults( IIRScram *line_info,
					     IIRScram_InterfaceList *formal_list ){
  ASSERT( formal_list != NULL );
  ASSERT( is_resolved() == TRUE );

  savant::set<IIRScram_InterfaceDeclaration> parameter_declarations;

  // Build a set of the parameter declarations.
  IIRScram_InterfaceDeclaration *current_formal = dynamic_cast<IIRScram_InterfaceDeclaration *>(formal_list->first());
  while( current_formal != NULL ){
    parameter_declarations.add( current_formal );
    current_formal = dynamic_cast<IIRScram_InterfaceDeclaration *>(formal_list->successor( current_formal ));
  }
  
  // Walk the list of locals, and remove each parameter found from the
  // set...
  IIRScram_AssociationElement *current_local = dynamic_cast<IIRScram_AssociationElement *>(first());
  while( current_local != NULL ){
    parameter_declarations.remove( _find_declaration_in_formal( current_local ) );
    current_local = dynamic_cast<IIRScram_AssociationElement *>(successor( current_local ));
  }

  // Now, we have all of the parameters with no association in the set 
  // "parameter_declarations".  We need to build an association for each, and
  // append it to the list.

  current_formal = parameter_declarations.getElement();
  while( current_formal != NULL ){
    IIRScram_AssociationElement *new_association = 0;
    if( current_formal->get_value() ){
      new_association = new IIRScram_AssociationElementByExpression();
      dynamic_cast<IIRScram_AssociationElementByExpression *>(new_association)->set_actual( current_formal->get_value());
    }
    else{
      new_association = new IIRScram_AssociationElementOpen();
    }
    copy_location( line_info, new_association );
    new_association->set_formal( current_formal );

    append( new_association );

    current_formal = parameter_declarations.getNextElement();
  }

  IIRScram_AssociationList *new_list = new IIRScram_AssociationList();
  // Now we're going to reorder ourself into the order of the interface list.
  if( num_elements() == formal_list->size() ){
    // The condition above won't hold in the case of associating indexed names, slices,
    // or record elements.
    IIRScram_InterfaceDeclaration *current_decl =
      dynamic_cast<IIRScram_InterfaceDeclaration *>(formal_list->first());
    while( current_decl != NULL ){
      IIRScram_AssociationElement *current_assoc =
	dynamic_cast<IIRScram_AssociationElement *>(first());
      IIR_Boolean one_matched = FALSE;
      while( current_assoc != NULL ){
	IIRScram_InterfaceDeclaration *formal_declaration =
	  _find_declaration_in_formal( current_assoc );
	if( formal_declaration == current_decl ){
	  one_matched = TRUE;
	  break;
	}
	current_assoc =
	  dynamic_cast<IIRScram_AssociationElement *>(successor( current_assoc ));      
      }
      if( one_matched == TRUE ){
	// current_assoc holds the match
	new_list->append( current_assoc );
 	remove( current_assoc );
      }
      else{
	ostringstream err;
	err << "Internal error in IIRScram_AssociationList::_fill_in_defaults - trying"
	    << " to reorder list and can't find declaration |" << *current_decl << "|";
	report_error( this, err.str() );
      }
      current_decl = dynamic_cast<IIRScram_InterfaceDeclaration *>(formal_list->successor( current_decl ));
    }
    *this = *new_list;
    delete new_list;
  }
}

IIRScram *
IIRScram_AssociationList::_clone(){
  IIRScram_AssociationList *retval = new IIRScram_AssociationList();
  IIRScram_List::_clone( retval );
  
  return retval;
}

IIRScram_Declaration *
IIRScram_AssociationList::_find_declaration( IIRScram_Name *to_find, IIRScram_DeclarationList *list ){
  ASSERT( to_find != NULL );
  ASSERT( list != NULL );

  IIRScram_Declaration *retval = NULL;
    
  savant::set<IIR_Declaration> *poss_decls = list->find_declarations( to_find );

  if( poss_decls != NULL ){
    ASSERT( poss_decls->size() == 1 );
    retval = dynamic_cast<IIRScram_Declaration *>(poss_decls->getElement());
    delete poss_decls;
  }
  
  return retval;
}

IIRScram *
IIRScram_AssociationList::_find_formal_designator( IIRScram *formal_part ){
  ASSERT( formal_part != 0 );

  IIRScram *retval = NULL;
  if( formal_part->is_resolved() ){
    retval = formal_part;
  }
  else{
    // According to Ashenden's book (pg. 594) the formal may only legally
    // be a generic name, a formal name, a parameter name, a function name,
    // or a type conversion.  This limits it to a simple name or an indexed
    // name.  (could be work.typename( formal_designator ), but this is
    // still an indexed name.
    switch( formal_part->get_kind() ){
    case IIR_SIMPLE_NAME:
    case IIR_SELECTED_NAME:
    retval = dynamic_cast<IIRScram_Name *>(formal_part);
      break;
    case IIR_INDEXED_NAME:
      // I need to pass the list, to be able to find it in the suffix OR prefix.
      retval = _get_formal_designator_from_indexed_name( dynamic_cast<IIRScram_IndexedName *>(formal_part) );
      break;
      
    default:
      // The parser handed us illegal syntax.
      ostringstream err;
      err << "Syntax error at |" << *formal_part << "| - expecting formal parameter,"
	  << "generic, port, type conversion, or conversion function.";
      report_error( formal_part, err.str() );
    }    
  }
  return retval;
}

IIRScram_Declaration *
IIRScram_AssociationList::_find_formal_declaration( IIRScram                    *formal_designator,
						    IIRScram_InterfaceList      *formal_list){
  IIRScram_Declaration *retval = NULL;

  // Now we have the name of the formal in "formal_designator" - we need
  // to search the paramter for the type of the formal.  NOTE that if we
  // had "integer( x )", we'd have "x" in "formal_designator".  Same goes
  // for a conversion function.
  if( formal_designator->_is_iir_declaration() ){
    retval = dynamic_cast<IIRScram_Declaration *>( formal_designator );
  }
  else if( formal_designator->get_kind() == IIR_INDEXED_NAME ){
    IIRScram *prefix = formal_designator;
    while( prefix->get_kind() == IIR_INDEXED_NAME ){
      ASSERT( dynamic_cast<IIRScram_IndexedName *>(prefix)->_get_prefix() != NULL );
      prefix = dynamic_cast<IIRScram_IndexedName *>(prefix)->_get_prefix();
    }
    
    // This method searches a declaration list for a SINGLE match.
    ASSERT( prefix->_is_iir_name() );
    retval = _find_declaration( dynamic_cast<IIRScram_Name *>(prefix), formal_list );
    if( retval == NULL ){
      ASSERT( formal_designator->_is_iir_name() );
      // The formal wasn't in the prefix - look in the suffix.
      IIRScram *suffix = dynamic_cast<IIRScram_Name *>(formal_designator)->_get_suffix();
      ASSERT( suffix->_is_iir_name() == TRUE );
      retval = _find_declaration( dynamic_cast<IIRScram_Name *>(suffix), formal_list );
    }
  }
  else{
    ASSERT( formal_designator->_is_iir_name() );    
    retval = _find_declaration( dynamic_cast<IIRScram_Name *>(formal_designator), formal_list );
  }

  return retval;
}

IIRScram *
IIRScram_AssociationList::_find_actual_designator( IIRScram *actual_part ){
  IIRScram *retval = NULL;

  if( actual_part->get_kind() == IIR_INDEXED_NAME ){
    retval = _get_actual_designator_from_indexed_name( dynamic_cast<IIRScram_IndexedName *>(actual_part) );
  }
  else{
    retval = actual_part;
  }

  return retval;
}

bool 
IIRScram_AssociationList::_find_formal_types(IIRScram_AssociationElement      *current_association,
					     IIRScram                         *actual_part, 
					     IIRScram                         *actual_designator,
					     IIRScram                         *formal_part,
					     IIRScram                         *formal_designator,
					     IIRScram_Declaration             *formal_declaration,
					     savant::set<IIRScram_TypeDefinition> *add_types_to_me){

  bool retval = FALSE;
  ASSERT( formal_part != NULL );
  ASSERT( formal_declaration != NULL );
  ASSERT( add_types_to_me != NULL && add_types_to_me->size() == 0 );
  
  if( (formal_designator != formal_part) && (actual_designator != actual_part ) ){
    add_types_to_me->add(formal_declaration->_get_subtype());
  }
  else{
    if( current_association->_get_symbol_table()->is_visible( formal_declaration ) == FALSE ){
      current_association->_get_symbol_table()->make_visible( formal_declaration );
      retval = TRUE;
    }
    savant::set<IIRScram_TypeDefinition> *formal_rvals = formal_part->_get_rval_set();
    if( formal_rvals != NULL ){
      add_types_to_me->add( formal_rvals );
      delete formal_rvals;
    }
    else{
      report_undefined_symbol( formal_part );
    }
  }

  if( retval == TRUE ){
    //    current_association->_get_symbol_table()->remove_from_visibility( formal_declaration );
    current_association->_get_symbol_table()->remove_from_scope( formal_declaration );
  }
  
  return retval;
}

void
IIRScram_AssociationList::_build_default_map( IIRScram_ComponentInstantiationStatement *err_info,
					      IIRScram_InterfaceList *formal_list,
					      IIRScram_InterfaceList *actual_list ){

  IIRScram_InterfaceDeclaration *current_actual = dynamic_cast<IIRScram_InterfaceDeclaration *>(actual_list->first());
  while( current_actual != 0 ){
    if( !formal_list->_find_declaration( current_actual->_get_declarator() ) ){
      string err;
      err = "No formal corresponds to actual |" + 
	current_actual->get_declarator()->convert_to_string() + "|";
      report_error( err_info, err );
      return;
    }
    current_actual = dynamic_cast<IIRScram_InterfaceDeclaration *>(actual_list->successor( current_actual ));
  }

  IIRScram_InterfaceDeclaration *current_formal = dynamic_cast<IIRScram_InterfaceDeclaration *>(formal_list->first());
  while( current_formal != 0 ){
    IIRScram_InterfaceDeclaration *actual_decl = 
      actual_list->_find_declaration( current_formal->_get_declarator() );
    IIRScram_AssociationElement *new_association = 0;
    if( actual_decl ){
      new_association = new IIRScram_AssociationElementByExpression();
      new_association->set_formal( current_formal );
      new_association->set_actual( actual_decl );
    }
    else{
      new_association = new IIRScram_AssociationElementOpen();
      new_association->set_formal( current_formal );
    }
    copy_location( err_info, new_association );
    append( new_association );

    current_formal = dynamic_cast<IIRScram_InterfaceDeclaration *>(formal_list->successor( current_formal ));
  }
  
}

visitor_return_type *
IIRScram_AssociationList::_accept_visitor( node_visitor *visitor, 
					   visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_AssociationList(this, arg);
}
