// Copyright (c) 1996-2004 The University of Cincinnati.
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
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam 
//          Radharamanan Radhakrishnan
//          Swaminathan Subramanian
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_ArchitectureDeclaration.hh"
#include "IIRScram_Attribute.hh"
#include "IIRScram_AttributeDeclaration.hh"
#include "IIRScram_AttributeSpecification.hh"
#include "IIRScram_DeclarationList.hh"
#include "IIRScram_DesignatorExplicit.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_StringLiteral.hh"

#include "error_func.hh"
#include "symbol_table.hh"

#include <sstream>
using std::ostringstream;

IIRScram_Declaration::IIRScram_Declaration(){}

IIRScram_Declaration::~IIRScram_Declaration(){}

IIR_Boolean
IIRScram_Declaration::_is_homograph_of( IIRScram_Declaration *to_check ){
  IIR_Boolean retval = FALSE;

  if( IIRBase_TextLiteral::cmp( _get_declarator(), to_check->_get_declarator() ) == 0 ){
    int olCount = 0;
    if( _is_overloadable() == TRUE ){
      olCount++;
    }
    if( to_check->_is_overloadable() == TRUE ){
      olCount++;
    }

    switch( olCount ){
    case 0:
    case 1:{
      retval = TRUE;
      break;
    }
    case 2:{
      retval = FALSE;
      break;
    }
    default:{
      ostringstream err;
      err << "Internal error in IIRScram_Declaration::_is_homograph_of( IIRScram_Declaration"
	  << " *to_check ) - olCount == " << olCount;
      report_error( this, err.str() );
      abort();
    }
    }
    
  }
 return retval;
}

IIRScram_DesignatorList *
IIRScram_Declaration::_get_instantiation_list() {
  _report_undefined_scram_fn("_get_instantiation_list()");
  return NULL;
}

void
IIRScram_Declaration::_get_headers(savant::set<IIRScram>&) {
  _report_undefined_scram_fn("_get_headers(set<IIRScram>&)");
}

bool 
IIRScram_Declaration::_check_param( IIRScram_TypeDefinition *, int ){
  return false;
}


// For the next two methods, since we're assuming that we've already
// correctly resolved everything, we'll just new a set with "this" in it.
savant::set<IIRScram_Declaration> *
IIRScram_Declaration::_symbol_lookup(){
  return new savant::set<IIRScram_Declaration>( this );
}

savant::set<IIRScram_Declaration> *
IIRScram_Declaration::_symbol_lookup( savant::set<IIRScram_Declaration> * ){
  return new savant::set<IIRScram_Declaration>( this );
}

IIR_Boolean 
IIRScram_Declaration::_is_physical_type(){
  if( _get_subtype() != NULL ){
    return _get_subtype()->_is_physical_type();
  }
  else{
    return FALSE;
  }
}

IIRScram_Attribute *
IIRScram_Declaration::_get_attribute_name(){
  return dynamic_cast<IIRScram_Attribute *>(get_attribute_name());
}

IIRScram_TypeDefinition *
IIRScram_Declaration::_get_type_of_param( int ){
  _report_undefined_scram_fn("_get_type_of_param( int )");
  return NULL;
}

IIRScram_TypeDefinition*
IIRScram_Declaration::_get_name_type() {
  return _get_subtype();
}


IIR_Int32 
IIRScram_Declaration::get_num_indexes(){
  return 0;
}


IIR_Int32 
IIRScram_Declaration::_num_required_args(){
  return 0;
}

IIRScram*
IIRScram_Declaration::_clone() {
  _report_undefined_scram_fn("IIRScram *_clone()");
  return NULL;
}


void
IIRScram_Declaration::_clone(IIRScram *cl) {
  IIRScram_Declaration *clone = dynamic_cast<IIRScram_Declaration*>(cl);
  IIRScram::_clone(clone);
  IIRScram_TextLiteral *declclone = dynamic_cast<IIRScram_TextLiteral *>(_get_declarator()->_clone());
  clone->set_declarator(declclone);

  clone->set_is_visible( is_visible() );
  clone->set_is_implicit( is_implicit_declaration() );
  clone->set_declarative_region( get_declarative_region() );

  IIRScram_Attribute *attrclone = _get_attribute_name();
  if (attrclone != NULL) {
    attrclone = dynamic_cast<IIRScram_Attribute*>(attrclone->_clone());
  }
  clone->set_attribute_name(attrclone);
}

void 
IIRScram_Declaration::_add_to_declarative_region( savant::set<IIRScram_Declaration> * ){
  _report_undefined_scram_fn("_add_to_declarative_region");
}

void 
IIRScram_Declaration::_add_to_declarative_region( IIRScram_DeclarationList *region,
						  savant::set<IIRScram_Declaration> *set_to_add ){
  ASSERT( set_to_add != NULL );
  
  IIRScram_Declaration *current_decl = NULL;
#ifdef DEVELOPER_ASSERTIONS
  IIRScram_Declaration *decl_in_region = dynamic_cast<IIRScram_Declaration *>(region->first());
  while( decl_in_region != NULL ){
    current_decl = set_to_add->getElement();
    while( current_decl != NULL ){
      ASSERT( current_decl != decl_in_region );
      current_decl = set_to_add->getNextElement();
    }
    decl_in_region = dynamic_cast<IIRScram_Declaration *>(region->successor( decl_in_region ));
  }
#endif

  current_decl = set_to_add->getElement();
  while( current_decl != NULL ){
    region->append( current_decl );
    current_decl = set_to_add->getNextElement();
  }
}


IIR_Boolean
IIRScram_Declaration::_in_process_statement() {
  if(_get_declarative_region()->get_kind() == IIR_PROCESS_STATEMENT) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

// This method is common for SignalDeclaration and
// SignalInterfaceDeclaration and hence defined here.

void
IIRScram_Declaration::_add_declarations_in_initializations() {
  _report_undefined_scram_fn("_add_declarations_in_initializations()");
}


void
IIRScram_Declaration::_add_declaration_and_open_scope( ){
  _get_symbol_table()->add_declaration( (IIRScram_Declaration *)this);
  _get_symbol_table()->open_scope( this );
}


void
IIRScram_Declaration::_add_declaration( ){
  _get_symbol_table()->add_declaration( this );
}


void
IIRScram_Declaration::_close_scope( ){
  _get_symbol_table()->close_scope( this );
}


void 
IIRScram_Declaration::_make_interface_visible(symbol_table *sym_tab ){
  if( sym_tab == NULL ){
    _get_symbol_table()->make_visible( (IIRScram_Declaration *)this );
  }
  else{
    sym_tab->make_visible( (IIRScram_Declaration *)this );
  }
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_Declaration::_get_rval_set( constraint_functor *functor ){
  if (functor != 0 ) {
    ASSERT((*functor)(this) == TRUE );
  }
  ASSERT( _get_subtype() != 0 );
  return new savant::set<IIRScram_TypeDefinition>( _get_subtype() );
}


IIRScram *
IIRScram_Declaration::_decl_to_decl( IIRScram_Declaration *new_decl ){
  ASSERT( new_decl == (IIRScram_Declaration *)this );
  return this;
}

// Helper functions
IIRScram *
IIRScram_Declaration::_get_value() {
  return dynamic_cast<IIRScram *>(get_value());
}

IIRScram *
IIRScram_Declaration::_get_declarative_region() {
  return dynamic_cast<IIRScram *>(get_declarative_region());
}
