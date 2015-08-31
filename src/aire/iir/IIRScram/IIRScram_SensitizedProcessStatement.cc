
// Copyright (c) 1996-2001 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING
// OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found
// in the file "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur    
//          Timothy J. McBrayer
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam
//---------------------------------------------------------------------------

#include "IIRScram_Attribute.hh"
#include "IIRScram_DeclarationList.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_DesignatorExplicit.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_ElementDeclarationList.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_Name.hh"
#include "IIRScram_ProcessStatement.hh"
#include "IIRScram_SensitizedProcessStatement.hh"
#include "IIRScram_SequentialStatementList.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_WaitStatement.hh"

#include "error_func.hh"
#include "set.hh"

#include <sstream>
using std::ostringstream;

IIRScram_SensitizedProcessStatement::IIRScram_SensitizedProcessStatement() {
  set_sensitivity_list(new IIRScram_DesignatorList());
}

IIRScram_SensitizedProcessStatement::~IIRScram_SensitizedProcessStatement() {
  //Release the list memory
  delete get_sensitivity_list();
}

void 
IIRScram_SensitizedProcessStatement::_type_check(){
  IIRScram *signal_decl;

  IIRScram_Designator *current_designator = dynamic_cast<IIRScram_Designator *>(get_sensitivity_list()->first());
  while( current_designator != NULL ){
    ASSERT( current_designator->get_kind() == IIR_DESIGNATOR_EXPLICIT );

    IIRScram *current_signal_name =
      (dynamic_cast<IIRScram_DesignatorExplicit *>(current_designator))->_get_name();

    // If a signal in the sensitivity list can't be resolved, it will
    // complain about it in this function call...
    signal_decl = _resolve_signal_name( current_signal_name );
    if( signal_decl != NULL ){
      // This might leak a name...
      (dynamic_cast<IIRScram_DesignatorExplicit *>(current_designator))->set_name( signal_decl );
    }
    current_designator = dynamic_cast<IIRScram_Designator *>(get_sensitivity_list()->successor( current_designator ));
  }
}

IIRScram *
IIRScram_SensitizedProcessStatement::_resolve_signal_name( IIRScram *signal_name ){
  IIRScram *retval = NULL;
  
  if( signal_name->is_resolved() == TRUE ){
    return signal_name;
  }

  IIRScram *orig_name = signal_name;

  while( signal_name->get_kind() == IIR_INDEXED_NAME ){
    signal_name = (dynamic_cast<IIRScram_Name *>(signal_name))->_get_prefix();
  }

  savant::set<IIRScram_Declaration> *signal_decls = signal_name->_symbol_lookup();

  if( signal_decls == NULL ){
    report_undefined_symbol( signal_name );
    return NULL;
  }

  switch( signal_decls->size() ){
  case 0:{
    ostringstream err;
    err << "Symbol |" << *signal_name 
	<< "| is not valid as an element of a process sensitivity list";
    report_error( this, err.str() );
    break;
  }
  case 1:{
    IIRScram_Declaration *sig_decl = signal_decls->getElement();
    // Everything but signals have been eliminated, meaning, this must be an array
    // access.
    IIRScram *signal_name_transformed = NULL;
    if( orig_name->get_kind() == IIR_INDEXED_NAME ){
      savant::set<IIRScram_TypeDefinition> *orig_types = orig_name->_get_rval_set();

      if( orig_types == NULL ){
	report_undefined_symbol( orig_name );
      }

      switch( orig_types->size() ){
      case 1:{
	IIRScram_TypeDefinition *right_type = orig_types->getElement();
	signal_name_transformed = orig_name->_semantic_transform( right_type );
	signal_name_transformed->_type_check( right_type );
	
	retval = signal_name_transformed->_rval_to_decl( right_type );

	break;
      }
      default:{
	report_ambiguous_error( orig_name, orig_types->convert_set<IIR_TypeDefinition>() );
      }
      }
    }
    else{
      signal_name_transformed = signal_name->_semantic_transform( sig_decl->_get_subtype() );
      signal_name_transformed->_type_check( sig_decl->_get_subtype() );      
      retval = signal_name_transformed->_decl_to_decl( sig_decl );
    }

    if( retval != NULL ){
      ASSERT( retval->is_resolved() == TRUE );
    }

    break;
  }
  default:
    report_ambiguous_error( signal_name, signal_decls->convert_set<IIR_Declaration>() );
    break;    
  }

  delete signal_decls;
  if( retval->_is_iir_declaration() == TRUE ){
    IIRScram_Attribute *my_attribute =  (dynamic_cast<IIRScram_Declaration *>(retval))->_get_attribute_name();
    if( my_attribute != NULL ){
      retval = dynamic_cast<IIRScram *>(my_attribute);
    }
  }
  
  if( retval && retval->is_signal() == FALSE ){
    ostringstream err;
    err << "Symbol |" << *signal_name 
	<< "| is not a signal and there for is invalid as an element of a process sensitivity list";
    report_error( this, err.str() );
  }

  return retval;
}

visitor_return_type *
IIRScram_SensitizedProcessStatement::_accept_visitor( node_visitor *visitor,
						      visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_SensitizedProcessStatement(this, arg);
}

// IIRBase Function Wrapper(s)
IIRScram_DesignatorList *
IIRScram_SensitizedProcessStatement::_get_sensitivity_list() {
  return dynamic_cast<IIRScram_DesignatorList *>(get_sensitivity_list());
}
