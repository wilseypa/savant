
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

//---------------------------------------------------------------------------

#include "IIRBase_EnumerationTypeDefinition.hh"
#include "IIRBase_EnumerationLiteralList.hh"

IIRBase_EnumerationTypeDefinition::IIRBase_EnumerationTypeDefinition() :
  enumeration_literals(0){}

IIRBase_EnumerationTypeDefinition::~IIRBase_EnumerationTypeDefinition() {
  delete enumeration_literals;
  enumeration_literals = 0;
}

// List Accessor(s)
IIR_EnumerationLiteralList *
IIRBase_EnumerationTypeDefinition::get_enumeration_literals() {
  if( is_subtype() ){
    ASSERT(get_base_type() != 0);
    ASSERT(enumeration_literals == 0);
    ASSERT( dynamic_cast<IIR_EnumerationTypeDefinition *>(get_base_type()) != 0 );
    return dynamic_cast<IIR_EnumerationTypeDefinition *>(get_base_type())->get_enumeration_literals();
  }
  else{
    ASSERT(enumeration_literals != NULL);
    return enumeration_literals;
  }
}


void
IIRBase_EnumerationTypeDefinition::set_enumeration_literals(IIR_EnumerationLiteralList *new_enumeration_literals) {
  ASSERT(new_enumeration_literals != NULL);
  delete enumeration_literals;
  enumeration_literals = new_enumeration_literals;
}

IIR *
IIRBase_EnumerationTypeDefinition::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_EnumerationTypeDefinition *new_node =
    dynamic_cast<IIRBase_EnumerationTypeDefinition *>(IIRBase_ScalarTypeDefinition::convert_tree(factory));

  // Process the variables
  if( !is_subtype() ){
    ASSERT( !new_node->is_subtype() );
    ASSERT( new_node->enumeration_literals == 0 );
    ASSERT( enumeration_literals != 0 );
    new_node->enumeration_literals =
      dynamic_cast<IIR_EnumerationLiteralList *>(convert_node(enumeration_literals, factory));
    ASSERT( new_node->enumeration_literals != 0 );
    ASSERT( new_node->enumeration_literals->num_elements() == enumeration_literals->num_elements() );
  }

  return new_node;
}

savant::set<IIR_Declaration> *
IIRBase_EnumerationTypeDefinition::find_declarations( IIR_TextLiteral *to_find ){
  // This is a little ugly, but we need to get the type's enum list, and not the subtype
  return dynamic_cast<IIR_EnumerationLiteralList *>((IIRBase_EnumerationTypeDefinition::get_enumeration_literals()))->find_declarations( to_find );
}

savant::set<IIR_Declaration> *
IIRBase_EnumerationTypeDefinition::find_declarations( IIR_Name *to_find ){
  // This is a little ugly, but we need to get the type's enum list, and not the subtype
  return dynamic_cast<IIR_EnumerationLiteralList *>((IIRBase_EnumerationTypeDefinition::get_enumeration_literals()))->find_declarations( to_find );
}

// LRM defnies an enumeration type as a character type thus (Section 3.1.1):
//   An enumeration type is said to be a character type if at least one of
//   its enumeration literals is a character literal.
IIR_Boolean
IIRBase_EnumerationTypeDefinition::is_character_type() {
  IIR_Boolean retval = FALSE;

  if( get_base_type() != 0 ){
    retval = get_base_type()->is_character_type();
  }
  else{

    IIR_EnumerationLiteral *literal = dynamic_cast<IIR_EnumerationLiteral *>(get_enumeration_literals()->first());
    while(literal != NULL) {
      if(literal->is_character_literal() == TRUE) {
	retval = TRUE;
	break;
      }
      literal = dynamic_cast<IIR_EnumerationLiteral *>(get_enumeration_literals()->successor(literal));
    }
  }

  return retval;
}

ostream&
IIRBase_EnumerationTypeDefinition::print(ostream& os) {
  if( get_enumeration_literals()->num_elements() > 0 ){
    get_enumeration_literals()->print(os);
  }
  else{
    IIRBase_ScalarTypeDefinition::print( os );
  }
  return os;
}

void 
IIRBase_EnumerationTypeDefinition::publish_vhdl_type_decl(ostream &vhdl_out) {
  // This is a little ugly, but we need to get the type's enum list, and not the subtype
  dynamic_cast<IIRBase_EnumerationLiteralList *>((get_enumeration_literals()))->publish_vhdl(vhdl_out);
}
