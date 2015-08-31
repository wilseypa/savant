// Copyright (c) 2003-2004 The University of Cincinnati.  
// All rights reserved.
// 
// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
// 
// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.
// 
// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.
// 
// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
// 	    Dale E. Martin	dmartin@cliftonlabs.com
// 
// --------------------------------------------------------------------------

#include "PluginStandardPackage.hh"

#include "IIR_ArraySubtypeDefinition.hh"
#include "IIR_AttributeDeclaration.hh"
#include "IIR_DeclarationList.hh"
#include "IIR_EnumerationLiteral.hh"
#include "IIR_EnumerationSubtypeDefinition.hh"
#include "IIR_FloatingSubtypeDefinition.hh"
#include "IIR_FunctionDeclaration.hh"
#include "IIR_IntegerSubtypeDefinition.hh"
#include "IIR_LibraryDeclaration.hh"
#include "IIR_PhysicalSubtypeDefinition.hh"
#include "IIR_SubtypeDeclaration.hh"
#include "IIR_TypeDeclaration.hh"
#include "ScramStandardPackage.hh"

#include "IIRBase_Identifier.hh"

PluginStandardPackage::PluginStandardPackage( plugin_class_factory *factory )
  : std_decl(0),
    universal_integer_type(0),
    universal_real_type(0),
    null_type_definition(0){}

PluginStandardPackage::~PluginStandardPackage() {
  //Release the list memory
  delete get_package_declarative_part();
}

// Ruda M.: Return singleton of StandardPackage
PluginStandardPackage *
PluginStandardPackage::instance(){
  static PluginStandardPackage *_instance = new PluginStandardPackage();
  return _instance;
}

// Boolean has to be defined before anything else
IIR_EnumerationSubtypeDefinition *
PluginStandardPackage::get_boolean_type(){
  return dynamic_cast<IIR_EnumerationSubtypeDefinition *>(get_boolean_decl()->get_type());
}

IIR_TypeDeclaration *
PluginStandardPackage::get_boolean_decl(){
  static IIR_TypeDeclaration *bool_decl = dynamic_cast<IIR_TypeDeclaration *>(find_item("boolean"));
  return bool_decl;
}

// Here are the builtin universal types.
IIR_IntegerSubtypeDefinition *
PluginStandardPackage::get_savant_universal_integer(){
  return universal_integer_type;
}

void
PluginStandardPackage::set_savant_universal_integer( IIR_IntegerSubtypeDefinition *new_universal_integer_type ){
  universal_integer_type = new_universal_integer_type;
}

IIR_FloatingSubtypeDefinition *
PluginStandardPackage::get_savant_universal_real(){
  return universal_real_type;
}

void
PluginStandardPackage::set_savant_universal_real( IIR_FloatingSubtypeDefinition *new_universal_real_type ){
  universal_real_type = new_universal_real_type;
}

// These types represent those declared in std.standard.
IIR_EnumerationSubtypeDefinition *
PluginStandardPackage::get_bit_type(){
  return dynamic_cast<IIR_EnumerationSubtypeDefinition *>(get_bit_decl()->get_type());
}

IIR_TypeDeclaration *
PluginStandardPackage::get_bit_decl(){
  static IIR_TypeDeclaration *bit_decl = dynamic_cast<IIR_TypeDeclaration *>(find_item("bit"));
  return bit_decl;
}

IIR_IntegerSubtypeDefinition *
PluginStandardPackage::get_integer_type(){
  return dynamic_cast<IIR_IntegerSubtypeDefinition *>(get_integer_decl()->get_type());
}

IIR_TypeDeclaration *
PluginStandardPackage::get_integer_decl(){
  static IIR_TypeDeclaration *integer_decl = dynamic_cast<IIR_TypeDeclaration *>(find_item("integer"));
  return integer_decl;
}

IIR_EnumerationSubtypeDefinition *
PluginStandardPackage::get_character_type(){
  IIR_EnumerationSubtypeDefinition *result = dynamic_cast<IIR_EnumerationSubtypeDefinition *>(get_character_decl()->get_type());
  return result;
}

IIR_TypeDeclaration *
PluginStandardPackage::get_character_decl(){
  static IIR_TypeDeclaration *character_decl = dynamic_cast<IIR_TypeDeclaration *>(find_item("character"));
  return character_decl;
}

IIR_IntegerSubtypeDefinition *
PluginStandardPackage::get_positive_type(){
  return dynamic_cast<IIR_IntegerSubtypeDefinition *>(get_positive_decl()->get_subtype());
}

IIR_SubtypeDeclaration *
PluginStandardPackage::get_positive_decl(){
  static IIR_SubtypeDeclaration *positive_type = dynamic_cast<IIR_SubtypeDeclaration *>(find_item("positive"));
  return positive_type;
}

IIR_ArraySubtypeDefinition *
PluginStandardPackage::get_string_type(){
  return dynamic_cast<IIR_ArraySubtypeDefinition *>(get_string_decl()->get_type());
}

IIR_TypeDeclaration *
PluginStandardPackage::get_string_decl(){
  static IIR_TypeDeclaration *string_decl = dynamic_cast<IIR_TypeDeclaration *>(find_item("string"));
  return string_decl;
}

IIR_EnumerationSubtypeDefinition *
PluginStandardPackage::get_severity_level_type(){
  return dynamic_cast<IIR_EnumerationSubtypeDefinition *>(get_severity_level_decl()->get_type());
}

IIR_TypeDeclaration *
PluginStandardPackage::get_severity_level_decl(){
  static IIR_TypeDeclaration *severity_level_decl = dynamic_cast<IIR_TypeDeclaration *>(find_item("severity_level"));
  return severity_level_decl;
}

IIR_FloatingSubtypeDefinition *
PluginStandardPackage::get_real_type(){
  return dynamic_cast<IIR_FloatingSubtypeDefinition *>(get_real_decl()->get_type());
}

IIR_TypeDeclaration *
PluginStandardPackage::get_real_decl(){
  static IIR_TypeDeclaration *real_decl = dynamic_cast<IIR_TypeDeclaration *>(find_item("real"));
  return real_decl;
}

IIR_PhysicalSubtypeDefinition *
PluginStandardPackage::get_time_type(){
  return dynamic_cast<IIR_PhysicalSubtypeDefinition *>(get_time_decl()->get_type());
}

IIR_TypeDeclaration *
PluginStandardPackage::get_time_decl(){
  static IIR_TypeDeclaration *time_decl = dynamic_cast<IIR_TypeDeclaration *>(find_item("time"));
  return time_decl;
}

IIR_PhysicalSubtypeDefinition *
PluginStandardPackage::get_delay_length_type(){
  return dynamic_cast<IIR_PhysicalSubtypeDefinition *>(get_delay_length_decl()->get_subtype());
}

IIR_SubtypeDeclaration *
PluginStandardPackage::get_delay_length_decl(){
  static IIR_SubtypeDeclaration *delay_length_decl = dynamic_cast<IIR_SubtypeDeclaration *>(find_item("delay_length"));
  return delay_length_decl;
}

IIR_IntegerSubtypeDefinition *
PluginStandardPackage::get_natural_type(){
  return dynamic_cast<IIR_IntegerSubtypeDefinition *>(get_natural_decl()->get_subtype());
}

IIR_SubtypeDeclaration *
PluginStandardPackage::get_natural_decl(){
  static IIR_SubtypeDeclaration *natural_decl = dynamic_cast<IIR_SubtypeDeclaration *>(find_item("natural"));
  return natural_decl;
}

IIR_ArraySubtypeDefinition *
PluginStandardPackage::get_bit_vector_type(){
  return dynamic_cast<IIR_ArraySubtypeDefinition *>(get_bit_vector_decl()->get_type());
}

IIR_TypeDeclaration *
PluginStandardPackage::get_bit_vector_decl(){
  static IIR_TypeDeclaration *bit_vector_decl = dynamic_cast<IIR_TypeDeclaration *>(find_item("bit_vector"));
  return bit_vector_decl;
}

IIR_EnumerationSubtypeDefinition *
PluginStandardPackage::get_file_open_kind_type(){
  return dynamic_cast<IIR_EnumerationSubtypeDefinition *>(get_file_open_kind_decl()->get_type());
}

IIR_TypeDeclaration *
PluginStandardPackage::get_file_open_kind_decl(){
  static IIR_TypeDeclaration *file_open_kind_decl = dynamic_cast<IIR_TypeDeclaration *>(find_item("file_open_kind"));
  return file_open_kind_decl;
}

IIR_EnumerationSubtypeDefinition *
PluginStandardPackage::get_file_open_status_type(){
  return dynamic_cast<IIR_EnumerationSubtypeDefinition *>(get_file_open_status_decl()->get_type());
}

IIR_TypeDeclaration *
PluginStandardPackage::get_file_open_status_decl(){
  static IIR_TypeDeclaration *file_open_status_decl = dynamic_cast<IIR_TypeDeclaration *>(find_item("file_open_status"));
  return file_open_status_decl;
}

IIR_AttributeDeclaration *
PluginStandardPackage::get_foreign_decl(){
  static IIR_AttributeDeclaration *foreign_decl = dynamic_cast<IIR_AttributeDeclaration *>(find_item("foreign"));
  return foreign_decl;
}

IIR_FunctionDeclaration *
PluginStandardPackage::get_now_decl(){
  static IIR_FunctionDeclaration *now_decl = dynamic_cast<IIR_FunctionDeclaration *>(find_item("now"));
  return now_decl;
}

IIR_LibraryDeclaration *
PluginStandardPackage::get_std_decl(){
  return std_decl;
}

void
PluginStandardPackage::set_std_decl( IIR_LibraryDeclaration *new_std_decl ){
  std_decl = new_std_decl;
}

IIR_AccessSubtypeDefinition *
PluginStandardPackage::get_savant_null_type_definition(){
  return null_type_definition;
}

void
PluginStandardPackage::set_savant_null_type_definition( IIR_AccessSubtypeDefinition *new_null_type ){
  null_type_definition = new_null_type;
}

IIR_EnumerationLiteral *
PluginStandardPackage::get_false_literal(){
  static IIR_EnumerationLiteral *false_literal = dynamic_cast<IIR_EnumerationLiteral *>(find_item("false"));
  return false_literal;
}

IIR_EnumerationLiteral *
PluginStandardPackage::get_true_literal(){
  static IIR_EnumerationLiteral *true_literal = dynamic_cast<IIR_EnumerationLiteral *>(find_item("true"));
  return true_literal;
}

StandardPackage *
PluginStandardPackage::get_std_standard_decl(){
  return this;
}

IIR_Declaration *
PluginStandardPackage::find_item(const char *id) {
  IIR_DeclarationList   *decl_list = get_package_declarative_part();
  IIR_Declaration       *cur_decl = dynamic_cast<IIR_Declaration *>(decl_list->first());

  while (cur_decl != NULL) {
    // Check to see if this is the declaration we're looking for
    if (IIRBase_TextLiteral::cmp(cur_decl->get_declarator(), const_cast<char *>(id)) == 0) {
      return cur_decl;
    }
    cur_decl = dynamic_cast<IIR_Declaration *>(decl_list->successor(cur_decl));
  }          

  // Unable to find what we're looking for, this is an error!
  ASSERT(0);
  return NULL;
}
