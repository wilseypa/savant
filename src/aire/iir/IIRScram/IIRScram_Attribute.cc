// Copyright (c) The University of Cincinnati.  All rights reserved.

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

#include "savant.hh"
#include "IIRScram_Attribute.hh"
#include "IIRScram_AccessTypeDefinition.hh"
#include "IIRScram_ArrayTypeDefinition.hh"
#include "IIRScram_AttributeDeclaration.hh"
#include "IIRScram_BranchQuantityDeclaration.hh"
#include "IIRScram_ConstantDeclaration.hh"
#include "IIRScram_DesignatorExplicit.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EnumerationLiteral.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "IIRScram_FreeQuantityDeclaration.hh"
#include "IIRScram_FunctionDeclaration.hh"
#include "IIRScram_FunctionCall.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_IndexedName.hh"
#include "IIRScram_IntegerLiteral.hh"
#include "IIRScram_IntegerSubtypeDefinition.hh"
#include "IIRScram_InterfaceList.hh"
#include "IIRScram_LeftAttribute.hh"
#include "IIRScram_PhysicalLiteral.hh"
#include "IIRScram_PhysicalSubtypeDefinition.hh"
#include "IIRScram_RangeTypeDefinition.hh"
#include "IIRScram_RightAttribute.hh"
#include "IIRScram_ScalarNatureDefinition.hh"
#include "IIRScram_SignalDeclaration.hh"
#include "IIRScram_VariableInterfaceDeclaration.hh"

#include "StandardPackage.hh"
#include "constraint_functors.hh"
#include "error_func.hh"
#include "set.hh"
#include "symbol_table.hh"
#include "resolution_func.hh"

#include <sstream>

IIRScram_Attribute::IIRScram_Attribute() {}

IIRScram *
IIRScram_Attribute::_clone(){
  _report_undefined_scram_fn("_clone()");  
  return NULL;
}

void 
IIRScram_Attribute::_set_suffix( IIRScram *suffix ){
  set_suffix(suffix);
}

IIRScram *
IIRScram_Attribute::_get_suffix( ){
  return dynamic_cast<IIRScram *>(get_suffix());
}

void 
IIRScram_Attribute::_resolve_suffix(){
  if( _get_suffix() == NULL || _get_suffix()->is_resolved() == TRUE ) {
    return;
  }
  else{
    // Can't do much more here.  Some of the classes have limitations on
    // the types you can put in the suffix.
		
    // This will call the correct virtual method in the derived class.
    _resolve_suffix_special();
  }
}

void 
IIRScram_Attribute::_resolve_suffix_special(){
  _report_undefined_scram_fn("_resolve_suffix_special()");
}

IIRScram_RangeTypeDefinition *
IIRScram_Attribute::_build_range_type(){
  // Common code between range and reverse range.
  IIRScram_RangeTypeDefinition *retval = new IIRScram_RangeTypeDefinition();
  copy_location( this, retval );
  IIRScram_LeftAttribute *left = new IIRScram_LeftAttribute();
  copy_location( this, left );
  IIRScram_RightAttribute *right = new IIRScram_RightAttribute();
  copy_location( this, right );
	
  left->set_prefix( _get_prefix()->_clone() );
  right->set_prefix( _get_prefix()->_clone() );
  IIRScram_TypeDefinition *subtype = _get_subtype();
  ASSERT( subtype != NULL );
  StandardPackage *package = _get_design_file()->get_standard_package();
  if( get_kind() == IIR_RANGE_ATTRIBUTE ){
    retval->set_left( left );
    retval->set_right( right );
    if( subtype->_get_direction() == NULL || subtype->is_ascending_range() == TRUE ){
      // This is the "true" literal
      retval->set_direction( package->get_boolean_type()->get_right() );
    }
    else{
      // This is the "false" literal
      retval->set_direction( package->get_boolean_type()->get_left() );
    }
  }
  else{
    ASSERT( get_kind() == IIR_REVERSE_RANGE_ATTRIBUTE );
    retval->set_left( right );
    retval->set_right( left );
    if( subtype->_get_direction() == NULL || subtype->is_ascending_range() == TRUE ){
      retval->set_direction( package->get_boolean_type()->get_right() );
    }
    else{
      retval->set_direction( package->get_boolean_type()->get_left() );
    }
  }
  return retval;
}

IIRScram_TextLiteral *
IIRScram_Attribute::_get_attribute_name(){
  return dynamic_cast<IIRScram_TextLiteral *>(get_attribute_name());
}

savant::set<IIRScram_Declaration> *
IIRScram_Attribute::_symbol_lookup(){
  // We have a virtual function, "_get_attribute_name", that returns
  // to us the name of attribute that this instance created...    
  IIRScram_TypeDefinition       *my_subtype = NULL;
  savant::set<IIRScram_Declaration>     *my_decls;

  constraint_functor *functor = new is_attribute_declaration_functor;
  my_decls = _get_attribute_name()->_symbol_lookup(functor);
  delete functor;
  if( my_decls == NULL ){
    my_subtype = _get_subtype();
    // Then this attribute hasn't been declared.  Now we need to create
    // a declaration for it...
    IIRScram_AttributeDeclaration *attribute_decl = new IIRScram_AttributeDeclaration();
    copy_location( this, attribute_decl );
		
    attribute_decl->set_declarator( _get_attribute_name() );
    attribute_decl->set_subtype( my_subtype );
    attribute_decl->set_attribute( (IIRScram_Attribute *)this );
    attribute_decl->_add_declaration();
		
    my_decls = _get_attribute_name()->_symbol_lookup();
  }
  else{
    // OK, there was at least one declaration of an attribute with our 
    // name.  We need to find the one with OUR subtype...
		
    // Now, if there is no attribute declaration for whatever
    // attribute this is, we'll generate one.
    if( get_kind() != IIR_USER_ATTRIBUTE ){
      IIRScram_AttributeDeclaration *current_attribute_decl;
      current_attribute_decl = dynamic_cast<IIRScram_AttributeDeclaration *>(my_decls->getElement());
      while( current_attribute_decl != NULL ){
	if( _get_subtype()->is_compatible( dynamic_cast<IIRScram_TypeDefinition *>(current_attribute_decl->IIRBase_AttributeDeclaration::get_subtype()) ) == 0 ){
	  my_decls->remove( current_attribute_decl );
	}
	current_attribute_decl = dynamic_cast<IIRScram_AttributeDeclaration *>(my_decls->getNextElement());
      }    
      
      if(my_decls->size() == 0) {
				// Then this attribute hasn't been declared.  Now we need to create
				// a declaration for it...
	IIRScram_AttributeDeclaration *attribute_decl = new IIRScram_AttributeDeclaration();
	copy_location( this, attribute_decl );
	attribute_decl->set_declarator( _get_attribute_name() );
	attribute_decl->set_subtype( _get_subtype() );
	attribute_decl->set_attribute( this );
	_get_symbol_table()->add_declaration( attribute_decl );
				//      my_decls = sym_tab->find_set( _get_attribute_name() );
	my_decls->add(attribute_decl);
      }
      //$$$ - end of my code 
    }
  }
	
  ASSERT( my_decls->size() == 1 );
  //  IIRScram_Declaration *my_decl = my_decls->getElement();
  
  // So, we have a declaration for this attribute now.  What this attribute
  // represents is a signal, or a function or something.  We want
  // "_symbol_lookup" to return a reference to that "thing".  We'll take
  // the prefix "foo" in foo'quiet and generate something like foo_quiet,
  // and then use a virtual method to generate a declaration...
  ostringstream decl_name;
  
  if( _get_prefix()->_is_iir_declaration() == true ){
    decl_name << _get_prefix()->_get_declarator() << "_" 
	      << _get_attribute_name();
  }
  else{
    decl_name << _get_prefix() << "_" << _get_attribute_name();
  }
	
  string decl_name_string = decl_name.str();
	
  savant::set<IIRScram_Declaration> *attached_to = _get_prefix()->_symbol_lookup();
	
  if( attached_to == NULL ){
    ostringstream err;
    err << *_get_prefix() << " undefined";
    report_error( this, err.str() );
    return NULL;
  }
	
  IIRScram_Declaration *signal_decl = NULL;
  switch ( attached_to->size() ) {
  case 1:{
    signal_decl = attached_to->getElement();
    break;
  }
  case 0:
  default:
    cerr << "Internal error in overload resolution in "
	 << "IIRScram_Attribute::_symbol_lookup() - got "
	 << attached_to->size() << " possibilities." << endl;
    abort();
  }

  delete my_decls;
  delete attached_to;
	
//   _set_implicit_declaration( implicit_decl );
 
  savant::set<IIRScram_Declaration> *retval =  NULL;
//   savant::set<IIRScram_Declaration> *retval = new savant::set<IIRScram_Declaration>( implicit_decl );
	
  return retval;
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_Attribute::_get_rval_set( constraint_functor * ){
  IIRScram_TypeDefinition *rval = _get_subtype();
  savant::set<IIRScram_TypeDefinition> *my_rvals = NULL;
	
  if( rval != NULL ){
    my_rvals = new savant::set<IIRScram_TypeDefinition>( rval );
  }
  return my_rvals;
}

IIRScram_TypeDefinition *
IIRScram_Attribute::_get_prefix_subtype( constraint_functor *functor ){
  IIRScram_TypeDefinition *retval = NULL;
  if( _get_prefix()->is_resolved() == true ){
    retval = _get_prefix()->_get_subtype();
  }
  else{
    savant::set<IIRScram_TypeDefinition> *prefix_types = _get_prefix()->_get_rval_set( functor );
    if( prefix_types == NULL ){
      report_undefined_symbol( _get_prefix() );
      return NULL;
    }
    switch( prefix_types->size() ){
    case 0:{
      ostringstream err;
      err << "|" << *_get_prefix()
	  << "| has no definition appropriate for use as a prefix "
	  << "to attribute " << _get_attribute_name();
      report_error( this, err.str() );
      break;
    }
    case 1:{
      retval = prefix_types->getElement();
      break;
    }
    default: {
      ostringstream err;
      err << "Cannot disambiguate |" << *_get_prefix() << "| in its usage.";
      report_error( this, err.str() );
    }
    }
    delete prefix_types;
  }
  return retval;
}

void 
IIRScram_Attribute::_type_check( savant::set<IIRScram_TypeDefinition> * ){
  // We need to resolve our prefix. 
  _resolve_prefix();
  if( has_suffix() == TRUE ){
    _resolve_suffix();
  }
  set_subtype(_get_subtype());
  ASSERT( is_resolved() == TRUE );
}

void 
IIRScram_Attribute::_resolve_prefix(){
  bool done = false;
  // The prefix can be a library unit and therefore not have a return
  // type.  It can also be an indexed name and not have a declaration.
  // Therefore, we have to check for both...
  savant::set<IIRScram_Declaration> *prefix_decls = _get_prefix()->_symbol_lookup();
  if( prefix_decls != NULL ){
    switch( prefix_decls->size() ){
    case 1:{
      set_prefix( _get_prefix()->_decl_to_decl( prefix_decls->getElement() ) );
      done = true;
      break;
    }
    default:{
      // We're not done and we'll fall through.
    }
    }
  }
  savant::set<IIRScram_TypeDefinition> *prefix_rvals = NULL;
  if( done == false ){
    prefix_rvals = _get_prefix()->_get_rval_set();
    
    if( prefix_rvals == NULL ){
      report_undefined_symbol( _get_prefix() );
      goto finish;
    }
    
    set_prefix( _get_prefix()->_semantic_transform( prefix_rvals ) );
    
    delete prefix_rvals;
    prefix_rvals = _get_prefix()->_get_rval_set();
    
    if( prefix_rvals == NULL || prefix_rvals->size() == 0 ){
      report_undefined_symbol( _get_prefix() );
      goto finish;
    }
    
    if( prefix_rvals->size() > 1 ){
      report_ambiguous_error( _get_prefix(), prefix_rvals->convert_set<IIR_TypeDefinition>() );
      goto finish;
    }
    _get_prefix()->_type_check( prefix_rvals );  
    set_prefix( _get_prefix()->_rval_to_decl( prefix_rvals->getElement() ) );
    ASSERT( _get_prefix()->is_resolved() == TRUE );
    
    if( _get_prefix()->get_kind() == IIR_FUNCTION_CALL ){
      IIRScram_FunctionCall *as_func_call = dynamic_cast<IIRScram_FunctionCall *>(_get_prefix());
      ASSERT( as_func_call->get_implementation() != NULL );
      IIRScram_Declaration *new_prefix = as_func_call->_get_implementation();
      delete _get_prefix();
      set_prefix( new_prefix );
    }
  }
 finish:
  delete prefix_rvals;
  delete prefix_decls;
}

IIRScram *
IIRScram_Attribute::_decl_to_decl( IIRScram_Declaration * ){
  // So, we're being told our declaration is "my_decl".  We don't really
  // care, but we DO need to make that our prefix is resolved.  We probably
  // need to do the exact same stuff in rval_to_decl.  This should be put
  // into a function "resolve_prefix".
  _resolve_prefix();
  if( has_suffix() == TRUE ){
    _resolve_suffix();
  }
  return this;
}

IIRScram *
IIRScram_Attribute::_rval_to_decl( IIRScram_TypeDefinition * ){
  IIRScram_Attribute *retval = this;

  if( _get_prefix()->is_resolved() == TRUE ){
    ostringstream imp_name;
    imp_name << _get_prefix();
    imp_name << "_";
    imp_name << _get_attribute_name();
    
    ASSERT( _get_suffix() == NULL || _get_suffix()->is_resolved() == TRUE );
    
    string decl_name = imp_name.str();
    
    ASSERT( retval != NULL );
  }
  return retval;
}

void
IIRScram_Attribute::_clone( IIRScram *copy_into ){
  ASSERT( copy_into->_is_iir_attribute() == TRUE );
  IIRScram_Name::_clone( copy_into );
}

void 
IIRScram_Attribute::_resolve_suffix_base_type_of_prefix(){
  IIRScram              *suffix_to_process = NULL;

  if( _get_suffix() == NULL || _get_suffix()->is_resolved() == FALSE ){
    suffix_to_process = _get_suffix();
    ASSERT( _get_prefix()->is_resolved() == TRUE );

    // The suffix must be an expression whose type is the base type of
    // of the prefix.
    IIRScram_TypeDefinition *prefix_type = _get_prefix()->_get_subtype();

    savant::set<IIRScram_TypeDefinition> *suffix_types = suffix_to_process->_get_rval_set();
  
    IIRScram_TypeDefinition *current_type = suffix_types->getElement();
    while( current_type != NULL ){
      if( current_type->is_compatible( prefix_type ) ){
	break;
      }
    
      current_type = suffix_types->getNextElement();
    }
    if( current_type != NULL ){
      ASSERT( current_type->is_scalar_type() == TRUE );
      set_suffix( _get_suffix()->_semantic_transform( current_type ) );
      _get_suffix()->_type_check( current_type );
      set_suffix( _get_suffix()->_rval_to_decl( current_type ) );
    }
    else{
      ostringstream err;
      err << "|" << *_get_suffix() << "| is not a valid suffix for |" << *this << "|. ";
      err << "The suffix must be an expression whose type is the base type of the prefix.";
    
      report_error( this, err.str() );
    }
  }
}

void 
IIRScram_Attribute::_resolve_suffix_local_static_int(){
  
  // X a locally static expression of type universal integer, the
  // value of which must not exceed the dimensionality of of A
  // (defautls to 1)
  
  // Called by
  
  // IIRScram_LeftAttribute
  // IIRScram_RightAttribute
  // IIRScram_HighAttribute
  // IIRScram_LowAttribute
  // IIRScram_RangeAttribute
  // IIRScram_ReverseRangeAttribute
  // IIRScram_LengthAttribute
  // IIRScram_AscendingAttribute

  IIRScram              *suffix_to_process = _get_suffix();
  StandardPackage       *package = _get_design_file()->get_standard_package();
  if( _get_suffix() != NULL && _get_suffix()->is_resolved() == FALSE ){

    ASSERT( _get_prefix()->is_resolved() == TRUE );

    savant::set<IIRScram_TypeDefinition> *suffix_types = suffix_to_process->_get_rval_set();
  
    IIRScram_TypeDefinition *current_type = suffix_types->getElement();
    while( current_type != NULL ){
      if( current_type == dynamic_cast<IIRScram_TypeDefinition *> (package->get_savant_universal_integer()) ){
	break;
      }
    
      current_type = suffix_types->getNextElement();
    }

    if( current_type != NULL ){
      _set_suffix( _get_suffix()->_semantic_transform( current_type ) );
      _get_suffix()->_type_check( current_type );
      _set_suffix( _get_suffix()->_rval_to_decl( current_type ) );
    }
    else{
      ostringstream err;
      err << "|" << *_get_suffix() << "| is not a valid suffix for |" << *this << "|.";
      err << " The suffix must be a locally static expression of type universal integer.";
    
      report_error( this, err.str() );
    }
    delete suffix_types;
  }
}

void 
IIRScram_Attribute::_resolve_suffix_non_negative_time(){
  // a static expression of type time that evaluates to a
  // nonnegative value
  
  // Used for:
  // IIRScram_DelayedAttribute
  // IIRScram_StableAttribute
  // IIRScram_QuietAttribute

  StandardPackage       *package = _get_design_file()->get_standard_package();
  if( _get_suffix() != NULL && _get_suffix()->is_resolved() == FALSE ){
    ASSERT( _get_prefix()->is_resolved() == TRUE );
    savant::set<IIRScram_TypeDefinition> *suffix_types = _get_suffix()->_get_rval_set();
    IIR_TypeDefinition *time_rval = package->get_time_type();

    IIRScram_TypeDefinition *current_type = suffix_types->getElement();
    while( current_type != NULL ){
      if( current_type == time_rval ){
	break;
      }
    
      current_type = suffix_types->getNextElement();
    }

    if( current_type != NULL ){
      _set_suffix( _get_suffix()->_semantic_transform( current_type ) );
      _get_suffix()->_type_check( current_type );
      _set_suffix( _get_suffix()->_rval_to_decl( current_type ) );
    }
    else{
      ostringstream err;
      err << "|" << *_get_suffix() << "| is not a valid suffix for |" << *this << "|.";
      err << " The suffix must be a locally static expression of type universal integer.";
    
      report_error( this, err.str() );
    }
  }  
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_Attribute::_get_rval_set_high_low_left_right( constraint_functor *functor ){
  savant::set<IIRScram_TypeDefinition> *retval = NULL;

  savant::set<IIRScram_TypeDefinition> *prefix_rvals = _get_prefix()->_get_rval_set(functor);
  if( prefix_rvals != NULL ){
    retval = new savant::set<IIRScram_TypeDefinition>;
    IIRScram_TypeDefinition *current_rval = prefix_rvals->getElement();
    while( current_rval != NULL ){
      if( current_rval->is_array_type() == TRUE ){
	retval->add( current_rval->_get_resolved_index_subtype() );
      }
      else if ( current_rval->is_scalar_type() == TRUE ){
	retval->add( current_rval );
      }
      current_rval = prefix_rvals->getNextElement();
    }
  }
  delete prefix_rvals;

  if( retval != NULL && retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }

  return retval;
}

IIRScram_TypeDefinition *
IIRScram_Attribute::_get_subtype_high_low_left_right(){
  ASSERT( _get_prefix()->is_resolved() == TRUE );

  IIRScram_TypeDefinition *prefix_rval = _get_prefix()->_get_subtype();

  if( prefix_rval->is_array_type() == TRUE ){
    return prefix_rval->_get_resolved_index_subtype();
  }
  else if ( prefix_rval->is_scalar_type() == TRUE ){
    return prefix_rval;
  }
  else{
    ostringstream err;
    err << "|" << *_get_prefix() << "| must a scalar or an array type to use the "
	<< "attribute 'HIGH." << endl;
    report_error( this, err.str() );
    abort();
    return 0;
  }
}

IIRScram_TypeDefinition *
IIRScram_Attribute::_get_prefix_rval_range_attributes(){
  IIRScram_TypeDefinition *retval = NULL;

  savant::set<IIRScram_TypeDefinition> *prefix_types = 
    _get_prefix()->_get_rval_set();
  if( prefix_types == NULL ){
    report_undefined_symbol( _get_prefix() );
    return NULL;
  }
  constraint_functor *functor = new is_array_type_functor();
  prefix_types->reduce_set( functor );
  delete functor;
  switch( prefix_types->size() ){
  case 0:{
    ostringstream err;
    err << "|" << *_get_prefix() << "| has no array definition - "
	<< "'range is invalid here.";
    report_error( this, err.str() );
    break;
  }

  case 1:{
    retval = prefix_types->getElement();
    break;
  }

  default:{
    ostringstream err;
    err << "Cannot disambiguate |" << *_get_prefix() << "| in it's usage.";
    report_error( this, err.str() );
  }
  }
  delete prefix_types;
  
  return retval;
}

IIRScram_ScalarTypeDefinition *
IIRScram_Attribute::_get_subtype_range_attribute(){
  IIRScram_ScalarTypeDefinition *retval = NULL;
  if( _get_prefix_subtype()->is_array_type() ){
    if( _get_suffix() == NULL ){
      retval = _get_prefix_subtype()->_get_resolved_index_subtype();
    }
    else{
      IIRScram_IntegerLiteral *static_val = _get_suffix()->_get_integer_static_value();
      if( static_val != NULL ){
	int val = static_val->get_integer_value();
	if( val > _get_prefix_subtype()->get_num_indexes() ){
	  ostringstream err;
	  err << "'range( " << val << " ) not allowed for " 
	      << _get_prefix_subtype()->get_num_indexes() << " dimensional array.";
	  report_error( this, err.str() );
	}
	else{
	  IIRScram_TypeDefinition *current_array_type = _get_prefix_subtype();
	  int i;
	  for( i = 1; i < val; i++ ){
	    current_array_type = current_array_type->_get_element_subtype();
	    ASSERT( current_array_type->is_array_type() == TRUE );
	  }
	  retval = current_array_type->_get_resolved_index_subtype();
	}
	delete static_val;
      }
    }

    if( get_kind() == IIR_REVERSE_RANGE_ATTRIBUTE ){
      retval = dynamic_cast<IIRScram_ScalarTypeDefinition *>((dynamic_cast<IIRScram *>(retval))->_clone());
      IIRScram *tmp = retval->_get_base_type_left();
      retval->set_left( retval->_get_base_type_right() );
      retval->set_right( tmp );

      StandardPackage *package = _get_design_file()->get_standard_package();
      if( retval->get_direction() ){
	if( retval->get_direction() == package->get_true_literal() ){
	  retval->set_direction( package->get_false_literal() );
	}
	else{
	  ASSERT( retval->get_direction() == package->get_false_literal() );
	  retval->set_direction( package->get_true_literal() );
	}
      } // else get_direction is null and we don't need to do anything.
    }
  }
  return retval;
}

IIRScram_TextLiteral *
IIRScram_Attribute::_build_attribute_name() {
  return dynamic_cast<IIRScram_TextLiteral *>(build_attribute_name());
}
