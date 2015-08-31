
#ifndef IIRBASE_HH
#define IIRBASE_HH

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
#include "IIR.hh"
#include "IRBasicDataTypes.hh"

/** This is the base node definition for the intermediate form.  All nodes
    in IIR are descendants of this node.  */

class IIRBase : public virtual IIR {
public:

  /** Returns the IIR_Kind of this node.  This is useful
      in determining the type of a node when an IIR * is
      all that's available */
  virtual IIR_Kind get_kind() const = 0;

  /** Returns the kind of this node in text form.  This is here for output
      and debugging purposes. */
  virtual const IIR_Char *get_kind_text() const = 0;

  string get_implementation_class() const;

  /** Accessor to set the VHDL file name that this node was parsed from. 
      @param file_name The IIR_Identifier representation of the file name.
  */
  void set_file_name(IIR_Identifier *file_name, plugin_class_factory *factory);
  
  /** Accessor to set the line number of the VHDL this node corresponds
      to. 
      @param line_number The IIR_Int32 corresponding to the line number.
  */
  void set_line_number(IIR_Int32 line_number) {
    iir_line_number = line_number;
  }

  /** Read the file name from the node. */
  IIR_Identifier *get_file_name();

  /** Read the line number from the node. */
  IIR_Int32 get_line_number()  const { return iir_line_number; }

  /** Get and set the design file */
  virtual IIR_DesignFile *get_design_file() const { return _my_design_file; }
  virtual void set_design_file(IIR_DesignFile *new_file) {
    ASSERT(new_file != NULL);
    _my_design_file = new_file;
  }
   
  virtual void set_base_info( IIR_DesignFile    *design_file,
                              int               line_number,
                              int               column_offset, 
                              int               character_offset );

  virtual void copy_location( const IIR *, IIR *);
  virtual void copy_location(IIR *);
#ifdef SCHEMATIC_INFO
  /** The following nodes apply to schematic capture tools only and have to
      be #ifdefed in with SCHEMATIC_INFO. */
  //@{
  
  /** Set the sheet name of this node (if instantiated from schematic capture).
      @param sheet_name The IIR_Identifier representation of the sheet name.
  */
  void set_sheet_name(IIR_Identifier *sheet_name) {
    iir_sheet_name = sheet_name;
  }

  /** Set the X coordinate of this node (if instantiated from schematic capture).
      @param x_coordinate The IIR_Int32 representation of the X coordinate.
  */
  void set_x_coordinate(IIR_Int32 x_coordinate) {
    iir_x_coordinate = x_coordinate;
  }

  /** Set the Y coordinate of this node (if instantiated from schematic capture).
      @param y_coordinate The IIR_Int32 representation of the Y coordinate.
  */
  void set_y_coordinate(IIR_Int32 y_coordinate) {
    iir_y_coordinate = y_coordinate;
  }

  /** Get the sheet name. */
  IIR_Identifier *get_sheet_name() {return iir_sheet_name;}

  /** Get the X coordinate. */
  IIR_Int32 get_x_coordinate()     {return iir_x_coordinate;}

  /** Get the Y coordinate. */
  IIR_Int32 get_y_coordinate()     {return iir_y_coordinate;}

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
  void set_column_offset(IIR_Int32 column_offset) {
    iir_column_offset = column_offset;
  }

  /** Set the character offset.
      @param character_offset The IIR_Int32 representation of the character offset of this
      node in the VHDL source. */
  void set_character_offset(IIR_Int32 character_offset) {
    iir_character_offset = character_offset;
  }

  /** Get the column offset */
  IIR_Int32 get_column_offset()    {return iir_column_offset;}

  /** Get the character offset */
  IIR_Int32 get_character_offset() {return iir_character_offset;}
  //@}

#endif  
  
  /** This method gets the prefix of a name, and returns the string version
      of it. */
  IIR_TextLiteral *get_prefix_string();

  /** This method has been introduced to remove unneccessary type
      casting.  If this method is overridden, it will call the derived
      method.  If not it simply returns NULL. */
  virtual IIR *get_value();

  /** This function performs the conversion of one tree into another.  At this 
      level it creates a copy of the current node using the passed in factory, 
      assuming it hasn't already been created.  */
  virtual IIR *convert_tree(plugin_class_factory *factory);
  virtual IIR *convert_node(IIR *node, plugin_class_factory *factory);

  /** Needed for guard signals */
  IIR_SignalKind get_signal_kind();
  IIR_Boolean is_guard_signal();

  IIR_Boolean is_incomplete_type_declaration(){ return FALSE; }

  IIR_Boolean is_name(){ return FALSE; }
  IIR_Boolean is_signal(){ return FALSE; }
  //@{
  /** Querying various type properties */
  IIR_Boolean is_access_type();
  IIR_Boolean is_array_type();
  IIR_Boolean is_enumeration_type();
  IIR_Boolean is_file_type();
  IIR_Boolean is_record_type();
  IIR_Boolean is_scalar_type();
  //@}
  IIR_Boolean is_entity_declaration() { return FALSE; }
  IIR_Boolean is_resolved(){ return FALSE; }
  IIR_Boolean is_ascending_range();
  IIR_Boolean is_subtype(){ return FALSE; }
  IIR_Boolean is_interface(){ return FALSE; }
  IIR_Boolean is_text_literal() {return FALSE; }
  IIR_Boolean is_aggregate_expression() { return FALSE; }
  IIR_Boolean is_constant(){ return FALSE; }
  IIR_Boolean is_type(){ return FALSE; }
  IIR_Boolean is_subprogram(){ return FALSE; }
  IIR_Boolean is_character_type(){ return FALSE; }
  IIR_Boolean is_discrete_type(){ return FALSE; }
  IIR_Boolean is_integer_type(){ return FALSE; }
  IIR_Boolean is_variable(){ return FALSE; }
  IIR_Boolean is_literal() { return FALSE; }
  IIR_Boolean is_operator() { return FALSE; }
  IIR_Boolean is_above_attribute_found() { return FALSE; }
  IIR_Boolean is_logical_operator(){ return FALSE; }
  IIR_Boolean is_relational_operator(){ return FALSE; }

  /** Does this node represent an "object".  (An object, according to
      the LRM, is a constant, signal, variable, or a file.)  This method
      is overriden by things like IIR_SelectedName, and
      IIR_AliasDeclaration.  A "TRUE" from this method does NOT mean
      that it's safe to cast to IIR_ObjectDeclaration. */
  IIR_Boolean is_object(){ return FALSE; }

  /** This returns TRUE, if the type definition, or subtype definition is
      part of subtype declaration. */
  IIR_Boolean is_subtype_decl() { return FALSE; }

  /// Is this node an architecture declaration?
  IIR_Boolean is_architecture_declaration(){ return FALSE; }

  /// Is this node an attribute declaration?
  IIR_Boolean is_attribute_declaration(){ return FALSE; }

  /// Is this node a scalar type definition?
  IIR_Boolean is_scalar_type_definition(){ return FALSE; }

  /// Is this node a Label?
  IIR_Boolean is_label(){ return FALSE; }

  /// Is this node a component declaration?
  IIR_Boolean is_component_declaration(){ return FALSE; }

  /// Is this node a function declaration?
  IIR_Boolean is_function_declaration(){ return FALSE; }

  /// Is this node a configuration declaration?
  IIR_Boolean is_configuration_declaration(){ return FALSE; }

  /// Is this node a procedure declaration?
  IIR_Boolean is_procedure_declaration(){ return FALSE; }

  /// Is this node a procedure declaration?
  IIR_Boolean is_physical_unit(){ return FALSE; }

  /// Is this node a package declaration?
  IIR_Boolean is_package_declaration(){ return FALSE; }

  /// Is this node a type declaration?
  IIR_Boolean is_type_declaration(){ return FALSE; }

  /// Is this node a subtype declaration?
  IIR_Boolean is_subtype_declaration() { return FALSE; }

  /// Is this node a group declaration?
  IIR_Boolean is_group_declaration(){ return FALSE; }

  /// Is this node a file declaration?
  IIR_Boolean is_file() { return FALSE; }

  //@{

  /** These methods tell us whether an expression is locally (or globally
      static) as defined by the LRM in section 7.4.1.  These methods also
      apply to names, as the rules given in LRM section 6.1.  The to find
      out if an IIR meets the criteria for a "static name", the method
      "is_globally_static" should be called where a name is appropriate.
      To find out if an IIR meets the criteria for a "locally static name",
      the method "is_locally_static" should be called where a name is
      appropriate.  Note too, that after resoultion simple names will be
      replaced with their declaration...*/
  IIR_Boolean is_locally_static();
  //@}

  IIR_TypeDefinition *get_subtype();
  void set_subtype(IIR_TypeDefinition *);

  /** This method returns the number of indexes an array object has. */
  IIR_Int32 get_num_indexes( );

  IIRBase* converted_node;

  /** The "print" method is intended to print out ONLY the raw data found
      in the IF.  This means it should not be made to print any formatting
      or "labels", like "NAME: foo".  An exception might be for lists that
      it would be alright to put commas between elements, although I'm not
      sure why anyone would want to print a list in this manner.  This
      method is NOT meant to be a way to publish VHDL source code.  It is
      intended more for debuging and/or the generation of error messages.
      Also, note that every overloaded _print method should call the print
      method of it's direct decendent. */
  ostream &print( ostream & );

  virtual IIR_TextLiteral *get_declarator();

  /** This method returns the declaration of an indexed name.  If the
      prefix is a declaration, returns it, or else, gets the declaration of
      the prefix recursively. */
  virtual IIR_Declaration* get_prefix_declaration();

  /** @name VHDL publishing methods 
      Methods related to publishing of VHDL.
  */
  //@{
  /** Publishes VHDL for the node that the method is called on.  In
    general, the VHDL that is generated by calling this method will be
    appropriate for a reference to a node rather than defining the node.
    For instance, a declaration node can appear both in a declarative
    region or in a statement/use context.  If "_publish_vhdl" is called
    on a declaration, the name of the declaration will be the output.
    To publish the full declaration, one would call _publish_vhdl_decl.
     
     @see IIRScram#_publish_vhdl_decl */
  virtual void publish_vhdl(ostream &);
  virtual void publish_vhdl_range(ostream &);
  virtual void publish_vhdl_decl(ostream &);
  virtual void publish_vhdl_type_decl(ostream &);
  virtual void publish_vhdl_subtype_decl(ostream &);
  virtual void publish_vhdl_operator(ostream &);
  //@}

  enum Precedence {LOGICAL_OPERATOR, RELATIONAL_OPERATOR, SHIFT_OPERATOR,
		   ADDING_OPERATOR, SIGN_OPERATOR, MULTIPLYING_OPERATOR,
		   MISCELLANEOUS_OPERATOR, OTHERS};
  /** This method will return precedence levels for any operator and
      literals.  The precedence levels are given in the LRM.  There are 8
      levels of precedence level 8 are the integer literals and all
      function calls which return value. All others take precedence values
      according to LRM. The higher the number , the higher the
      precedence. 
  */
  virtual Precedence get_precedence();

protected:
  IIRBase();
  virtual ~IIRBase() = 0;

  plugin_class_factory *get_class_factory();

  /** The Savant implementation of IIR stores a pointer back to the design
      file.  This allows access to the file name, as well as the symbol
      table associated with the file. */
  IIR_DesignFile *_my_design_file;
    
  void _report_undefined_fn(const char *);
private:
  /** Where the line number is stored. */
  IIR_Int32  iir_line_number;
  
#ifdef SCHEMATIC_INFO
  /** Where the X coordinate is stored. */
  IIR_Int32  iir_x_coordinate;

  /** Where the Y coordinate is stored. */
  IIR_Int32  iir_y_coordinate;

  /** Where the sheet name is stored. */
  IIR_Identifier *iir_sheet_name;
#endif

#ifdef EXTRA_LOCATERS
  /** Where the column offset is stored. */
  IIR_Int32  iir_column_offset;

  /** Where the character offset is stored. */
  IIR_Int32  iir_character_offset;
#endif
  bool already_entered;
  IIR_TypeDefinition *subtype;
};

#endif
