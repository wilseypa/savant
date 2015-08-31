#ifndef STANDARD_PACKAGE_HH
#define STANDARD_PACKAGE_HH

// Copyright (c) 1996-2001 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING
// OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found
// in the file "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer
//          Krishnan Subramani
//          Malolan Chetlur     mal@ece.uc.edu
//          Narayanan Thondugulam
//          Radharamanan Radhakrishnan
//          Swaminathan Subramanian
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_PackageDeclaration.hh"

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

/** Interface for VHDL Standard Package.  In order to support multiple versions
    of standard package, generally one for each plugin, here is an interface
    to allow the system to deal with it in a much more general sense. */
class StandardPackage : virtual public IIR_PackageDeclaration {
public:
  StandardPackage(){}

  virtual ~StandardPackage(){}

  // Boolean has to be defined before anything else
  virtual IIR_EnumerationLiteral *get_false_literal() = 0;
  virtual IIR_EnumerationLiteral *get_true_literal() = 0;
  virtual IIR_EnumerationSubtypeDefinition *get_boolean_type() = 0;
  virtual IIR_TypeDeclaration *get_boolean_decl() = 0;

  // Here are the builtin universal types.
  virtual IIR_IntegerSubtypeDefinition *get_savant_universal_integer() = 0;
  virtual void set_savant_universal_integer( IIR_IntegerSubtypeDefinition * ) = 0;
  virtual IIR_FloatingSubtypeDefinition *get_savant_universal_real() = 0;
  virtual void set_savant_universal_real( IIR_FloatingSubtypeDefinition * ) = 0;

  // These types represent those declared in std.standard.
  virtual IIR_EnumerationSubtypeDefinition *get_bit_type() = 0;
  virtual IIR_TypeDeclaration *get_bit_decl() = 0;

  virtual IIR_IntegerSubtypeDefinition *get_integer_type() = 0;
  virtual IIR_TypeDeclaration *get_integer_decl() = 0;

  virtual IIR_EnumerationSubtypeDefinition *get_character_type() = 0;
  virtual IIR_TypeDeclaration *get_character_decl() = 0;

  virtual IIR_IntegerSubtypeDefinition *get_positive_type() = 0;
  virtual IIR_SubtypeDeclaration *get_positive_decl() = 0;

  virtual IIR_ArraySubtypeDefinition *get_string_type() = 0;
  virtual IIR_TypeDeclaration *get_string_decl() = 0;

  virtual IIR_EnumerationSubtypeDefinition *get_severity_level_type() = 0;
  virtual IIR_TypeDeclaration *get_severity_level_decl() = 0;

  virtual IIR_FloatingSubtypeDefinition *get_real_type() = 0;
  virtual IIR_TypeDeclaration *get_real_decl() = 0;

  virtual IIR_PhysicalSubtypeDefinition *get_time_type() = 0;
  virtual IIR_TypeDeclaration *get_time_decl() = 0;

  virtual IIR_PhysicalSubtypeDefinition *get_delay_length_type() = 0;
  virtual IIR_SubtypeDeclaration *get_delay_length_decl() = 0;

  virtual IIR_IntegerSubtypeDefinition *get_natural_type() = 0;
  virtual IIR_SubtypeDeclaration *get_natural_decl() = 0;

  virtual IIR_ArraySubtypeDefinition *get_bit_vector_type() = 0;
  virtual IIR_TypeDeclaration *get_bit_vector_decl() = 0;

  virtual IIR_EnumerationSubtypeDefinition *get_file_open_kind_type() = 0;
  virtual IIR_TypeDeclaration *get_file_open_kind_decl() = 0;

  virtual IIR_EnumerationSubtypeDefinition *get_file_open_status_type() = 0;
  virtual IIR_TypeDeclaration *get_file_open_status_decl() = 0;

  virtual IIR_AttributeDeclaration *get_foreign_decl() = 0;
  virtual IIR_FunctionDeclaration *get_now_decl() = 0;

  virtual IIR_LibraryDeclaration *get_std_decl() = 0;
  virtual void set_std_decl( IIR_LibraryDeclaration * ) = 0;

  virtual StandardPackage *get_std_standard_decl() = 0;

  // This is a Savant specific plugin
  virtual IIR_AccessSubtypeDefinition *get_savant_null_type_definition() = 0;
  virtual void set_savant_null_type_definition( IIR_AccessSubtypeDefinition * ) = 0;

protected:
};

#endif
