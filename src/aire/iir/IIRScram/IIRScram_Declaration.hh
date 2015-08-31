
#ifndef IIRSCRAM_DECLARATION_HH
#define IIRSCRAM_DECLARATION_HH

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
#include "IIRBase_Declaration.hh"
#include "IRBasicDataTypes.hh"
#include "savant.hh"

class IIRScram_Attribute;
class IIRScram_AttributeSpecification;
class IIRScram_AttributeSpecificationList;
class IIRScram_DeclarationList;
class IIRScram_DesignatorList;
class IIRScram_GenericList;
class IIRScram_Identifier;
class IIRScram_List;
class IIRScram_PortList;
class IIRScram_Name;
class IIRScram_TypeDefinition;

#define numSignalAttributes 10

class IIRScram_Declaration : public virtual IIRScram, public virtual IIRBase_Declaration{
public:
  IIRScram_Declaration();
  virtual ~IIRScram_Declaration();
  
  IIR_Boolean _is_iir_declaration() { return TRUE; }
  virtual IIR_Boolean _is_overloadable() { return FALSE; }
  virtual IIR_Boolean _is_specification() { return FALSE; }
  virtual IIR_Boolean _is_implicit_operator(){ return FALSE; }
  virtual IIR_Boolean _is_enumeration_literal() { return FALSE; }

  /** This method returns TRUE if this declaration is a homograph of the one
      passed in, and FALSE otherwise. */
  virtual IIR_Boolean _is_homograph_of( IIRScram_Declaration * );
  
  /** There are special circumstances that two declarations that _are_
      homographs can be in the same region.  For instance, a subprogram
      declaration and a subprogram body, or an incomplete type declaration
      and it's complete type.  These are mainly due to implentation issues
      and AIRE specific quirks.  The following method tells us if these two
      homographs can be in the same region or not. */
  virtual IIR_Boolean _can_be_in_same_region( IIRScram_Declaration * ){ return FALSE; }

  virtual IIR_Boolean _is_physical_type();

  virtual IIR_Boolean _designates_incomplete_type(){ return FALSE; }

  virtual IIRScram_PortList *_get_port_list(){ return NULL; }
  virtual IIRScram_GenericList *_get_generic_list(){ return NULL; }
  virtual IIRScram_DesignatorList *_get_instantiation_list();

  //ams additions
  /** This function tells if a quantity is an across-quantity */
  virtual IIR_Boolean _is_across_quantity() { return FALSE; }

  /** This method returns a pointer to a cstringolding the "type" of the
      declaration.  For instance, an entity declaration would return
      "entity", a variable declaration "variable", and so forth. */
  virtual const char *_get_type_string() const { return "(unknown)"; }
  
  IIRScram_Declaration *_find_formal_declaration(){
    return (IIRScram_Declaration *)this;
  }

  void _type_check( savant::set<IIRScram_TypeDefinition> * ){}

  /** This method checks to see if the type of argument "arg_num" matches
      that passed in and returns a boolean. */
  virtual bool _check_param( IIRScram_TypeDefinition *decl, int arg_num );

  /** This seems unnecessary, but it gets called when a symbol has already
      been resolved and something else in the same statement is getting
      resolved.. */
  savant::set<IIRScram_Declaration> *_symbol_lookup();
  savant::set<IIRScram_Declaration> *_symbol_lookup( savant::set<IIRScram_Declaration> * );

  virtual void _get_headers(savant::set<IIRScram>&);

  savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor=0);
  IIRScram *_decl_to_decl( IIRScram_Declaration * );

  virtual IIRScram_TypeDefinition *_get_type_of_param( int );

  /** This returns the dimension of an array type.  It returns "0" if the
      declaration isn't for an array object.. */
  virtual IIR_Int32 get_num_indexes();

  /** This returns how many arguments are required by a subprogram
      declaration.  "0" is returned for non-subprograms. */
  virtual IIR_Int32 _num_required_args();

  virtual IIRScram_TypeDefinition *_get_name_type();
  virtual IIRScram_NatureDefinition *_get_nature(){ return NULL; }
  
  IIRScram *_clone();
  virtual void _clone( IIRScram * );

  /** This method will add the set to this declaration's declarative
      region. */
  virtual void _add_to_declarative_region( savant::set<IIRScram_Declaration> * );
  void _add_to_declarative_region( IIRScram_DeclarationList *, savant::set<IIRScram_Declaration> * );

  /** The following function returns true if the declaration is in the
      process statement's declarative part. */
  IIR_Boolean _in_process_statement();

  /** The following function adds the object and interface declarations
      that appear as initialization objects in declarations. */
  virtual void _add_declarations_in_initializations();

  /** This method adds this declaration, adds it to the symbol table, and
      opens a new scope. */
  void _add_declaration_and_open_scope( );

  /** This method simply adds this declaration to the symbol table. */
  void _add_declaration();
  void _close_scope();
  virtual void _make_interface_visible(symbol_table *sym_tab = NULL );
  
  /** Since we can now have implicit declarations due to attributes, we
      need to be able to tell if THIS declaration is the result of an
      attribute. */
  IIRScram_Attribute *_get_attribute_name();
  
  virtual IIR_Boolean _is_terminal() { return FALSE; }
  virtual IIR_Boolean _is_quantity() { return FALSE; }

  virtual IIR_Boolean   _is_branchQ()  { return FALSE; }

  // Helper functions
  IIRScram              *_get_value();
  IIRScram              *_get_declarative_region();
  
protected:
private:

};
#endif
