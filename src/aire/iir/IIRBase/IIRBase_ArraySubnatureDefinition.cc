
// Copyright (c) 2002-2003 The University of Cincinnati.
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
// NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S., and
// the terms of this license.

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2, June
// 1991. A copy of this license agreement can be found in the file "LGPL",
// distributed with this archive.

// Author: Sivakumar Gowrisankar             gowriss@ececs.uc.edu

//---------------------------------------------------------------------------

#include "IIRBase_ArraySubnatureDefinition.hh"
#include "IIRBase_ScalarTypeDefinition.hh"
#include "IIR_Declaration.hh"

IIRBase_ArraySubnatureDefinition::IIRBase_ArraySubnatureDefinition(){}

IIRBase_ArraySubnatureDefinition::~IIRBase_ArraySubnatureDefinition(){}

IIR_Boolean
IIRBase_ArraySubnatureDefinition::is_subtype() {
  return TRUE;
}

void
IIRBase_ArraySubnatureDefinition::publish_vhdl( ostream &vhdl_out ){
  if( get_declaration() != NULL ){
    get_declaration()->publish_vhdl(vhdl_out);
  }
  else {
    ASSERT( get_base_type() != NULL );
    get_base_type()->publish_vhdl(vhdl_out);
    if (get_resolved_index_subtype() != NULL) {
      vhdl_out << "(";
      dynamic_cast<IIRBase_ScalarTypeDefinition *>
	(get_resolved_index_subtype())->publish_vhdl_range(vhdl_out);
      vhdl_out << ")";
    }
  }
}

void
IIRBase_ArraySubnatureDefinition::publish_vhdl_type_decl( ostream &vhdl_out ){
  IIRBase_TypeDefinition *node ;
  int index, max_index ;

  ASSERT(get_resolved_index_subtype() != NULL );
  ASSERT(get_element_subtype() != NULL );

  vhdl_out << "array ";
  ASSERT ( get_base_type()->get_resolved_index_subtype() != NULL );

  if(( get_base_type()->is_unconstrained_array_type() == TRUE) ||
      (get_base_type()->get_resolved_index_subtype()->is_enumeration_type() == TRUE) ){

    vhdl_out << " ( ";

    index = 1 ;
    max_index = get_num_indexes();
    for( node = this;
	 index <= max_index;
	 index++, node = dynamic_cast<IIRBase_TypeDefinition *>(node->get_element_subtype()) ){
      ASSERT(node->is_array_type() == TRUE );
      ASSERT(node->get_resolved_index_subtype() != NULL );
      ASSERT(node->get_element_subtype() != NULL );
      if (index > 1) {
        vhdl_out << ", ";
      }

      dynamic_cast<IIRBase_ScalarTypeDefinition *>
	(node->get_resolved_index_subtype())->publish_vhdl_index(vhdl_out);
    }

    vhdl_out << " ) ";

  }
  vhdl_out << " of ";
  get_final_subtype()->publish_vhdl(vhdl_out);
}

void
IIRBase_ArraySubnatureDefinition::publish_vhdl_decl(ostream &vhdl_out) {
  IIRBase_TypeDefinition *node ;
  int index, max_index ;

  ASSERT(get_resolved_index_subtype() != NULL );
  ASSERT(get_element_subtype() != NULL );
  get_base_type()->publish_vhdl(vhdl_out);
  ASSERT ( get_base_type()->get_resolved_index_subtype() != NULL );

  if( get_base_type()->is_unconstrained_array_type() == TRUE &&
      is_unconstrained_array_type() == FALSE ){

    vhdl_out << " ( ";

    index = 1 ;
    max_index = get_num_indexes();
    for (node = this;
	 index <= max_index; index++,
	   node = dynamic_cast<IIRBase_TypeDefinition *>(node->get_element_subtype()) ){
      ASSERT(node->is_array_type() == TRUE );
      ASSERT(node->get_resolved_index_subtype() != NULL );
      ASSERT(node->get_element_subtype() != NULL );
      if (index > 1) {
        vhdl_out << ", ";
      }

      dynamic_cast<IIRBase_ScalarTypeDefinition *>
	(node->get_resolved_index_subtype())->publish_vhdl_index(vhdl_out);
    }

    vhdl_out << " ) ";

    if ( get_base_type()->is_anonymous() == TRUE )  {
      vhdl_out << " of ";
      node->publish_vhdl(vhdl_out);
    }
  }
}

void
IIRBase_ArraySubnatureDefinition::publish_vhdl_subtype_decl(ostream &vhdl_out){
  publish_vhdl_decl(vhdl_out);
}
