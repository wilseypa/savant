
// Copyright (c) 1996-1999 The University of Cincinnati.  
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

//---------------------------------------------------------------------------

#include "savant.hh"
#include "error_func.hh"
#include "StandardPackage.hh"
#include "IIR_DesignFile.hh"
#include "IIR_FloatingSubtypeDefinition.hh"
#include "IIR_FunctionDeclaration.hh"
#include "IIR_IntegerSubtypeDefinition.hh"
#include "IIR_SubtypeDeclaration.hh"
#include "IIR_TextLiteral.hh"
#include "IIRBase_ScalarTypeDefinition.hh"
#include <sstream>

IIRBase_ScalarTypeDefinition::IIRBase_ScalarTypeDefinition() :
  left(0), direction(0), right(0){}

IIRBase_ScalarTypeDefinition::~IIRBase_ScalarTypeDefinition(){
  // In some cases resolution will have pointed left, direction, and right
  // to elements of other lists.  We're not going to delete them for now.
}

void
IIRBase_ScalarTypeDefinition::set_left( IIR* left) {
  this->left = left;
}

IIR*
IIRBase_ScalarTypeDefinition::get_left() {
  return left;
}

void
IIRBase_ScalarTypeDefinition::set_direction( IIR* direction) {
  this->direction = direction;
}

IIR*
IIRBase_ScalarTypeDefinition::get_direction() {
  return direction;
}

void
IIRBase_ScalarTypeDefinition::set_right(IIR* right) {
  this->right = right;
}

IIR*
IIRBase_ScalarTypeDefinition::get_right() {
  return right;
}

IIR *
IIRBase_ScalarTypeDefinition::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_ScalarTypeDefinition *new_node = dynamic_cast<IIRBase_ScalarTypeDefinition *>(IIRBase_TypeDefinition::convert_tree(factory));

  // Process the variables
  new_node->left = convert_node(left, factory);
  new_node->direction = convert_node(direction, factory);
  new_node->right = convert_node(right, factory);

  return new_node;
}

IIR_Boolean
IIRBase_ScalarTypeDefinition::is_ascending_range() {
  if( get_direction() == NULL ){
    ostringstream err;
    err << "Get direction called on type that has no direction.";
    report_error( this, err.str(), WARNING );

    return FALSE;
  }
  else{
    return get_direction()->is_ascending_range();
  }
}

IIR_Boolean 
IIRBase_ScalarTypeDefinition::is_resolved(){
  IIR_Boolean retval = TRUE;

  StandardPackage *package = get_design_file()->get_standard_package();
  if( this != dynamic_cast<IIR_ScalarTypeDefinition *>(package->get_savant_universal_integer()) &&
      this != dynamic_cast<IIR_ScalarTypeDefinition *>(package->get_savant_universal_real()) ){
    if( get_left() == NULL || get_right() == NULL || get_direction() == NULL ){
      ASSERT( get_left() == NULL);
      ASSERT( get_right() == NULL);
      ASSERT( get_direction() == NULL);
    }
    else{
      ASSERT( get_left() != NULL);
      ASSERT( get_right() != NULL);
      ASSERT( get_direction() != NULL);
      
      if( get_left()->is_resolved() == FALSE ||
	  get_right()->is_resolved() == FALSE || 
	  get_direction()->is_resolved() == FALSE ){
	retval = FALSE;
      }
    }
  }
  
  return retval;
}

IIR *
IIRBase_ScalarTypeDefinition::get_base_type_left() {
  IIR *retval = 0;

  if( get_left() != NULL ){
    retval = get_left();
  } 
  else if( get_resolved_base_type() != NULL ){
    retval = get_resolved_base_type()->get_base_type_left();
  }
  return retval;
}

IIR *
IIRBase_ScalarTypeDefinition::get_base_type_right() {
  IIR *retval = 0;

  if( get_right() != NULL ){
    retval = get_right();
  } 
  else if( get_resolved_base_type() != NULL ){
    retval = get_resolved_base_type()->get_base_type_right();
  }
  return retval;
}

IIR *
IIRBase_ScalarTypeDefinition::get_base_type_direction() {
  IIR *retval = 0;

  if( get_direction() != NULL ){
    retval = get_direction();
  } 
  else if( get_resolved_base_type() != NULL ){
    retval = get_resolved_base_type()->get_base_type_direction();
  }
  return retval;
}

IIR_TypeDefinition *
IIRBase_ScalarTypeDefinition::get_resolved_base_type() {
  IIR_TypeDefinition *retval = get_base_type();

  if( dynamic_cast<IIR_SubtypeDeclaration *>(this) != NULL || 
      ( is_anonymous() == TRUE && get_type_mark() != NULL )){
    retval = get_type_mark();
  }
  return retval;
}

IIR_Boolean 
IIRBase_ScalarTypeDefinition::is_locally_static(){
  IIR_Boolean retval = false;

  if( get_left() ){
    ASSERT( get_right() );
    retval = ( get_left()->is_locally_static() && get_right()->is_locally_static() );
  }
  else{
    ASSERT( get_base_type_left() != 0 );
    ASSERT( get_base_type_right() != 0 );
    retval = ( get_base_type_left()->is_locally_static() &&
	       get_base_type_right()->is_locally_static() );
  }
  return retval;
}

ostream &
IIRBase_ScalarTypeDefinition::print( ostream &os ){
  if( get_left() == NULL && get_right() == NULL && get_direction() == NULL ){
    // This is an unconstrained type.
    if( get_base_type() != NULL ){
      os << *(get_base_type()->get_declarator()) << " range <> ";
    }
    else{
      os << *get_declarator() << " range <> ";
    }
  }
  else{
    if( get_left() != NULL ){
      os << *get_base_type_left();
    }
    if( is_ascending_range() == TRUE ){
      os << " to ";
    }
    else{
      os << " downto ";
    }
    if( get_right() != NULL ){
      os << *get_base_type_right();
    }
  }
  return os;
}

void 
IIRBase_ScalarTypeDefinition::publish_vhdl_decl(ostream &vhdl_out){
  ASSERT(get_base_type_left() != NULL && get_base_type_left()->is_resolved());
  ASSERT(get_direction() != NULL && get_direction()->is_resolved());
  ASSERT(get_base_type_right() != NULL && get_base_type_right()->is_resolved());

  if( get_resolution_function() != NULL ){
    get_resolution_function()->get_declarator()->publish_vhdl(vhdl_out);
    vhdl_out << " ";
  }

  if (get_type_mark() != NULL) {
    get_type_mark()->get_declaration()->get_declarator()->publish_vhdl(vhdl_out);
    
    if (get_type_mark()->is_scalar_type_definition() == TRUE) {
      IIRBase_ScalarTypeDefinition *as_scalar = dynamic_cast<IIRBase_ScalarTypeDefinition *>(get_type_mark());
      if( get_base_type_left() == as_scalar->get_base_type_left() &&
	  get_base_type_right() == as_scalar->get_base_type_right() &&
	  get_direction() == as_scalar->get_direction() ){
	// If none of the fields is different  don't bother with ranges
	// just quit;
	return;
      }
    }
  }
  vhdl_out << " range ";
  get_base_type_left()->publish_vhdl(vhdl_out);
  vhdl_out << " ";
  if( is_ascending_range() == TRUE ){
    vhdl_out << " to ";
  }
  else {
    vhdl_out << " downto ";
  }
  vhdl_out << " ";
  get_base_type_right()->publish_vhdl(vhdl_out);
}

void 
IIRBase_ScalarTypeDefinition::publish_vhdl(ostream &vhdl_out){
  if( is_anonymous() == TRUE ){
    if( get_type_mark() != NULL ){
      ASSERT( get_type_mark()->is_scalar_type_definition() == TRUE );
      IIRBase_ScalarTypeDefinition *as_scalar = dynamic_cast<IIRBase_ScalarTypeDefinition *>(get_type_mark());
      get_type_mark()->publish_vhdl( vhdl_out );
      if( get_base_type_left() != as_scalar->get_base_type_left() ||
	  get_base_type_right() != as_scalar->get_base_type_right() ||
	  get_direction() != as_scalar->get_direction() ){
	// If one of the fields is different, print the range.  otherwise,
	// don't bother.
	vhdl_out << " range ";
	publish_vhdl_range( vhdl_out );
      }
    }
    else{
      publish_vhdl_range( vhdl_out );
    }
  } 
  else {
    ASSERT(get_declaration()->is_resolved() == TRUE);
    get_declaration()->publish_vhdl(vhdl_out);
  }
}

void
IIRBase_ScalarTypeDefinition::publish_vhdl_index(ostream &vhdl_out) {
  if ( !is_anonymous() ){
    get_declaration()->get_declarator()->publish_vhdl(vhdl_out);
  }
  else {
    if( get_type_mark() != NULL ){
      get_type_mark()->publish_vhdl(vhdl_out);
      vhdl_out << " range "; 
    }
    publish_vhdl_range(vhdl_out);
  }
}

void 
IIRBase_ScalarTypeDefinition::publish_vhdl_range(ostream &vhdl_out) {

  if( get_left() == NULL ){
    ASSERT( get_right() == NULL );
    ASSERT( get_direction() == NULL );
    vhdl_out << "<>";
  } 
  else {
    ASSERT(get_base_type_right() != NULL);
    ASSERT(get_direction() != NULL);
    get_base_type_left()->publish_vhdl(vhdl_out);
    vhdl_out << " ";
    if( is_ascending_range() == TRUE ){
      vhdl_out << "to";
    } else {
      vhdl_out << "downto";
    }
    vhdl_out << " ";
    get_base_type_right()->publish_vhdl(vhdl_out);
  }
}

void 
IIRBase_ScalarTypeDefinition::publish_vhdl_constraint(ostream &) {
  _report_undefined_fn("publish_vhdl_constraint(ostream &)");
}
