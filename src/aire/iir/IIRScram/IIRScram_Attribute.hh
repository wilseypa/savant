
#ifndef IIRSCRAM_ATTRIBUTE_HH
#define IIRSCRAM_ATTRIBUTE_HH

// Copyright (c) 1996-2003 The University of Cincinnati.  
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
//          Malolan Chetlur     
//          Krishnan Subramani  
//          Umesh Kumar V. Rajasekaran
//          Timothy J. McBrayer 
//          Swaminathan Subramanian

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Name.hh"
#include "IIRBase_Attribute.hh"

class IIRScram_Attribute;
class IIRScram_BranchQuantityDeclaration;
class IIRScram_ConstantDeclaration;
class IIRScram_Declaration;
class IIRScram_FreeQuantityDeclaration;
class IIRScram_FunctionDeclaration;
class IIRScram_Identifier;
class IIRScram_NatureDefinition;
class IIRScram_RangeTypeDefinition;
class IIRScram_ScalarTypeDefinition;
class IIRScram_SignalDeclaration;
class IIRScram_TextLiteral;
class IIRScram_TypeDeclaration;
class IIRScram_TypeDefinition;

class IIRScram_Attribute : public virtual IIRScram_Name, public virtual IIRBase_Attribute{

public:
  IIRScram_Attribute();
  
  virtual savant::set<IIRScram_Declaration> *_symbol_lookup();
  virtual savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor = 0); 
  virtual IIRScram_TypeDefinition *_get_prefix_subtype(constraint_functor *functor = 0); 
  IIRScram_TypeDefinition *_get_prefix_rval_range_attributes();

  /** High, low, left, and right get_attributes() use these. */
  virtual savant::set<IIRScram_TypeDefinition> *
  _get_rval_set_high_low_left_right(constraint_functor *functor = 0); 
  virtual IIRScram_TypeDefinition *_get_subtype_high_low_left_right();

  virtual void _type_check( savant::set<IIRScram_TypeDefinition> * );
  void set_subtype(IIR_TypeDefinition *type) {IIRBase::set_subtype(type);}

  IIRScram *_decl_to_decl( IIRScram_Declaration * );

  virtual void _set_suffix( IIRScram * );
  virtual IIRScram *_get_suffix( );

  IIRScram *_rval_to_decl( IIRScram_TypeDefinition * );
  /** This method takes a 'range or 'reverse_range attribute, and builds an
      IIRScram_RangeTypeDefinition in the form of prefix'left to
      prefix'right.  */
  virtual IIRScram_RangeTypeDefinition *_build_range_type();

  virtual IIR_Boolean _is_iir_attribute(){ return TRUE; }
  virtual IIR_Boolean _is_attribute(){ return TRUE; }
  virtual IIR_Boolean _is_readable(){ return TRUE; }
  virtual IIR_Boolean _is_range_attribute(){ return FALSE; }
  virtual IIR_Boolean _is_signal_attribute(){ return FALSE; }  
  virtual IIR_Boolean _is_quiet_attribute() { return FALSE; }
  virtual IIR_Boolean _is_stable_attribute() { return FALSE; }
  virtual IIR_Boolean _is_transaction_attribute() { return FALSE; }
  virtual IIR_Boolean _is_event_attribute() { return FALSE; }
  virtual IIR_Boolean _is_active_attribute() { return FALSE; }
  virtual IIR_Boolean _is_lastevent_attribute() { return FALSE; }
  virtual IIR_Boolean _is_lastactive_attribute() { return FALSE; }
  virtual IIR_Boolean _is_lastvalue_attribute() { return FALSE; }
  virtual IIR_Boolean _is_driving_attribute() { return FALSE; }
  virtual IIR_Boolean _is_drivingvalue_attribute() { return FALSE; }
  virtual IIR_Boolean _is_delayed_attribute() { return FALSE; }

  /** If you hit this, an attribute has an unimplemented clone(). */
  virtual IIRScram *_clone();
  virtual void _clone( IIRScram * );

  IIRScram_TextLiteral *_get_attribute_name();
  IIRScram_TextLiteral *_build_attribute_name();

  /** This method does the subtype calculation for IIRScram_Range and
      IIRScram_ReverseRange attributes.  In the case of some error, NULL is
      returned. */
  IIRScram_ScalarTypeDefinition *_get_subtype_range_attribute();

protected:

  virtual void _resolve_suffix_special();
  void _resolve_suffix_base_type_of_prefix();
  void _resolve_suffix_local_static_int();
  void _resolve_suffix_non_negative_time();
  
private:
  void _resolve_prefix();
  void _resolve_suffix();

  virtual IIR_Boolean _need_to_process_prefix_prefix(){ return FALSE; }
};

#endif
