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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_DesignFile.hh"
#include "IIRScram_SelectedName.hh"
#include "IIRScram_LibraryDeclaration.hh"
#include "IIRScram_SimpleName.hh"
#include "IIRScram_AccessTypeDefinition.hh"
#include "IIRScram_RecordTypeDefinition.hh"
#include "IIRScram_FileDeclaration.hh"
#include "IIRScram_LibraryUnitList.hh"
#include "IIRScram_LibraryUnit.hh"
#include "IIRScram_TextLiteral.hh"

#include "error_func.hh"
#include "library_manager.hh"
#include "set.hh"
#include "symbol_table.hh"

#include <sstream>
using std::ostringstream;

IIRScram_LibraryDeclaration *
IIRScram_SelectedName::_get_library_declaration(){
  ASSERT( is_resolved() == true );
  ASSERT( _get_prefix() != NULL );
  if( _get_prefix()->get_kind() == IIR_LIBRARY_DECLARATION ){
    return dynamic_cast<IIRScram_LibraryDeclaration *>(_get_prefix());
  }
  else{
    ASSERT( get_prefix()->get_kind() == IIR_SELECTED_NAME );
    return (dynamic_cast<IIRScram_SelectedName *>(get_prefix()))->_get_library_declaration();
  }
}

savant::set<IIRScram_Declaration> *
IIRScram_SelectedName::_symbol_lookup(){
  savant::set<IIRScram_Declaration> *prefix_decls;
  savant::set<IIRScram_Declaration> *retval = NULL;

  ASSERT( _get_prefix() != NULL );
  ASSERT( _get_suffix() != NULL );

  prefix_decls = _get_prefix()->_symbol_lookup();
  if( prefix_decls == NULL ){
    return NULL;
  }
  else{
    IIRScram_Declaration *current_decl = dynamic_cast<IIRScram_Declaration *>(prefix_decls->getElement());
    savant::set<IIRScram_Declaration> *suffix_decls = NULL;
    while( current_decl != NULL ){
      IIR_Boolean found_in_library = FALSE;
      suffix_decls = _get_suffix()->_symbol_lookup( prefix_decls );
      if( suffix_decls == NULL ){
	savant::set<IIRScram_Declaration>       *decls = NULL;
	savant::set<IIR_Declaration>            *temp_decls 
          = current_decl->find_declarations( this );
        if ( temp_decls != NULL ) {
          decls = temp_decls->convert_set<IIRScram_Declaration>();
          delete temp_decls;
        }

	if( decls != NULL ){
	  suffix_decls = decls;
	  found_in_library = TRUE;
	}
      }
      if( suffix_decls != NULL ){
	if( retval == NULL ){
	  retval = new savant::set<IIRScram_Declaration>;
	}
	retval->add( suffix_decls );
	if( found_in_library == TRUE ){
	  current_decl->_add_to_declarative_region( suffix_decls );
	}
      }      
      current_decl = dynamic_cast<IIRScram_Declaration *>(prefix_decls->getNextElement());
    }
  }

  return retval;
}

IIRScram *
IIRScram_SelectedName::_get_suffix(){
  ASSERT( get_suffix() != NULL );
  return dynamic_cast<IIRScram *>(get_suffix());
}

const string
IIRScram_SelectedName::convert_to_library_name(){
  string retval;
  string tmp_str = _get_prefix()->convert_to_library_name();
  if(_get_suffix()->get_kind() != IIR_DESIGNATOR_BY_ALL){
    if((_get_prefix()->get_kind() == IIR_SELECTED_NAME) && 
       (_get_suffix()->get_kind() == IIR_SIMPLE_NAME)){
      //this is for handling the case where IIR_DESIGNATOR_BY_ALL is not
      //used in the use clause. ie. some type/subtype/function has been
      //specified.
      return tmp_str;
    }
    else {
      retval = tmp_str + library_manager::get_library_suffix();
    }
  }
  else {
    retval = tmp_str;
  }

  if(_get_suffix()->get_kind() != IIR_DESIGNATOR_BY_ALL){
    retval += "/";
  }

  tmp_str = _get_suffix()->convert_to_library_name();

  if( tmp_str != "" ){
    retval += library_manager::get_package_suffix();
  }

  return retval;
}

IIRScram *
IIRScram_SelectedName::_rval_to_decl( IIRScram_TypeDefinition *my_type){
  if( is_resolved() == FALSE ){
    savant::set<IIRScram_Declaration> *prefix_decls = _get_prefix()->_symbol_lookup();
    if( prefix_decls == NULL ){
      savant::set<IIRScram_TypeDefinition> *prefix_rvals = _get_prefix()->_get_rval_set();
      
      // This returns to us the proper type of the prefix...
      IIRScram_TypeDefinition *prefix_rval = _get_suffix()->_determine_rval_in_set( prefix_rvals,my_type );
      // Resolve the prefix...
      set_prefix( _get_prefix()->_semantic_transform( prefix_rval ) );
      _get_prefix()->_type_check( prefix_rval );
      set_prefix( _get_prefix()->_rval_to_decl( prefix_rval ) );
      
      // Finish resolving the suffix...
      set_suffix( _get_suffix()->_rval_to_decl( prefix_rval, my_type ) );
      delete prefix_rvals;
    }
    else{
      IIRScram_Declaration *prefix_decl;
      prefix_decl = _get_suffix()->_determine_decl_in_set( prefix_decls, my_type );
      ASSERT( prefix_decl != NULL );
      // Tell the prefix this is it's decl, and continue
      set_prefix( _get_prefix()->_decl_to_decl( prefix_decl ) );
      set_suffix( _get_suffix()->_rval_to_decl( prefix_decl, my_type ));
    }
    delete prefix_decls;
  }

  return this;
}

void 
IIRScram_SelectedName::_type_check( savant::set<IIRScram_TypeDefinition> * ){
  // Don't need to do anything here...
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_SelectedName::_get_rval_set(constraint_functor *functor){
  savant::set<IIRScram_TypeDefinition> *retval = NULL;
  if( is_resolved() == FALSE ){
    savant::set<IIRScram_Declaration> *prefix_decls = _get_prefix()->_symbol_lookup();
    
    if( prefix_decls == NULL ){
      savant::set<IIRScram_TypeDefinition> *prefix_rvals = _get_prefix()->_get_rval_set(functor);
      if( prefix_rvals == NULL ){
	return NULL;
      }
      retval = _get_suffix()->_get_rval_set( prefix_rvals, functor );
      delete prefix_rvals;
    }
    else{
      retval = _get_suffix()->_get_rval_set( prefix_decls, functor );
    }
    delete prefix_decls;
  }
  else{
    retval = new savant::set<IIRScram_TypeDefinition>( _get_subtype() );
  }

  return retval;
}

IIR_Boolean
IIRScram_SelectedName::is_object( ){
  ASSERT( is_resolved() == TRUE );
  if( _get_prefix()->is_object() == TRUE || _get_suffix()->is_object() == TRUE ){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

IIR_Boolean
IIRScram_SelectedName::_is_readable( ){
  ASSERT( is_resolved() == TRUE );
  if( _get_prefix() && _get_prefix()->is_object() ){
    return _get_prefix()->_is_readable();
  }
  else{
    return _get_suffix()->_is_readable();
  }
}

IIR_Boolean
IIRScram_SelectedName::_is_writable( ){
  ASSERT( is_resolved() == TRUE );
  if( _get_prefix() && _get_prefix()->is_object() ){
    return _get_prefix()->_is_writable();
  }
  else{
    return _get_suffix()->_is_writable();
  }
}

IIR_Boolean
IIRScram_SelectedName::is_configuration_declaration() {
  ASSERT ( is_resolved() == TRUE );
  
  if ((_get_suffix()->is_configuration_declaration() == TRUE) ||
      (_get_prefix()->is_configuration_declaration() == TRUE)) {
    return TRUE;
  }
  
  return FALSE;
}

IIR_Boolean 
IIRScram_SelectedName::_is_by_all(){
  return _get_suffix()->_is_by_all();
}

void
IIRScram_SelectedName::_set_suffix(IIRScram *suffix){
  ASSERT( suffix != NULL );

  set_suffix(suffix);
}

IIRScram *
IIRScram_SelectedName::_decl_to_decl( IIRScram_Declaration *suffix_decl ){
  savant::set<IIRScram_Declaration> *prefix_decls = _get_prefix()->_symbol_lookup();
  if( prefix_decls == NULL ){
    // Then someting probably went wrong - we shouldn't have ended up here,
    // I don't think...
    ostringstream err;
    err << "Internal error in IIRScram_SelectedName::_set_selected_name_declaration -"
	<< " found no prefix declarations.";
    report_error( this, err.str() );
    abort();
  }
  
  if( get_suffix()->get_kind() == IIR_DESIGNATOR_BY_ALL ){
    IIRScram_Declaration *current_decl = prefix_decls->getElement();
    while( current_decl != NULL ){
      if( current_decl == suffix_decl ){
	set_prefix( _get_prefix()->_decl_to_decl( current_decl ) );
	break;
      }
      current_decl = prefix_decls->getNextElement();
    }    
  }
  else{
    set_suffix( suffix_decl );
    
    IIRScram_Declaration *current_outer_decl = prefix_decls->getElement();
    while( current_outer_decl != NULL ){
      IIRScram_SimpleName temp_name;
      temp_name.set_prefix( suffix_decl->get_declarator() );
      savant::set<IIRScram_Declaration> *found = NULL;
      savant::set<IIR_Declaration>      *temp_set 
        = current_outer_decl->find_declarations( &temp_name );

      if ( temp_set != NULL ) {
        found = temp_set->convert_set<IIRScram_Declaration>();
        delete temp_set;
      }

      if( found != NULL ){
	IIRScram_Declaration *current_inner_decl = found->getElement();
	while( current_inner_decl != NULL ){
	  if( current_inner_decl == suffix_decl ){
	    set_prefix( _get_prefix()->_decl_to_decl( current_outer_decl ) );
	    break;
	  }
	  current_inner_decl = found->getNextElement();
	}
	delete found;
      }
      current_outer_decl = prefix_decls->getNextElement();
    }
  }

  delete prefix_decls;

  ASSERT( is_resolved() == TRUE );
  return this;
}
  
void 
IIRScram_SelectedName::_build_lib( IIRScram_LibraryUnit *new_unit ){
  if( get_prefix()->get_kind() == IIR_SIMPLE_NAME ){
    savant::set<IIRScram_Declaration> *prefix_decls = _get_prefix()->_symbol_lookup();
    if( prefix_decls != NULL ){
      IIRScram_Declaration *current_lib = prefix_decls->getElement();
      while( current_lib != NULL ){
	if( current_lib->get_kind() != IIR_LIBRARY_DECLARATION ){
	  prefix_decls->remove( current_lib );
	}
	current_lib = prefix_decls->getNextElement();
      }
      
      ASSERT( prefix_decls->size() == 1 );
      IIRScram_Declaration *decl = prefix_decls->getElement();
      ASSERT( decl->get_kind() == IIR_LIBRARY_DECLARATION );
      IIRScram_LibraryDeclaration *lib_decl = dynamic_cast<IIRScram_LibraryDeclaration *>(decl);
      
      lib_decl->get_primary_units()->append( new_unit );
      
    }
    else{
      ostringstream err;
      err << "Can't find library |" << *_get_prefix() << "| - perhaps you're"
	  << " missing a library clause?";
      report_error( this, err.str() );
    }
  }
  else{
    ASSERT( get_prefix()->get_kind() == IIR_SELECTED_NAME );
    (dynamic_cast<IIRScram_Name *>(_get_prefix()))->_build_lib( new_unit );
  }
}

void 
IIRScram_SelectedName::_make_interface_visible( symbol_table *sym_tab ){
  ASSERT( is_resolved() == TRUE );

  if( get_suffix()->get_kind() == IIR_DESIGNATOR_BY_ALL ){
    _get_prefix()->_make_interface_visible( sym_tab );
  }
  else{
    // This should actually be "_make_visible", not
    // "_make_interface_visible".  However the there is 
    // no "make_visible" defined yet, and they are essentially
    // equivalent for the moment.
    _get_suffix()->_make_interface_visible( sym_tab );
  }
}

void 
IIRScram_SelectedName::_come_into_scope( symbol_table *sym_tab ){
  ASSERT( _get_suffix()->is_resolved() == TRUE );
  _get_suffix()->_come_into_scope( sym_tab );
}

void 
IIRScram_SelectedName::_come_out_of_scope( symbol_table *sym_tab ){
  _get_suffix()->_come_out_of_scope( sym_tab );
}


IIRScram_GenericList *
IIRScram_SelectedName::_get_generic_list(){
  ASSERT( is_resolved() == TRUE );
  ASSERT( _get_suffix() != NULL );
  return _get_suffix()->_get_generic_list();
}


IIRScram *
IIRScram_SelectedName::_clone(){
  IIRScram_SelectedName *retval = new IIRScram_SelectedName();
  IIRScram_Name::_clone( retval );

  IIRScram *suffix = _get_suffix()->_clone();
  retval->set_suffix( suffix );
  
  return retval;
}

IIR_Boolean 
IIRScram_SelectedName::is_locally_static(){
  IIR_Boolean retval = TRUE;
  
  if( _get_prefix()->is_locally_static() == FALSE || 
      _get_suffix()->is_locally_static() == FALSE ){
    retval = FALSE;
  }
  
  return retval;
}

IIRScram_TypeDefinition *
IIRScram_SelectedName::_get_rval_pointed_at(){
  ASSERT( is_resolved() == TRUE );
  return _get_suffix()->_get_rval_pointed_at();
}

visitor_return_type *
IIRScram_SelectedName::_accept_visitor( node_visitor *visitor,
					visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_SelectedName(this, arg);
}

IIRScram_PortList *
IIRScram_SelectedName::_get_port_list(){
  ASSERT( is_resolved() == TRUE );
  ASSERT( _get_suffix() != NULL );
  return _get_suffix()->_get_port_list();
}
