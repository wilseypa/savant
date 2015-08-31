
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

//---------------------------------------------------------------------------

#include "IIRScram_DesignFile.hh"
#include "IIRScram_DisconnectSpecification.hh"
#include "IIRScram_PhysicalSubtypeDefinition.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_Designator.hh"

#include "constraint_functors.hh"
#include "error_func.hh"
#include "resolution_func.hh"
#include "set.hh"
#include "StandardPackage.hh"

#include <sstream>
using std::ostringstream;

IIRScram_DisconnectSpecification::IIRScram_DisconnectSpecification() {
  set_guarded_signal_list(new IIRScram_DesignatorList());
}

IIRScram_DisconnectSpecification::~IIRScram_DisconnectSpecification(){}

void 
IIRScram_DisconnectSpecification::_type_check( IIRScram_DeclarationList * ){
  ASSERT( get_guarded_signal_list()->size() > 0 );
  ASSERT( get_time_expression() != NULL );
  ASSERT( get_type_mark() != NULL );
      
  savant::set<IIRScram_TypeDefinition> type_mark_set( _get_type_mark() );
  savant::set<IIRScram_TypeDefinition> *signal_types = NULL;
  IIRScram_Designator *current_designator = dynamic_cast<IIRScram_Designator *>(get_guarded_signal_list()->first());
  while( current_designator != NULL ){
    if( current_designator->get_kind() == IIR_DESIGNATOR_EXPLICIT ){
      constraint_functor *functor = new is_signal_functor();
      signal_types = current_designator->_get_rval_set( functor );
      delete functor;

      if( signal_types == NULL ){
	report_undefined_symbol( current_designator );
	goto next;
      }

      reconcile_sets( signal_types, &type_mark_set );
      switch( signal_types->size() ){
      case 0:{
	ostringstream err;
	err << "No signal |" << *current_designator << "| of type << " << _get_type_mark()
	    << " defined in this scope.";
	report_error( current_designator, err.str() );
	goto next;
      }
      case 1:{
	IIRScram_TypeDefinition *correct_type = signal_types->getElement();
	IIRScram *new_designator = current_designator->_semantic_transform( correct_type );
	ASSERT( new_designator == current_designator );
	current_designator->_type_check( correct_type );
	new_designator = current_designator->_rval_to_decl( correct_type );
	ASSERT( new_designator == current_designator );

	if( new_designator->is_locally_static() == FALSE ){
	  ostringstream err;
	  err << "Signal |" << *current_designator << "| is not locally static.  Only "
	      << "locally static signals are allowed in disconnection specifications.";
	  report_error( current_designator, err.str() );
	}
	if( new_designator->is_guard_signal() == FALSE ){
	  ostringstream err;
	  err << "Signal |" << *current_designator << "| is not a guarded signal.  Only "
	      << "guard signals are allowed in disconnection specifications.";
	  report_error( current_designator, err.str() );
	}

	break;
      }
      default:{
	report_ambiguous_error( current_designator, signal_types->convert_set<IIR_TypeDefinition>() );
	break;
      }
      }
    }
    else{
      ostringstream err;
      err << "No support for disconnection specifications with OTHERS or ALL yet!";
      report_error( current_designator, err.str() );
      abort();
    } 
    next:
      delete signal_types;
      current_designator = dynamic_cast<IIRScram_Designator *>(get_guarded_signal_list()->successor( current_designator ));
  }

  savant::set<IIRScram_TypeDefinition> *time_expression_types = _get_time_expression()->_get_rval_set();
  savant::set<IIRScram_TypeDefinition> *time_types = new savant::set<IIRScram_TypeDefinition>(dynamic_cast<IIRScram_PhysicalSubtypeDefinition *>(_get_design_file()->get_standard_package()->get_time_type()) );

  if( time_expression_types == NULL ){
    report_undefined_symbol( _get_time_expression() );
    goto finish;
  }
  
  ASSERT( time_types != NULL && time_types->size() == 1 );
  reconcile_sets( time_expression_types, time_types );
  switch( time_expression_types->size() ){
  case 0:{
    ostringstream err;
    err << "Expression |" << *_get_time_expression() << "| must have builtin type TIME";
    report_error( get_time_expression(), err.str() );
    goto finish;
  }
  case 1:{
    IIRScram_TypeDefinition *time_rval = time_expression_types->getElement();

    set_time_expression( _get_time_expression()->_semantic_transform( time_rval ) );
    _get_time_expression()->_type_check( time_rval );
    set_time_expression( _get_time_expression()->_rval_to_decl( time_rval ) );

    break;
  }
  default:{
    report_ambiguous_error( _get_time_expression(), time_expression_types->convert_set<IIR_TypeDefinition>()  );
    goto finish;
  }
  }

 finish:
  delete time_types;
  delete time_expression_types;
}

visitor_return_type *
IIRScram_DisconnectSpecification::_accept_visitor( node_visitor *visitor,
						   visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_DisconnectSpecification(this, arg);
};

// IIRBase Function Wrapper(s)
IIRScram_DesignatorList *
IIRScram_DisconnectSpecification::_get_guarded_signal_list() {
  return dynamic_cast<IIRScram_DesignatorList *>(get_guarded_signal_list());
}

IIRScram_TypeDefinition *
IIRScram_DisconnectSpecification::_get_type_mark() {
  return dynamic_cast<IIRScram_TypeDefinition *>(get_type_mark());
}

IIRScram *
IIRScram_DisconnectSpecification::_get_time_expression() {
  return dynamic_cast<IIRScram *>(get_time_expression());
}
