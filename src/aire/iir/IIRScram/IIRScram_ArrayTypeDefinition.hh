#ifndef IIRSCRAM_ARRAY_TYPE_DEFINITION_HH
#define IIRSCRAM_ARRAY_TYPE_DEFINITION_HH

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
#include "IIRScram_TypeDefinition.hh"
#include "IIRBase_ArrayTypeDefinition.hh"
#include "set.hh"

class IIRScram_ArraySubtypeDefinition;
class IIRScram_FunctionDeclaration;
class IIRScram_Name;
class IIRScram_ScalarTypeDefinition;
class IIRScram_TypeDefinition;
class IIRScram_TypeDeclaration;

/** The extension base for array type definitions. */
class IIRScram_ArrayTypeDefinition : public virtual IIRScram_TypeDefinition, public virtual IIRBase_ArrayTypeDefinition{
  friend class StandardPackage;

public:
  IIRScram_ArrayTypeDefinition();
  virtual ~IIRScram_ArrayTypeDefinition();
  
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  
  IIR_Boolean _is_iir_array_type_definition() { return TRUE; }
  IIR_Int32 get_num_indexes();

  IIRScram_TypeDefinition *_get_element_subtype();

  /** Due to the complexities of the IIR, sometimes
      _get_element_subtype() doesn't actually return the element
      subtype.  This is the case for multidimensional arrays, for
      instance.  _get_final_subtype() _will_ return the _real_ element
      subtype. */
  virtual IIRScram_TypeDefinition *_get_final_subtype();

  virtual IIRScram_ScalarTypeDefinition *_get_index_subtype();

  /** This method takes the range passed in, applies the semantic rules
      given in LRM ('93) section 3.2.1.1, and returns the proper type. */
  static IIRScram_ScalarTypeDefinition *_build_proper_index( IIRScram_RangeTypeDefinition *);

  IIRScram_TypeDefinition *_index_constrain_array( IIRScram_ScalarTypeDefinition *);

  IIRScram_TypeDefinition *_get_new_subtype();

  IIRScram_TypeDefinition *
  _construct_new_subtype( IIRScram_Name                 *resolution_function,
			  IIRScram_ScalarTypeDefinition *new_constraint);  

  static IIRScram_ArrayTypeDefinition *_construct_array_type( IIRScram_ScalarTypeDefinition     *index_subtype,
                                                              IIRScram_TypeDefinition           *element_subtype,
                                                              IIRScram_TypeDeclaration          *declaration);

  IIRScram *_clone();
  virtual void _clone( IIRScram *my_clone );

  virtual void _type_check();

  static IIRScram_ArraySubtypeDefinition *_construct_constrained(IIRScram_ScalarTypeDefinition  *index_subtype,
                                                                 IIRScram_TypeDefinition        *element_subtype,
                                                                 IIRScram_TypeDeclaration       *declaration);

  static IIRScram_ArraySubtypeDefinition *_construct_unconstrained(IIRScram_ScalarTypeDefinition        *index_subtype,
                                                                   IIRScram_TypeDefinition              *element_subtype,
                                                                   IIRScram_TypeDeclaration             *declaration);

  virtual void set_is_element(IIR_Boolean new_element) { IIRBase_ArrayTypeDefinition::set_is_element(new_element); }

  void _come_into_scope( symbol_table *sym_tab, IIRScram_TypeDeclaration * );
  void _come_out_of_scope( symbol_table *sym_tab );
  void _build_implicit_operators( savant::set<IIRScram_Declaration> * );
  
  virtual void _set_resolution_function( IIRScram_FunctionDeclaration * );

private:  
};
#endif
