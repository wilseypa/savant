#ifndef IIRBASE_ARRAY_TYPE_DEFINITION_HH
#define IIRBASE_ARRAY_TYPE_DEFINITION_HH

// Copyright (c) 1996-1999 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
// DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.


// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_TypeDefinition.hh"
#include "IIR_ArrayTypeDefinition.hh"

class IIR_ScalarTypeDefinition;
class IIR_TypeDefinition;
template <class type> class set;

class IIRBase_ArrayTypeDefinition : public virtual IIRBase_TypeDefinition,
				    public virtual IIR_ArrayTypeDefinition{
public:
  IIR_Kind get_kind() const {return IIR_ARRAY_TYPE_DEFINITION;}
  const IIR_Char *get_kind_text() const {return "IIR_ArrayTypeDefinition";}

  void set_index_subtype( IIR_ScalarTypeDefinition *index_subtype );
  IIR_Int32 get_num_indexes(); //DRH - Fix plugin hierarchy errors
  IIR_ScalarTypeDefinition *get_index_subtype();
  IIR_ScalarTypeDefinition *get_resolved_index_subtype() { return get_index_subtype(); }
  IIRBase_TypeDefinition *_get_element_subtype();
  void set_element_subtype( IIR_TypeDefinition *element_subtype );
  IIR_TypeDefinition *get_element_subtype();

  /** Due to the complexities of the IIR, sometimes
      _get_element_subtype() doesn't actually return the element
      subtype.  This is the case for multidimensional arrays, for
      instance.  _get_final_subtype() _will_ return the _real_ element
      subtype. */
  IIR_TypeDefinition *get_final_subtype();

  // This method returns TRUE if the element_subtype is REALLY that of the
  // element, or FALSE if it's simply a placeholder for a mutlidimensional array.
  IIR_Boolean is_element();
  void set_is_element( IIR_Boolean );

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_array_type() { return TRUE; }
  IIR_Boolean is_unconstrained_array_type( );
  IIR_Boolean is_discrete_type();

  /** is_character_type() is TRUE for an Enumeration type, that has
      at least one character literal in its set of enumerations.  But
      scram/code-generator overloads this function for single dimensional
      array types whose element is a scalar type and is a character
      type. */
  IIR_Boolean is_character_type();
  IIR_Boolean is_locally_static();

  savant::set<IIR_Declaration> *find_declarations( IIR_Name * );

  ostream &print(ostream &);

  void set_declaration( IIR_Declaration *corresponding_decl );

  
  void publish_vhdl_subtype_decl(ostream &);
  void publish_vhdl_decl(ostream &);
  void publish_vhdl(ostream &);
protected:
  IIRBase_ArrayTypeDefinition();
  virtual ~IIRBase_ArrayTypeDefinition() = 0;
    
private:
  IIR_ScalarTypeDefinition *my_index_subtype;
  IIR_TypeDefinition *my_element_subtype;
  IIR_Boolean my_is_element;
};
#endif
