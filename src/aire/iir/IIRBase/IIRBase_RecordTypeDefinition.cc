
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


#include "IIRBase_RecordTypeDefinition.hh"
#include "IIR_ElementDeclarationList.hh"
#include "IIR_FunctionDeclaration.hh"
#include "IIR_TextLiteral.hh"

IIRBase_RecordTypeDefinition::IIRBase_RecordTypeDefinition() :
  element_declarations(0),
  my_resolution_function(0){}

IIRBase_RecordTypeDefinition::~IIRBase_RecordTypeDefinition(){
  delete element_declarations;
  element_declarations = 0;
  // my_resolution_function belongs to some declaration list somewhere.
}

IIR_FunctionDeclaration *
IIRBase_RecordTypeDefinition::get_resolution_function(){
  return my_resolution_function;
}

void 
IIRBase_RecordTypeDefinition::set_resolution_function( IIR_FunctionDeclaration *resolution_function ){
  my_resolution_function = resolution_function;
}

// List Accessor(s)
IIR_ElementDeclarationList *
IIRBase_RecordTypeDefinition::get_element_declarations() {
  ASSERT(element_declarations != NULL);
  return element_declarations;
}


void
IIRBase_RecordTypeDefinition::set_element_declarations(IIR_ElementDeclarationList *new_element_declarations) {
  ASSERT(new_element_declarations != NULL);
  delete element_declarations;
  element_declarations = new_element_declarations;
}

IIR *
IIRBase_RecordTypeDefinition::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_RecordTypeDefinition *new_node = dynamic_cast<IIRBase_RecordTypeDefinition *>(IIRBase_TypeDefinition::convert_tree(factory));

  // Process the variables
  new_node->element_declarations = dynamic_cast<IIR_ElementDeclarationList *>(convert_node(element_declarations, factory));

  if (my_resolution_function != NULL)
    new_node->my_resolution_function = dynamic_cast<IIR_FunctionDeclaration *>(convert_node(my_resolution_function, factory));
  else
    new_node->my_resolution_function = NULL;

  return new_node;
}

IIR_Boolean 
IIRBase_RecordTypeDefinition::is_subtype(){
  // This is to make up for no IIR_RecordSubtypeDefinition
  if( get_base_type() == NULL ){
    return false;
  }
  else{
    return true;
  }
}

IIR_TypeDefinition * 
IIRBase_RecordTypeDefinition::get_element_subtype( int index ){
  IIR_TypeDefinition *retval = NULL;

  ASSERT( index <= get_element_declarations()->num_elements() );

  IIR_ElementDeclaration *element_decl = NULL;
  
  element_decl = dynamic_cast<IIR_ElementDeclaration *>(get_element_declarations()->get_nth_element( index ));
  retval = element_decl->get_subtype();

  return retval;
}

IIR_Boolean
IIRBase_RecordTypeDefinition::is_locally_static(){
  IIR_Boolean retval = TRUE;

  IIR_ElementDeclaration *current_decl = dynamic_cast<IIR_ElementDeclaration *>(get_element_declarations()->first());
  while( current_decl != NULL ){
    ASSERT( current_decl->get_subtype() != NULL );
    if( current_decl->get_subtype()->is_locally_static() == FALSE ){
      retval = FALSE;
      break;
    }
    current_decl = dynamic_cast<IIR_ElementDeclaration *>(get_element_declarations()->successor( current_decl ));
  }

  return retval;
}

savant::set<IIR_Declaration> *
IIRBase_RecordTypeDefinition::find_declarations( IIR_Name *to_find ){
  return get_element_declarations()->find_declarations( to_find );
}

IIR_ScalarTypeDefinition*
IIRBase_RecordTypeDefinition::get_resolved_index_subtype(){
  return NULL;
}

ostream &
IIRBase_RecordTypeDefinition::print( ostream &os ){
  os << "record ";

  IIR_ElementDeclaration *current_decl = dynamic_cast<IIR_ElementDeclaration *>(get_element_declarations()->first());

  if( current_decl != NULL ){
    os << current_decl << " : " << *(current_decl->get_subtype()->get_declarator());

    current_decl = dynamic_cast<IIR_ElementDeclaration *>(get_element_declarations()->successor( current_decl ));
    while( current_decl != NULL ){
      os << ", " << current_decl << " : " << *(current_decl->get_subtype()->get_declarator());
      current_decl = dynamic_cast<IIR_ElementDeclaration *>(get_element_declarations()->successor( current_decl ));
    }
  }

  os << " end record";

  return os;
}

void 
IIRBase_RecordTypeDefinition::publish_vhdl_decl(ostream &vhdl_out) {
  vhdl_out << "\nrecord\n ";
  get_element_declarations()->publish_vhdl(vhdl_out);
  vhdl_out << "\nend record";
}

void 
IIRBase_RecordTypeDefinition::publish_vhdl_subtype_decl(ostream &vhdl_out) {
  if(get_resolution_function() != NULL) {
    get_resolution_function()->publish_vhdl(vhdl_out);
    vhdl_out << " ";
  }
  
  // The base type can be NULL if I have:
  // type foo is record
  //               first_element : string;
  //             end record;
  //

  // subtype bar is foo;

  // (if you don't believe the base type is NULL in this case, read page 53,
  // the paragraph at the top of the page.

  if( get_base_type() != NULL ){
    get_base_type()->publish_vhdl(vhdl_out);
  }
  else{
    ASSERT( get_declaration() != NULL );
    get_declaration()->publish_vhdl(vhdl_out);
  }
}
