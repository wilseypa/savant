#ifndef IIRSCRAM_HH
#define IIRSCRAM_HH

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
#include "IIRBase.hh"
#include "node_visitor.hh"
#include "dl_list.hh"

using std::string;
using std::ostream;

class symbol_table;
class include_manager;
class published_file;
class break_handler;
class constraint_functor;
class IIR_AboveAttribute;

namespace savant {
  template <class type> class set;
}

class IIRScram;
class IIRScram_ArchitectureDeclaration;
class IIRScram_ArchitectureStatementList;
class IIRScram_AssociationList;
class IIRScram_AttributeSpecification;
class IIRScram_AttributeSpecificationList;
class IIRScram_ConcurrentStatement;
class IIRScram_ConstantDeclaration;
class IIRScram_ContributionAttribute;
class IIRScram_Declaration;
class IIRScram_DeclarationList;
class IIRScram_Designator;
class IIRScram_DesignatorList;
class IIRScram_DesignFile;
class IIRScram_DotAttribute;
class IIRScram_EntityDeclaration;
class IIRScram_FunctionDeclaration;
class IIRScram_GenericList;
class IIRScram_Identifier;
class IIRScram_IntegerLiteral;
class IIRScram_InterfaceList;
class IIRScram_Label;
class IIRScram_LibraryDeclaration;
class IIRScram_LibraryUnit;
class IIRScram_List;
class IIRScram_NatureDeclaration;
class IIRScram_NatureDefinition;
class IIRScram_PackageDeclaration;
class IIRScram_PortList;
class IIRScram_ProcessStatement;
class IIRScram_ReferenceAttribute;
class IIRScram_SimultaneousStatement;
class IIRScram_Statement;
class IIRScram_TypeDeclaration;
class IIRScram_TypeDefinition;
class IIRScram_TextLiteral;

/** This class is the base of the SAVANT extensions to the IIR.  Due to the
    design of the IIR, lots of things have been put in here that seem like
    they might be better suited somewhere else.  Unfortunately, it is often
    the case that IIR is the closest common ancestor that one can find to
    insert a virtual method into. */
class IIRScram : public virtual IIRBase{

public:
  IIRScram();
  /** Accepts a visitor for this node.

      Pure virtual method that allows visitors access to the intermediate
      form.  The visitor pattern implemented in this intermediate provides
      support for parameter transmission by a visitor.  This capability is
      achieved by defining the visitor pattern with a return type of void*
      and with an input parameter of type void*.

      @return a void* parameter, allowing parameter transmission within the
      visitor that is not predetermined by the core intermediate.

      @param visitor a pointer to the visitor object.
      @param arg location for a visitor specific pointer to be passed
      into the visitor methods.

      @see node_visitor */
  virtual visitor_return_type *_accept_visitor( node_visitor *, 
						visitor_argument_type *){ return 0; }

  //@{
  /** These methods only apply to entities, components, etc.  (Or names
      representing them, like resolved selected names, etc.) */
  virtual IIRScram_GenericList *_get_generic_list();
  virtual IIRScram_PortList *_get_port_list();
  //@}

  /** This method returns any statement region found in the node. */
  virtual IIRScram_List *_get_statement_list();

  /** This method has been introduced to remove unneccessary type
      castings. */
  virtual IIR_Mode _get_mode();

  /** This method tells use whether or not this is <name>.all */
  virtual IIR_Boolean _is_by_all(){ return FALSE; }

  virtual IIR_Boolean _is_floating_type(){ return FALSE; }
  virtual IIR_Boolean _is_integer_literal(){ return FALSE; }
  virtual IIR_Boolean _is_floating_literal(){ return FALSE; }
  virtual IIR_Boolean _is_string_literal(){ return FALSE; }
  virtual IIR_Boolean _is_association(){ return FALSE; }
  virtual IIR_Boolean _is_sequential_signal_assignment(){ return FALSE; }
  virtual IIR_Boolean _is_designator(){ return FALSE; }
  virtual IIR_Boolean _is_enumeration_literal(){ return FALSE; }
  virtual IIR_Boolean _is_numeric_literal();
  virtual IIR_Boolean _is_numeric_type(){ return FALSE; }
  virtual IIR_Boolean _is_physical_type(){ return FALSE; }
  virtual IIR_Boolean _is_attribute();

  /** @name Node Type Queries
      The Intent of these operators is that if one of them returns true,
      it is absolutely safe to cast straight to the class implied by the
      name.  This is in direct contrast with some methods like
      "_is_signal", which will tell you if something is a signal but it
      doesn't mean the node is an IIRScram_SignalDeclaration.  

      The other method to perform these type of operations is via the
      get_kind method.  However, this technique doesn't allow a query of
      an abstract type - it only works for leaf nodes in the inheritence
      tree.  
  */

  //@{
  /// Is this node an IIRScram_Attribute?
  virtual IIR_Boolean _is_iir_attribute(){ return FALSE; }
  /// Is this node an IIRScram_ConcurrentStatement?
  virtual IIR_Boolean _is_iir_concurrent_statement(){ return FALSE; }
  /// Is this node an IIRScram_ConfigurationItem?
  virtual IIR_Boolean _is_iir_configuration_item(){ return FALSE; }
  /// Is this node an IIRScram_Declaration?
  virtual IIR_Boolean _is_iir_declaration(){ return FALSE; }
  /// Is this node an IIRScram_Expression?
  virtual IIR_Boolean _is_iir_expression(){ return FALSE; }
  /// Is this node an IIRScram_ObjectDeclaration?
  virtual IIR_Boolean _is_iir_object_declaration(){ return FALSE; }
  /// Is this node an IIRScram_PackageBodyDeclaration?
  virtual IIR_Boolean _is_iir_package_body_declaration(){ return FALSE; }
  /// Is this node an IIRScram_List?
  virtual IIR_Boolean _is_iir_list(){ return FALSE; }
  /// Is this node an IIRScram_SignalDeclaration?
  virtual IIR_Boolean _is_iir_signal_declaration(){ return FALSE; }
  /// Is this node an IIRScram_InterfaceDeclaration?
  virtual IIR_Boolean _is_iir_interface_declaration(){ return FALSE; }
  /// Is this node an IIRScram_ElementDeclaration?
  virtual IIR_Boolean _is_iir_element_declaration(){ return FALSE; }
  /// Is this node an IIRScram_PhysicaTypeSubtypeDefinition?
  virtual IIR_Boolean _is_iir_physical_subtype_definition(){ return FALSE; }
  /// Is this node an IIRScram_SequentialStatement?
  virtual IIR_Boolean _is_iir_sequential_statement(){ return FALSE; }
  /// Is this node an IIRScram_TypeDefinition?
  virtual IIR_Boolean _is_iir_type_definition(){ return FALSE; }
  /// Is this node an IIRScram_RecordTypeDefinition?
  virtual IIR_Boolean _is_iir_record_type_definition(){ return FALSE; }
  /// Is this node an IIRScram_FloatingTypeDefinition?
  virtual IIR_Boolean _is_iir_floating_type_definition(){ return FALSE; }
  /// Is this node an IIRScram_IntegerTypeDefinition?
  virtual IIR_Boolean _is_iir_integer_type_definition(){ return FALSE; }
  /// Is this node an IIRScram_AccessTypeDefinition?
  virtual IIR_Boolean _is_iir_access_type_definition(){ return FALSE; }
  /// Is this node an IIRScram_EnumerationTypeDefinition?
  virtual IIR_Boolean _is_iir_enumeration_type_definition(){ return FALSE; }
  /// Is this node an IIRScram_PhysicalTypeDefinition?
  virtual IIR_Boolean _is_iir_physical_type_definition(){ return FALSE; }
  /// Is this node an IIRScram_ArrayTypeDefinition?
  virtual IIR_Boolean _is_iir_array_type_definition(){ return FALSE; }
  /// Is this node an IIRScram_CaseStatementAlternative?
  virtual IIR_Boolean _is_iir_case_statement_alternative(){ return FALSE; }
  /// Is this node an IIRScram_ConfigurationSpecification?
  virtual IIR_Boolean _is_iir_configuration_specification(){ return FALSE; }
  /// Is this node an IIRScram_AttributeSpecification?
  virtual IIR_Boolean _is_iir_attribute_specification(){ return FALSE; }
  /// Is this node an IIRScram_DisconnectSpecification?
  virtual IIR_Boolean _is_iir_disconnect_specification(){ return FALSE; }
  /// Is this node an IIRScram_EnumerationLiteral?
  virtual IIR_Boolean _is_iir_enumeration_literal(){ return FALSE; }
  /// Is this node an IIRScram_TextLiteral?
  virtual IIR_Boolean _is_iir_text_literal(){ return FALSE; }
  /// Is this node an IIRScram_Name?
  virtual IIR_Boolean _is_iir_name(){ return FALSE; }
  /// Is this node an IIRScram_Statement?
  virtual IIR_Boolean _is_iir_statement(){ return FALSE; }
  /// Is this node an IIRScram_LibraryUnit?
  virtual IIR_Boolean _is_iir_library_unit(){ return FALSE; }
  /// Is this node an IIRScram_LibraryDeclaration?
  virtual IIR_Boolean _is_iir_library_declaration(){ return FALSE; }
  //@}

  /** Returns true if static analysis says this expression is readable,
     in a variable or signal assignment context, else returns false. */
  virtual IIR_Boolean _is_readable();

  /** Returns true if static analysis says this expression is writable,
     in a variable or signal assignment context, else returns false. */
  virtual IIR_Boolean _is_writable();

  virtual IIRScram *_clone();
  virtual void _clone( IIRScram *);

  virtual IIRScram_AttributeSpecificationList *_get_attribute_specification_list( );

  /** This method returns the declaration of an indexed name.  If the
      prefix is a declaration, returns it, or else, gets the declaration of
      the prefix recursively. */
  virtual IIRScram_Declaration* _get_prefix_declaration();

  /** This is used on a selected name to get the package name in it. */
  virtual IIRScram_Declaration* _get_package_declaration();

  /** The following function returns the type of the IIRScram_Name object that
      is referred to. */
  virtual IIRScram_TypeDefinition* _get_name_type();

  /** The following function is used for building the generic parameter
      set when generic statements occur inside Simultaneous Statements */
  virtual void _build_generic_parameter_set( savant::set<IIRScram_Declaration> *);

  /** The following function is used to pick up the resolution function
      for a subtype/type definition. This function is needed as all the
      vhdl publishing is now done in scalar type.  This function is
      overloaded in the corresponding nodes that have resolution
      function defined.  */
  virtual IIRScram_FunctionDeclaration *_get_resolution_function();

  IIRScram_LibraryDeclaration *_get_work_library( );

  /** These methods give derived classes a chance to generate implicit
      declarations and so forth. */
  virtual void _come_into_scope( symbol_table * ){}
  virtual void _come_out_of_scope( symbol_table * ){}
      
  IIR_Boolean _is_currently_publishing_generate_for();

  void _report_undefined_scram_fn(const char *);

  // These methods have to do with semantic checks and such.
  
  /** Symbol lookup methods are intended to be used on names. The method
      accepting an argument essentially narrows the search to be within the
      context of a set of declarations.  I.e. find the "foo.bars" within
      the context of the declarations of "baz"es. */
  virtual savant::set<IIRScram_Declaration> *_symbol_lookup();
  virtual savant::set<IIRScram_Declaration> *_symbol_lookup( IIRScram_Declaration *);
  virtual savant::set<IIRScram_Declaration> *_symbol_lookup( savant::set<IIRScram_Declaration> *);
  virtual savant::set<IIRScram_Declaration> *_symbol_lookup(constraint_functor *functor);

  
  IIRScram_Label *_lookup_label( IIR_Boolean complain_on_error );
  
  /** These methods calculate a node's rval_set.  Either will return a
      a set with a bunch of type definitions, or will return NULL if it
      doesn't have a valid rval.  (Like for an undefined symbol, or a
      library declaration or something).  The optional argument is a
      method declared in IIRScram that returns a boolean value.  This method
      will be called on declarations of things when being considered as
      possbilities for symbols.  If the method returns false, the
      declaration will not be considered as a possibility.  For
      instance, if there is a type "FOO" in the current scope, and a
      variable "FOO", and we're looking for the target of a variable
      assignment statement, only the variable assignment will be
      considered. */
  virtual savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor = 0);

  virtual savant::set<IIRScram_TypeDefinition> *_get_rval_set( savant::set<IIRScram_TypeDefinition> *,
                                                               constraint_functor *functor = 0 );
  virtual savant::set<IIRScram_TypeDefinition> *_get_rval_set( savant::set<IIRScram_Declaration> *,
                                                               constraint_functor *functor = 0 );

  /** This method takes the a set of return values that are context,
      and a known return type, and returns the rval from the
      context rvals that is correct.  For instance, if we have:
      foo( 1 to  3 ).bar( 1 ) and we know the type of the whole expression,
      and we have a set of types for foo( 1 to 3 ), this method will tell
      us which is correct... */
  virtual IIRScram_TypeDefinition *_determine_rval_in_set( savant::set<IIRScram_TypeDefinition> *,
                                                           IIRScram_TypeDefinition * );

  /** Same as previous method, but in cases like: work.foo( 1 ), where the
      prefix has a declaration, but not a type... */
  virtual IIRScram_Declaration *_determine_decl_in_set( savant::set<IIRScram_Declaration> *,
                                                        IIRScram_TypeDefinition * );  

  /** This method looks at this node as having been resolved as a formal in
      an association, and returns the declaration associated with it. */
  virtual IIRScram_Declaration *_find_formal_declaration();

  /** This method should only be called on resolved "things".  For
      instance, declarations, resolved names (indexed names with
      declaration prefixes, etc.) */
  virtual IIRScram_TypeDefinition *_get_subtype();

  /** This method should only be called on resolved "things".  For
      instance, declarations, resolved names (indexed names with
      declaration prefixes, etc.)  It should only be called in objects that
      are access types (otherwise, it returns NULL). */
  virtual IIRScram_TypeDefinition *_get_rval_pointed_at();

  /** This method calculates the locally static value of the expression
      it's called on.  If this is impossible (i.e. the expression isn't
      static, or it's not integer valued, it will return NULL.)  If
      possible, it _allocates_ an IIRScram_IntegerLiteral with the result
      represented in it. */
  virtual IIRScram_IntegerLiteral *_get_integer_static_value();
  
  /** This method should only be called on resolved "things".  For
      instance, declarations, resolved names (indexed names with
      declaration prefixes, etc.)  Or, on type definitions.  This method
      returns the element subtype of an array for the index passed in.  If
      the array is multidimensional, the returned subtype will be another
      array type definition.  If the number passed in is higher than the
      number of indexes of the array, or if the object the method is called
      on isn't an array, the return value is NULL.  */
  virtual IIRScram_TypeDefinition *_get_type_of_element( int );

  /** This method returns the type of an objects port in a particular
      position: port( x : in bit; y : out integer; ) 0 = bit
      typedefinition, 1 = integertypedefinition */
  virtual IIRScram_TypeDefinition *_get_port_type( int );
  
  /** Given our (resolved) r value, plus knowing what type of node we are,
      transform ourselves into the correct declaration... */
  virtual IIRScram *_rval_to_decl( IIRScram_TypeDefinition * );

  /** Given a prefix of type (param 1), return the declaration for a suffix
      with type (param 2) */
  virtual IIRScram *_rval_to_decl( IIRScram_TypeDefinition *, IIRScram_TypeDefinition * );

  /** Given a prefix declaration (param 1), return the declaration for a suffix with
      type (param 2) */
  virtual IIRScram *_rval_to_decl( IIRScram_Declaration *, IIRScram_TypeDefinition * );

  /** This method takes a declaration, and returns a resolved IIRScram * that
      has had the declaration applied to it.  For instance, a
      IIRScram_SimpleName returns the declaration itself.  An IIRScram_SelectedName
      resolves the prefix and the suffix, and returns itself. */
  virtual IIRScram *_decl_to_decl( IIRScram_Declaration * );

  /** This is the main call into the semantic processing routines.  The set
      that gets passed in is the list of possible l-values of the node
      being type-checked. */
  virtual void _type_check( savant::set<IIRScram_TypeDefinition> * );
  virtual void _type_check( IIRScram_TypeDefinition * );

  /** The following methods are used to type check component
      configurations, and configuration specifications.  Unfortunately, IIR
      is their closest direct ancestor.
    
      Note the that int is actually an 
      IIRScram_ConfigurationSpecification::type_check_mode, but we can't easily
      #include that here.*/
  void _type_check_configuration( IIRScram_AssociationList &port_map_aspect,
				  IIRScram_AssociationList &generic_map_aspect,
				  int mode );

  /** Used by _type_check_configuration to resolve the port/generic map
      aspects.
     
      @see IIRScram#_type_check_configuration  */
  void _resolve_map( IIRScram_InterfaceList *entity_interface_list,
		     IIRScram_InterfaceList *component_interface_list,
		     IIRScram_AssociationList &map,
		     int tmp_mode );

  /** This method type checks the iteration scheme of IIR_ForLoopStatement
      and IIR_ConcurrentGenerateForLoop statement.  Again, IIR is the
      closest ancestor.  It takes the iteration scheme as param, and
      returns the correctly resolved subtype for it. */
  IIRScram_TypeDefinition *_type_check_iteration_scheme( IIRScram_ConstantDeclaration *iteration_scheme );

  /**
     Type check/resolve this node to make sure it's valid "file open
     information".  Typically it's going to be an enumeration literal that
     is READ_MODE or WRITE_MODE, but technically it could be something like
     a function call.  The return is the resolved node.
  */
  IIR *_type_check_file_open_information();

  virtual IIRScram *_get_component_name( );
  virtual void _set_component_name( IIRScram * );

  /** Calls "get_entity_aspect" on nodes that define it.  Generates an
      error for any other node. */
  virtual IIRScram_LibraryUnit *_get_entity_aspect();

  /** This method implements the rules found in section 5.2.2 of the '93
      LRM.  It looks for an entity with the same simple name as the
      component passed in.  Nodes that can be passed into this method
      include IIR_SimpleName, and IIR_ComponentDeclaration.  Anything else
      will generate an error.  If no matching entity is found, NULL is
      returned. */
  IIRScram_LibraryUnit *_find_default_binding( IIRScram *component_name );

  /** This virtual method allows semantic transformations to be made as
      part of type_checking.  These transformations include things like the
      conversion of indexed_names into function calls, and removing some of
      the bizarreness that occurs in parsing.  The argument to this
      function is the context that the node is seen in. (It's possible
      rvalues).  Most nodes don't have transformations - therefore the
      default behavior of this method, when not overridden, is simply to
      return "this".  NOTE: This method is intended to be called from
      _type_check of the _containing_ node. I.e. this method is not
      intended to be "recursively descending". */
  virtual IIRScram *_semantic_transform( savant::set<IIRScram_TypeDefinition> * );
  virtual IIRScram *_semantic_transform( IIRScram_TypeDefinition * );

  /** This method, defined within the name class, IIRScram_Identifier class, and
      IIRScram_Identifier class, converts a name into a string suitable for use
      in a unix-type file system. */
  virtual const string convert_to_library_name();

  /* This gets the symbol table of the parser that parsed this file. */
  symbol_table *_get_symbol_table( );

  virtual IIR_Boolean _is_quantity();
  virtual IIR_Boolean _is_terminal();

  // Is it a Branch Quantity
  virtual IIR_Boolean _is_branchQ();

  /** Sometimes a declaration that goes out of scope needs to have it's
      interface made visible.  For instance, in
      component_instantiation_statements, the interface of the entity,
      component, or configuration instantiated needs to be visible at the
      time of type checking. */
  virtual void _make_interface_visible( symbol_table *add_declarations_into );
  virtual void _make_interface_visible( );

  IIRScram_DesignFile *_get_design_file() const;
  void _set_design_file( IIRScram_DesignFile *new_design_file );

  /** Like strdup but allocates the memory with "new".  If no length > 0 is
      passed / in then strlen is called on "to_copy". */
  static char *_strdup( const char * const to_copy, unsigned int size = 0 );

  /** The following methods get called by the parser to hook specifications
      to IIRScram nodes that need them.  For instance, if there is a variable
      declaration foo and it has attribute bar, and in the VHDL exists
      "attribute bar of foo is 7;", this attribute specification will be
      attached to foo.  Similarly, disconnection specifications will be
      attached to guarded signals as required. */
  IIR_Boolean _attach_attribute_specification( IIRScram_AttributeSpecification * );
  IIR_Boolean _attach_disconnection_specification( IIRScram_AttributeSpecification * );

  virtual IIRScram_DeclarationList* _get_declaration_list();

  virtual void _build_reference_quantity_list(dl_list<IIRScram_ReferenceAttribute> *);

  virtual ~IIRScram();

  // IIRScram level wrapper functions
  IIRScram_Identifier *_get_file_name();
  IIRScram_TextLiteral *_get_declarator();
protected:
  // Return a cast pointer to the design file
  IIRScram_DesignFile *_get_my_design_file(); 

private:

  /** Get the singleton instance of the include manager. */
  static include_manager *get_include_manager();
};
 
#endif
