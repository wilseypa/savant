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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_AttributeDeclaration.hh"
#include "IIRScram_AttributeSpecification.hh"
#include "IIRScram_DesignatorExplicit.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_TypeDefinition.hh"
#include "error_func.hh"
#include "set.hh"
#include "symbol_table.hh"
#include "resolution_func.hh"
#include <sstream>
using std::ostringstream;


IIRScram_AttributeSpecification::IIRScram_AttributeSpecification(){
  set_entity_name_list(new IIRScram_DesignatorList());
}

IIRScram_AttributeSpecification::~IIRScram_AttributeSpecification(){}

IIRScram_Declaration *
IIRScram_AttributeSpecification::_get_declaration(){
  return dynamic_cast<IIRScram_Declaration *>(get_declaration());
}

void 
IIRScram_AttributeSpecification::_type_check( IIRScram_DeclarationList * ){
  ASSERT( get_declarator() != NULL );

  // First, figure out what attribute we're talking about.

  savant::set<IIRScram_Declaration> *attribute_decls = _get_declarator()->_symbol_lookup();
  if( attribute_decls == NULL ){
    report_undefined_symbol( _get_declarator() );
    return;
  }

  IIRScram_Declaration *attr_declaration = NULL;
  IIRScram_Designator *current = NULL;

  // Pull out the non-attribute symbols...
  constraint_functor *functor = new  is_attribute_declaration_functor;
  attribute_decls->reduce_set( functor );        
  delete functor;

  switch( attribute_decls->size() ){
  case 0:{
    ostringstream err;
    err << "|" << *_get_declarator() << "| was not defined as an attribute.";
    report_error( this, err.str() );
    goto finish;
  }

  case 1:{
    ASSERT( IIRBase_TextLiteral::cmp( attribute_decls->getElement()->_get_declarator(), 
                                      _get_declarator() ) == 0  );
    attr_declaration = attribute_decls->getElement();
    
    set_value( _get_value()->_semantic_transform( attr_declaration->_get_subtype() ));
    _get_value()->_type_check( attr_declaration->_get_subtype() );
    set_value( _get_value()->_rval_to_decl( attr_declaration->_get_subtype() ));
    
    set_declaration( attr_declaration );
    break;
  }

  default:{
    report_ambiguous_error( _get_declarator(), attribute_decls->convert_set<IIR_Declaration>() );
    goto finish;
  }
  }

  delete attribute_decls;

  // Now, resolve the designator list.
  current = dynamic_cast<IIRScram_Designator *>(get_entity_name_list()->first());
  while( current != NULL ){
    if( current->get_kind() == IIR_DESIGNATOR_EXPLICIT ){
      IIRScram_DesignatorExplicit *as_explicit = dynamic_cast<IIRScram_DesignatorExplicit *>(current);
      IIRScram_Declaration *decl_to_attach_to = NULL;
      IIRScram *current_name= as_explicit->_get_name();
      
      savant::set<IIRScram_Declaration> *decl_set = current_name->_symbol_lookup();
      if( decl_set == NULL ){
	report_undefined_symbol( current_name );
      }
      else{
	decl_to_attach_to = decl_set->getElement();
	while( decl_to_attach_to != NULL ){  
          constraint_functor *functor = _get_entity_constraint();
	  if( (*functor)(decl_to_attach_to) == TRUE ){
	    // We also need to resolve the attribute itself, and see if it 
	    // is defined for the object that it's being attached to.
	    if( decl_to_attach_to->_attach_attribute_specification( (IIRScram_AttributeSpecification *)this ) == TRUE ){
	      as_explicit->set_name( decl_to_attach_to );
	    }
	    else{
	      ostringstream err;
	      err << "Object |" << *current_name << 
		"| may not have get_attributes() associated with it.";
	      report_error( current_name, err.str() );
	      goto finish;
	    }
	  }  
	  decl_to_attach_to = decl_set->getNextElement();
	}
      }
    }
    else{
      ostringstream err;
      err << "Only explicit designators (not by others or all)"
	  << " are supported yet!";
      report_error( current, err.str() );
      goto finish;
    }
    current = dynamic_cast<IIRScram_Designator *>(get_entity_name_list()->successor( current ));
  }

 finish:
  ;
}

IIR_Boolean 
IIRScram_AttributeSpecification::_can_be_in_same_region( IIRScram_Declaration *to_check ){
  IIR_Boolean retval = FALSE;
  if( to_check != 0 && to_check->get_kind() == get_kind() ){
    retval = TRUE;
  }

  return retval;
}

visitor_return_type *
IIRScram_AttributeSpecification::_accept_visitor( node_visitor *visitor, 
						  visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_AttributeSpecification(this, arg);
}

IIRScram_DesignatorList *
IIRScram_AttributeSpecification::_get_entity_name_list() {
  return dynamic_cast<IIRScram_DesignatorList *>(get_entity_name_list());
}

IIRScram_Identifier *
IIRScram_AttributeSpecification::_get_entity_class() {
  return dynamic_cast<IIRScram_Identifier *>(get_entity_class());
}

IIRScram *
IIRScram_AttributeSpecification::_get_value() {
  return dynamic_cast<IIRScram *>(IIRBase_AttributeSpecification::get_value());
}
