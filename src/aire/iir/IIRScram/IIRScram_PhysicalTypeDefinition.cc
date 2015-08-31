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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajsek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Magnus Danielson    cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "savant.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EnumerationLiteral.hh"
#include "IIRScram_FloatingSubtypeDefinition.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_IntegerSubtypeDefinition.hh"
#include "IIRScram_PhysicalLiteral.hh"
#include "IIRScram_PhysicalSubtypeDefinition.hh"
#include "IIRScram_PhysicalUnit.hh"
#include "IIRScram_TypeDeclaration.hh"
#include "IIRScram_UnitList.hh"

#include "error_func.hh"
#include "set.hh"
#include "StandardPackage.hh"

#include <sstream>
using std::ostringstream;

IIRScram_PhysicalTypeDefinition::IIRScram_PhysicalTypeDefinition(){}

IIRScram_PhysicalTypeDefinition::~IIRScram_PhysicalTypeDefinition(){}

IIRScram_TypeDefinition *
IIRScram_PhysicalTypeDefinition::_get_new_subtype(){
  IIRScram_TypeDefinition *retval = new IIRScram_PhysicalSubtypeDefinition();
  copy_location( this, retval );
  return retval;
}

IIRScram *
IIRScram_PhysicalTypeDefinition::_clone(){
  IIRScram_PhysicalTypeDefinition *retval = new IIRScram_PhysicalTypeDefinition();
  _clone( retval );
  return retval;
}

void 
IIRScram_PhysicalTypeDefinition::_clone( IIRScram *copy_into ){
  ASSERT( copy_into->_is_iir_physical_type_definition() == TRUE );
  IIRScram_PhysicalTypeDefinition *as_physical_type = 
    dynamic_cast<IIRScram_PhysicalTypeDefinition *>(copy_into);

  as_physical_type->set_primary_unit( get_primary_unit() );
  as_physical_type->set_units(get_units());
  
  IIRScram_ScalarTypeDefinition::_clone( copy_into );
}

IIRScram_TypeDefinition *
IIRScram_PhysicalTypeDefinition::_construct_new_subtype( IIRScram_Name *resolution_function,
							 IIRScram_ScalarTypeDefinition *new_constraint){

  IIRScram_PhysicalSubtypeDefinition *retval = 0;
  IIRScram_TypeDefinition *temp = 
    IIRScram_ScalarTypeDefinition::_construct_new_subtype( resolution_function,
                                                           new_constraint);

  ASSERT( temp->get_kind() == IIR_PHYSICAL_SUBTYPE_DEFINITION );
  retval = dynamic_cast<IIRScram_PhysicalSubtypeDefinition *>(temp);

  if( new_constraint != 0 ){
    retval->set_declaration( new_constraint->get_declaration() );
  }

  return retval;
}


void 
IIRScram_PhysicalTypeDefinition::_build_implicit_operators( savant::set<IIRScram_Declaration> *add_to ){
  IIRScram_ScalarTypeDefinition::_build_implicit_operators( add_to );
  
  StandardPackage *package = _get_design_file()->get_standard_package();
  IIRScram_TypeDefinition *integer_type = dynamic_cast<IIRScram_TypeDefinition *>(package->get_integer_type());
  IIRScram_TypeDefinition *real_type =  dynamic_cast<IIRScram_TypeDefinition *>(package->get_real_type());

  IIRScram_TypeDefinition::_build_implicit_operator( "\"*\"",
						add_to,
						this,
						this,
						integer_type );

  IIRScram_TypeDefinition::_build_implicit_operator( "\"*\"",
						add_to,
						this,
						this,
						real_type );

  IIRScram_TypeDefinition::_build_implicit_operator( "\"*\"",
						add_to,
						this,
						integer_type,
						this );

  IIRScram_TypeDefinition::_build_implicit_operator( "\"*\"",
						add_to,
						this,
					        real_type,
						this );

  IIRScram_TypeDefinition::_build_implicit_operator( "\"/\"",
						add_to,
						this,
						this,
					        integer_type );

  IIRScram_TypeDefinition::_build_implicit_operator( "\"/\"",
						add_to,
						this,
						this,
						real_type );

  IIRScram_IntegerSubtypeDefinition *temp = dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(package->get_savant_universal_integer());
  IIRScram_TypeDefinition::_build_implicit_operator( "\"/\"",
						add_to,
						temp,
						this,
					        this );
}

void 
IIRScram_PhysicalTypeDefinition::_set_resolution_function( IIRScram_FunctionDeclaration * ){
  ostringstream err;
  err << "Internal error - IIRScram_PhysicalTypeDefinition::_set_resolution_function was "
      << "called.  Resolution functions can't be associated with an physical type and this "
      << "should have been caught earlier.";
  report_error( this, err.str() );
}


visitor_return_type *
IIRScram_PhysicalTypeDefinition::_accept_visitor( node_visitor *visitor, 
						  visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_PhysicalTypeDefinition(this, arg);
}

// IIRBase Function Wrapper(s)
IIRScram_UnitList *
IIRScram_PhysicalTypeDefinition::_get_units() {
  return dynamic_cast<IIRScram_UnitList *>(get_units());
}

IIRScram_PhysicalUnit *
IIRScram_PhysicalTypeDefinition::_get_primary_unit() {
  return dynamic_cast<IIRScram_PhysicalUnit *>(get_primary_unit());
}
