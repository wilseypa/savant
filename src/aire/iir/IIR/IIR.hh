
#ifndef IIR_HH
#define IIR_HH

// Copyright (c) The University of Cincinnati.  
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

#include "savant_config.hh"
#include <iostream>
#include <string>
#include "IRBasicDataTypes.hh"
#include "savant.hh"

using std::string;

class IIR_Identifier;
class IIR_Declaration;
class IIR_DesignFile;
class IIR_TextLiteral;
class IIR_TypeDefinition;
class plugin_class_factory;

/** This is the base node definition for the intermediate form.  All nodes
    in IIR are descendants of this node.  */

class IIR {
public:

  /** Returns the IIR_Kind of this node.  This is useful
      in determining the type of a node when an IIR * is
      all that's available */
  virtual IIR_Kind get_kind() const = 0;

  /** Returns the kind of this node in text form.  This is here for output
      and debugging purposes. */
  virtual const IIR_Char *get_kind_text() const = 0;

  /**
     Returns the name of the concrete class implementing this interface as
     reported by RTTI.
  */
  virtual string get_implementation_class() const = 0;

  /** Accessor to set the VHDL file name that this node was parsed from. 
      @param file_name The IIR_Identifier representation of the file name.
   */
  virtual void set_file_name(IIR_Identifier *file_name, plugin_class_factory *) = 0;
  
  /** Accessor to set the line number of the VHDL this node corresponds
      to. 
      @param line_number The IIR_Int32 corresponding to the line number.
  */
  virtual void set_line_number(IIR_Int32 line_number) = 0;

  /** Read the file name from the node. */
  virtual IIR_Identifier *get_file_name() = 0;

  /** Read the line number from the node. */
  virtual IIR_Int32 get_line_number() const = 0;

  /** Get and set the design file */
  virtual IIR_DesignFile *get_design_file() const = 0;
  virtual void set_design_file(IIR_DesignFile *) = 0;
  
  /** Set basic information about the IIR node */
  virtual void set_base_info( IIR_DesignFile    *design_file,
                              int               line_number,
                              int               column_offset, 
                              int               character_offset ) = 0;

  virtual void copy_location( const IIR *, IIR *) = 0;
  virtual void copy_location(IIR *) = 0;
#ifdef SCHEMATIC_INFO
  /** The following nodes apply to schematic capture tools only and have to
      be #ifdefed in with SCHEMATIC_INFO. */
  //@{
  
  /** Set the sheet name of this node (if instantiated from schematic capture).
      @param sheet_name The IIR_Identifier representation of the sheet name.
   */
  virtual void set_sheet_name(IIR_Identifier *sheet_name) = 0;

  /** Set the X coordinate of this node (if instantiated from schematic capture).
      @param x_coordinate The IIR_Int32 representation of the X coordinate.
   */
  virtual void set_x_coordinate(IIR_Int32 x_coordinate) = 0;

  /** Set the Y coordinate of this node (if instantiated from schematic capture).
      @param y_coordinate The IIR_Int32 representation of the Y coordinate.
  */
  virtual void set_y_coordinate(IIR_Int32 y_coordinate) = 0;

  /** Get the sheet name. */
  virtual IIR_Identifier *get_sheet_name() = 0;

  /** Get the X coordinate. */
  virtual IIR_Int32 get_x_coordinate() = 0;

  /** Get the Y coordinate. */
  virtual IIR_Int32 get_y_coordinate() = 0;

  //@}

#endif

#ifdef EXTRA_LOCATERS
  /** The following allow the analyzer to supply extra locator info
      if desired.  Savant doesn't supply this info.  To enable the space in
      the Savant IIR, #define EXTRA_LOCATERS. */

  //@{

  /** Set the column offset.
      @param column_offset The IIR_Int32 representation of the column offset of this
      node in the VHDL source. */
  virtual void set_column_offset(IIR_Int32 column_offset) = 0;

  /** Set the character offset.
      @param character_offset The IIR_Int32 representation of the character offset of this
      node in the VHDL source. */
  virtual void set_character_offset(IIR_Int32 character_offset) = 0;

  /** Get the column offset */
  virtual IIR_Int32 get_column_offset() = 0;

  /** Get the character offset */
  virtual IIR_Int32 get_character_offset() = 0;
  //@}

#endif  
  
  /** This method gets the prefix of a name, and returns the string version
      of it. */
  virtual IIR_TextLiteral *get_prefix_string() = 0;

  /** This method has been introduced to remove unneccessary type
      casting.  If this method is overridden, it will call the derived
      method.  If not it simply returns NULL.
  */
  virtual IIR* get_value() = 0;

  virtual ~IIR() {}

  /** The Savant implementation of IIR stores a pointer back to the design
      file.  This allows access to the file name, as well as the symbol
      table associated with the file. */

  virtual IIR* convert_tree(plugin_class_factory *) = 0;

  /** Needed for guard signals */
  virtual IIR_SignalKind get_signal_kind() = 0;
  virtual IIR_Boolean is_guard_signal() = 0;

  virtual IIR_Boolean is_incomplete_type_declaration() = 0;

  /** Does this node represent an "object".  (An object, according to
      the LRM, is a constant, signal, variable, or a file.)  This method
      is overriden by things like IIR_SelectedName, and
      IIR_AliasDeclaration.  A "TRUE" from this method does NOT mean
      that it's safe to cast to IIR_ObjectDeclaration. */
  virtual IIR_Boolean is_object() = 0;

  virtual IIR_Boolean is_name() = 0;
  virtual IIR_Boolean is_signal() = 0;
  virtual IIR_Boolean is_scalar_type() = 0;
  virtual IIR_Boolean is_record_type() = 0;
  virtual IIR_Boolean is_array_type() = 0;
  virtual IIR_Boolean is_entity_declaration() = 0;
  virtual IIR_Boolean is_resolved() = 0;
  virtual IIR_Boolean is_ascending_range() = 0;
  virtual IIR_Boolean is_subtype() = 0;
  virtual IIR_Boolean is_access_type() = 0;
  virtual IIR_Boolean is_interface() = 0;
  virtual IIR_Boolean is_enumeration_type() = 0;
  virtual IIR_Boolean is_text_literal() = 0;
  virtual IIR_Boolean is_aggregate_expression() = 0;
  virtual IIR_Boolean is_constant() = 0;
  virtual IIR_Boolean is_file_type() = 0;
  virtual IIR_Boolean is_type() = 0;
  virtual IIR_Boolean is_subprogram()  = 0;
  virtual IIR_Boolean is_integer_type() = 0;
  virtual IIR_Boolean is_character_type() = 0;
  virtual IIR_Boolean is_discrete_type() = 0;
  virtual IIR_Boolean is_variable() = 0;
  virtual IIR_Boolean is_literal() = 0;
  virtual IIR_Boolean is_operator() = 0;
  virtual IIR_Boolean is_above_attribute_found() = 0;
  virtual IIR_Boolean is_relational_operator() = 0;
  virtual IIR_Boolean is_logical_operator() = 0;

  /** This returns TRUE, if the type definition, or subtype definition is
      part of subtype declaration. */
  virtual IIR_Boolean is_subtype_decl() = 0;

  /// Is this node an architecture declaration?
  virtual IIR_Boolean is_architecture_declaration() = 0;

  /// Is this node an attribute declaration?
  virtual IIR_Boolean is_attribute_declaration() = 0;

  /// Is this node an scalar type definition?
  virtual IIR_Boolean is_scalar_type_definition() = 0;

  /// Is this node a label?
  virtual IIR_Boolean is_label() = 0;

  /// Is this node an component declaration?
  virtual IIR_Boolean is_component_declaration() = 0;

  /// Is this node a function declaration?
  virtual IIR_Boolean is_function_declaration() = 0;

  /// Is this node an configuration declaration?
  virtual IIR_Boolean is_configuration_declaration() = 0;

  /// Is this node a procedure declaration?
  virtual IIR_Boolean is_procedure_declaration() = 0;

  /// Is this node a package declaration?
  virtual IIR_Boolean is_package_declaration() = 0;

  /// Is this node a type declaration?
  virtual IIR_Boolean is_type_declaration() = 0;

  /// Is this node a subtype declaration?
  virtual IIR_Boolean is_subtype_declaration() = 0;

  /// Is this node a physical unit?
  virtual IIR_Boolean is_physical_unit() = 0;

  /// Is this node a group declaration?
  virtual IIR_Boolean is_group_declaration() = 0;

  /// Is this node a file declaration?
  virtual IIR_Boolean is_file() = 0;

  //@{

  /** These methods tell us whether an expression is locally (or globally
      static) as defined by the LRM in section 7.4.1.  If
      is_locally_static() isn't overridden, then being a locally static
      primary is sufficient to say we're locally static.  These methods
      also apply to names, as the rules given in LRM section 6.1.  The to
      find out if an IIR meets the criteria for a "static name", the method
      "_is_globally_static" should be called where a name is appropriate.
      To find out if an IIR meets the criteria for a "locally static name",
      the method "_is_locally_static" should be called where a name is
      appropriate.  Note too, that after resoultion simple names will be
      replaced with their declaration...*/
  //@}
  virtual IIR_Boolean is_locally_static() = 0;

  virtual IIR_TypeDefinition *get_subtype() = 0;
  virtual void set_subtype(IIR_TypeDefinition *) = 0;

  /** The following methods help to avoid publish the same signal attribute
      multiple times.  Okay, these do not make sense here, but virtual
      functions are better than having type casts in the code. */
  enum SignalAttribute {LAST_EVENT = 0, EVENT, ACTIVE, LAST_ACTIVE, LAST_VALUE,
			DRIVING, DRIVING_VALUE, QUIET, STABLE, TRANSACTION,
			INVALID};

  /** The code generator needs to know what kind of unit is being
      published.  This is acheived by the following static variable and the
      corresponding wrapper methods. */
  enum PublishedUnit {ENTITY_DECL, ARCHITECTURE_DECL, BLOCK, FUNCTION, 
		      PROCEDURE, PACKAGE_PUB, PACKAGE_BODY, PROCESS, 
		      PROCESS_STATE, TYPE, GENERIC_MAP, GENERATE_FOR, 
		      GENERATE_IF, DUMMY_ENTITY_DECL, CONFIGURATION_DECLARATION,
		      CASE_STATEMENT, NONE_PARSING, SIMULTANEOUS_STATEMENT, 
		      SIMULTANEOUS_IF, BREAK_STATEMENT, ABOVE_ATTRIBUTE, NONE}; 

  /** This method returns the number of indexes an array object has. */
  virtual IIR_Int32 get_num_indexes( ) = 0;


  /** The "print" method is intended to print out ONLY the raw data found
      in the IF.  This means it should not be made to print any formatting
      or "labels", like "NAME: foo".  An exception might be for lists that
      it would be alright to put commas between elements, although I'm not
      sure why anyone would want to print a list in this manner.  This
      method is NOT meant to be a way to publish VHDL source code.  It is
      intended more for debuging and/or the generation of error messages.
      Also, note that every overloaded _print method should call the print
      method of it's direct decendent. */
  virtual ostream &print( ostream & ) = 0;

  virtual IIR_TextLiteral *get_declarator() = 0;

  /** This method returns the declaration of an indexed name.  If the
      prefix is a declaration, returns it, or else, gets the declaration of
      the prefix recursively. */
  virtual IIR_Declaration* get_prefix_declaration() = 0;

  /**
     Republish the VHDL that this node represents.  Called on a expression,
     it would republish just the expression.  Called on a design file, the whole
     file worth of vhdl would be republished.     
  */
  virtual void publish_vhdl( ostream &os ) = 0;

};


inline 
ostream &
operator<<(ostream &os, IIR &is ) {
  return is.print( os );
}

#endif
