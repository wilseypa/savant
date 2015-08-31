
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

#include "IIRScram_AccessTypeDefinition.hh"
#include "IIRScram_Aggregate.hh"
#include "IIRScram_ArchitectureDeclaration.hh"
#include "IIRScram_AssociationElementByExpression.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_CaseStatementAlternativeByChoices.hh"
#include "IIRScram_CaseStatementAlternativeByExpression.hh"
#include "IIRScram_CaseStatementAlternativeByOthers.hh"
#include "IIRScram_Choice.hh"
#include "IIRScram_ChoiceList.hh"
#include "IIRScram_DesignatorExplicit.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_EnumerationLiteral.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "IIRScram_FunctionCall.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_IndexedName.hh"
#include "IIRScram_InterfaceDeclaration.hh"
#include "IIRScram_InterfaceList.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_OthersInitialization.hh"
#include "IIRScram_Signature.hh"
#include "IIRScram_SubprogramDeclaration.hh"
#include "IIRScram_StringLiteral.hh"
#include "IIRScram_TypeDeclaration.hh"

#include "StandardPackage.hh"
#include "symbol_table.hh"
#include "resolution_func.hh"
#include "error_func.hh"
#include "set.hh"
#include <sstream>
using std::ostringstream;

using savant::set;

IIRScram_Declaration *
resolve_if_one( set<IIRScram_Declaration> *set_to_resolve,
		IIRScram_Name *name_for_error ){

  IIRScram_Declaration *retval = NULL;
  switch ( set_to_resolve->size() ){
  case 0:{
    if( name_for_error != NULL ){
      report_undefined_symbol( name_for_error );
    }
    break;
  }
  case 1:{
    retval = set_to_resolve->getElement();
    
    break;
  }
  default:{
    break;
  }
  }

  return retval;
}

set<IIRScram_TypeDefinition> *
decl_set_to_typedef_set(set<IIRScram_Declaration> *decl_set,constraint_functor *functor ){
  set<IIRScram_TypeDefinition> *typedef_set = NULL;

  if( decl_set != NULL ){
    int size = decl_set->size();
    
    if( size > 0 ){
      typedef_set = new set<IIRScram_TypeDefinition>;
      
      if( functor != 0 ){
	decl_set->reduce_set( functor );
      }

      IIRScram_TypeDefinition *current_rval = NULL;
      IIRScram_Declaration *current_decl = decl_set->getElement();
      while( current_decl != NULL ){
	current_rval = current_decl->_get_subtype();
	if( current_rval != NULL ){
	  typedef_set->add( current_rval );
	}
	current_decl = decl_set->getNextElement();
      }
    }
    // else nothing..
  }
  // else nothing..

  return typedef_set;
}


void 
reconcile_sets( set<IIRScram_TypeDefinition> *lval_set, 
		set<IIRScram_TypeDefinition> *rval_set){
  
  ASSERT( lval_set != NULL );
  ASSERT( rval_set != NULL );
  
  set<IIRScram_TypeDefinition> new_rval_set;

  bool one_matched = false;
  IIRScram_TypeDefinition *current_lval = lval_set->getElement();
  current_lval = lval_set->getElement();
  while( current_lval != NULL ){
    IIRScram_TypeDefinition *current_rval = rval_set->getElement();
    one_matched = false;
    while( current_rval != NULL ){
      IIRScram_TypeDefinition *compatible_subtype = dynamic_cast<IIRScram_TypeDefinition *>(current_lval->is_compatible( current_rval));
      if( compatible_subtype != NULL ){
	one_matched = true;
	new_rval_set.add( current_rval );
      }
      current_rval = rval_set->getNextElement();
    }
    if( one_matched == false ){
      lval_set->remove( current_lval );
    }
    current_lval = lval_set->getNextElement();
  }

  // So we have our matches in lval_set.  Let's build our rval_set.
  int size = lval_set->size();

  rval_set->reset( size );
  *rval_set = new_rval_set;

  // Nothing to return - the sets are built!
}


void 
reconcile_sets( set<IIRScram_Declaration> *decls, 
		set<IIRScram_TypeDefinition> *rval_set){

  ASSERT( decls != NULL );
  ASSERT( rval_set != NULL );
  
  set<IIRScram_Declaration> original_set( *decls );

  bool one_matched = false;
  // First try to do an exact subtype match...
  IIRScram_Declaration *current_decl = decls->getElement();
  while( current_decl != NULL ){
    if( current_decl->_get_subtype() != NULL ){
      if( rval_set->contains( current_decl->_get_subtype() ) ){
	one_matched = true;
      }
      else {
	decls->remove( current_decl );
      }
    }

    current_decl = decls->getNextElement();
  }
  
  if( one_matched == false ){
    *decls = original_set;

    IIRScram_Declaration *current_decl = decls->getElement();
    while( current_decl != NULL ){
      if( current_decl->_get_subtype() != NULL ){
	one_matched = false;
	IIRScram_TypeDefinition *current_rval = rval_set->getElement();
	while( current_rval != NULL ){
	  if( current_decl->_get_subtype()->is_compatible( current_rval ) != NULL ){
	    one_matched = TRUE;
	  }
	
	  current_rval = rval_set->getNextElement();
	} // inner loop

	if( one_matched == FALSE ){
	  decls->remove( current_decl );
	}
      }
      current_decl = decls->getNextElement();
    } // outer loop
  } // Check for simple compatibility

  // So we have our matches in decls.  Let's build our rval_set.
  int i;
  int size = decls->size();

  rval_set->reset( size );
  
  current_decl = decls->getElement();
  if( current_decl != NULL ){
    if(  current_decl->_get_subtype() != NULL ){
      rval_set->add( current_decl->_get_subtype() );
    }
  }
  for( i = 1; i < size;  i++ ){
    current_decl = decls->getNextElement();
    if(  current_decl->_get_subtype() != NULL ){
      rval_set->add( current_decl->_get_subtype() );
    }
  }

  // Nothing to return - the sets are built!
}


void 
resolve_subprogram_decls(set<IIRScram_Declaration>              *possible_subprogram_decls,
			 IIRScram_AssociationList                       *argument_list,
			 const set<IIRScram_TypeDefinition>     *possible_return_types){

  ASSERT( possible_subprogram_decls != NULL );
  ASSERT( argument_list != NULL );

  // Consider each function, one at a time...
  bool arguments_match;

  IIRScram_Declaration *current_decl = possible_subprogram_decls->getElement();
  while( current_decl != NULL ){
    ASSERT( current_decl->is_subprogram() == TRUE );
    IIRScram_SubprogramDeclaration *as_subprog = dynamic_cast<IIRScram_SubprogramDeclaration *>(current_decl);
    ASSERT(as_subprog != NULL);
    arguments_match =
      argument_list->_check_valid_arguments( as_subprog->_get_interface_declarations(), NULL);

    if( arguments_match == FALSE ){
      possible_subprogram_decls->remove( current_decl );
    }
    current_decl = possible_subprogram_decls->getNextElement();
  }

  // So now we have all of the subprogram declarations whose arguments
  // match those passed in...  We need need to now check against the
  // return types...
 if( possible_return_types != NULL ){
   // This function (resolve_subprogram_decls) isn't supposed to
   // modify the set of possible return types.
   set<IIRScram_TypeDefinition> temp_return_types( (set<IIRScram_TypeDefinition> &)*possible_return_types );
   reconcile_sets( possible_subprogram_decls, &temp_return_types);
 }
}


void 
resolve_subprogram_decls(set<IIRScram_Declaration>                      *possible_subprogram_decls,
			 dl_list<set<IIRScram_TypeDefinition> >         *parameter_rval_list,
			 set<IIRScram_TypeDefinition>                   *possible_return_types ){

  // Consider each function, one at a time...
  IIRScram_Declaration *current_subprog_decl; 
  bool one_matched = false;

  current_subprog_decl = possible_subprogram_decls->getElement();
  while( current_subprog_decl != NULL ){
    // Go through all of the parameters, and see if one matches..
    int i = 0;
    
    set<IIRScram_TypeDefinition> *current_parameter_rvals;

    current_parameter_rvals = parameter_rval_list->first();
    while( current_parameter_rvals != NULL ){
      // All of the possible r_vals for this argument...
      IIRScram_TypeDefinition *current_parameter_rval;
      current_parameter_rval = current_parameter_rvals->getElement();
      while( current_parameter_rval != NULL ){	
	if(current_subprog_decl->_check_param(current_parameter_rval, i)
	   == true){
	  one_matched = true;
	  break;
	}
	
	current_parameter_rval = current_parameter_rvals->getNextElement();
      }
    
      if( one_matched == false ){
	// Then this subprogram declaration COULD NOT be correct... (Given
	// positional association ONLY...
	possible_subprogram_decls->remove( current_subprog_decl );
	break;
      }
    
    
      current_parameter_rvals = 
	parameter_rval_list->successor( current_parameter_rvals );
      i++;
    }
    
    // Even though all of the arguments so far have matched, the subprog
    // might require more...
    if((dynamic_cast<IIRScram_SubprogramDeclaration *>
	(current_subprog_decl)->_num_required_args()) >
       parameter_rval_list->size() ){
      possible_subprogram_decls->remove( current_subprog_decl );
    }
    
    // So now we have all of the subprogram declarations whose arguments
    // match those passed in...  We need need to now check against the
    // return types...
    if( possible_return_types != NULL ){
      // This function (resolve_subprogram_decls) isn't supposed to
      // modify the set of possible return types.
      set<IIRScram_TypeDefinition> temp_return_types( *possible_return_types );
      reconcile_sets( possible_subprogram_decls, &temp_return_types );
    }
    
    current_subprog_decl = possible_subprogram_decls->getNextElement();
  }
}

void 
resolve_subprogram_decls( set<IIRScram_Declaration>     *possible_subprogram_decls,
			  IIRScram_Signature            *signature){

  // So, we just need to build a dl_list of sets of r_vals for the
  // signature of this function, and one for the return type...
  IIRScram_TypeDefinition *return_type = dynamic_cast<IIRScram_TypeDefinition *>(signature->get_return_type());

  IIRScram_DesignatorExplicit *desig_explicit;

  dl_list<IIRScram_TypeDefinition> *type_def_list = new dl_list<IIRScram_TypeDefinition>;
  IIRScram_Designator *current_desig = dynamic_cast<IIRScram_Designator *>(signature->get_argument_type_list()->first());
  while( current_desig != NULL ){
    ASSERT( current_desig->get_kind() == IIR_DESIGNATOR_EXPLICIT );
    desig_explicit = dynamic_cast<IIRScram_DesignatorExplicit *>(current_desig);
    ASSERT( desig_explicit->get_signature() == NULL );

    type_def_list->append( dynamic_cast<IIRScram_TypeDefinition *>(desig_explicit->get_name()) );
    current_desig = dynamic_cast<IIRScram_Designator *>(signature->get_argument_type_list()->successor( current_desig ));
  }

  // Now we need to generate sets for all of the data we have, and pass
  // it on to the other function...
  set<IIRScram_TypeDefinition> return_set( return_type );
  dl_list<set<IIRScram_TypeDefinition> > signature_list;

  IIRScram_TypeDefinition *current_type_def;
  current_type_def = dynamic_cast<IIRScram_TypeDefinition *>(type_def_list->first());
  while( current_type_def != NULL ){
    set<IIRScram_TypeDefinition> *current_typedef_set;

    current_typedef_set = new set<IIRScram_TypeDefinition>( current_type_def );
    signature_list.append( current_typedef_set );

    current_type_def = dynamic_cast<IIRScram_TypeDefinition *>(type_def_list->successor( current_type_def ));
  }

  resolve_subprogram_decls( possible_subprogram_decls,
			    &signature_list,
			    &return_set );
}

IIRScram *
reduce_aggregate( IIRScram_Aggregate *aggregate ){
  IIRScram *retval = aggregate;

  // If the aggregate only has one element, there's a good chance we can
  // optimize it down to it's one element, or at least the association.
  if( aggregate->get_element_association_list()->size() == 1 ){
    IIRScram_AssociationElement *first_element = dynamic_cast<IIRScram_AssociationElement *>(aggregate->get_element_association_list()->first());
    if( first_element->get_kind() == IIR_ASSOCIATION_ELEMENT_BY_EXPRESSION ){
      IIRScram_AssociationElementByExpression *by_expression;
      by_expression = dynamic_cast<IIRScram_AssociationElementByExpression *>(first_element);
      if( by_expression->get_formal() == NULL &&
	  ( by_expression->get_actual() != NULL && 
	    by_expression->get_actual()->get_kind() != IIR_OTHERS_INITIALIZATION ) ){
	retval = by_expression->_get_actual();
	delete by_expression;
	delete aggregate;
      }
    }
  }

  return retval;
}


IIRScram *
reduce_association_list( IIRScram_AssociationList *list ){
  IIRScram *retval = list;

  if( list->size() == 1 ){
    IIRScram_AssociationElement *first_element = dynamic_cast<IIRScram_AssociationElement *>(list->first());
    if( first_element->get_kind() == IIR_ASSOCIATION_ELEMENT_BY_EXPRESSION ){
      IIRScram_AssociationElementByExpression *by_expr;
      by_expr = dynamic_cast<IIRScram_AssociationElementByExpression *>(first_element);
      if( by_expr->get_formal() == NULL ){
	retval = by_expr->_get_actual();
	delete list;
	delete by_expr;
      }
    }
  }

  return retval;
}

void 
process_aggregate_with_choices( IIRScram *formal_part, IIRScram *actual_part, IIRScram_Aggregate *retval ){
  IIRScram_AssociationElementByExpression *new_association;
  if( formal_part == NULL ){
    ASSERT( actual_part->get_kind() == IIR_CASE_STATEMENT_ALTERNATIVE_BY_EXPRESSION );
    actual_part = (dynamic_cast<IIRScram_CaseStatementAlternativeByExpression *>(actual_part))->_get_choice();
    ASSERT( actual_part->get_kind() == IIR_CHOICE );
    actual_part = (dynamic_cast<IIRScram_Choice *>(actual_part))->_get_value();
    
    new_association = new IIRScram_AssociationElementByExpression();
    new_association->set_actual( actual_part );
    actual_part->copy_location( new_association );
    retval->get_element_association_list()->append( new_association );  
  }
  else{
    IIRScram *new_formal = NULL;
    switch( formal_part->get_kind() ){
    case IIR_CASE_STATEMENT_ALTERNATIVE_BY_CHOICES:{
      IIRScram_CaseStatementAlternativeByChoices *as_choices;
      as_choices = dynamic_cast<IIRScram_CaseStatementAlternativeByChoices *>(formal_part);

      IIRScram_Choice *current_choice = dynamic_cast<IIRScram_Choice *>(as_choices->get_choices()->first());
      while( current_choice != NULL ){
	new_association = new IIRScram_AssociationElementByExpression();

	new_association->set_formal( current_choice->_get_value() );
	new_association->set_actual( actual_part );
	actual_part->copy_location( new_association );
	retval->get_element_association_list()->append( new_association );  
	current_choice = dynamic_cast<IIRScram_Choice *>(as_choices->get_choices()->successor( current_choice ));
      }
      break;
    }
    case IIR_CASE_STATEMENT_ALTERNATIVE_BY_EXPRESSION:{
      new_association = new IIRScram_AssociationElementByExpression();
      new_formal = (dynamic_cast<IIRScram_CaseStatementAlternativeByExpression *>(formal_part))->_get_choice();
      if( new_formal->get_kind() == IIR_CHOICE ){
	IIRScram *temp = (dynamic_cast<IIRScram_Choice *>(new_formal))->_get_value();
	delete new_formal;
	new_formal = temp;
      }
      delete formal_part;
      new_association->set_formal( new_formal );
      new_association->set_actual( actual_part );
      actual_part->copy_location( new_association );
      retval->get_element_association_list()->append( new_association );  
      break;
    }
    case IIR_CASE_STATEMENT_ALTERNATIVE_BY_OTHERS:{
      new_association = new IIRScram_AssociationElementByExpression();
      IIRScram_OthersInitialization *others = new IIRScram_OthersInitialization();
      actual_part->copy_location( others );
      actual_part->copy_location( new_association );
      others->set_expression( actual_part );
      delete formal_part;
      actual_part = others;
      formal_part = NULL;
      new_association->set_formal( new_formal );
      new_association->set_actual( actual_part );
      retval->get_element_association_list()->append( new_association );  
      break;
    }
    default:{
      ostringstream err;
      err << "Internal error in VHDLParser::aggregate - unknown formal type "
	  << formal_part->get_kind_text();
      report_error( formal_part, err.str() );
      abort();
    }
    }
  }
}

void 
check_name( IIR_TextLiteral *id, IIR_Name *name, const char *declaration_type ){
  if( IIRBase_TextLiteral::cmp( id, name ) != 0 ) {
    ostringstream err;
    err << "end |" << *name << "|"
	<< " does not match " << declaration_type <<" name |" 
	<< *id << "|.";
    report_error( name, err.str() );
  }
}

void 
check_name( IIR_TextLiteral *id, IIR_TextLiteral *name, const char *declaration_type ){
  if( IIRBase_TextLiteral::cmp( id, name ) != 0 ) {
    ostringstream err;
    err << "end |" << *name << "|"
	<< " does not match " << declaration_type <<" name |" 
	<< *id << "|.";
    report_error( name, err.str() );
  }
}

void 
check_name( IIR_Label *label, IIR_Name *name, const char *declaration_type ){
  if( label == NULL && name != NULL ){
    ostringstream err;
    err << "This " << declaration_type << " does not have a label, "
	<< "and therefore |end " << *name << "| does not apply.";
    report_error( name, err.str() );
  }
  else{
    ASSERT( label != NULL && name != NULL );
    check_name( label->get_declarator(), name, declaration_type );
  }
}


// This function takes as its input three interface lists--the formal and
// actual lists to be associated together, and the default map to be
// created.
void
build_default_map( IIRScram_InterfaceList       *formal_list,
		   IIRScram_InterfaceList       *actual_list,
		   IIRScram_AssociationList     &default_map) {

  ASSERT( (formal_list->get_kind()==IIR_PORT_LIST && actual_list->get_kind() == IIR_PORT_LIST)
	  || 
	  (formal_list->get_kind()==IIR_GENERIC_LIST&&actual_list->get_kind() == IIR_GENERIC_LIST));
  
  IIRScram_InterfaceDeclaration *formal, *actual;
  formal = dynamic_cast<IIRScram_InterfaceDeclaration *>(formal_list->first());
  while ( formal != 0 ) {
    IIRScram_TextLiteral *formal_name = formal->_get_declarator();

    // Find matching actual for this formal
    actual = dynamic_cast<IIRScram_InterfaceDeclaration *>(actual_list->first());
    while ( actual != 0 ) {
      IIRScram_TextLiteral *actual_name = actual->_get_declarator();
      if ( IIRBase_TextLiteral::cmp(formal_name, actual_name) == 0 ){
	break; // found the matching name
      }
      actual = dynamic_cast<IIRScram_InterfaceDeclaration *>(actual_list->successor( actual ));
    }
    
    IIRScram_AssociationElementByExpression *new_association;
    new_association = new IIRScram_AssociationElementByExpression();

    ASSERT( formal != actual );

    new_association->set_formal( formal );
    
    if ( actual == NULL ) { // matching name not found
      // This is implementing section 1.1.1.1 of the LRM.
      if( formal->_get_value() != NULL ){
	new_association->set_actual( formal->_get_value() );	
      }
      else{
	ostringstream err;
	err << "No local " 
	    << ((formal_list->get_kind() == IIR_PORT_LIST)?"port":"generic")
	    << " found with name |" << *formal_name << "|, and no default expression "
	    << "specified for formal.";
	report_error( &default_map, err.str() );
      }
    }
    else{
      new_association->set_actual( actual );	
    }

    default_map.append( new_association );

    formal = dynamic_cast<IIRScram_InterfaceDeclaration *>(formal_list->successor( formal ));
  }
}

IIR_TypeDeclaration *
find_incomplete_type_declaration( IIR_Identifier *type_name ){
  IIR_TypeDeclaration *retval = NULL;

  ASSERT( type_name != NULL );
  bool found_one = false;
  symbol_table *sym_tab = dynamic_cast<IIRScram_Identifier *>(type_name)->_get_symbol_table();
  set<IIR_TypeDeclaration> *incomplete_types = sym_tab->get_incomplete_types();
  IIR_TypeDeclaration *current = incomplete_types->getElement();
  while( current != NULL ){
    ASSERT( current->get_declarator() != NULL );
    if( IIRBase_TextLiteral::cmp( current->get_declarator(),
                                  type_name ) == 0 ){
      found_one = true;
      break;
    }
    current = incomplete_types->getNextElement();
  }
  if( found_one == true ){
    ASSERT( current != NULL );
    retval = current;
  }
  return retval;
}
