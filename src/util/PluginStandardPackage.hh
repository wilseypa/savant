#ifndef PLUGIN_STANDARD_PACKAGE_HH
#define PLUGIN_STANDARD_PACKAGE_HH

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

#include "savant_config.hh"
#include "BaseStandardPackage.hh"
#include "IIRBase_PackageDeclaration.hh"

class IIR_EnumerationSubtypeDefinition;
class IIR_EnumerationLiteralList;
class IIR_EnumerationLiteral;
class IIR_IntegerSubtypeDefinition;
class IIR_FloatingSubtypeDefinition;
class IIR_PhysicalSubtypeDefinition;
class IIR_ArraySubtypeDefinition;
class IIR_AttributeDeclaration;
class IIR_TypeDeclaration;
class IIR_SubtypeDeclaration;
class IIR_FunctionDeclaration;
class IIR_TypeDefinition;
class IIR_ScalarTypeDefinition;
class IIR_PhysicalUnit;
class IIR_LibraryDeclaration;
class IIR_AccessSubtypeDefinition;
class plugin_class_factory;
class scram;

/**  This is the generic implementation of StandardPackage for plugins.  This provides a default
     implementation for any plugin extensions that don't need a custom version of StandardPackage.
     To use this version, plugin writers should either inherit from it using a dummy class, or have
     their class factory generate an instance of it via the get_StandardPackage method. */
class PluginStandardPackage : public virtual BaseStandardPackage,
			      public virtual IIRBase_PackageDeclaration {
public:
  // Ruda M.: Allocate memory for the use in plugin_class_factory.
  PluginStandardPackage() {};

  PluginStandardPackage(plugin_class_factory *);

  ~PluginStandardPackage();

  // Boolean has to be defined before anything else
  IIR_EnumerationLiteral *get_false_literal();
  IIR_EnumerationLiteral *get_true_literal();
  IIR_EnumerationSubtypeDefinition *get_boolean_type();
  IIR_TypeDeclaration *get_boolean_decl();

  // Here are the builtin universal types.
  IIR_IntegerSubtypeDefinition *get_savant_universal_integer();
  void set_savant_universal_integer( IIR_IntegerSubtypeDefinition * );

  IIR_FloatingSubtypeDefinition *get_savant_universal_real();
  void set_savant_universal_real( IIR_FloatingSubtypeDefinition * );

  // These types represent those declared in std.standard.
  IIR_EnumerationSubtypeDefinition *get_bit_type();
  IIR_TypeDeclaration *get_bit_decl();

  IIR_IntegerSubtypeDefinition *get_integer_type();
  IIR_TypeDeclaration *get_integer_decl();

  IIR_EnumerationSubtypeDefinition *get_character_type();
  IIR_TypeDeclaration *get_character_decl();

  IIR_IntegerSubtypeDefinition *get_positive_type();
  IIR_SubtypeDeclaration *get_positive_decl();

  IIR_ArraySubtypeDefinition *get_string_type();
  IIR_TypeDeclaration *get_string_decl();

  IIR_EnumerationSubtypeDefinition *get_severity_level_type();
  IIR_TypeDeclaration *get_severity_level_decl();

  IIR_FloatingSubtypeDefinition *get_real_type();
  IIR_TypeDeclaration *get_real_decl();

  IIR_PhysicalSubtypeDefinition *get_time_type();
  IIR_TypeDeclaration *get_time_decl();

  IIR_PhysicalSubtypeDefinition *get_delay_length_type();
  IIR_SubtypeDeclaration *get_delay_length_decl();

  IIR_IntegerSubtypeDefinition *get_natural_type();
  IIR_SubtypeDeclaration *get_natural_decl();

  IIR_ArraySubtypeDefinition *get_bit_vector_type();
  IIR_TypeDeclaration *get_bit_vector_decl();

  IIR_EnumerationSubtypeDefinition *get_file_open_kind_type();
  IIR_TypeDeclaration *get_file_open_kind_decl();

  IIR_EnumerationSubtypeDefinition *get_file_open_status_type();
  IIR_TypeDeclaration *get_file_open_status_decl();

  IIR_AttributeDeclaration *get_foreign_decl();
  IIR_FunctionDeclaration *get_now_decl();

  IIR_LibraryDeclaration *get_std_decl();
  void set_std_decl( IIR_LibraryDeclaration * );

  StandardPackage *get_std_standard_decl();

  // This is a Savant specific extension
  IIR_AccessSubtypeDefinition *get_savant_null_type_definition();
  void set_savant_null_type_definition( IIR_AccessSubtypeDefinition * );

  // Ruda M.: Return singleton of the StandardPackage. It doesn't make
  // much sense to have a singleton here, since all constructors are
  // public and the PluginStandardPackage is cloned from
  // ScramStandardPackage.
  static PluginStandardPackage *instance();

private:

  /** Find the declaration in the package_declarative_part list via it's name. */
  IIR_Declaration *find_item(const char *id);
  IIR_LibraryDeclaration        *std_decl;
  IIR_IntegerSubtypeDefinition  *universal_integer_type;
  IIR_FloatingSubtypeDefinition *universal_real_type;
  IIR_AccessSubtypeDefinition   *null_type_definition;
};

#endif
