
#ifndef IIRBASE_ARRAY_NATURE_DEFINITION_HH
#define IIRBASE_ARRAY_NATURE_DEFINITION_HH

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
#include "IIR_TypeDefinition.hh"
#include "IIR_ScalarTypeDefinition.hh"
#include "IIR_ArrayNatureDefinition.hh"
#include "IIRBase_NatureDefinition.hh"
#include "IRBasicDataTypes.hh"

class IIRBase_ArrayNatureDefinition : public virtual IIRBase_NatureDefinition, public virtual IIR_ArrayNatureDefinition {

public:
  IIR_Kind
  get_kind(){
    return IIR_ARRAY_NATURE_DEFINITION;
  }
  
  const IIR_Char *get_kind_text() const { return "IIR_ArrayNatureDefinition"; }
  
  /** Sets the index subtype of the array nature definition */
  void
  set_index_subtype(IIR_ScalarTypeDefinition* index_subtype);
  
  /** Gets the index subtype of the array nature definition */
  IIR_ScalarTypeDefinition* get_index_subtype();
  IIR_ScalarTypeDefinition* get_resolved_index_subtype() { return get_index_subtype(); }
  
  /** Sets the element subtype in the array nature definition */
  void
  set_element_subtype(IIR_TypeDefinition* element_subtype);
  
  /** The Boolean variable is set TRUE if the object is of element type
      i.e. one of subnature_indication type */
  void set_is_element(IIR_Boolean);

  /** Returns true if the calling object is of element type */
  IIR_Boolean is_element();

  IIR *convert_tree(plugin_class_factory *factory);

  /** Used to check if the its an unconstrained array type */
  IIR_Boolean is_unconstrained_array_type();

  /** It is used to identify if the object if of array type */
  IIR_Boolean is_array_type() { return TRUE; }     
  
  /** Gets the element subtype of a given index object */
  IIR_TypeDefinition *get_element_subtype();        
 
  /** Gets the pointer to the final index in a multidimensional array */
  IIR_TypeDefinition *get_final_subtype();

  /** Sets the element subtype of the current index. Used to 
      form a linked list like structure to progressively refer 
      to the consecutive indexes in the array. The final index will 
      refer to the object returned by the subnature_indication  */
  void _set_element_subtype(IIR_NatureDefinition *);        
  void publish_vhdl_decl(ostream &);
  void publish_vhdl(ostream &);
  void publish_vhdl_subtype_decl(ostream &);
protected:
  IIRBase_ArrayNatureDefinition();
  virtual ~IIRBase_ArrayNatureDefinition() = 0;
  
private:
  IIR_ScalarTypeDefinition*     index_subtype;
  IIR_NatureDefinition*         element_subtype;
  IIR_Boolean                   my_is_element;
  
};
#endif
