
// Copyright (c) 2002-2003 The University of Cincinnati.
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

// Authors: Prashanth Cherukuri cherukps@ececs.uc.edu

//---------------------------------------------------------------------------
	
#include "IIRScram_BranchQuantityDeclaration.hh"
#include "IIRScram_Declaration.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_FreeQuantityDeclaration.hh"
#include "IIRScram_TypeDeclaration.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_ZTFAttribute.hh"

#include "error_func.hh"
#include "resolution_func.hh"
#include "set.hh"
#include "symbol_table.hh"

#include <sstream>
using std::ostringstream;

IIRScram_TypeDefinition *
IIRScram_ZTFAttribute::_get_subtype() {
  savant::set<IIRScram_Declaration> *prefix_decls = _get_prefix()->_symbol_lookup();
  if( prefix_decls == NULL ) {
    report_undefined_symbol( _get_prefix() );
    return NULL;
  }

  IIRScram_Declaration *current_decl;
  current_decl = prefix_decls->getElement();
  while( current_decl != NULL ) {
    if( current_decl->_is_quantity() == FALSE ) {
      prefix_decls->remove( current_decl );
    }
    current_decl = prefix_decls->getNextElement();
  }

  switch( prefix_decls->size() ) {
  case 0: {
    ostringstream err;
    err << "|" << _get_attribute_name() << "| may only be applied to quantities." << endl;
    return NULL;
  }
  case 1: {
    set_prefix( prefix_decls->getElement() );

    break;
  }
  default: {
    report_ambiguous_error( _get_prefix(), prefix_decls->convert_set<IIR_Declaration>() );
    return NULL;
  }
  }
  return _get_prefix()->_get_subtype();
}

void
IIRScram_ZTFAttribute::_resolve_attribute_parameters() {

  ASSERT( _get_num() != NULL && _get_den() != NULL);
  ASSERT( _get_t() != NULL && _get_initial_delay() != NULL);

  // processing for the numerator part of this attribute's suffix ...
  savant::set<IIRScram_TypeDefinition> *numerator_rvals = _get_num()->_get_rval_set();
      
  if( numerator_rvals == NULL ) {
    report_undefined_symbol( get_num() );
  }
  switch( numerator_rvals->size() ) {
  case 0: {
    ostringstream err;
    err << "|" << _get_num() << "| was not declared in this scope." << endl;
    break;
  }
  case 1: {
    IIRScram_TypeDefinition *my_rval = numerator_rvals->getElement();
    
    set_num( _get_num()->_semantic_transform( my_rval ) );
    _get_num()->_type_check( my_rval );
    set_num( _get_num()->_rval_to_decl( my_rval ) );
    
    break;
  }
  default: {
    report_ambiguous_error( _get_num(), numerator_rvals->convert_set<IIR_TypeDefinition>() );
  }
  }

  // now process for the denominator part of the attribute's suffix
  savant::set<IIRScram_TypeDefinition> *denominator_rvals = _get_den()->_get_rval_set();
      
  if( denominator_rvals == NULL ) {
    report_undefined_symbol( _get_den() );
  }
  switch( denominator_rvals->size() ) {
  case 0: {
    ostringstream err;
    err << "|" << _get_den() << "| was not declared in this scope." << endl;
    break;
  }
  case 1: {
    IIRScram_TypeDefinition *my_rval = denominator_rvals->getElement();
    
    set_den( _get_den()->_semantic_transform( my_rval ) );
    _get_den()->_type_check( my_rval );
    set_den( _get_den()->_rval_to_decl( my_rval ) );
    
    break;
  }
  default: {
    report_ambiguous_error( _get_den(), denominator_rvals->convert_set<IIR_TypeDefinition>() );
  }
  }

  // now process for the time parameter ....
  savant::set<IIRScram_TypeDefinition> *time_rvals = _get_t()->_get_rval_set();
      
  if( time_rvals == NULL ) {
    report_undefined_symbol( _get_t() );
  }
  switch( time_rvals->size() ) {
  case 0: {
    ostringstream err;
    err << "|" << _get_t() << "| was not declared in this scope." << endl;
    break;
  }
  case 1: {
    IIRScram_TypeDefinition *my_rval = time_rvals->getElement();
    
    set_t( _get_t()->_semantic_transform( my_rval ) );
    _get_t()->_type_check( my_rval );
    set_t( _get_t()->_rval_to_decl( my_rval ) );
    
    break;
  }
  default: {
    report_ambiguous_error( _get_t(), time_rvals->convert_set<IIR_TypeDefinition>() );
  }
  }

  // process for the initial delay parameter ....
  savant::set<IIRScram_TypeDefinition> *initial_delay_rvals = _get_initial_delay()->_get_rval_set();
      
  if( initial_delay_rvals == NULL ) {
    report_undefined_symbol( _get_initial_delay() );
  }
  switch( initial_delay_rvals->size() ) {
  case 0: {
    ostringstream err;
    err << "|" << _get_initial_delay() << "| was not declared in this scope." << endl;
    break;
  }
  case 1: {
    IIRScram_TypeDefinition *my_rval = initial_delay_rvals->getElement();
    
    set_initial_delay( _get_initial_delay()->_semantic_transform( my_rval ) );
    _get_initial_delay()->_type_check( my_rval );
    set_initial_delay( _get_initial_delay()->_rval_to_decl( my_rval ) );
    
    break;
  }
  default: {
    report_ambiguous_error( get_initial_delay(), initial_delay_rvals->convert_set<IIR_TypeDefinition>() );
  }
  }
}

IIRScram *
IIRScram_ZTFAttribute::_get_num() {
  return dynamic_cast<IIRScram *>(get_num());
}

IIRScram *
IIRScram_ZTFAttribute::_get_den() {
  return dynamic_cast<IIRScram *>(get_den());
}

IIRScram *
IIRScram_ZTFAttribute::_get_t() {
  return dynamic_cast<IIRScram *>(get_t());
}

IIRScram *
IIRScram_ZTFAttribute::_get_initial_delay() {
  return dynamic_cast<IIRScram *>(get_initial_delay());
}


