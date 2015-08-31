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
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_DesignFile.hh"
#include "IIRScram_ValueAttribute.hh"
#include "IIRScram_ScalarTypeDefinition.hh"
#include "IIRScram_ArraySubtypeDefinition.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_Declaration.hh"
#include "StandardPackage.hh"
#include "set.hh"
#include "error_func.hh"

#include <sstream>
using std::ostringstream;

IIRScram_TypeDefinition *
IIRScram_ValueAttribute::_get_subtype(){
  return _get_prefix_subtype();
}

void 
IIRScram_ValueAttribute::_resolve_suffix_special(){
  // Suffix must be an expression of type string
  StandardPackage       *package = _get_design_file()->get_standard_package();

  if( _get_suffix() != NULL && _get_suffix()->is_resolved() == FALSE ){

    ASSERT( _get_prefix()->is_resolved() == TRUE );

    savant::set<IIRScram_TypeDefinition> *suffix_types = _get_suffix()->_get_rval_set();
    IIRScram_TypeDefinition *string_rval = 
      dynamic_cast<IIRScram_ArraySubtypeDefinition *>(package->get_string_type());

    IIRScram_TypeDefinition *current_type = suffix_types->getElement();
    while( current_type != NULL ){
      if( current_type == string_rval ){
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
      err << "|" << *_get_suffix() << "| is not a valid suffix for |" << this << "|.";
      err << " The suffix must be a locally static expression of type string.";
    
      report_error( this, err.str() );
    }
  }  
}

visitor_return_type *IIRScram_ValueAttribute::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ValueAttribute(this, arg);
};
