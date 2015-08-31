#ifndef IIRSCRAM_TYPE_DEFINITION_HH
#define IIRSCRAM_TYPE_DEFINITION_HH

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
#include "IIRScram.hh"
#include "IIRBase_TypeDefinition.hh"

class StandardPackage;
class IIRScram_Attribute;
class IIRScram_ElementDeclarationList;
class IIRScram_FunctionDeclaration;
class IIRScram_Name;
class IIRScram_RangeTypeDefinition;
class IIRScram_ScalarTypeDefinition;
class IIRScram_TypeDeclaration;

/** The extension class for IIR_TypeDefinition. */
class IIRScram_TypeDefinition : public virtual IIRScram, public virtual IIRBase_TypeDefinition{

public:
  IIRScram_TypeDefinition();
  virtual ~IIRScram_TypeDefinition();

  virtual IIR_Boolean _is_line_type();
  virtual IIR_Boolean _designates_incomplete_type(){ return FALSE; }

  virtual IIR_Boolean _is_iir_type_definition() { return TRUE; }
  
  virtual IIRScram_TypeDefinition *get_across(); 
  virtual IIRScram_TypeDefinition *get_through();  

  /** This method sets the resolution function for types that are
     allowed to have them.  An internal error will be generated if
     called on file or access types.  */
  virtual void _set_resolution_function( IIRScram_FunctionDeclaration * );
  
  /** If this type is not anonymous, it prints declaration's name.
      Otherwise, it prints "ANONYMOUS". */
  IIRScram_Declaration *_get_declaration();

  virtual IIRScram *_get_direction();

  virtual IIRScram_TypeDefinition *_get_base_type();
  virtual IIRScram_TypeDefinition *_get_resolved_base_type();

  // A scalar subtype may return NULL as it's left even if it has a range
  // constraint.  These methods will travel down to the first base type
  // that has a left defined.  Similarly for right and direction.
  virtual IIRScram* _get_base_type_left();
  virtual IIRScram* _get_base_type_direction();
  virtual IIRScram* _get_base_type_right();

  IIRScram_TypeDefinition * _get_type_mark();

  /** If this is a record type (or an access to a record type?), it returns
      it's element list.  Otherwise it returns NULL. */
  virtual IIRScram_ElementDeclarationList *_get_element_declarations(){ return NULL; }

  /** If this is an array type (or an access to an array type?), returns
      it's element subtype.  Otherwise, it complains and aborts! */
  virtual IIRScram_TypeDefinition *_get_element_subtype(); 
  virtual IIRScram_ScalarTypeDefinition *_get_index_subtype();
  virtual IIRScram_ScalarTypeDefinition *_get_resolved_index_subtype();
  virtual IIR_Int32 get_num_indexes();
  virtual IIRScram_TypeDefinition *_get_type_of_element( int );

  virtual IIRScram_TypeDefinition *_is_explicit_type_conversion_needed(IIRScram_TypeDefinition *);
  virtual IIR_Boolean _is_base_type(IIRScram_TypeDefinition *);

  /** This method builds a new array subtype by index constraining this
      one.  You can index constrain an access to an array type, so it's
      defined here. */
  virtual IIRScram_TypeDefinition *_index_constrain_array( IIRScram_ScalarTypeDefinition * );
  
  /** This method takes a range type definition, and constructs an
      IIRScram_IntegerTypeDefinition, IIRScram_FloatingTypeDefinition. It
      allocates memory to hand back to the caller. */
  static IIRScram_ScalarTypeDefinition *_construct_new_type( IIRScram_RangeTypeDefinition *,
                                                             IIRScram_TypeDeclaration *,
                                                             IIRScram_DesignFile *);

  savant::set<IIRScram_TypeDefinition> *_get_rval_set( constraint_functor *functor = 0 );
  void _type_check( savant::set<IIRScram_TypeDefinition> * );

  /** Provides an entry into type checking a type definition.  By
     default, this does nothing.  If it's been overridden, then it does
     whatever the descendent type wants done in terms of type checking.  */
  virtual void _type_check(){}


  virtual IIRScram_TypeDefinition *
  _construct_new_subtype( IIRScram_Name                 *resolution_function,
			  IIRScram_ScalarTypeDefinition *new_constraint);

  virtual IIRScram_TypeDefinition *_get_new_subtype();

  static IIRScram_FunctionDeclaration *_resolve_resolution_function( IIRScram_Name * );

  IIRScram_TypeDefinition *
  _construct_new_subtype_resolution_function_only( IIRScram_Name *resolution_function );

  virtual void _clone( IIRScram * );
  
  virtual void set_is_element( IIR_Boolean );  
  
  /** This gives a type a chance to build operators, functions, and do
      other housekeeping. */
  virtual void _come_into_scope( symbol_table *, IIRScram_TypeDeclaration * );
  virtual void _come_out_of_scope( symbol_table * ){}

  /** For access subtypes, this method returns the type that is accessed.
      For other types/subtypes, this will generate a runtime error.  */
  virtual IIRScram_TypeDefinition *_get_designated_subtype();
protected:

  virtual void _build_implicit_operators( savant::set<IIRScram_Declaration> *add_to);
  void _build_implicit_operator( const char *op,
				 savant::set<IIRScram_Declaration> *add_to,
				 IIRScram_TypeDefinition *return_type,
				 IIRScram_TypeDefinition *left_type,
				 IIRScram_TypeDefinition *right_type = NULL );

  void _build_implicit_operators( const char *ops[],
				  savant::set<IIRScram_Declaration> *add_to,
				  IIRScram_TypeDefinition *return_type,
				  IIRScram_TypeDefinition *left_type,
				  IIRScram_TypeDefinition *right_type = NULL );

  void _build_logical_operators( savant::set<IIRScram_Declaration> *add_to );
  void _build_ordering_operators( savant::set<IIRScram_Declaration> *add_to );

  /* Simple helper function */
  IIRScram_TypeDefinition *_get_this_element_subtype();
private:
  static IIRScram_ScalarTypeDefinition *_determine_type_of_bound( IIRScram *left_or_right );

  IIRScram_Attribute *my_attribute;
};
#endif
