#ifndef SCRAM_STANDARD_PACKAGE_HH
#define SCRAM_STANDARD_PACKAGE_HH

// Copyright (c) 1996-2004 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
// DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer
//          Krishnan Subramani
//          Malolan Chetlur     mal@ece.uc.edu
//          Narayanan Thondugulam
//          Radharamanan Radhakrishnan
//          Swaminathan Subramanian
//	    Magnus Danielson	cfmd@swipnet.se

#include "savant_config.hh"
#include "BaseStandardPackage.hh"
#include "IIRScram_PackageDeclaration.hh"

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
class IIRScram_EnumerationSubtypeDefinition;
class IIRScram_EnumerationLiteralList;
class IIRScram_EnumerationLiteral;
class IIRScram_IntegerSubtypeDefinition;
class IIRScram_FloatingSubtypeDefinition;
class IIRScram_PhysicalSubtypeDefinition;
class IIRScram_ArraySubtypeDefinition;
class IIRScram_AttributeDeclaration;
class IIRScram_TypeDeclaration;
class IIRScram_SubtypeDeclaration;
class IIRScram_FunctionDeclaration;
class IIRScram_TypeDefinition;
class IIRScram_ScalarTypeDefinition;
class IIRScram_PhysicalUnit;
class IIRScram_LibraryDeclaration;
class IIRScram_AccessSubtypeDefinition;
class IIRScram_DeclarationList;
class IIRScram_Identifier;
class scram;

class ScramStandardPackage : public virtual IIRScram_PackageDeclaration,
			     public virtual BaseStandardPackage {
public:
  ~ScramStandardPackage();

  // Boolean has to be defined before anything else
  IIR_EnumerationLiteral *get_false_literal();
  IIR_EnumerationLiteral *get_true_literal();
  IIR_EnumerationSubtypeDefinition *get_boolean_type();
  IIR_TypeDeclaration *get_boolean_decl();

  // Here are the builtin universal types.
  IIR_IntegerSubtypeDefinition *get_savant_universal_integer();
  void set_savant_universal_integer( IIR_IntegerSubtypeDefinition * ){ abort(); }
  IIR_FloatingSubtypeDefinition *get_savant_universal_real();
  void set_savant_universal_real( IIR_FloatingSubtypeDefinition * ){ abort(); }

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
  void set_std_decl( IIR_LibraryDeclaration * ){ abort(); }
  StandardPackage *get_std_standard_decl();

  // This is a Savant specific extension
  IIR_AccessSubtypeDefinition *get_savant_null_type_definition();
  void set_savant_null_type_definition( IIR_AccessSubtypeDefinition * ){ abort(); }
  
  static ScramStandardPackage *instance();

  IIR *convert_tree(plugin_class_factory *factory);

private:
  friend class scram_plugin_class_factory;
  ScramStandardPackage();

  void fill_list( IIRScram_DeclarationList * ); 

  IIRScram_IntegerSubtypeDefinition *init_integer_type();
  IIRScram_IntegerSubtypeDefinition *init_positive_type();
  IIRScram_IntegerSubtypeDefinition *init_natural_type();
  IIRScram_FloatingSubtypeDefinition *init_real_type();
  IIRScram_EnumerationLiteral *init_false_literal();
  IIRScram_EnumerationLiteral *init_true_literal();
  IIRScram_TypeDeclaration *init_boolean_decl();
  IIRScram_EnumerationSubtypeDefinition *init_boolean_type();
  IIRScram_TypeDeclaration *init_bit_decl();
  IIRScram_EnumerationSubtypeDefinition *init_bit_type();
  IIRScram_TypeDeclaration *init_character_decl();
  IIRScram_EnumerationSubtypeDefinition *init_character_type();
  IIRScram_TypeDeclaration *init_severity_level_decl();
  IIRScram_EnumerationSubtypeDefinition *init_severity_level_type();
  IIRScram_TypeDeclaration *init_file_open_kind_decl();
  IIRScram_EnumerationSubtypeDefinition *init_file_open_kind_type();
  IIRScram_TypeDeclaration *init_file_open_status_decl();
  IIRScram_EnumerationSubtypeDefinition *init_file_open_status_type();
  IIRScram_TypeDeclaration *init_integer_decl( );
  IIRScram_TypeDeclaration *init_real_decl( );
  IIRScram_TypeDeclaration *init_string_decl( );
  IIRScram_TypeDeclaration *init_bit_vector_decl();
  IIRScram_PhysicalSubtypeDefinition *init_time_type();
  IIRScram_SubtypeDeclaration *init_delay_length_decl();
  IIRScram_PhysicalSubtypeDefinition *init_delay_length_type();
  IIRScram_AttributeDeclaration *init_foreign_decl();
  IIRScram_FunctionDeclaration *init_now_decl();
  IIRScram_LibraryDeclaration *init_std_decl();
  IIRScram_AccessSubtypeDefinition *init_null_type();

  IIRScram_TypeDeclaration *init_type_decl( char *, IIRScram_TypeDefinition * );  
  IIRScram_SubtypeDeclaration *init_subtype_decl( char *, IIRScram_TypeDefinition * );  

  IIRScram_EnumerationSubtypeDefinition *init_enumeration_type( const char * const literals[] );

  IIRScram_EnumerationSubtypeDefinition *init_enumeration_type( IIRScram_EnumerationLiteralList *literals );

  IIRScram_ArraySubtypeDefinition *
  init_unconstrained_array_type(  IIRScram_ScalarTypeDefinition *index_type,
				  IIRScram_TypeDefinition *element_type,
				  IIRScram_TypeDeclaration *type_decl );

  IIRScram_IntegerSubtypeDefinition *
  init_integer_type( int left_bound, int right_bound );

  IIRScram_FloatingSubtypeDefinition *
  init_real_type( double left_bound, double right_bound );
  
  void set_locator_info( IIR * );
  IIRScram_PhysicalUnit *find_unit( char *name,
				    IIRScram_PhysicalSubtypeDefinition *physical_type );

  struct unit {
    char *unit_name;
    int multiplier;
    char *base_unit;
  };

  IIRScram_PhysicalSubtypeDefinition *
  init_physical_type( int,
		      int,
		      char *,
		      struct unit[] );

  StandardPackage *init_std_standard();

  int STD_INT_MAX();
  int STD_INT_MIN();
  double REAL_MAX();
  double REAL_MIN();  
  IIR_Identifier *get_file_name();
  IIR_DesignFile *get_design_file();

  IIRScram_EnumerationLiteralList *build_literal_list( const char *const literals[] );

  scram                         *fake_parser;
};

#endif
