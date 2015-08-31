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
//          Timothy J. McBrayer tmcrbaye@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Swaminathan Subramanian ssurama@ececs.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram.hh"
#include "IIRScram_AliasDeclaration.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_TypeDefinition.hh"
#include "error_func.hh"
#include "resolution_func.hh"
#include "symbol_table.hh"
#include <sstream>

IIRScram_AliasDeclaration::~IIRScram_AliasDeclaration() {}

IIRScram_AttributeSpecificationList* 
IIRScram_AliasDeclaration::_get_attribute_specification_list() {
  ASSERT(_get_name() != NULL);
  ASSERT(_is_iir_declaration() == TRUE);
  return (dynamic_cast<IIRScram_Declaration*>(_get_name())->_get_attribute_specification_list());
}


IIR_Boolean 
IIRScram_AliasDeclaration::is_object(){
  ASSERT( _get_name()->is_resolved() == TRUE );
  return _get_name()->is_object();
}

IIR_Boolean 
IIRScram_AliasDeclaration::_is_readable(){
  ASSERT( _get_name()->is_resolved() == TRUE );
  return _get_name()->_is_readable();  
}

IIR_Boolean 
IIRScram_AliasDeclaration::_is_writable(){
  ASSERT( _get_name()->is_resolved() == TRUE );
  return _get_name()->_is_writable();  
}

IIRScram_TypeDefinition *
IIRScram_AliasDeclaration::_get_type_of_element( int index ){
  ASSERT( _get_name()->is_resolved() == TRUE );
  return _get_name()->_get_type_of_element( index );
}


IIR_Int32
IIRScram_AliasDeclaration::get_num_indexes( ){
  ASSERT( _get_name()->is_resolved() == TRUE );
  return _get_name()->_get_subtype()->get_num_indexes( );
}


void 
IIRScram_AliasDeclaration::_type_check(){
  ASSERT( _get_name() != NULL );
  
  savant::set<IIRScram_TypeDefinition> *name_rvals = _get_name()->_get_rval_set();
  if( name_rvals == NULL ){
    report_undefined_symbol( _get_name() );
    return;
  }

  if( _get_subtype() != NULL ){
    savant::set<IIRScram_TypeDefinition> *subtype_rvals = new savant::set<IIRScram_TypeDefinition>( _get_subtype() );

    reconcile_sets( name_rvals, subtype_rvals );
    delete subtype_rvals;

    if( name_rvals->size() == 0 ){
      ostringstream err;
      err << "|" << *_get_name() << "| is not of type |" << *_get_subtype() << "| - illegal alias"
	  << " declaration.";
      report_error( this, err.str() );
      return;
    }

  }

  switch( name_rvals->size() ){
  case 0:{
    ostringstream err;
    err << "Internal error in IIRScram_AliasDeclaration::_type_check - got 0 elements for"
	<< " name |" << *_get_name() << "|.";
    report_error( this, err.str() );
    break;
  }
  case 1:{
    IIRScram_TypeDefinition *my_type = name_rvals->getElement();

    if( _get_subtype() == NULL ){
      set_subtype( my_type );
    }

    set_name( _get_name()->_semantic_transform( _get_subtype() ) );
    _get_name()->_type_check( _get_subtype() );
    set_name( _get_name()->_rval_to_decl( _get_subtype() ) );
    
    break;
  }
  default:{
    report_ambiguous_error( _get_name(), name_rvals->convert_set<IIR_TypeDefinition>() );
    break;
  }
  }
  
}


const IIR_Char*
IIRScram_AliasDeclaration::_get_mangling_prefix() {
  return "";
}	  

IIRScram*
IIRScram_AliasDeclaration::_clone() {
  if (_my_clone == NULL) {
    _my_clone = new IIRScram_AliasDeclaration();
    IIRScram_Declaration::_clone(_my_clone);

    _my_clone->set_name(_get_name());
    _my_clone->set_subtype(_get_subtype());
  }
  return _my_clone;
}

void 
IIRScram_AliasDeclaration::_come_into_scope( symbol_table *sym_tab ){
  ASSERT( _get_name()->is_resolved() == TRUE );
  _get_name()->_come_into_scope( sym_tab );
}

void 
IIRScram_AliasDeclaration::_come_out_of_scope( symbol_table *sym_tab ){
  _get_name()->_come_out_of_scope( sym_tab );
}

visitor_return_type *IIRScram_AliasDeclaration::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_AliasDeclaration(this, arg);
};

IIRScram *
IIRScram_AliasDeclaration::_get_name() {
  return dynamic_cast<IIRScram *>(get_name());
}
